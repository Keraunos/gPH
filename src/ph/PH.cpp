#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "Exceptions.h"
#include "PH.h"
#include "PHScene.h"
#include "Sort.h"

#include <GVGraph.h>
#include <QDebug>


#define DEFAULT_INFINITE_DEFAULT_RATE true
#define DEFAULT_RATE 0.
#define DEFAULT_STOCHASTICITY_ABSORPTION 1


PH::PH () {	
	scene = boost::shared_ptr<PHScene>();
	
    // set defaults
	infinite_default_rate 		= DEFAULT_INFINITE_DEFAULT_RATE;
	default_rate 				= DEFAULT_RATE;
	stochasticity_absorption 	= DEFAULT_STOCHASTICITY_ABSORPTION;
}


// trigger the rendering in the Scene
void PH::render () {
	if (scene.use_count() == 0) scene = make_shared<PHScene>(this);
	scene->doRender();
}

// get graphics scene for display
PHScenePtr PH::getGraphicsScene() { 
	if (scene.use_count() == 0)	scene = make_shared<PHScene>(this);
	return scene;
}


// control headers
int PH::getStochasticityAbsorption () 			{ return stochasticity_absorption; }
void PH::setStochasticityAbsorption (int sa) 	{ stochasticity_absorption = sa; std::cerr << "set " << sa << std::endl; }
bool PH::getInfiniteDefaultRate () 				{ return infinite_default_rate; }
void PH::setInfiniteDefaultRate (bool b) 		{ infinite_default_rate = b; }
double PH::getDefaultRate () 		{ return default_rate; }
void PH::setDefaultRate (double r) 	{ default_rate = r; }


// add data: Sorts and Actions
void PH::addSort (SortPtr s) { sorts.insert(SortEntry(s->getName(), s)); }
void PH::addAction (ActionPtr a) { actions.push_back(a); }


// retrieve a Sort by name
SortPtr PH::getSort (const string& s) {
	map<string, SortPtr>::iterator f = sorts.find(s);
	if (f == sorts.end())
		throw sort_not_found() << sort_info(s);
	return sorts[s];
}


// retrieve all Sorts in a std::list
list<SortPtr> PH::getSorts(void) {
	list<SortPtr> res;
	for (auto &s : sorts)		
		res.push_back(s.second);
	return res;
}


// retrieve all Processes in a std::list
list<ProcessPtr> PH::getProcesses(void) {
	list<ProcessPtr> res;
	for (auto &s : sorts)
		for (auto &p : s.second->getProcesses())
			res.push_back(p);
	return res;
}


// retrieve the list of Actions
list<ActionPtr> PH::getActions(void) { return actions; }


// represent the PH as a mathematical graph and calculates a layout
GVGraphPtr PH::toGVGraph(void) {
	
	GVGraphPtr res = make_shared<GVGraph>(QString("PH Graph"));
	QString s;	
	
    QString posVal;
    // add Sorts and Processes (well named)
	for (auto &e : sorts) {
		s = makeClusterName(e.second->getName());
		res->addSubGraph(s);
        res->getSubGraph(s)->setLabel(QString::fromStdString(e.second->getName()));
        for (int i = 0; i < e.second->countProcesses(); i++) {
            res->getSubGraph(s)->addNode(makeProcessName(e.second->getProcess(i)));

            // check if _agset works on processes:
            //agsafeset(res->getNode(makeProcessName(e.second->getProcess(i))), "shape", "Msquare", "Mdiamond");

            posVal = QString::number(0).append(",").append(QString::number(i)).append("!");
            _agset(res->getNode(makeProcessName(e.second->getProcess(i))), "pos", posVal);

            //qDebug() << makeProcessName(e.second->getProcess(i)) << " >> " << posVal;
        }

        // check if _agset works on clusters:
        //_agset(res->getSubGraph(s)->graph(), "labelloc", "b"); // set label location in cluster: b(ottom), t(op)

        // pos attr DOES NOT WORK on clusters for fdp!
        //posVal = QString::number(k).append(",").append(QString::number(0)).append("!");
        //k++;
        //_agset(res->getSubGraph(s)->graph(), "pos", posVal);
        //qDebug() << ">>>> " << s << " >> " << posVal;
	}
	
    // to solve the issue of coincidence between hits' heads and bounces' tails:
//    const int nbPorts(8);
//    QString ports[nbPorts] = { "n", "ne", "e", "se", "s", "sw", "w", "nw" };
//    int i(0);

    // add Actions (well named)
	for (ActionPtr &a : actions) {
		res->addEdge(	makeProcessName(a->getSource())
					, 	makeProcessName(a->getTarget()));
		res->addEdge(	makeProcessName(a->getTarget())
					, 	makeProcessName(a->getResult()));

        // to solve the issue of coincidence between hits' heads and bounces' tails:
//        _agset(res->getEdge(makeProcessName(a->getSource()), makeProcessName(a->getTarget())), "headport", ports[i]);
//        _agset(res->getEdge(makeProcessName(a->getTarget()), makeProcessName(a->getResult())), "tailport", ports[i]);
//        i = (i+1) % (nbPorts-1);

        // if the target and the result are next to each other in their sort, prevent overlap
//        if (a->getTarget()->getSort() == a->getResult()->getSort()) {
//            //qDebug() << "intern bounce in " << a->getTarget()->getSort()->getName().c_str();
//            int diffIndex(a->getTarget()->getNumber() - a->getResult()->getNumber());
//            if (diffIndex == 1 || diffIndex == -1) {
//                // TODO do something to avoid edge overlap
//                //qDebug() << "close bounce: " << makeProcessName(a->getTarget()) << " -> " << makeProcessName(a->getResult());
//                //_agset(res->getEdge(makeProcessName(a->getTarget()), makeProcessName(a->getResult())), "len", "10");
//            }
//        }
	}
	
    // make graphviz calculate an appropriate layout
	res->applyLayout();

    for (auto &e : sorts) {
        s = makeClusterName(e.second->getName());
//        if (s == "cluster_c") {
//            qDebug() << "cluster_c top left x = " << GD_bb(res->getSubGraph(s)->graph()).LL.x <<
//                        " | y = " << GD_bb(res->getSubGraph(s)->graph()).UR.y;
//        }
        for (int i = 0; i < e.second->countProcesses(); i++) {
            s = makeProcessName(e.second->getProcess(i));
            //qDebug() << s << ": x = " << ND_coord(res->getNode(s)).x << " | y = " << ND_coord(res->getNode(s)).y;
            //qDebug() << s << ": x = " << res->getNode(s)->u.coord.x << " | y = " << res->getNode(s)->u.coord.y;
        }
    }

	return res;
}


