#include <iostream>
#include <QMatrix>
#include <QPointF>
#include <QVector>
#include <QColor>
#include <Qt>
#include "GAction.h"


GAction::GAction(ActionPtr a, GVEdge e, GVEdge f, PHScene* sc) : scene(sc), action(a) {

    edges = std::make_pair (e, f);
    display = new QGraphicsItemGroup();

    // Gsort where this action starts
    GSortPtr owner = scene->getGSort(action->getSource()->getSort()->getName());
    QColor color = *(owner->color);

    // arrow tails
    arrowTails.first 	= new QGraphicsPathItem(edges.first.path, display);
    arrowTails.first->setPen(QPen(color));
    arrowTails.second 	= new QGraphicsPathItem(edges.second.path, display);
    arrowTails.second->setPen(QPen(color, 1, Qt::DashLine));

    // arrow heads
    arrowHeads.first 	= makeArrowHead(edges.first, color);
    arrowHeads.second 	= makeArrowHead(edges.second, color);
}


GAction::~GAction() {
    delete display;
    //delete scene; <-- do not delete this pointer, it's owned by a shared pointer in PH.h
}


// draw an arrowhead
QGraphicsPolygonItem* GAction::makeArrowHead(const GVEdge& e, const QColor& color) {

    // arrow pointing to the right
    QPointF p = e.path.pointAtPercent(1);
    QPointF* q = new QPointF(p.x() - 8, p.y() - 5);
    QPointF* r = new QPointF(p.x() - 8, p.y() + 5);
    QPolygonF polygon;
    polygon.push_back(p);
    polygon.push_back(*q);
    polygon.push_back(*r);

    // rotate arrow
    QMatrix matrix;
    matrix.translate(p.x(), p.y());
    matrix.rotate(-e.path.angleAtPercent(1));
    matrix.translate(-p.x(), -p.y());
    polygon = matrix.map(polygon);

    // turn into QGraphicsPolygonItem
    QGraphicsPolygonItem* res = new QGraphicsPolygonItem (polygon, display);
    res->setPen(QPen(color));
    res->setBrush(QBrush(color));
    return res;
}


// getters

QGraphicsItem* GAction::getDisplayItem (void) {
    return display;
}

ActionPtr GAction::getAction() {
    return action;
}

GProcessPtr GAction::getSource() {
    return action->getSource()->getGProcess();
}

GProcessPtr GAction::getTarget() {
    return action->getTarget()->getGProcess();
}

GProcessPtr GAction::getResult() {
    return action->getResult()->getGProcess();
}
