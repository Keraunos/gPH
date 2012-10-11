#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include <list>
#include "Sort.h"

using std::string;

//Mutual inclusion
class Sort;
typedef boost::shared_ptr<Sort> SortPtr;

class Process;
typedef boost::shared_ptr<Process> ProcessPtr;

class Process {

	public:
		Process (SortPtr s, const int& n);
		int getNumber(void);
		SortPtr getSort(void);
		string getDotName (void);
		string toDotString (void);
		
	private:
		SortPtr sort;
		int number;

};