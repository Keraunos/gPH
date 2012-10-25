#pragma once
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <list>
#include "PH.h"
#include "Sort.h"
#include "GVCluster.h"

/**
  * @file GSort.h
  * @brief header for the GSort class
  * @author PAPPL_2012
  *
  */

class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;


/**
  * @class Gsort
  * @brief determines the way to draw a sort
  *
  */
class GSort {

	public:

        /**
          * @brief constructor for GSort
          *
          */
		GSort(SortPtr p, GVCluster c);
		~GSort();

        /**
          * @brief contains the whole drawing of the sort
          *
          */
        QGraphicsItem* getDisplayItem (void);

        /**
          * @brief determines the palette of colours used by the action coming from this sort
          *
          */
		QColor* color;
		
	protected:

        /**
          * @brief contains the whole drawing of the sort
          *
          */
		QGraphicsItem* display;

        /**
          * @brief graphical element to draw the sort: rectangle
          *
          */
		QGraphicsRectItem* rect;

        /**
          * @brief graphical element to draw the sort: text
          *
          */
		QGraphicsTextItem* text;

        /**
          * @brief sort related
          *
          */
		SortPtr sort;

        /**
          * @brief cluster related
          *
          */
		GVCluster cluster;		
		
        /**
          * @brief determines the colours
          *
          */
        static std::vector<QColor> palette;

        /**
          * @brief palette management index
          *
          */
		static int paletteIndex;

        /**
          * @brief returns the colour relative to the index
          *
          */
		static QColor* makeColor(void);
	
};
