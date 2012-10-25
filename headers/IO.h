#pragma once
#include <string>

/**
  * @file IO.h
  * @brief header for the IO class
  * @author PAPPL_2012
  *
  */

using std::string;

class IO {

	public:
		IO(){}		
		static string readFile (string const& path); 						//Read file content
		static void fileLocationCheck (string const& path); 				//Check that file exists
		static void writeFile (string const& path, string const& content);	//Write file

};
