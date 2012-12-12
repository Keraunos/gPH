#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QSizeF>
#include <QTextDocument>
#include <Qt>
#include "GProcess.h"


GProcess::GProcess(ProcessPtr p, GVNode n) : process(p), node(n) {

    display = new QGraphicsItemGroup();

    // ellipse
	ellipse = new QGraphicsEllipseItem (node.centerPos.x() - node.width/2, node.centerPos.y() - node.height/2, node.width, node.height, display);
	ellipse->setPen(QPen(QColor(238,232,213)));
	ellipse->setBrush(QBrush(QColor(238,232,213)));
	
    // text
	text = new QGraphicsTextItem (QString("%1").arg(process->getNumber()), display);
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


// getter
QGraphicsItem* GProcess::getDisplayItem (void) {
	return display;
}

QGraphicsEllipseItem* GProcess::getEllipseItem(){
    return ellipse;
}

#include <QDebug>
void GProcess::displayCoords() {
    qDebug() << process->getDotName().c_str() << ": x = " << node.centerPos.x() << " | y = " << node.centerPos.y();
}

void GProcess::setNodeCoords(int dx, int dy) {
    node.centerPos.setX(node.centerPos.x() + dx);
    node.centerPos.setY(node.centerPos.y() + dy);
}

GVNode* GProcess::getNode() { return &(this->node); }

void GProcess::setNode(GVNode gvNode) {

    //qDebug() << "__node " << node.name <<  ": x =" << node.centerPos.x() << " | y=" << node.centerPos.y();
    //qDebug() << "gvNode " << node.name <<  ": x =" << gvNode.centerPos.x() << " | y=" << gvNode.centerPos.y();

    //display->parentItem()->setPos(100, 100);
    //qDebug() << node.name << "ellipse: x =" << ellipse->pos().x() + node.width/2 << " | y=" << ellipse->pos().y() + node.height/2;
    //qDebug() << node.name << "display: x =" << display->pos().x() << " | y=" << display->pos().y();

    //this->node = gvNode;

    //display->setParentItem(NULL);

    //ellipse->setPos(10, 10);
    //ellipse->setPos(node.centerPos.x() - node.width/2, node.centerPos.y() - node.height/2);
    //text->setPos(node.centerPos.x(), node.centerPos.y());
    // position the text
    //QSizeF textSize = text->document()->size();
    //text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);
}
