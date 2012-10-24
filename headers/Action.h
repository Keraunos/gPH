#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include "PH.h"
#include "Sort.h"
#include "GAction.h"

/**
  * \file Action.h
  * \brief header for the Action class
  * \author PAPPL 2012
  *
  */


class Action;
typedef boost::shared_ptr<Action> ActionPtr;
class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;

/**
  * \class Action
  * \brief Represents an action of the process hitting
  *
  */
class Action {

	public:
    /**
      * \brief constructor for action
      *
      * \param source_: the source process
      * \param target_: the target process
      * \param result_: the result of the hit
      * \param infiniteRate_: boolean that determines if the rate of the hit is or is not infinite
      * \param r: defines the rate of the hit
      * \param sa: defines the stochasticity absorption of the hit
      */
		Action 	(	ProcessPtr source_, ProcessPtr target_, ProcessPtr result_
				, 	const bool& infiniteRate_
				, 	const double& r_
				,	const int& sa_
				);

        /**
          * \brief Method to get the source Process
          *
          */
        ProcessPtr getSource();

        /**
          * \brief Method to get the target Process
          *
          */
		ProcessPtr getTarget();

        /**
          * \brief Method to get the result Process
          *
          */
		ProcessPtr getResult();

        /**
          * \brief Method that gives a text representation of the process hitting (as it would be in a .ph file)
          *
          */
		string toString (void);

        /**
          * \brief Method that gives a text representation of the process hitting (in .dot format, used in Graphviz)
          *
          */
		string toDotString (void);

	protected:

       /**
         * \brief the source process
         *
         */
        ProcessPtr source;

        /**
          * \brief the target process
          *
          */
		ProcessPtr target;

        /**
          * \brief the result process
          *
          */
        ProcessPtr result;

        /**
          * \brief boolean that determines if if the rate of the hit is infinite or not
          *
          */
        bool infiniteRate;

        /**
          * \brief determines the rate of the hit
          *
          */
        float r;

        /**
          * \brief determines the stochasticity absorption
          *
          */
        int sa;
		
};
