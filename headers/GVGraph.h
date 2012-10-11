#pragma once
#include <graphviz/gvc.h>
#include <boost/shared_ptr.hpp>
#include <QFont>
#include <QList>
#include <QMap>
#include <QPair>
#include <QRectF>
#include <QString>
#include "GVSubGraph.h"

class GVGraph;
typedef boost::shared_ptr<GVGraph> GVGraphPtr;

// An object containing a libgraph graph and its associated nodes and edges
class GVGraph: public GVSubGraph {

	public:

		// Default DPI value used by dot (which uses points instead of pixels for coordinates)
		static const qreal DotDefaultDPI;

		/*!
		 * \brief Construct a Graphviz graph object
		 * \param name The name of the graph, must be unique in the application
		 * \param font The font to use for the graph
		 * \param node_size The size in pixels of each node
		 */
		GVGraph(QString name, QFont font=QFont());
		~GVGraph();

		// Layout and rendering
		void applyLayout (void);
		void renderToFile (QString name);
		
		//Layout results
		QRectF boundingRect();		

		// Set the font to use in all the labels
		void setFont(QFont font);

	private:
		QFont _font;
		GVC_t *_context;
};