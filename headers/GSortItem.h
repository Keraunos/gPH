#pragma once
#include <QGraphicsItemGroup>

class GSort;

class GSortItem : public QGraphicsItemGroup {

    public:
        GSortItem(GSort *sort);
        ~GSortItem();

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        GSort* sort;

};
