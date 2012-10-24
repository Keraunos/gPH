#pragma once
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <list>
#include "PH.h"
#include "Process.h"
#include "GVNode.h"

/**
  * \file GProcess.h
  * \brief header for the GProcess class
  * \author PAPPL 2012
  *
  */

class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class Process;
typedef boost::shared_ptr<Process> ProcessPtr;

class GProcess {

	public:
		GProcess(ProcessPtr p, GVNode n);
		~GProcess();
		QGraphicsItem* getDisplayItem (void);
	
	protected:
		QGraphicsItem* display;
		QGraphicsEllipseItem* ellipse;
		QGraphicsTextItem* text;
		ProcessPtr process;
		GVNode node;
	
};
