#pragma once
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <list>
#include "PH.h"
#include "Process.h"
#include "GVNode.h"

/**
  * @file GProcess.h
  * @brief header for the GProcess class
  * @author PAPPL_2012
  *
  */

class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class Process;
typedef boost::shared_ptr<Process> ProcessPtr;


/**
  * @class GProcess
  * @brief contains style and layout info to draw a process
  *
  */
class GProcess {

	public:

        /**
          * @brief constructor
          *
          * @param ProcessPtr the related Process object
          * @param GVNode the object that contains style and layout info
          */
		GProcess(ProcessPtr p, GVNode n);

		~GProcess();

        /**
          * @brief gets the display
          *
          * @return QGraphicsItem the graphical item representing the Process
          */
		QGraphicsItem* getDisplayItem (void);
	
	protected:

        /**
          * @brief the graphical item representing the Process
          *
          */
		QGraphicsItem* display;

        /**
          * @brief the graphical item representing the ellipse of the Process
          *
          */
		QGraphicsEllipseItem* ellipse;

        /**
          * @brief the graphical item representing the text of the Process
          *
          */
        QGraphicsTextItem* text;

        /**
          * @brief the related Process
          *
          */
		ProcessPtr process;

        /**
          * @brief the related node
          *
          */
		GVNode node;
	
};
