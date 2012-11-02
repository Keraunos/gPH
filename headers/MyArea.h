#pragma once

#include <QWidget>
#include <QApplication>
#include <QtGui>
#include "PH.h"

/**
  * @file MyArea.h
  * @brief header for the MyArea class
  * @author PAPPL_2012
  *
  */


/**
  * @class MyArea
  * @brief new tab
    extends QGraphicsView
  *
  */
class MyArea : public QGraphicsView {
    Q_OBJECT

    public:
        //builder

        /**
          * @brief constructor
          * @param QString path of the area
          *
          */
        MyArea(QString path);

        // getter + setter for myPHPtr
        /**
          * @brief gets myPHPtr
          *
          */
        PHPtr getPHPtr();

        /**
          * @brief sets myPHPtr
          *
          */
        void setPHPtr(PHPtr);

        // getter + setter for path

        /**
          * @brief gets path
          *
          */
        QString getPath();

        /**
          * @brief sets path
          *
          */
        void setPath(QString);

    protected:
        /**
          * @brief pointer to a PH object
          *
          */
        PHPtr myPHPtr;

        /**
          * @brief the path to the file
          *
          */
        QString path;

    signals:

    public slots:

};
