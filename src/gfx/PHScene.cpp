#include <iostream>
#include <utility>
#include <QBrush>
#include <QColor>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Exceptions.h"
#include "PH.h"
#include "Sort.h"
#include "Process.h"
#include "PHScene.h"
#include "GVGraph.h"

PHScene::PHScene(PH* _ph) : ph(_ph) {
	setBackgroundBrush(QBrush(QColor(0, 43, 54)));
}

void PHScene::doRender(void) {
	
	//Retrieve graph
	GVGraphPtr graph = ph->toGVGraph();
	
	//Create GProcesses linking actual processes (PH info) with GVNodes (display info)
	QList<GVNode> gnodes = graph->nodes();	
	for (GVNode &gn : gnodes) {
		for (SortPtr &s : ph->getSorts())
			for (ProcessPtr &p : s->getProcesses()) {				
				if (gn.name == makeProcessName(p))
					processes.push_back(make_shared<GProcess>(p, gn));		
			}
	}
	
	//Create GSorts linking actual sorts (PH info) with GVClusters (display info)
	QList<GVCluster> gclusters = graph->clusters();	
	for (GVCluster &gc : gclusters)
		for (SortPtr &s : ph->getSorts())
			if (gc.name == makeClusterName(s->getName()))
				sorts.insert(GSortEntry(s->getName(), make_shared<GSort>(s, gc)));
				
	//Create GActions linking actual actions to GVEdges (display info)
	QList<GVEdge> gedges = graph->edges();
	using std::pair;
	pair<GVEdge*, GVEdge*> edges;
	for (ActionPtr &a : ph->getActions()) {
		edges.first = NULL;
		edges.second = NULL;
		for (GVEdge &ge : gedges) {
			if 	(	makeProcessName(a->getSource()) == ge.source
				&&	makeProcessName(a->getTarget()) == ge.target
				) 	edges.first = &ge;
			if 	(	makeProcessName(a->getTarget()) == ge.source
				&&	makeProcessName(a->getResult()) == ge.target
				) 	edges.second = &ge;
			if (edges.first != NULL && edges.second != NULL) {
				actions.push_back(make_shared<GAction>(a, *(edges.first), *(edges.second), this));
				break;
			}
		}
	}			
	
	draw();
}

void PHScene::draw(void) {
	clear();
	for (auto &s : sorts)
		addItem(s.second->getDisplayItem());
	for (GProcessPtr &p : processes)
		addItem(p->getDisplayItem());
	for (GActionPtr &a : actions)
		addItem(a->getDisplayItem());
}

//Retrieve GSort
GSortPtr PHScene::getGSort (const string& s) {
	map<string, GSortPtr>::iterator f = sorts.find(s);
	if (f == sorts.end())
		throw sort_not_found() << sort_info(s);
	return sorts[s];
}