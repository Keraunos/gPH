#pragma once
#include <QPoint>
#include <QString>
#include <QPainterPath>

/// A struct containing the information for a GVGraph's edge
struct GVEdge {
	
    /// The source and target nodes of the edge
    QString source;
    QString target;

    /// Path of the edge's line
    QPainterPath path;
	
};