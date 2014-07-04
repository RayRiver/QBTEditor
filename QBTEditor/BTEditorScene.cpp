#include "BTEditorScene.h"

#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QFile>

#include "BTEditorItem.h"
#include "BTEditorArrow.h"

BTEditorScene::BTEditorScene( QObject *parent /*= 0*/ )
	: QGraphicsScene(parent)
{
	m_mode = Mode::Drag;

	m_itemColor = Qt::white;
	m_lineColor = Qt::black;
	m_drawingLine = nullptr;
}

void BTEditorScene::mousePressEvent( QGraphicsSceneMouseEvent *mouseEvent )
{
	if (mouseEvent->button() != Qt::LeftButton)
	{
		return;
	}

	BTEditorItem *item = nullptr;
	switch (m_mode)
	{
	case Mode::Drag:
		break;
	case Mode::InsertItem:
		item = new BTEditorItem(m_itemType);
		item->setBrush(m_itemColor);
		this->addItem(item);
		item->setPos(mouseEvent->scenePos());
		emit itemInserted(item);
		break;
	case Mode::InsertLine:
		m_drawingLine = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
			mouseEvent->scenePos()));
		m_drawingLine->setPen(QPen(m_lineColor, 2));
		addItem(m_drawingLine);
		break;
	default:
		break;
	}

	QGraphicsScene::mousePressEvent(mouseEvent);
}

void BTEditorScene::mouseMoveEvent( QGraphicsSceneMouseEvent *mouseEvent )
{
	switch (m_mode)
	{
	case Mode::Drag:
		{
			/*
			const QPointF &lastPos = mouseEvent->lastScenePos();
			const QPointF &pos = mouseEvent->scenePos();
			emit viewDragged(pos, lastPos);
			*/
			const QList<QGraphicsItem *> &selectedItems = this->selectedItems();
			for (int i=0; i<selectedItems.count(); ++i)
			{
				auto item = dynamic_cast<BTEditorItem *>(selectedItems.at(i));
				emit updatePropertyView(item);
				break;
			}

			QGraphicsScene::mouseMoveEvent(mouseEvent);
		}
		break;
	case Mode::InsertItem:
		break;
	case Mode::InsertLine:
		if (m_drawingLine)
		{
			QLineF newLine(m_drawingLine->line().p1(), mouseEvent->scenePos());
			m_drawingLine->setLine(newLine);
		}
		break;
	default:
		break;
	}

}

void BTEditorScene::mouseReleaseEvent( QGraphicsSceneMouseEvent *mouseEvent )
{
	switch (m_mode)
	{
	case Mode::Drag:
		break;
	case Mode::InsertItem:
		break;
	case Mode::InsertLine:
		if (m_drawingLine)
		{
			QList<QGraphicsItem *> startItems = items(m_drawingLine->line().p1());
			if (startItems.count() && startItems.first() == m_drawingLine)
			{
				startItems.removeFirst();
			}
			QList<QGraphicsItem *> endItems = items(m_drawingLine->line().p2());
			if (endItems.count() && endItems.first() == m_drawingLine)
			{
				endItems.removeFirst();
			}

			removeItem(m_drawingLine);
			m_drawingLine = nullptr;

			if (startItems.count() > 0 && endItems.count() > 0 &&
				startItems.first()->type() == BTEditorItem::Type &&
				endItems.first()->type() == BTEditorItem::Type &&
				startItems.first() != endItems.first()) 
			{
				BTEditorItem *startItem = qgraphicsitem_cast<BTEditorItem *>(startItems.first());
				BTEditorItem *endItem = qgraphicsitem_cast<BTEditorItem *>(endItems.first());

				BTEditorArrow *arrow = new BTEditorArrow(startItem, endItem);
				arrow->setColor(m_lineColor);
				startItem->addArrow(arrow);
				endItem->addArrow(arrow);
				arrow->setZValue(-1000.0);
				addItem(arrow);
				arrow->updatePosition();
			}
		}
		break;
	default:
		break;
	}

	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void BTEditorScene::exportFile( const QString &filename )
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Q_ASSERT(false);
		return;
	}

	file.write("json");
}

