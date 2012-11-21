#include <vector>

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QCursor>
#include <QTransform>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QPoint>
#include <QRectF>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsTextItem>
#include <QSizeF>
#include <QTextDocument>
#include <QPainter>
#include <QBitmap>

#include "GSortItem.h"
#include "GSort.h"
#include "Process.h"

// TODO get all this code back into GSort class: GSort can inherit from QGraphicsItem


GSortItem::GSortItem(GSort *_sort) :
    QGraphicsRectItem(_sort->getCluster().topLeft.x(), _sort->getCluster().topLeft.y(), _sort->getCluster().width, _sort->getCluster().height),
    sort(_sort) {

    // rectangle
    rect = new QGraphicsRectItem(boundingRect(), this);
    rect->setPen(QPen(QColor(7,54,66)));
    rect->setBrush(QBrush(QColor(7,54,66)));

    // label
    text = new QGraphicsTextItem (QString(), this);
    text->setHtml(QString::fromStdString("<u>sort " + sort->getSort()->getName() + "</u>"));
    text->setDefaultTextColor(*sort->color);
    text->setPos(sort->getCluster().labelPos.x(), sort->getCluster().labelPos.y());
    QSizeF textSize = text->document()->size();
    text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);

    setCursor(QCursor(Qt::OpenHandCursor));
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

    setFlag(ItemIsMovable);
    //setFlag(ItemIsSelectable);

    // set related GProcesses as children
    vector<ProcessPtr> processes = sort->getSort()->getProcesses();
    for (ProcessPtr &process : processes) {
        process->getGProcess()->getDisplayItem()->setParentItem(this);
    }

}
GSortItem::~GSortItem() {}


//void GSortItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

//    if (event->button() == Qt::RightButton) {
//        event->ignore();
//        return;
//    }

//    setCursor(QCursor(Qt::ClosedHandCursor));

//    qDebug() << "pos x = " << pos().x() << " | pos y = " << pos().y();
//    qDebug() << "x = " << pos().x()+boundingRect().x() << " | y = " << pos().y()+boundingRect().y();
//    qDebug() << "w = " << boundingRect().width() << " | h = " << boundingRect().height();

//    event->accept();
//}


//void GSortItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
//    setCursor(QCursor(Qt::OpenHandCursor));
//    event->accept();
//}


//void GSortItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
//    // TODO update related processes positions
//    // TODO make related actions disappear

//    qDebug() << "ok";
//    event->accept();

////    QRectF sortRect = sort->getRect()->boundingRect();
////    QPoint topLeft(pos().x()+sortRect.x(), pos().y()+sortRect.y());
////    QGraphicsRectItem topLeft(pos().x()+sortRect.x(), pos().y()+sortRect.y(), 4, 4, this);

////    QGraphicsRectItem *topLeft = new QGraphicsRectItem(0, 0, 40, 40);
////    topLeft->setBrush(QBrush(QColor(Qt::yellow)));
////    topLeft->setParentItem(this);

//}


//void GSortItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

//    // start a drag if the mouse has been dragged far enough (no mouse jitter noise)
//    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
//            < QApplication::startDragDistance()) {
//        return;
//    }

//    qDebug() << "mouseMoveEvent";

//    QDrag *drag = new QDrag(event->widget());
//    QMimeData *mime = new QMimeData;
//    drag->setMimeData(mime);

//    mime->setProperty("sort", QString::fromStdString(sort->getSort()->getName()));

//    QPixmap pixmap(sort->getCluster().width, sort->getCluster().height);
//    pixmap.fill(QColor(255, 255, 255, 200));

//    QPainter painter(&pixmap);
//    qDebug() << ">> click: " << event->pos().x();
//    painter.translate(-sort->getCluster().topLeft.x(), -sort->getCluster().topLeft.y());
//    painter.setRenderHint(QPainter::Antialiasing);
//    paint(&painter, 0, 0);
//    painter.end();

//    //pixmap.setMask(pixmap.createHeuristicMask());

//    drag->setPixmap(pixmap);
//    drag->setHotSpot(QPoint(
//                         event->pos().x() - sort->getCluster().topLeft.x(),
//                         event->pos().y() - sort->getCluster().topLeft.y()
//                     ));

//    drag->exec();
//    setCursor(Qt::OpenHandCursor);

//}


//void GSortItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

//    Q_UNUSED(option);
//    Q_UNUSED(widget);

//    GVCluster cluster = sort->getCluster();
//    painter->setPen(QPen(QColor(7,54,66)));
//    painter->setBrush(QBrush(QColor(7,54,66)));
//    painter->drawRect(cluster.topLeft.x(), cluster.topLeft.y(), cluster.width, cluster.height);
//    //painter->drawRect(sort->getRect()->rect());

// }


//void GSortItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

//    // if other mouse buttons are pressed, do nothing
//    if (QApplication::mouseButtons() != Qt::RightButton) {
//        event->ignore();
//        return;
//    }

//    // build context menu
//    QMenu menu;
//    QAction *actionSetColor = menu.addAction("Set color...");
//    menu.addSeparator();
//    QAction *actionProperties = menu.addAction("Properties");

//    //menu.connect(actionSetColor, SIGNAL(triggered()), this, qApp, SLOT(quit()));

//    // manage user click
//    QAction *a = menu.exec(event->screenPos());
//    if (a != NULL) {
//        QString text = a->text();
//        qDebug("User clicked %s", qPrintable(text));
//    }

//}

// getters
QGraphicsRectItem* GSortItem::getRect() { return this->rect; }
QGraphicsTextItem* GSortItem::getText() { return this->text; }




