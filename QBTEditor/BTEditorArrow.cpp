#include "BTEditorArrow.h"

#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

#include "BTEditorItem.h"

const qreal Pi = 3.14;

BTEditorArrow::BTEditorArrow( BTEditorItem *startItem, BTEditorItem *endItem, QGraphicsItem *parent /*= 0*/ )
	: QGraphicsLineItem(parent)
	, m_startItem(startItem)
	, m_endItem(endItem)
	, m_color(Qt::black)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setPen(QPen(m_color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void BTEditorArrow::updatePosition()
{
	QLineF line(mapFromItem(m_startItem, 0, 0), mapFromItem(m_endItem, 0, 0));
	setLine(line);
}

void BTEditorArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (m_startItem->collidesWithItem(m_endItem))
	{
		return;
	}

	QPen myPen = pen();
	myPen.setColor(m_color);
	qreal arrowSize = 20;
	painter->setPen(myPen);
	painter->setBrush(m_color);

	QLineF centerLine(m_startItem->pos(), m_endItem->pos());
	QPolygonF endPolygon = m_endItem->polygon();
	QPointF p1 = endPolygon.first() + m_endItem->pos();
	QPointF p2;
	QPointF intersectPoint;
	QLineF polyLine;
	for (int i = 1; i < endPolygon.count(); ++i) {
		p2 = endPolygon.at(i) + m_endItem->pos();
		polyLine = QLineF(p1, p2);
		QLineF::IntersectType intersectType =
			polyLine.intersect(centerLine, &intersectPoint);
		if (intersectType == QLineF::BoundedIntersection)
			break;
		p1 = p2;
	}

	setLine(QLineF(intersectPoint, m_startItem->pos()));

	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (Pi * 2) - angle;

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
		cos(angle + Pi / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
		cos(angle + Pi - Pi / 3) * arrowSize);

	m_arrowHead.clear();
	m_arrowHead << line().p1() << arrowP1 << arrowP2;

	painter->drawLine(line());
	painter->drawPolygon(m_arrowHead);
	if (isSelected()) {
		painter->setPen(QPen(m_color, 1, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0,-8.0);
		painter->drawLine(myLine);
	}
}
