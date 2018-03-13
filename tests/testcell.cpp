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
#include "testcell.h"
#include "../src/stitchlibrary.h"

#include <QtGui/QPainter>
#include <QtCore/QFile>
#include <QtCore/QCryptographicHash>
#include <QtSvg/QSvgGenerator>

void TestCell::initTestCase()
{
    i = 0;

    StitchLibrary::inst()->loadStitchSets();
}

void TestCell::setCellValues()
{
    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);

    Cell* c = new Cell();
    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QVERIFY(c->sceneBoundingRect().width() == width);
    QVERIFY(c->sceneBoundingRect().height() == height);

    delete c;
    c = 0;

}

void TestCell::setCellValues_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0;
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0;
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0;

}

void TestCell::setRotation()
{
    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(qreal, angle);
    QFETCH(QString, rasterHash);

    Cell* c = new Cell();
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    c->setRotation(angle);

    QString rasterImage = "TestCell-SetRotation-" + QString::number(i) + "-" + name + ".png";

    saveSceneSvg(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setRotation_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<qreal>("angle");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << 45.0 << "7a73f68758c6a7c46bc49a8c5505f4c2eaa839c0";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << 45.0 << "03059e40918d8a26dc8c8e6ea276a210088b4e20";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << 45.0 << "ab8b44b8047077ac1bcce9b3387df5ff4c8a1293";

}

void TestCell::setScale()
{

    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(qreal, scale);
    QFETCH(QString, rasterHash);

    Cell* c = new Cell();
    QGraphicsScene *scene = new QGraphicsScene();

    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    c->setScale(scale);

    QString rasterImage = "TestCell-ScaleTest-" + QString::number(i) + "-" + name + ".png";

    saveScene(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setScale_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<qreal>("scale");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << 1.0 << "dbfacd18635fef7df41086eeccdc37447760a0ed";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << 2.5 << "03fdaa34914ab8e27201ce4a8f8baa9a00b92e90";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << 2.5 << "c9ac8ea63a4d48e034c8c5dd582774a7ba18586c";
}

void TestCell::setBgColor()
{

    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(QString, color);
    QFETCH(QString, rasterHash);

    QGraphicsScene *scene = new QGraphicsScene();
    Cell* c = new Cell();
    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    c->setBgColor(QColor(color));

    QString rasterImage = "TestCell-BgColor-" + QString::number(i) + "-" + name + ".png";

    saveScene(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setBgColor_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<QString>("color");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << "#0000FF" << "77ce26028759a0ab5cd4c11ce8283d9176cb62c0";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << "#FF0000" << "9d21520992b236b71915220cd5a1cfbdfa69f459";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << "#00FF00" << "f530d91d6b475fabba6936c7015ebe1ade4efd7a";

}

void TestCell::setAllProperties()
{

    QFETCH(QString, name);
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(qreal, angle);
    QFETCH(qreal, scale);
    QFETCH(QString, color);
    QFETCH(QString, rasterHash);

    QGraphicsScene *scene = new QGraphicsScene();
    Cell* c = new Cell();
    scene->addItem(c);
    i++;

    Stitch* s = StitchLibrary::inst()->findStitch(name);
    c->setStitch(s);

    QPointF origin = QPointF(c->boundingRect().width()/2, c->boundingRect().height());
    c->setTransformOriginPoint(origin);
    c->setBgColor(QColor(color));
    c->setRotation(angle);
    c->setScale(scale);


    QString rasterImage = "TestCell-AllProperties-" + QString::number(i) + "-" + name + ".png";

    saveScene(scene, QSizeF(width, height), rasterImage);

    QString hexHash = hashFile(rasterImage);

    QCOMPARE(hexHash, rasterHash);

    scene->removeItem(c);
    delete c;
    c = 0;
}

void TestCell::setAllProperties_data()
{

    QTest::addColumn<QString>("name");
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<qreal>("angle");
    QTest::addColumn<qreal>("scale");
    QTest::addColumn<QString>("color");
    QTest::addColumn<QString>("rasterHash");

    QTest::newRow("ch")    << "ch" << 32.0 << 16.0 << 45.0 << 1.5 << "#0000FF"
                                    << "b15c52e72bfbc5d5c133a30b7e314a88c780a259";
    QTest::newRow("hdc")   << "hdc" << 32.0 << 64.0 << 45.0 << 1.5 << "#FF0000"
                                    << "3209b56458c2f7473adf43835dd502832cb93635";
    QTest::newRow("dc")    << "dc" << 32.0 << 80.0 << 45.0 << 1.5 << "#00FF00"
                                    << "0095bf007cadd3537b37ff64a11c97449921a874";

}

void TestCell::saveScene(QGraphicsScene* scene, QSizeF size, QString fileName)
{

    scene->setSceneRect(scene->itemsBoundingRect());

    QPixmap pix = QPixmap(scene->sceneRect().width(), scene->sceneRect().height());
    pix.fill(QColor(Qt::white));
    QPainter p;
    p.begin(&pix);
    scene->render(&p);
    p.end();
    pix.save(fileName, "PNG", 100);

}

void TestCell::saveSceneSvg(QGraphicsScene* scene, QSizeF size, QString fileName)
{
    scene->setSceneRect(scene->itemsBoundingRect());

    QPainter p;
    QSvgGenerator gen;
    gen.setFileName(fileName);
    gen.setSize(size.toSize());
    gen.setViewBox(QRectF(0,0,size.width(),size.height()));

    p.begin(&gen);
    scene->render(&p);
    p.end();

}

QString TestCell::hashFile(QString fileName)
{
    QFile f(fileName);

    if(!f.open(QIODevice::ReadOnly)) {
        qFatal("Could not compare png file with expected results");
    }

    QByteArray data = f.readAll();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha1);

    QString hexHash = hash.toHex();
    f.flush();
    f.close();

    return hexHash;
}

void TestCell::cleanupTestCase()
{
}
