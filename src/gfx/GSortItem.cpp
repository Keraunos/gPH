#include "GSortItem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QTransform>
#include "GSort.h"

GSortItem::GSortItem(GSort *sort) : QGraphicsItemGroup(), sort(sort) {}

GSortItem::~GSortItem() {}

void GSortItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QCursor *cursor = new QCursor(Qt::ClosedHandCursor);
    sort->getRect()->setCursor(*cursor);
//    // text
//    qDebug() << "x = " << childItems()[1]->x() << " | y = " << childItems()[1]->y();
//    //rect
//    qDebug() << "x = " << sort->getRect()->x() << " | y = " << sort->getRect()->y();
//    // cluster
//    qDebug() << "x = " << sort->getCluster().topLeft.x() << " | y = " << sort->getCluster().topLeft.y();
//    qreal _x = sort->getCluster().topLeft.x();
//    qreal _y = sort->getCluster().topLeft.y();
//    setTransform(QTransform().translate(_x, _y).rotate(90.0).translate(-_x, -_y));
    event->accept();
}

//void GSortItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
//    QCursor *cursor = new QCursor(Qt::OpenHandCursor);
//    sort->getRect()->setCursor(*cursor);
//    event->accept();
//}
