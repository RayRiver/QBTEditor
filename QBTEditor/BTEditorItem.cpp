#include "BTEditorItem.h"

#include <QString>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "BTEditorArrow.h"

BTEditorItem::BTEditorItem(ItemType itemType, QGraphicsItem *parent /*= 0*/ )
    : QGraphicsPolygonItem(parent)
	, m_itemType(itemType)
{
	QPainterPath path;
	switch (itemType) {
	case ItemType::PrioritySelectorNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);
		break;
	case ItemType::NonePrioritySelectorNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);;
		break;
	case ItemType::SequenceNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);
		break;
	case ItemType::LoopNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);
		break;
	case ItemType::ParallelNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);
		break;
	case ItemType::ActionNode:
		m_polygon << QPointF(-100, 0) << QPointF(0, 100)
			<< QPointF(100, 0) << QPointF(0, -100)
			<< QPointF(-100, 0);
		break;
	default:
		Q_ASSERT(false);
		break;
		/*
	case ItemType::StartEnd:
		path.moveTo(200, 50);
		path.arcTo(150, 0, 50, 50, 0, 90);
		path.arcTo(50, 0, 50, 50, 90, 90);
		path.arcTo(50, 50, 50, 50, 180, 90);
		path.arcTo(150, 50, 50, 50, 270, 90);
		path.lineTo(200, 25);
		m_myPolygon = path.toFillPolygon();
		break;
	case ItemType::Conditional:
		m_myPolygon << QPointF(-100, 0) << QPointF(0, 100)
			<< QPointF(100, 0) << QPointF(0, -100)
			<< QPointF(-100, 0);
		break;
	case ItemType::Step:
		m_myPolygon << QPointF(-100, -100) << QPointF(100, -100)
			<< QPointF(100, 100) << QPointF(-100, 100)
			<< QPointF(-100, -100);
		break;
	default:
		m_myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
			<< QPointF(120, 80) << QPointF(70, -80)
			<< QPointF(-120, -80);
		break;
		*/
	}
	setPolygon(m_polygon);
	//const auto &pixmap = QPixmap(":/images/pointer.png");
	//setPixmap(pixmap);

	m_text = new QGraphicsTextItem(this);
	m_text->setPlainText(QObject::tr("ddddddd\ndsafsadfdsaf"));
	auto w = m_text->textWidth();
	m_text->setPos(-w/2, 0);

	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QPixmap BTEditorItem::image() const
{
	/*
	QPixmap pixmap(250, 250);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.setPen(QPen(Qt::black, 8));
	painter.translate(125, 125);
	painter.drawPolyline(m_polygon);
	*/

	QPixmap pixmap;
	switch (m_itemType) {
	case ItemType::PrioritySelectorNode:
		pixmap.load(":/images/pointer.png");
		break;
	case ItemType::NonePrioritySelectorNode:
		pixmap.load(":/images/pointer.png");
		break;
	case ItemType::SequenceNode:
		pixmap.load(":/images/pointer.png");
		break;
	case ItemType::LoopNode:
		pixmap.load(":/images/pointer.png");
		break;
	case ItemType::ParallelNode:
		pixmap.load(":/images/pointer.png");
		break;
	case ItemType::ActionNode:
		pixmap.load(":/images/pointer.png");
		break;
	default:
		Q_ASSERT(false);
		break;
	}

	return pixmap;
}

void BTEditorItem::addArrow( BTEditorArrow *arrow )
{
	m_arrows.append(arrow);
}

void BTEditorItem::removeArrow( BTEditorArrow *arrow )
{
	int index = m_arrows.indexOf(arrow);
	if (index != -1)
	{
		m_arrows.removeAt(index);
	}
}

void BTEditorItem::removeArrows()
{
	foreach (BTEditorArrow *arrow, m_arrows) 
	{
		arrow->getStartItem()->removeArrow(arrow);
		arrow->getEndItem()->removeArrow(arrow);
		scene()->removeItem(arrow);
		delete arrow;
	}
}
