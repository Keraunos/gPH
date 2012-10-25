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

/**
  * @class PHScene
  * @brief the graphic object representing the process hitting
    extends QGraphicsScene
  *
  */
class PHScene: public QGraphicsScene {
	
	public:
        /**
          * @brief builder for PHScene
          *
          */
        PHScene(PH* _ph);

        /**
          * @brief recalculates the position of the scene
          *
          */
        void doRender(void);

        /**
          * @brief getter for the GSort
          * @param string: the name of the sort needed
          * @return GSortPtr: the sort called
          *
          */
		GSortPtr getGSort (const string& s);
		
	protected:

        /**
          * @brief PH file contained
          *
          */
		PH* ph;

        /**
          * @brief empties the scene and add the elements composing the representation of the process hitting
          *
          */
		void draw(void);

        /**
          * @brief map of the sorts of the scene
          *
          */
		map<string, GSortPtr> sorts;

        /**
          * @brief vector of the processes of the scene
          *
          */
		std::vector<GProcessPtr> processes;

        /**
          * @brief vector of the actions of the scene
          *
          */
		std::vector<GActionPtr> actions;
	
};
