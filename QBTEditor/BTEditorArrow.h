#ifndef BTEditorArrow_h__
#define BTEditorArrow_h__

#include <QGraphicsLineItem>

class BTEditorItem;
class BTEditorArrow : public QGraphicsLineItem
{
public:
	enum { Type = UserType + 4 };

	BTEditorArrow(BTEditorItem *startItem, BTEditorItem *endItem, QGraphicsItem *parent = 0);

	int type() const { return Type; }
	inline BTEditorItem *getStartItem() { return m_startItem; }
	inline BTEditorItem *getEndItem() { return m_endItem; }
	inline void setColor(const QColor &color) { m_color = color; }
	inline const QColor &getColor() { return m_color; }

	void updatePosition();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
	BTEditorItem *m_startItem;
	BTEditorItem *m_endItem;
	QColor m_color;
	QPolygonF m_arrowHead;

};

#endif // BTEditorArrow_h__
