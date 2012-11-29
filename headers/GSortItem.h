#pragma once
#include <QGraphicsRectItem>

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
class GSortItem : public QGraphicsRectItem {

    public:

        /**
          * @brief Constructor
          *
          * @param GSort the related graphic sort object
          */
        GSortItem(GSort *sort);

        ~GSortItem();

        /**
          * @brief Handles mouse press event (handles drag start)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse move event (handles drag)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse release event (handles drop)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles context menu event (typically on right click)
          *
          * @param QGraphicsSceneContextMenuEvent the event to be handled
          */
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

        /**
          * @brief gets the rectangle item of the sort
          * @return QGraphicsRectItem* a pointer to the rectangle item
          *
          */
        QGraphicsRectItem* getRect();

        /**
          * @brief gets the label item of the sort
          * @return QGraphicsTextItem* a pointer to the label item
          *
          */
        QGraphicsTextItem* getText();

    private:

        /**
          * @brief the related GSort
          *
          */
        GSort* sort;

        /**
          * @brief the graphical item representing the rectangle of the Sort
          *
          */
        QGraphicsRectItem* _rect;

        /**
          * @brief the graphical item representing the label of the Sort
          *
          */
        QGraphicsTextItem* text;

        /**
          * @brief the point used to record coordinates when user clicks on the item (ie. starts drag&drop)
          *
          */
        QPoint mousePressPoint;

};
