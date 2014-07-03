#include "mainwindow.h"

#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBox>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>
#include <QIcon>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QComboBox>
#include <QDebug>
/*
#include <QtGui>
*/

#include "BTEditorScene.h"
#include "BTEditorItem.h"

const int InsertTextButton = 10;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	createActions();
	createToolBox();
	createMenus();
	createToolbars();

	m_scene = new BTEditorScene(this);
	m_scene->setSceneRect(QRectF(0, 0, 5000, 5000));
	connect(m_scene, SIGNAL(itemInserted(BTEditorItem *)), this, SLOT(onItemInserted(BTEditorItem *)));
	connect(m_scene, SIGNAL(itemSelected(QGraphicsItem *)), this, SLOT(onItemInserted(QGraphicsItem *)));
	connect(m_scene, SIGNAL(viewDragged(const QPointF &, const QPointF &)), this, SLOT(onViewDragged(const QPointF &, const QPointF &)));

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(m_toolBox);
	m_view = new QGraphicsView(m_scene);
	layout->addWidget(m_view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setWindowTitle(tr("Behavior Tree Editor"));
	setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setShortcuts(QKeySequence::Quit);
	m_exitAction->setStatusTip(tr("Quit Program"));
	connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));

	m_aboutAction = new QAction(tr("A&bout"), this);
	m_aboutAction->setShortcut(tr("CTRL+B"));
	connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(onAbout()));
}

void MainWindow::createToolBox()
{
	m_buttonGroup = new QButtonGroup(this);
	m_buttonGroup->setExclusive(false);
	connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonGroupClicked(int)));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(createCellWidget(tr("Priority Selector"), BTEditorItem::ItemType::PrioritySelectorNode), 0, 0);
	layout->addWidget(createCellWidget(tr("None Priority Selector"), BTEditorItem::ItemType::NonePrioritySelectorNode),0, 1);
	layout->addWidget(createCellWidget(tr("Sequence"), BTEditorItem::ItemType::SequenceNode), 1, 0);
	layout->addWidget(createCellWidget(tr("Loop"), BTEditorItem::ItemType::LoopNode), 1, 1);
	layout->addWidget(createCellWidget(tr("Parallel"), BTEditorItem::ItemType::ParallelNode), 2, 0);
	layout->addWidget(createCellWidget(tr("Action"), BTEditorItem::ItemType::ActionNode), 2, 1);

	layout->setRowStretch(3, 10);
	layout->setColumnStretch(2, 10);

	QWidget *itemWidget = new QWidget;
	itemWidget->setLayout(layout);

	m_toolBox = new QToolBox;
	m_toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
	m_toolBox->setMinimumWidth(itemWidget->sizeHint().width());
	m_toolBox->addItem(itemWidget, tr("Basic Widgets"));
}

void MainWindow::createMenus()
{
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_exitAction);

	m_aboutMenu = menuBar()->addMenu(tr("&Help"));
	m_aboutMenu->addAction(m_aboutAction);
}

void MainWindow::createToolbars()
{
	QToolButton *dragButton = new QToolButton;
	dragButton->setCheckable(true);
	dragButton->setChecked(true);
	dragButton->setIcon(QIcon(":/images/pointer.png"));

	QToolButton *linePointerButton = new QToolButton;
	linePointerButton->setCheckable(true);
	linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

	m_pointerTypeGroup = new QButtonGroup(this);
	m_pointerTypeGroup->addButton(dragButton, int(BTEditorScene::Mode::Drag));
	m_pointerTypeGroup->addButton(linePointerButton, int(BTEditorScene::Mode::InsertLine));
	connect(m_pointerTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(onPointerTypeGroupClicked(int)));

	m_sceneScaleCombo = new QComboBox;
	QStringList scales;
	scales << tr("25%") << tr("50%") << tr("75%") << tr("100%") << tr("150%") << tr("200%");
	m_sceneScaleCombo->addItems(scales);
	m_sceneScaleCombo->setCurrentIndex(3);
	connect(m_sceneScaleCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSceneScaleChanged(QString)));

	m_pointerToolbar = addToolBar(tr("pointer"));
	m_pointerToolbar->addWidget(dragButton);
	m_pointerToolbar->addWidget(linePointerButton);
	m_pointerToolbar->addWidget(m_sceneScaleCombo);
}

void MainWindow::onButtonGroupClicked( int id )
{
	QList<QAbstractButton *> buttons = m_buttonGroup->buttons();
	foreach (QAbstractButton *button, buttons) {
		if (m_buttonGroup->button(id) != button)
			button->setChecked(false);
	}

	m_scene->setItemType(BTEditorItem::ItemType(id));
	m_scene->setMode(BTEditorScene::Mode::InsertItem);
}

void MainWindow::onPointerTypeGroupClicked( int id )
{
	QList<QAbstractButton *> buttons = m_pointerTypeGroup->buttons();
	foreach (QAbstractButton *button, buttons) {
		if (m_pointerTypeGroup->button(id) != button)
			button->setChecked(false);
	}

	m_scene->setMode(BTEditorScene::Mode(m_pointerTypeGroup->checkedId()));
}

void MainWindow::onAbout()
{
	QMessageBox::about(this, tr("about Diagram Scene"),
		tr("The <b>Diagram Scene</b> example shows "
		"use of the graphics framework."));
}

QWidget *MainWindow::createCellWidget( const QString &text, BTEditorItem::ItemType type )
{
	BTEditorItem item(type);
	QIcon icon(item.image());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	m_buttonGroup->addButton(button, int(type));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

void MainWindow::onItemInserted( BTEditorItem *item )
{
	m_pointerTypeGroup->button(int(BTEditorScene::Mode::Drag))->setChecked(true);
	m_scene->setMode(BTEditorScene::Mode(m_pointerTypeGroup->checkedId()));
	m_buttonGroup->button(int(item->getItemType()))->setChecked(false);
}

void MainWindow::onItemSelected( QGraphicsItem *item )
{

}

void MainWindow::onSceneScaleChanged( const QString &scale )
{
	double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
	QMatrix oldMatrix = m_view->matrix();
	m_view->resetMatrix();
	m_view->translate(oldMatrix.dx(), oldMatrix.dy());
	m_view->scale(newScale, newScale);
}

void MainWindow::onViewDragged( const QPointF &pos, const QPointF &lastPos )
{

}

