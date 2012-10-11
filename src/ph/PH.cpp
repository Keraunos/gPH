#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "Exceptions.h"
#include "PH.h"
#include "PHScene.h"
#include "Sort.h"

#define DEFAULT_INFINITE_DEFAULT_RATE true
#define DEFAULT_RATE 0.
#define DEFAULT_STOCHASTICITY_ABSORPTION 1

PH::PH () {	
	scene = boost::shared_ptr<PHScene>();
	
	//Defaults
	infinite_default_rate 		= DEFAULT_INFINITE_DEFAULT_RATE;
	default_rate 				= DEFAULT_RATE;
	stochasticity_absorption 	= DEFAULT_STOCHASTICITY_ABSORPTION;
}

//Get graphics scene for display
void PH::render () {
	if (scene.use_count() == 0) scene = make_shared<PHScene>(this);
	scene->doRender();
}
PHScenePtr PH::getGraphicsScene() { 
	if (scene.use_count() == 0)	scene = make_shared<PHScene>(this);
	return scene;
}

//Control headers
int PH::getStochasticityAbsorption () 			{ return stochasticity_absorption; }
void PH::setStochasticityAbsorption (int sa) 	{ stochasticity_absorption = sa; std::cerr << "set " << sa << std::endl; }
bool PH::getInfiniteDefaultRate () 				{ return infinite_default_rate; };
void PH::setInfiniteDefaultRate (bool b) 		{ infinite_default_rate = b; };
double PH::getDefaultRate () 		{ return default_rate; }
void PH::setDefaultRate (double r) 	{ default_rate = r; }

//Add data
void PH::addSort (SortPtr s) { sorts.insert(SortEntry(s->getName(), s)); }
void PH::addAction (ActionPtr a) { actions.push_back(a); }

//Retrieve data
SortPtr PH::getSort (const string& s) {
	map<string, SortPtr>::iterator f = sorts.find(s);
	if (f == sorts.end())
		throw sort_not_found() << sort_info(s);
	return sorts[s];
}

list<SortPtr> PH::getSorts(void) {
	list<SortPtr> res;
	for (auto &s : sorts)		
		res.push_back(s.second);
	return res;
}

list<ProcessPtr> PH::getProcesses(void) {
	list<ProcessPtr> res;
	for (auto &s : sorts)
		for (auto &p : s.second->getProcesses())
			res.push_back(p);
	return res;
}

list<ActionPtr> PH::getActions(void) { return actions; }

//Represent as mathematical graph
GVGraphPtr PH::toGVGraph(void) {
	
	GVGraphPtr res = make_shared<GVGraph>(QString("PH Graph"));
	QString s;	
	
	//Add sorts and processes
	for (auto &e : sorts) {
		s = makeClusterName(e.second->getName());
		res->addSubGraph(s);
		res->getSubGraph(s)->setLabel(QString::fromStdString(e.second->getName()));
		for (int i = 0; i < e.second->countProcesses(); i++)
			res->getSubGraph(s)->addNode(makeProcessName(e.second->getProcess(i)));
	}
	
	//Add actions
	for (ActionPtr &a : actions) {
		res->addEdge(	makeProcessName(a->getSource())
					, 	makeProcessName(a->getTarget()));
		res->addEdge(	makeProcessName(a->getTarget())
					, 	makeProcessName(a->getResult()));
	}
	
	//Ask graphviz to do his job
	res->applyLayout();
	return res;
}

string PH::toDotString (void) {
	string res;
	res += "digraph G {\n";
	res += "node [style=filled,color=lightgrey]\n";
	//Output sorts
	res += "\n\n";
	for (auto &e : sorts)
		res += e.second->toDotString() + "\n";
	//Output actions
	res += "\n\n";
	for (ActionPtr &a : actions)
		res += a->toDotString() + "\n";
	res += "}\n";
	return res;

}

string PH::toString (void) {
	string res;
	//Output headers
	res += "directive default_rate " + (infinite_default_rate ? "Inf" : 
		(default_rate == (int) default_rate) ?
			boost::lexical_cast<string>(default_rate) + "."
		:	boost::lexical_cast<string>(default_rate)
	) + "\n";
	res += "directive stochasticity_absorption " + boost::lexical_cast<string>(stochasticity_absorption) + "\n";
	//Output sorts
	for (auto &e : sorts)
		res += e.second->toString();
	res += "\n";
	//Output actions
	for (ActionPtr &a : actions)
		res += a->toString();
	res += "\n";
	//Output initial state
	if (!sorts.empty()) {
		res += "initial_state ";
		list<string> l;
		for (auto &e : sorts)
			l.push_back(e.second->getName() + " " + boost::lexical_cast<string>(e.second->getActiveProcess()->getNumber()));
		res += boost::algorithm::join(l, ", ");
	}
	res += "\n";
	return res;
}
