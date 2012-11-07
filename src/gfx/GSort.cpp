#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QTextDocument>
#include <QCursor>
#include "GSort.h"


GSort::GSort(SortPtr s, GVCluster c) : sort(s), cluster(c) {
	
    // graphic items set and Actions color
    //display = new QGraphicsItemGroup();
    display = new GSortItem(this);
    display->setFlag(display->ItemIsMovable, true);

    QCursor *curs = new QCursor(Qt::OpenHandCursor);
    //display->setCursor(*curs);
	color = makeColor();
	
    // rectangle
	rect = new QGraphicsRectItem(cluster.topLeft.x(), cluster.topLeft.y(), cluster.width, cluster.height, display);
	rect->setPen(QPen(QColor(7,54,66)));
	rect->setBrush(QBrush(QColor(7,54,66)));
    rect->setCursor(*curs);

    // label
	text = new QGraphicsTextItem (QString(), display);
	text->setHtml(QString::fromStdString("<u>sort " + sort->getName() + "</u>"));
	text->setDefaultTextColor(*color);
	text->setPos(cluster.labelPos.x(), cluster.labelPos.y());	
	QSizeF textSize = text->document()->size();
	text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);
}


GSort::~GSort() {
	delete rect;
	delete text;
	delete display;
}


// getter
//QGraphicsItem* GSort::getDisplayItem (void) {
GSortItem* GSort::getDisplayItem (void) {
	return display;
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

QGraphicsRectItem* GSort::getRect() {
    return rect;
}

GVCluster GSort::getCluster() {
    return cluster;
}
