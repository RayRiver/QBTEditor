#include "BTEditorItem.h"

#include <QString>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QStandardItemModel>
#include <QComboBox>
#include <QDebug>

#include "BTEditorArrow.h"
#include "ComboBoxDelegate.h"

BTEditorItem::BTEditorItem(ItemType itemType, QGraphicsItem *parent /*= 0*/ )
    : QGraphicsPolygonItem(parent)
	, m_itemType(itemType)
{

	m_model = new QStandardItemModel;


	QPainterPath path;
	switch (itemType) {
	case ItemType::PrioritySelectorNode:
		{
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);

		m_model->setRowCount(2);
		m_model->setHeaderData(0, Qt::Vertical, QObject::tr("Item Type"));
		m_model->setHeaderData(1, Qt::Vertical, QObject::tr("Precondition"));
		m_model->setItem(0, 0, new QStandardItem("PrioritySelectorNode"));
		//m_model->setItem(1, 0, new QStandardItem("kkk"));

		QModelIndex index = m_model->index(1, 0, QModelIndex());
		m_model->setData(index, QVariant(ComboBoxDelegate::defaultValue(ComboBoxDelegate::ComboType::Precondition)));

		auto s = m_model->data(index).toString();
		qDebug() << "test: " << s;

		int x= 0;

		}

		break;
	case ItemType::NonePrioritySelectorNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);;

		m_model->setRowCount(1);
		m_model->setHeaderData(0, Qt::Vertical, QObject::tr("Item Type"));
		m_model->setItem(0, 0, new QStandardItem("NonePrioritySelectorNode"));
		break;
	case ItemType::SequenceNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);

		m_model->setRowCount(1);
		m_model->setHeaderData(0, Qt::Vertical, QObject::tr("Item Type"));
		m_model->setItem(0, 0, new QStandardItem("SequenceNode"));
		break;
	case ItemType::LoopNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);

		m_model->setRowCount(1);
		m_model->setHeaderData(0, Qt::Vertical, QObject::tr("Item Type"));
		m_model->setItem(0, 0, new QStandardItem("LoopNode"));
		break;
	case ItemType::ParallelNode:
		m_polygon << QPointF(-100, -60) << QPointF(100, -60)
			<< QPointF(100, 60) << QPointF(-100, 60)
			<< QPointF(-100, -60);

		m_model->setRowCount(1);
		m_model->setHeaderData(0, Qt::Vertical, QObject::tr("Item Type"));
		m_model->setItem(0, 0, new QStandardItem("ParallelNode"));
		break;
	case ItemType::ActionNode:
		m_polygon << QPointF(-100, 0) << QPointF(0, 100)
			<< QPointF(100, 0) << QPointF(0, -100)
			<< QPointF(-100, 0);

		m_model->setRowCount(2);
		m_model->setHeaderData(0, Qt::Vertical, QObject::tr("Item Type"));
		m_model->setHeaderData(1, Qt::Vertical, QObject::tr("implenment"));
		m_model->setItem(0, 0, new QStandardItem("ActionNode"));
		m_model->setItem(1, 0, new QStandardItem("???"));
		break;
	default:
		Q_ASSERT(false);
		break;

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
