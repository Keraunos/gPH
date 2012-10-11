#pragma once
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <list>
#include <utility>
#include "GVEdge.h"
#include "PH.h"
#include "PHScene.h"
#include "Action.h"

class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;
class Action;
typedef boost::shared_ptr<Action> ActionPtr;
class PHScene;

using std::pair;

class GAction {

	public:
		GAction(ActionPtr a, GVEdge e, GVEdge f, PHScene* sc);
		~GAction();
		QGraphicsItem* getDisplayItem (void);
	
	protected:
	
		PHScene* scene;
		QGraphicsItem* display;
		pair<QGraphicsPathItem*, QGraphicsPathItem*> 		arrowTails;
		pair<QGraphicsPolygonItem* , QGraphicsPolygonItem*>	arrowHeads;		
		pair<GVEdge, GVEdge> edges;
		ActionPtr action;
		QGraphicsPolygonItem* makeArrowHead(const GVEdge& e, const QColor& color);		
	
};