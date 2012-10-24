#pragma once
#include <QPoint>
#include <QString>
#include <QPainterPath>

/**
  * \file Action.h
  * \brief header for the GVEdge class
  * \author PAPPL 2012
  *
  */

/// A struct containing the information for a GVGraph's edge
struct GVEdge {
	
    /// The source and target nodes of the edge
    QString source;
    QString target;

    /// Path of the edge's line
    QPainterPath path;
	
};
