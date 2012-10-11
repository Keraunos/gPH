#pragma once
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <list>
#include "PH.h"
#include "Sort.h"
#include "GVCluster.h"

class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;

class GSort {

	public:
		GSort(SortPtr p, GVCluster c);
		~GSort();
		QGraphicsItem* getDisplayItem (void);		
		QColor* color;
		
	protected:
		QGraphicsItem* display;
		QGraphicsRectItem* rect;
		QGraphicsTextItem* text;
		SortPtr sort;
		GVCluster cluster;		
		
		static std::vector<QColor> palette; //Drawing colors
		static int paletteIndex;
		static QColor* makeColor(void);
	
};