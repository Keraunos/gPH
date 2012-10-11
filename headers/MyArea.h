#pragma once

#include <QWidget>
#include <QApplication>
#include <QtGui>
#include "PH.h"

class MyArea : public QGraphicsView {
    Q_OBJECT

	public:
        //builder
        MyArea(QString path);

        // getter + setter for myPHPtr
        PHPtr getPHPtr();
		void setPHPtr(PHPtr);

        // getter + setter for path
        QString getPath();
        void setPath(QString);

	protected:
		PHPtr myPHPtr;
        QString path;
		
	signals:
		
	public slots:
    
};
