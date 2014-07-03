#ifndef BTCANVAS_H
#define BTCANVAS_H

#include <QGraphicsWidget>

class BTCanvas : public QGraphicsWidget
{
	Q_OBJECT

public:
	BTCanvas(QGraphicsWidget *parent = 0);
	~BTCanvas();

};

#endif // BTCANVAS_H
