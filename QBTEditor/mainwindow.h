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
class QTableView;
class QTreeView;
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
	QTableView *createPropertyView();

private slots:
	void onItemInserted(BTEditorItem *item);
	void onItemSelected(QGraphicsItem *item);
	void onButtonGroupClicked(int id);
	void onPointerTypeGroupClicked(int id);
	void onSceneScaleChanged(const QString &scale);
	void onViewDragged(const QPointF &pos, const QPointF &lastPos);
	void onUpdatePropertyView(BTEditorItem *);
	void onSave();
	void onAbout();

private:
	QAction *m_saveAction;
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

	QTableView *m_propertyView;
	QTreeView *m_preconditionView;
};

#endif // MAINWINDOW_H
