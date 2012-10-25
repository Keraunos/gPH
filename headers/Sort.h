#pragma once
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Process.h"

/**
  * @file Sort.h
  * @brief header for the Sort class
  * @author PAPPL_2012
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

/**
  * @class sort
  * @brief represents a sort of the process hitting
  *
  */
class Sort {

public:
	
        /**
          * @brief creates pointers to sorts
          *
          */
		static SortPtr make(const string&, const int&);
		

        /**
          * @brief getter for the process
          *
          */
		ProcessPtr getProcess (const uint&);

        /**
          * @brief getter for the vector of processes
          *
          */
		vector<ProcessPtr> getProcesses (void);

        /**
          * @brief getter for the active process
          *
          */
		ProcessPtr getActiveProcess (void);

        /**
          * @brief setter for the active process
          *
          */
		void setActiveProcess (const int&);

        /**
          * @brief counts the number of processes
          *
          */
		int countProcesses (void);

        /**
          * @brief getter for the Name of the sort
          *
          */
		string getName (void);

        /**
          * @brief gives a text representation of the process hitting (as it would be in a .ph file)
          *
          */
		string toString(void);

        /**
          * @brief gives a text representation of the process hitting (in .dot format, used in Graphviz)
          *
          */
		string toDotString(void);

	protected:

        /**
          * @brief constructor for sort
          *
          */
        Sort (const string&);

        /**
          * @brief adds a process
          *
          */
		void addProcess(ProcessPtr p);

        /**
          * @brief name of the sort
          *
          */
		string name;

        /**
          * @brief processes related to the sort
          *
          */
		vector<ProcessPtr> processes;

        /**
          * @brief active process in the sort
          *
          */
		ProcessPtr activeProcess;
};
