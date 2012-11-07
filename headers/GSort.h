#pragma once
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <list>
#include "PH.h"
#include "Sort.h"
#include "GVCluster.h"
#include "GSortItem.h"

/**
  * @file GSort.h
  * @brief header for the GSort class
  * @author PAPPL_2012
  *
  */

class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;


/**
  * @class GSort
  * @brief contains style and layout info to draw a Sort
  *
  */
class GSort {

	public:

        /**
          * @brief constructor
          *
          * @param SortPtr the related Sort object
          * @param GVCluster the object that contains style and layout info
          */
		GSort(SortPtr p, GVCluster c);

		~GSort();

        /**
          * @brief gets the display
          *
          * @return QGraphicsItem the graphical item representing the Sort
          */
        //QGraphicsItem* getDisplayItem (void);
        GSortItem* getDisplayItem (void);

        QGraphicsRectItem* getRect();
        GVCluster getCluster();

        /**
          * @brief the color used by the Actions that have this Sort as source
          *
          */
		QColor* color;
		
	protected:

        /**
          * @brief the graphical item representing the Sort
          *
          */
        //QGraphicsItem* display;
        GSortItem* display;

        /**
          * @brief the graphical item representing the rectangle of the Sort
          *
          */
		QGraphicsRectItem* rect;

        /**
          * @brief the graphical item representing the text of the Sort
          *
          */
		QGraphicsTextItem* text;

        /**
          * @brief the related Sort
          *
          */
		SortPtr sort;

        /**
          * @brief the related cluster
          *
          */
		GVCluster cluster;		
		
        /**
          * @brief the palette of colors that may be used as color member
          *
          */
        static std::vector<QColor> palette;

        /**
          * @brief palette management index
          *
          */
		static int paletteIndex;

        /**
          * @brief gets a new color in the palette
          *
          * @return QColor* the color retrieved in the palette
          */
		static QColor* makeColor(void);
	
};
