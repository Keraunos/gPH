#include <boost/lexical_cast.hpp>
#include "Process.h"

Process::Process (SortPtr s, const int& n) : sort(s), number(n) {}

//Output for dot file
string Process::toDotString () {
	string n = boost::lexical_cast<string>(number);
	return getDotName() + " [label=\"" + n + "\"];\n";
}

//Name in dot files
string Process::getDotName () {
	string n = boost::lexical_cast<string>(number);
	return sort->getName() + "_p" + n;
}

//Getters
int Process::getNumber () { return number; }
SortPtr Process::getSort () { return sort; }
