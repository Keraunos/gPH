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
  * @brief determines the way to draw a process
  *
  */
class GProcess {

	public:

        /**
          * @brief constructor for GProcess
          *
          * @param ProcessPtr the Process object that will be agregated
          * @param GVNode the GVNode object that will be agregated
          */
		GProcess(ProcessPtr p, GVNode n);
		~GProcess();
        /**
          * @brief getter for the whole drawing of the process
          *
          * @return QGraphicsItem* representing the whole drawing of the process
          */
		QGraphicsItem* getDisplayItem (void);
	
	protected:

        /**
          * @brief contains the whole drawing of the process
          *
          */
		QGraphicsItem* display;

        /**
          * @brief graphical element to draw the action: ellipse
          *
          */
		QGraphicsEllipseItem* ellipse;

        /**
          * @brief graphical element to draw the action: text
          *
          */
        QGraphicsTextItem* text;

        /**
          * @brief process related
          *
          */
		ProcessPtr process;

        /**
          * @brief node related
          *
          */
		GVNode node;
	
};
