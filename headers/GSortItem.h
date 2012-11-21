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
          * @brief Handles mouse press event
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        //void mousePressEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse release event
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse move event
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles drag move event
          *
          * @param QGraphicsSceneDragDropEvent the event to be handled
          */
        //void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
        //void dragMoveEvent(QGraphicsSceneDragDropEvent *event);


        /**
          * @brief Handles context menu event (typically: right click)
          *
          * @param QGraphicsSceneContextMenuEvent the event to be handled
          */
        //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

        /**
          * @brief Paints the item
          *
          */
        //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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
        QGraphicsRectItem* rect;

        /**
          * @brief the graphical item representing the label of the Sort
          *
          */
        QGraphicsTextItem* text;

};
