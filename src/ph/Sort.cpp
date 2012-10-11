#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include "Exceptions.h"
#include "Process.h"
#include "Sort.h"

using boost::make_shared;

//Factory
SortPtr Sort::make (const string& name, const int& processes) {
	//Create Sort
	SortPtr s (new Sort(name));
	//Add processes
	if (processes < 1) throw process_required();
	for (int i = 0; i < processes + 1; i++)
		s->addProcess(make_shared<Process>(s, i));
	//Set first process as active
	s->setActiveProcess(0);
	return s;
}

//Private constructor
Sort::Sort (const string& n) : name(n) {}

//Add a process
void Sort::addProcess (ProcessPtr p) {
	processes.push_back(p);
}

//Output for dot file
string Sort::toDotString (void) {
	string res;

	//Processes
	res += "subgraph cluster_" + name + " {\n";
	res += "\tlabel = \"Sort " + name + "\";\n";
	res += "\tcolor = lightgray;\n";
	for (ProcessPtr &p : processes)
		res += "\t" + p->toDotString();
	res += "}\n";

	return res;
}

//Output for PH file
string Sort::toString (void) {
	return "process " + getName() + " " +  boost::lexical_cast<string>(processes.size() - 1) + "\n";
}

//Getters & setters
ProcessPtr Sort::getProcess (const uint& i) {
	if (i >= processes.size())
		throw process_not_found() << process_info(i);
	return processes[i];
}

vector<ProcessPtr> Sort::getProcesses (void) {	
	return processes;
}

void Sort::setActiveProcess (const int& i) { activeProcess = getProcess(i); }
ProcessPtr Sort::getActiveProcess (void) { return activeProcess; }

string Sort::getName (void) { return name; }
int Sort::countProcesses() { return processes.size() ; }