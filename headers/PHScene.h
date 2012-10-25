#pragma once
#include <boost/shared_ptr.hpp>
#include <QObject>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"
#include "GProcess.h"
#include "GSort.h"

/**
  * @file PHScene.h
  * @brief header for the PHScene class
  * @author PAPPL_2012
  *
  */

using std::map;
using std::string;

//Mutual inclusion madness
class PH;
class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;
class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;

class PHScene;
typedef boost::shared_ptr<PHScene> PHScenePtr;

typedef std::pair<string, GSortPtr> GSortEntry;

class PHScene: public QGraphicsScene {
	
	public:
		PHScene(PH* _ph);
		void doRender(void);
		GSortPtr getGSort (const string& s);
		
	protected:
		PH* ph;
		void draw(void);
		map<string, GSortPtr> sorts;
		std::vector<GProcessPtr> processes;
		std::vector<GActionPtr> actions;
	
};
