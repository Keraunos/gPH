#pragma once
#include <string>
#include "PH.h"

using std::string;

class PHIO {

	public:
		static bool canParseFile(string const& path);
		static PHPtr parseFile  (string const& path);
		static void writeToFile (string const& path, PHPtr ph);			
		static void exportToPNG (PHPtr ph, QString name);
	
	private:
		PHIO(){}
		static PHPtr parse (string const& input); 		//Actual parsing

};