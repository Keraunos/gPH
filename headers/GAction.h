#pragma once
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <list>
#include <utility>
#include "GVEdge.h"
#include "PH.h"
#include "PHScene.h"
#include "Action.h"

/**
  * @file GAction.h
  * @brief header for the GAction class
  * @author PAPPL 2012
  *
  */

class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;
class Action;
typedef boost::shared_ptr<Action> ActionPtr;
class PHScene;

using std::pair;


/**
  * @class Gaction
  * @brief determines the way to draw an action
  *
  */
class GAction {

	public:

    /**
      * @brief constructor for Gaction
      *
      */
		GAction(ActionPtr a, GVEdge e, GVEdge f, PHScene* sc);
        ~GAction();

     /**
       * @brief contains the whole drawing of the action
       *
       */
		QGraphicsItem* getDisplayItem (void);
	
	protected:
	
        /**
          * @brief
          *
          */
		PHScene* scene;

        /**
          * @brief
          *
          */
		QGraphicsItem* display;
		pair<QGraphicsPathItem*, QGraphicsPathItem*> 		arrowTails;
		pair<QGraphicsPolygonItem* , QGraphicsPolygonItem*>	arrowHeads;		
		pair<GVEdge, GVEdge> edges;
		ActionPtr action;
		QGraphicsPolygonItem* makeArrowHead(const GVEdge& e, const QColor& color);		
	
};
