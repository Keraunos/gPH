#include <vector>

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QCursor>
#include <QMenu>
#include <QAction>
#include <QGraphicsTextItem>
#include <QTextDocument>
#include <QApplication>

#include "GSortItem.h"
#include "GSort.h"
#include "Process.h"

// TODO get all this code back into GSort class: GSort can inherit from QGraphicsItem


GSortItem::GSortItem(GSort *_sort) :
    QGraphicsRectItem(_sort->getCluster().topLeft.x(), _sort->getCluster().topLeft.y(), _sort->getCluster().width, _sort->getCluster().height),
    sort(_sort) {

    // rectangle
    _rect = new QGraphicsRectItem(boundingRect(), this);
    _rect->setPen(QPen(QColor(7,54,66)));
    _rect->setBrush(QBrush(QColor(7,54,66)));

    // label
    text = new QGraphicsTextItem (QString(), this);
    text->setHtml(QString::fromStdString("<u>sort " + sort->getSort()->getName() + "</u>"));
    text->setDefaultTextColor(*sort->color);
    text->setPos(sort->getCluster().labelPos.x(), sort->getCluster().labelPos.y());
    QSizeF textSize = text->document()->size();
    text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);

    setCursor(QCursor(Qt::OpenHandCursor));
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

    // set related GProcesses as children (so they move with this item)
    vector<ProcessPtr> processes = sort->getSort()->getProcesses();
    for (ProcessPtr &process : processes) {
        process->getGProcess()->getDisplayItem()->setParentItem(this);
    }

}

GSortItem::~GSortItem() {
    delete _rect;
    delete text;
}


// mouse press event handler: start "drag"
void GSortItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    // ignore right click
    if (event->button() == Qt::RightButton) {
        event->ignore();
        return;
    }

    setCursor(QCursor(Qt::ClosedHandCursor));

    // record coordinates for drawing item when mouse is moved/released
    mousePressPoint.setX(pos().x() - event->scenePos().x());
    mousePressPoint.setY(pos().y() - event->scenePos().y());

    event->accept();
}


// mouse move event handler: process "drag"
void GSortItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    // update item position
    setX(mousePressPoint.x() + event->scenePos().x());
    setY(mousePressPoint.y() + event->scenePos().y());

    event->accept();
}


// mouse release event handler: process "drop"
void GSortItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

    setCursor(QCursor(Qt::OpenHandCursor));

    // update item position
    setX(mousePressPoint.x() + event->scenePos().x());
    setY(mousePressPoint.y() + event->scenePos().y());

    event->accept();
}


// context menu event handler
void GSortItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

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

    //menu.connect(actionSetColor, SIGNAL(triggered()), scene(), this->scene(), SLOT(???));

    // TODO create acual context menu

    // manage user click
    QAction *a = menu.exec(event->screenPos());
    if (a != NULL) {
        QString text = a->text();
        qDebug("User clicked %s", qPrintable(text));
    }

}


// getters
QGraphicsRectItem* GSortItem::getRect() { return this->_rect; }
QGraphicsTextItem* GSortItem::getText() { return this->text; }




