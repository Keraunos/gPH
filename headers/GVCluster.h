#pragma once
#include <QPoint>
#include <QString>

/**
  * @file GVCluster.h
  * @brief header for the GVCluster class
  * @author PAPPL_2012
  *
  */

//A struct containing the information for a GVGraph's node
struct GVCluster {
	
    //The unique identifier of the cluster in the graph
    QString name;

    //The position of the top-left corner
    QPoint topLeft;

    //The size of the cluster in pixels
    float height, width;
	
	//The label position
	QPoint labelPos;
	
};
