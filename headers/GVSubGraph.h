#pragma once
#include <graphviz/gvc.h>
#include <boost/shared_ptr.hpp>
#include <QFont>
#include <QMap>
#include <QPair>
#include <QString>
#include "GVCluster.h"
#include "GVNode.h"
#include "GVEdge.h"

class GVSubGraph;
typedef boost::shared_ptr<GVSubGraph> GVSubGraphPtr;

// An object containing a libgraph subgraph and its associated nodes and edges
class GVSubGraph {

	public:
		
		static const qreal nodeSize;
		
		GVSubGraph(Agraph_t *_graph);
		virtual ~GVSubGraph();
		
		// Add and remove subgraphs
		void addSubGraph (const QString& name);
		void removeSubGraph (const QString& name);
		GVSubGraphPtr getSubGraph (const QString& name);

		// Add and remove nodes
		int countNodes(void);
		void addNode(const QString& name);
		void addNodes(const QStringList& names);
		void removeNode(const QString& name);
		void clearNodes();

		// Add and remove edges
		void addEdge(const QString& source, const QString& target);
		void removeEdge(const QString& source, const QString& target);
		void removeEdge(const QPair<QString, QString>& key);
		
		//Setter
		void setLabel (const QString& name);
		
		//Layout results
		QList<GVNode> nodes();
		QList<GVCluster> clusters();
		QList<GVEdge> edges();

	protected:
		GVSubGraph();
		qreal getDPI();
		void setGraphAttributes(void);
		Agraph_t* _graph;
		bool hasNode (const QString& name);
		Agnode_t* getNode (const QString& name);
		QMap<QString, Agnode_t*> _nodes;
		QMap<QString, GVSubGraphPtr> _subgraphs;
		QMap<QPair<QString, QString>, Agedge_t*> _edges;

};

//Utils
/// The agopen method for opening a graph
static inline Agraph_t* _agopen(QString name, int kind) {
	return agopen(const_cast<char *>(qPrintable(name)), kind);
}

/// Add an alternative value parameter to the method for getting an object's attribute
static inline QString _agget(void *object, QString attr, QString alt=QString()) {
	QString str=agget(object, const_cast<char *>(qPrintable(attr)));
	if(str==QString())	return alt;
	else				return str;
}

/// Directly use agsafeset which always works, contrarily to agset
static inline int _agset(void *object, QString attr, QString value) {
	return agsafeset(object, const_cast<char *>(qPrintable(attr)),
					 const_cast<char *>(qPrintable(value)),
					 const_cast<char *>(qPrintable(value)));
}

/// Set node attribute
static inline Agsym_t* _agnodeattr(Agraph_t* object, QString attr, QString value) {
	return agnodeattr(object, const_cast<char *>(qPrintable(attr)),
					 const_cast<char *>(qPrintable(value)));
}

/// Set edge attribute
static inline Agsym_t* _agedgeattr(Agraph_t* object, QString attr, QString value) {
	return agedgeattr(object, const_cast<char *>(qPrintable(attr)),
					 const_cast<char *>(qPrintable(value)));
}

//Layout
static inline void _gvLayout(GVC_t* context, Agraph_t* graph, QString alg) {
	gvLayout(context, graph, const_cast<char *>(qPrintable(alg)));
}