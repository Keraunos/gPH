#pragma once
#include <QPoint>
#include <QString>

/// A struct containing the information for a GVGraph's node
struct GVNode {
	
    /// The unique identifier of the node in the graph
    QString name;

    /// The position of the center point of the node from the top-left corner
    QPoint centerPos;

    /// The size of the node in pixels
    float height, width;
	
};