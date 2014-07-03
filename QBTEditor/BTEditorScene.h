#ifndef BTEditorScene_h__
#define BTEditorScene_h__

#include <QGraphicsScene>

#include "BTEditorItem.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class BTEditorItem;
class BTEditorScene : public QGraphicsScene
{
	Q_OBJECT

public:
	enum class Mode
	{
		Drag,
		InsertLine,
		InsertItem,
	};

	explicit BTEditorScene(QObject *parent = 0);

	inline void setMode(Mode mode) { m_mode = mode; }
	inline Mode getMode() { return m_mode; }
	inline void setItemType(BTEditorItem::ItemType type) { m_itemType = type; }
	inline BTEditorItem::ItemType getItemType() { return m_itemType; }

	inline const QColor &getItemColor() { return m_itemColor; }
	inline void setItemColor(const QColor &itemColor) { m_itemColor = itemColor; }

signals:
	void itemInserted(BTEditorItem *item);
	void itemSelected(QGraphicsItem *item);
	void viewDragged(const QPointF &pos, const QPointF &lastPos);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
	Mode m_mode;
	BTEditorItem::ItemType m_itemType;

	QColor m_itemColor;
	QColor m_lineColor;
	QGraphicsLineItem *m_drawingLine;
};

#endif // BTEditorScene_h__
