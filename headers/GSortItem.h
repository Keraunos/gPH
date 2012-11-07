#pragma once
#include <QGraphicsItemGroup>

/**
  * @file GSortItem.h
  * @brief GSortItem class header file
  * @author PGROU_2012
  *
  */

class GSort;


/**
  * @class GSortItem
  * @brief graphic item representing a Sort
  *
  */
class GSortItem : public QGraphicsItemGroup {

    public:

        /**
          * @brief Constructor
          *
          * @param GSort the related graphic sort object
          */
        GSortItem(GSort *sort);

        ~GSortItem();

        /**
          * @brief Handles mouse press event
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse release event
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    private:
        GSort* sort;

};