GVGraphPtr PH::updateGVGraph(PHScene *scene) {

    // TODO make sure graph name is always unique in the application (see GVGraph constructor)
    GVGraphPtr res = make_shared<GVGraph>(QString("PH Graph 2"));

    // add Processes as Nodes (well named)
    QString clusterName, processName, posVal;
    qreal nodeX, nodeY;
    for (auto &e : scene->getGSorts()) {
        clusterName = makeClusterName(e.second->getSort()->getName());
        //qDebug() << "cluster name: " << clusterName;
        for (int i(0); i < e.second->getSort()->countProcesses(); i++) {
            processName = makeProcessName(e.second->getSort()->getProcess(i));
            res->addNode(processName);
            nodeX =   (qreal) e.second->getSort()->getProcess(i)->getGProcess()->getNode()->centerPos.x() / res->getDPI();
            nodeY = - (qreal) e.second->getSort()->getProcess(i)->getGProcess()->getNode()->centerPos.y() / res->getDPI();
            //qDebug() << processName << ": x = " << nodeX << " | y = " << nodeY;
            posVal = QString::number(nodeX).append(",").append(QString::number(nodeY)).append("!");
            _agset(res->getNode(processName), "pos", posVal);
        }
    }

    // add Actions as Edges (well named)
    for (ActionPtr &a : actions) {
        res->addEdge(	makeProcessName(a->getSource())
                    , 	makeProcessName(a->getTarget()));
        res->addEdge(	makeProcessName(a->getTarget())
                    , 	makeProcessName(a->getResult()));
    }

    // let graphviz apply layout
    qDebug() << "start applying layout";
    res->applyLayout();
    qDebug() << "stop applying layout";

    for (auto &e : sorts) {
        for (int i = 0; i < e.second->countProcesses(); i++) {
            processName = makeProcessName(e.second->getProcess(i));
            //qDebug() << processName << ": x = " << ND_coord(res->getNode(processName)).x << " | y = " << ND_coord(res->getNode(processName)).y;
            //qDebug() << processName << ": x = " << res->getNode(processName)->u.coord.x << " | y = " << res->getNode(processName)->u.coord.y;
        }
    }

    return res;
}

// output for DOT file
string PH::toDotString (void) {

	string res;
	res += "digraph G {\n";
	res += "node [style=filled,color=lightgrey]\n";

    // output Sorts
	res += "\n\n";
	for (auto &e : sorts)
		res += e.second->toDotString() + "\n";

    // output Actions
	res += "\n\n";
	for (ActionPtr &a : actions)
		res += a->toDotString() + "\n";
	res += "}\n";

    return res;
}


// output for PH file
string PH::toString (void) {

    string res;

    // output headers
	res += "directive default_rate " + (infinite_default_rate ? "Inf" : 
		(default_rate == (int) default_rate) ?
			boost::lexical_cast<string>(default_rate) + "."
		:	boost::lexical_cast<string>(default_rate)
	) + "\n";
    res += "directive stochasticity_absorption " + boost::lexical_cast<string>(stochasticity_absorption) + "\n";

    // output Sorts
	for (auto &e : sorts)
		res += e.second->toString();
	res += "\n";

    // output actions
	for (ActionPtr &a : actions)
		res += a->toString();
	res += "\n";

    // output initial state
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
