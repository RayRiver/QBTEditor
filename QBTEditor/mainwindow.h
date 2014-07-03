#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "BTEditorItem.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
class QToolBox;
class QToolBar;
class QButtonGroup;
class QGraphicsView;
class QComboBox;
QT_END_NAMESPACE

class BTEditorScene;
class BTEditorItem;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void createActions();
	void createToolBox();
	void createMenus();
	void createToolbars();

	QWidget *createCellWidget(const QString &text, BTEditorItem::ItemType type);

private slots:
	void onItemInserted(BTEditorItem *item);
	void onItemSelected(QGraphicsItem *item);
	void onButtonGroupClicked(int id);
	void onPointerTypeGroupClicked(int id);
	void onSceneScaleChanged(const QString &scale);
	void onViewDragged(const QPointF &pos, const QPointF &lastPos);
	void onAbout();

private:
	QAction *m_exitAction;
	QAction *m_aboutAction;

	QToolBox *m_toolBox;
	QButtonGroup *m_buttonGroup;
	QButtonGroup *m_pointerTypeGroup;

	QMenu *m_fileMenu;
	QMenu *m_aboutMenu;

	QToolBar *m_pointerToolbar;

	BTEditorScene *m_scene;
	QGraphicsView *m_view;

	QComboBox *m_sceneScaleCombo;
};

#endif // MAINWINDOW_H
