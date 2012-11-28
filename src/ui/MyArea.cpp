#include <QPainter>
#include "MyArea.h"


// constructor
MyArea::MyArea(QString path) : QGraphicsView() {
    this->path = path;
	setRenderHints (QPainter::Antialiasing);
    setAcceptDrops(true);
}


// get/set myPHPtr
PHPtr MyArea::getPHPtr() {
    return this->myPHPtr;
}
void MyArea::setPHPtr(PHPtr pPHPtr) {
     this->myPHPtr = pPHPtr;
}


// get/set path
QString MyArea::getPath() {
    return this->path;
}
void MyArea::setPath(QString Path) {
     this->path = path;
}

void MyArea::wheelEvent(QWheelEvent *event)
{

        if(event->delta()>=0 && event->modifiers() == Qt::ControlModifier)
        {
            this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            this->scale(1.2, 1.2);
        }
        else if(event->delta()<0 && event->modifiers() == Qt::ControlModifier)
        {
            this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
            this->scale(1 / 1.2, 1 / 1.2);
        }
        else
        {
            QGraphicsView::wheelEvent(event);
        }

}

// method to zoom In
void MyArea::zoomIn()
{
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    this->scale(1.2, 1.2);
}

// method to zoom out
void MyArea::zoomOut()
{
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    this->scale(1 / 1.2, 1 / 1.2);
}


#include "moc_MyArea.cpp"
