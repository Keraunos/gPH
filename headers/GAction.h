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
  * @author PAPPL_2012
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
       * @return a QgraphicsItem containing the whole drawing
       */
		QGraphicsItem* getDisplayItem (void);
	
	protected:
	
        /**
          * @brief the PHScene related to the action
          *
          */
		PHScene* scene;

        /**
          * @brief the QGraphicsItem* containing the whole drawing
          *
          */
		QGraphicsItem* display;

        /**
          * @brief the QGraphicsItem* related to the tails of the arrows
          *
          */
		pair<QGraphicsPathItem*, QGraphicsPathItem*> 		arrowTails;

        /**
          * @brief the QGraphicsPolygonItem* related to the heads of the arrows
          *
          */
        pair<QGraphicsPolygonItem* , QGraphicsPolygonItem*>	arrowHeads;

        /**
          * @brief the GVEdge related to the arrows
          *
          */
		pair<GVEdge, GVEdge> edges;

        /**
          * @brief the action object
          *
          */
		ActionPtr action;

        /**
          * @brief builds the head of the arrow as a QGraphicsPolygonItem*
          *
          * @param GVEdge e related to the arrows
          * @param Qcolor color the color of the arrows
          *
          * @return QGraphicsPolygonItem* built from the GVEdge, with the color chosen
          *
          */
		QGraphicsPolygonItem* makeArrowHead(const GVEdge& e, const QColor& color);		
	
};
