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

/**
  * @file GVSubGraph.h
  * @brief header for the GVSubGraph class
  * @author PAPPL_2012
  *
  */

class GVSubGraph;
typedef boost::shared_ptr<GVSubGraph> GVSubGraphPtr;

// An object containing a libgraph subgraph and its associated nodes and edges
/**
  * @class GVSubGraph
  * @brief defines the object containing a libraph subgraph and its associated nodes and edges
  *
  */
class GVSubGraph {

	public:
		
        /**
          * @brief the size in pixels of each node
          *
          */
		static const qreal nodeSize;
		

		GVSubGraph(Agraph_t *_graph);
		virtual ~GVSubGraph();

        // Add an remove SubGraph
        /**
          * @brief add a subgraph
          *
          * @param the name of the SubGraph you want to add
          *
          */
		void addSubGraph (const QString& name);

        /**
          * @brief remove a subgraph
          *
          * @param the name of the SubGraph you want to remove
          *
          */
		void removeSubGraph (const QString& name);

        /**
          * @brief Get the SubGraph
          *
          * @param the name of the SubGraph you want
          * @return the GVSubGraphPtr related to the name
          *
          */
		GVSubGraphPtr getSubGraph (const QString& name);

		// Add and remove nodes

        /**
          * @brief counts the number of nodes
          *
          * @return int the number of nodes
          *
          */
		int countNodes(void);

        /**
          * @brief add a node, entering its name
          *
          * @param Qstring the name of the node you want to add
          *
          */
		void addNode(const QString& name);

        /**
          * @brief add a list of nodes, entering the name of the list
          *
          * @param QStringList of the names of the nodes you want to add
          */
		void addNodes(const QStringList& names);

        /**
          * @brief remove a node, entering its name
          *
          * @param the Qstring name of the node you want to remove
          *
          */
		void removeNode(const QString& name);

        /**
          * @brief remove all the nodes present
          *
          */
		void clearNodes();

		// Add and remove edges

        /**
          * @brief add an edge ,entering the names of the source and the target
          *
          * @brief the name of the source
          * @brief the name of the target
          *
          */
		void addEdge(const QString& source, const QString& target);

        /**
          * @brief remove an edge ,entering the names of the source and the target
          *
          * @brief the name of the source
          * @brief the name of the target
          *
          */
		void removeEdge(const QString& source, const QString& target);

        /**
          * @brief remove an edge, entering the pair (source target)
          *
          * @brief the name of the pair
          *
          */
		void removeEdge(const QPair<QString, QString>& key);
		
		//Setter

        /**
          * @brief setter for the label
          *
          * @param name of the label
          *
          */
		void setLabel (const QString& name);
		
		//Layout results

        /**
          * @brief returns the list of the nodes
          *
          */
		QList<GVNode> nodes();

        /**
          * @brief returns the list of the clusters
          *
          */
		QList<GVCluster> clusters();

        /**
          * @brief returns the list of the edges
          *
          */
		QList<GVEdge> edges();

	protected:
		GVSubGraph();

        /**
          * @brief getter for the DPI
          *
          * @return qreal DPI
          *
          */
		qreal getDPI();

        /**
          * @brief sets the Graph Attributes
          *
          */
		void setGraphAttributes(void);
		Agraph_t* _graph;

        /**
          * @brief checks if the node exists
          *
          * @param name of the node you want to check the existence
          *
          */
		bool hasNode (const QString& name);

        /**
          * getter returns the node
          *
          * @param QString name of the node
          *
          */
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
