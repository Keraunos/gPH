#pragma once
#include <QPoint>
#include <QString>
#include <QPainterPath>

/**
  * @file GVEdge.h
  * @brief header for the GVEdge class
  * @author PAPPL_2012
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
