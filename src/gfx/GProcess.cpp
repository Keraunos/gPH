#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QSizeF>
#include <QTextDocument>
#include <Qt>
#include "GProcess.h"
#include <math.h>


GProcess::GProcess(ProcessPtr p, GVNode n) : process(p), node(n) {

    display = new QGraphicsItemGroup();

    // ellipse
	ellipse = new QGraphicsEllipseItem (node.centerPos.x() - node.width/2, node.centerPos.y() - node.height/2, node.width, node.height, display);
	ellipse->setPen(QPen(QColor(238,232,213)));
	ellipse->setBrush(QBrush(QColor(238,232,213)));
	
    // TODO refactor margin definition using values in GVSubGraph (dpi ratios, "sep" attribute's value)
    int margin((int) ceil(12.0 * 96.0/72.0));
    marginRect = new QGraphicsRectItem(
                node.centerPos.x() - node.width/2 - margin,
                node.centerPos.y() - node.height/2 - margin,
                node.width + 2*margin,
                node.height + 2*margin,
                display);
    //marginRect->setBrush(QBrush(QColor(255, 0, 0, 100)));
    marginRect->setBrush(Qt::NoBrush);
    marginRect->setPen(Qt::NoPen);
    marginRect->setData(marginZone, true);
    marginRect->setData(11, process->getSort()->getName().c_str());

    // text
    text = new QGraphicsTextItem (QString("%1").arg(process->getNumber()), ellipse);
	text->setDefaultTextColor(QColor(7,54,66));
	text->setPos(node.centerPos.x(), node.centerPos.y());
    // position the text
	QSizeF textSize = text->document()->size();
	text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);
}


GProcess::~GProcess() {
    delete ellipse;
    delete text;
	delete display;
}


// getters

QGraphicsItem* GProcess::getDisplayItem (void) { return display; }

QGraphicsEllipseItem* GProcess::getEllipseItem(){ return ellipse; }

GVNode* GProcess::getNode() { return &(this->node); }


void GProcess::setNodeCoords(int dx, int dy) {
    node.centerPos.setX(node.centerPos.x() + dx);
    node.centerPos.setY(node.centerPos.y() + dy);
}


void GProcess::setNode(GVNode gvnode) {
    this->node = gvnode;
}


#include <QDebug>
bool GProcess::checkCollisions() {

    QList<QGraphicsItem*> collidItems = marginRect->collidingItems();
    foreach (QGraphicsItem *item, collidItems) {
        if (item->data(marginZone).toBool()) {
            if (item->data(11).toString() != process->getSort()->getName().c_str()) {
                qDebug() << "---> collision with a process' margin of sort " << item->data(11).toString();
                return true;
            }
        }
    }

    return false;
}

