#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <QtCore/QPointF>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsRotation>
#include <QtWidgets/QGraphicsScale>

/**
 * static helping class to aid in manipulating the transform of graphicsitems
 */
class ChartItemTools
{
private:
	ChartItemTools() {};
	~ChartItemTools() {};

public:
	static qreal getRotation(QGraphicsItem* item);
	static void setRotation(QGraphicsItem* item, qreal rotation);
	static void addRotation(QGraphicsItem* item, qreal rotation);
	
	static QPointF getRotationPivot(QGraphicsItem* item);
	static void setRotationPivot(QGraphicsItem* item, QPointF pivot, bool reposition = true);
	static void addRotationPivot(QGraphicsItem* item, QPointF pivot, bool reposition = true);

	static qreal getScaleX(QGraphicsItem* item);
	static void setScaleX(QGraphicsItem* item, qreal scaleX);
	static void addScaleX(QGraphicsItem* item, qreal scaleX);
	
	static qreal getScaleY(QGraphicsItem* item);
	static void setScaleY(QGraphicsItem* item, qreal scaleY);
	static void addScaleY(QGraphicsItem* item, qreal scaleY);
	
	static QPointF getScale(QGraphicsItem* item);

	static QPointF getScalePivot(QGraphicsItem* item);
	static void setScalePivot(QGraphicsItem* item, QPointF pivot, bool reposition = true);
	static void addScalePivot(QGraphicsItem* item, QPointF pivot, bool reposition = true);
	
	/**
	 * recalculates the transform of a graphicsitem to the system used in the chart. 
	 * The visible state of the stitch will stay identical, but the method it is stored with
	 * will be different.
	 */
	static void recalculateTransformations(QGraphicsItem* item);
	
	/**
	 * rotate a point in local coordinates (boundingrect coordinates) with the rotation of the graphicsitem
	 */
	static QPointF mapToRotation(QGraphicsItem* item, QPointF point);
	/**
	 * scale a point in local coordinates (boundingrect coordinates) with the rotation of the graphicsitem
	 */
	static QPointF mapToScale(QGraphicsItem* item, QPointF point);
	/**
	 * rotate and scale a point in local coordinates (boundingrect coordinates) with the data of the item
	 */
	static QPointF mapToRotationAndScale(QGraphicsItem* item, QPointF point);
	
	static QList<QGraphicsTransform*> cloneGraphicsTransformations(QGraphicsItem* item);

	static void initIfNotAlreadyInitialised(QGraphicsItem* item);
	
protected:
	static QGraphicsRotation* getGraphicsRotation(QGraphicsItem* item);
	static QGraphicsScale* getGraphicsScale(QGraphicsItem* item);
	static QList<QGraphicsTransform*> getGraphicsTransformations(QGraphicsItem* item);
};

#endif // CHARTITEM_H
