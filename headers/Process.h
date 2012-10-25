#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include <list>
#include "Sort.h"

/**
  * \file Process.h
  * \brief header for the Process class
  * \author PAPPL_2012
  *
  */

using std::string;

//Mutual inclusion
class Sort;
typedef boost::shared_ptr<Sort> SortPtr;

class Process;
typedef boost::shared_ptr<Process> ProcessPtr;

/**
  * @class Process
  * @brief represents a process of the process hitting
  *
  */
class Process {

	public:

        /**
          * @brief builder for Process
          *
          * @param Sortptr s sort the process is related to
          * @param int n number of the process in the sort it is related to
          *
          */
		Process (SortPtr s, const int& n);

        /**
          * @brief getter for the number
          *
          */
		int getNumber(void);

        /**
          * @brief getter for the sort
          *
          */
		SortPtr getSort(void);

        /**
          * @brief renames in DOT file
          * @return string renamed
          */
		string getDotName (void);

        /**
          * @brief gives a text representation of the process hitting (in .dot format, used in Graphviz)
          * @return string the representation in DOT format
          *
          */
		string toDotString (void);
		
	private:

        /**
          * @brief sort the process is related to
          *
          */
		SortPtr sort;

        /**
          * @brief number of the process in the sort it is related to
          *
          */
		int number;

};
