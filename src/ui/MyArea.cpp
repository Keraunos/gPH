#include <QPainter>
#include "MyArea.h"


// constructor
MyArea::MyArea(QWidget *parent, QString path) : QGraphicsView(parent) {
    this->path = path;
	setRenderHints (QPainter::Antialiasing);
}

MyArea::MyArea(QString path) : QGraphicsView() {
    this->path = path;
    setRenderHints (QPainter::Antialiasing);
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
        // get the delta of the wheel event and check if control key is pushed
        if(event->delta()>=0 && event->modifiers() == Qt::ControlModifier)
        {
            // if the delta is positive, the action must follow the position of the pointer
            this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            // scale positively
            this->scale(1.2, 1.2);
        }
        else if(event->delta()<0 && event->modifiers() == Qt::ControlModifier)
        {
            // if the delta is negative, the action must follow the center of the view
            this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
            // scale negatively
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
