#ifndef BTEditorItem_h__
#define BTEditorItem_h__

#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
class QMenu;
class QStandardItemModel;
QT_END_NAMESPACE

class BTEditorArrow;
class BTEditorItem : public QGraphicsPolygonItem
{
public:
	enum { Type = UserType + 15 };
    enum class ItemType 
	{ 
		PrioritySelectorNode, 
		NonePrioritySelectorNode,
		SequenceNode,
		LoopNode,
		ParallelNode,

		ActionNode,


	};

	BTEditorItem(BTEditorItem::ItemType itemType, QGraphicsItem *parent = 0);

	inline ItemType getItemType() { return m_itemType; }

	inline QStandardItemModel *model() { return m_model; }
	QPixmap image() const;
	int type() const { return Type; }

	void addArrow(BTEditorArrow *arrow);
	void removeArrow(BTEditorArrow *arrow);
	void removeArrows();

private:
	QPolygonF m_polygon;
	ItemType m_itemType;

	QList<BTEditorArrow *> m_arrows;

	QGraphicsTextItem *m_text;

	QStandardItemModel *m_model;
};

#endif // BTEditorItem_h__
