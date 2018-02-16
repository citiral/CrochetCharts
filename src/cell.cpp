/****************************************************************************\
 Copyright (c) 2010-2014 Stitch Works Software
 Brian C. Milco <bcmilco@gmail.com>

 This file is part of Crochet Charts.

 Crochet Charts is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Crochet Charts is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Crochet Charts. If not, see <http://www.gnu.org/licenses/>.

 \****************************************************************************/
#include "cell.h"

#include <QtCore/QDebug>
#include <QtGui/qpainter.h>
#include <QtSvg/qsvgrenderer.h>
#include "stitchlibrary.h"
#include "stitchset.h"
#include "settings.h"
#include "ChartItemTools.h"
#include <QtWidgets/QStyleOption>
#include <QtCore/QEvent>

#include <QtWidgets/QGraphicsScene>

Cell::Cell(QGraphicsItem *parent)
    : QGraphicsSvgItem(parent),
	mLayer(0),
    mStitch(0),
    mHighlight(false)
{

    setCachingEnabled(false);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    //if we don't set the bgColor it'll end up black.
    setBgColor();
}

Cell::~Cell()
{
}

QRectF Cell::boundingRect() const
{
    if(!stitch())
        return QRectF(0,0,32,32);

    if(stitch()->isSvg()) {
		QRectF r = QGraphicsSvgItem::boundingRect();
        return r;
    } else
        return stitch()->renderPixmap()->rect();
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!stitch())
        return;

    QColor clr = bgColor();
    if(!clr.isValid())
        clr = QColor(Qt::white);

    if(clr != Qt::white)
        painter->fillRect(option->rect, clr);
    if(mHighlight)
        painter->fillRect(option->rect, option->palette.highlight());

    if(stitch()->isSvg()) {
        QGraphicsSvgItem::paint(painter, option, widget);
    } else {
        painter->drawPixmap(option->rect.x(), option->rect.y(), *(stitch()->renderPixmap()));

         if(option->state & QStyle::State_Selected) {
            painter->setPen(Qt::DashLine);
            painter->drawRect(option->rect);
            painter->setPen(Qt::SolidLine);
        }
    }
}

bool Cell::event(QEvent *e)
{
    //Pass the mouse control back to the scene,
    //allowing for changing stitches by click.
    int selectedItems = 1;

    if(scene()) {
        selectedItems = scene()->selectedItems().count();
    }

    if(isSelected() && selectedItems == 1
		&& Settings::inst()->value("replaceStitchWithPress").toBool() == true) {
        e->setAccepted(false);
        return false;
    }

    return QGraphicsSvgItem::event(e);
}

bool Cell::isGrouped()
{

    if(parentItem()) {
        qDebug() << "isGrouped parent type:" << parentItem()->Type;
        return true;
    }

    return false;
}

void Cell::setStitch(Stitch *s)
{

    if (mStitch != s) {
        QString old;
        bool doUpdate = false;
        
        if (mStitch) {
            old = mStitch->name();
            doUpdate = (mStitch->isSvg() != s->isSvg());
        }
        mStitch = s;
        if(s->isSvg()) {
            setSharedRenderer(s->renderSvg(mColor));
        }

        if(doUpdate)
            update();
        
        emit stitchChanged(old, s->name());
    }
    
    setTransformOriginPoint(s->width()/2, s->height());
}

void Cell::setBgColor(QColor c)
{
    if (mBgColor != c) {
        QString old = "";
        if (mBgColor.isValid())
            old = mBgColor.name();
        mBgColor = c;
        emit colorChanged(old, c.name());
        update();
    }
}

void Cell::setColor(QColor c)
{

    if(mColor != c) {
        QString old = "";
        if(mColor.isValid())
            old = mColor.name();
        mColor = c;

        QSvgRenderer *r = stitch()->renderSvg(c);
        if(r)
            setSharedRenderer(r);

        emit colorChanged(old, c.name());
        update();
    }

}

void Cell::setStitch(QString s)
{
    Stitch *stitch = StitchLibrary::inst()->findStitch(s);

    if (!stitch) {
        QString st = Settings::inst()->value("defaultStitch").toString();
        stitch = StitchLibrary::inst()->findStitch(st);
    }

    setStitch(stitch);
}

QString Cell::name()
{
    if(mStitch)
        return mStitch->name();
    else
        return QString();
}

void Cell::useAlternateRenderer(bool useAlt)
{
    if(mStitch->isSvg() && mStitch->renderSvg()->isValid()) {
        QString primary = Settings::inst()->value("stitchPrimaryColor").toString();
        QString secondary = Settings::inst()->value("stitchAlternateColor").toString();
        QString color;

        //only use the primary and secondary colors if the stitch is using the default colors.
        if(useAlt && mColor == primary) {
            color = secondary;
        } else if(!useAlt && mColor == secondary) {
            color = primary;
        } else {
            color = mColor.name();
        }

        mColor = QColor(color);
        setSharedRenderer(mStitch->renderSvg(mColor.name()));
    }
}

Cell* Cell::copy(Cell *cell)
{
    Cell *c = 0;
    if(!cell)
        c = new Cell();
    else
        c = cell;

    c->setStitch(stitch());
    c->setBgColor(bgColor());
    c->setColor(c->color());
    c->setTransformOriginPoint(transformOriginPoint());
    c->setRotation(0);
    c->setTransform(QTransform());
	c->setTransformations(ChartItemTools::cloneGraphicsTransformations(this));
	foreach (QGraphicsTransform* t, transformations())
		t->setParent(parentObject());

    return c;
}
