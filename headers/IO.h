#pragma once
#include <string>

/**
  * @file IO.h
  * @brief header for the IO class
  * @author PAPPL_2012
  *
  */

using std::string;


/**
  * @class IO
  * @brief manages the inputs and outputs at the lowest level
  *
  */
class IO {

	public:
		IO(){}		

        /**
          * @brief reads the file content
          * @param string name of the file
          * @return string file read
          *
          */
        static string readFile (string const& path);

        /**
          * @brief checks that the file exists
          *
          * @param string name of the file
          *
          */
        static void fileLocationCheck (string const& path);

        /**
          * @brief Writes the file
          *
          *
          */
		static void writeFile (string const& path, string const& content);	//Write file

};
