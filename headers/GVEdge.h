#pragma once
#include <QPoint>
#include <QString>
#include <QPainterPath>

/**
  * @file GVEdge.h
  * @brief header for the GVEdge class
  * @author PAPPL 2012
  *
  */


/// A struct containing the information for a GVGraph's edge
struct GVEdge {

    /// The source and target nodes of the edge
    Qstring source;
    Qstring target;

    /// Path of the edge's line
    QPainterPath path;

};
