/****************************************************************************\
 Copyright (c) 2011-2014 Stitch Works Software
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
#ifndef CROCHETTAB_H
#define CROCHETTAB_H

#include <QtWidgets/QWidget>
#include <QtCore/QMap>

#include "chartview.h"
#include <QtCore/QPointer>

#include "scene.h"

#include "roweditdialog.h"

class QGraphicsView;
class TextView;
class QUndoStack;

namespace Ui {
    class OptionsBar;
}

class CrochetTab : public QWidget
{
    Q_OBJECT
    friend class FileFactory;
    friend class File_v1;
    friend class File_v2;
    friend class ExportUi;
	friend class ResizeUI;
    friend class PropertiesDock;
public:

    explicit CrochetTab(Scene::ChartStyle style, int defEditMode, QString defStitch, QColor defFgColor, QColor defBgColor, QWidget* parent = 0);
    ~CrochetTab();
	
    void renderChart(QPainter* painter, QRectF rect = QRectF());
	void renderChartSelected(QPainter* painter, QRectF rect = QRectF());

    void setPatternStitches(QMap<QString, int>* stitches) { mPatternStitches = stitches; }
    void setPatternColors(QMap<QString, QMap<QString, qint64> >* colors) { mPatternColors = colors; }

    //list of modes available from this tab.
    QStringList editModes();

    void setEditMode(int mode);
    int editMode() const;
	
	void setSelectMode(Scene::SelectMode mode);
	Scene::SelectMode selectMode() const;

    void setEditFgColor(QColor color);
    void setEditBgColor(QColor color);

    void setEditStitch(QString stitch);

    void sceneUpdate();

    void updateRows();

    void alignSelection(int alignmentStyle);
    void distributeSelection(int distributionStyle);
    void arrangeGrid(QSize grid, QSize alignment, QSize spacing, bool useSelection);

	void addLayer(const QString& layer);
	void addLayer(const QString& layer, unsigned int uid);
	void removeSelectedLayer();
	void mergeLayer(unsigned int from, unsigned int to);
	void selectLayer(unsigned int uid);
	void editedLayer(ChartLayer* layer);

    void copy(int direction);
    void mirror(int direction);
    void rotate(qreal degrees);
	void resizeScene(QRectF rectangle);
    void copy();
    void cut();
    void paste();
	void insertImage(const QString& filename, QPointF pos = QPointF(0, 0));

    void group();
    void ungroup();

    bool hasChartCenter();
    void setChartCenter(bool state);

    void setGuidelinesType(QString guides);
    bool hasGuidelines();
    
    void propertiesUpdate(QString property, QVariant newValue);

    void updateDefaultStitchColor(QColor originalColor, QColor newColor);

    QList<QGraphicsItem*> selectedItems();

signals:
	void layersChanged(QList<ChartLayer*>& layers, ChartLayer* selected);
    void chartStitchChanged();
    void chartColorChanged();
    void tabModified(bool state);
    
    void guidelinesUpdated(Guidelines guidelines);
public:
    void updateGuidelines(Guidelines guidelines) {
        emit guidelinesUpdated(guidelines);
    }

public slots:
    void zoomIn();
    void zoomOut();

    void stitchChanged(QString oldSt, QString newSt);
    void colorChanged(QString oldColor, QString newColor);
	void layersChangedSlot(QList<ChartLayer*>& layers, ChartLayer* selected);

    QUndoStack* undoStack();

    void createChart(Scene::ChartStyle style, int rows, int cols, QString defStitch, QSizeF rowSize, int increaseBy);

    void copyInstructions();

    /**
     *Clear any selections of objects on the chart.
     */
    void clearSelection();

    void showRowEditor(bool state);

    void replaceStitches(QString original, QString replacement);
    void replaceColor(QColor original, QColor replacement, int selection);
    
protected:
    QMap<QString, int>* patternStitches() { return mPatternStitches; }
    
private slots:
    void zoomChanged(int value);
    void updateZoomLevel(int percent);

    void setShowChartCenter(bool state);
    
public:
    Scene* scene() { return mScene; }
    ChartView* view() { return mView; }
    
private:    
    QPointer<ChartView> mView;
    Scene* mScene;
    TextView* mTextView;

    QMap<QString, int>* mPatternStitches;
    QMap<QString, QMap<QString, qint64> >* mPatternColors;
    
    QString mName;

    Ui::OptionsBar* ui;
    RowEditDialog* mRowEditDialog;
    

    Scene::ChartStyle mChartStyle;
};

#endif // CROCHETTAB_H
