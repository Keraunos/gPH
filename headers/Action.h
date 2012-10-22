#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include "PH.h"
#include "Sort.h"
#include "GAction.h"

class Action;
typedef boost::shared_ptr<Action> ActionPtr;
class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;

class Action {

	public:
		Action 	(	ProcessPtr source_, ProcessPtr target_, ProcessPtr result_
				, 	const bool& infiniteRate_
				, 	const double& r_
				,	const int& sa_
				);
		ProcessPtr getSource();
		ProcessPtr getTarget();
		ProcessPtr getResult();
		string toString (void);
		string toDotString (void);

	protected:
		ProcessPtr source;
		ProcessPtr target;
		ProcessPtr result;		
		bool infiniteRate;	//rate is infinite
		float r; 			//rate
		int sa; 			//stochasticity absorption factor		
		
};

// test Marlène utilisation de git
