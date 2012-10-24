#pragma once
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Process.h"

/**
  * \file Sort.h
  * \brief header for the Sort class
  * \author PAPPL 2012
  *
  */

using std::string;
using std::list;
using std::vector;
using boost::make_shared;

//Mutual inclusion
class Process;
typedef boost::shared_ptr<Process> ProcessPtr;

class Sort;
typedef boost::shared_ptr<Sort> SortPtr;

class GSort;

class Sort {

public:
	
		//Factory
		static SortPtr make(const string&, const int&);
		
		//Getters & setters
		ProcessPtr getProcess (const uint&);
		vector<ProcessPtr> getProcesses (void);
		ProcessPtr getActiveProcess (void);
		void setActiveProcess (const int&);
		int countProcesses (void);
		string getName (void);
		string toString(void);
		string toDotString(void);

	protected:
		Sort (const string&); //Constructor
		void addProcess(ProcessPtr p);
		string name;
		vector<ProcessPtr> processes;
		ProcessPtr activeProcess;
};
