#include <QPainter>
#include "MyArea.h"


// constructor
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


#include "moc_MyArea.cpp"
