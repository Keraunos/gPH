#pragma once
#include <list>
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Action.h"
#include "GVGraph.h"
#include "PHScene.h"
#include "Process.h"
#include "Sort.h"

using std::list;
using std::map;
using std::string;
using boost::make_shared;

//Mutual inclusion madness
class Action;
typedef boost::shared_ptr<Action> ActionPtr;

class PH;
typedef boost::shared_ptr<PH> PHPtr;
typedef std::pair<string, SortPtr> SortEntry;

//Build node and subgraph names for graphviz
static inline QString makeClusterName (string s) {
	return QString::fromStdString("cluster_" + s);
}
static inline QString makeProcessName (ProcessPtr p) {
	return QString::fromStdString(p->getSort()->getName()) + QString("_%1").arg(p->getNumber());
}

class PH {

	public:
		PH();
		void addSort(SortPtr s);
		void addAction(ActionPtr a);
		SortPtr getSort(string const&);
		list<ActionPtr> getActions(void);		
		list<SortPtr> getSorts(void);		
		list<ProcessPtr> getProcesses(void);		
		
		string toString (void);					//String output for .ph file
		string toDotString (void);				//String output for dot file		
		void render (void);
		GVGraphPtr toGVGraph(void);
		PHScenePtr getGraphicsScene (void); 	//Output for display
		
		//Headers control
		int 	getStochasticityAbsorption ();
		void 	setStochasticityAbsorption (int sa);
		double 	getDefaultRate ();
		void	setDefaultRate (double r);
		bool 	getInfiniteDefaultRate ();
		void 	setInfiniteDefaultRate (bool b);

	protected:

		//Headers
		int stochasticity_absorption;
		bool infinite_default_rate; //Has priority over default_rate
		double default_rate;

		//Content
		map<string, SortPtr> sorts;
		list<ActionPtr> actions;
		
		//Display
		PHScenePtr scene;		

};