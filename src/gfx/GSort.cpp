#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QTextDocument>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>
#include <QApplication>
#include <QMenu>
#include "GSort.h"
#include "Process.h"

GSort::GSort(SortPtr s, GVCluster c) :
    QGraphicsRectItem(c.topLeft.x(), c.topLeft.y(), c.width, c.height),
    sort(s), cluster(c) {
	
    qDebug() << "GVCluster " << s->getName().c_str() << " x = " << c.topLeft.x() <<
                " | y = " << c.topLeft.y();

    // graphic items set and Actions color
    color = makeColor();

    // rectangle
    _rect = new QGraphicsRectItem(boundingRect(), this);
    _rect->setPen(QPen(QColor(7,54,66)));
    _rect->setBrush(QBrush(QColor(7,54,66)));

    // label
    text = new QGraphicsTextItem (QString(), this);
    text->setHtml(QString::fromStdString("<u>sort " + sort->getName() + "</u>"));
    text->setDefaultTextColor(*color);
    text->setPos(cluster.labelPos.x(), cluster.labelPos.y());
    QSizeF textSize = text->document()->size();
    text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);

    setCursor(QCursor(Qt::OpenHandCursor));
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

    // set related GProcesses as children (so they move with this GSort)
    vector<ProcessPtr> processes = sort->getProcesses();
    for (ProcessPtr &process : processes) {
        process->getGProcess()->getDisplayItem()->setParentItem(this);
    }
}


GSort::~GSort() {
    delete _rect;
    delete text;
}


// mouse press event handler: start "drag"
void GSort::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    // ignore right click
    if (event->button() == Qt::RightButton) {
        event->ignore();
        return;
    }

    setCursor(QCursor(Qt::ClosedHandCursor));

    dynamic_cast<PHScene*>(scene())->hideActions();

    // record coordinates for drawing item when mouse is moved/released
    initPosPoint.setX(pos().x());
    initPosPoint.setY(pos().y());
    eventPressPoint.setX(event->scenePos().x());
    eventPressPoint.setY(event->scenePos().y());

    event->accept();
}


// mouse move event handler: process "drag"
void GSort::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    // update item position
    setX(initPosPoint.x() + event->scenePos().x() - eventPressPoint.x());
    setY(initPosPoint.y() + event->scenePos().y() - eventPressPoint.y());

    event->accept();
}


// mouse release event handler: process "drop"
void GSort::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

    setCursor(QCursor(Qt::OpenHandCursor));

    // update item position
    setX(initPosPoint.x() + event->scenePos().x() - eventPressPoint.x());
    setY(initPosPoint.y() + event->scenePos().y() - eventPressPoint.y());

    // update cluster position
    cluster.topLeft.setX(boundingRect().x() + pos().x());
    cluster.topLeft.setY(boundingRect().y() + pos().y());
    qDebug() << cluster.name << cluster.topLeft.x();
    qDebug() << cluster.name << cluster.topLeft.y();

    vector<ProcessPtr> processes = sort->getProcesses();
    for (ProcessPtr &process : processes) {
        process->getGProcess()->setNodeCoords(
                    pos().x() - initPosPoint.x(),
                    pos().y() - initPosPoint.y());
        process->getGProcess()->displayCoords();
    }

    dynamic_cast<PHScene*>(scene())->updateGraph();

    event->accept();
}


// context menu event handler
void GSort::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

    // if other mouse buttons are pressed, do nothing
    if (QApplication::mouseButtons() != Qt::RightButton) {
        event->ignore();
        return;
    }

    // build context menu
    QMenu menu;
    QAction *actionSetColor = menu.addAction("Set color...");
    menu.addSeparator();
    QAction *actionProperties = menu.addAction("Properties");

    // TODO create acual context menu

    // manage user click
    QAction *a = menu.exec(event->screenPos());
    if (a != NULL) {
        QString text = a->text();
        qDebug("User clicked %s", qPrintable(text));
    }

}


// palette management

int GSort::paletteIndex = 0;

// TODO see QPalette class?
std::vector<QColor> GSort::palette = 	{	QColor(181,137,0)
										, 	QColor(220,50,47)
										, 	QColor(211,54,130)
										, 	QColor(108,113,196)
										, 	QColor(38,139,210)
										, 	QColor(42,161,152)
										, 	QColor(133,153,0)
										};

QColor* GSort::makeColor () {
	paletteIndex = (paletteIndex + 1) % palette.size();
	return &(palette[paletteIndex]);
}


// getters

QGraphicsRectItem* GSort::getRect() { return this->_rect; }

SortPtr GSort::getSort() { return this->sort; }

GVCluster GSort::getCluster() { return this->cluster; }

