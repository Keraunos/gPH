#pragma once
#include <string>
#include "PH.h"

/**
  * @file PHIO.h
  * @brief header for the PHIO class
  * @author PAPPL_2012
  *
  */

using std::string;

/**
  * @class PHIO
  * @brief manages the inputs and outputs of the PH files
  *
  */
class PHIO {

	public:
        /**
          * @brief checks if the file exists and is recognized by the parser
          * @param string the path of the file
          * @return bool 1 if the file exists
          *
          */
		static bool canParseFile(string const& path);

        /**
          * @brief parses the file if it is possible
          * @param string the path of the file to parse
          * @return PHPtr the parsed PH file
          *
          */
		static PHPtr parseFile  (string const& path);

        /**
          * @brief saves the PH object as a PH file
          * @param string the path of the file
          * @param PHPtr the object that will be saved
          *
          */
        static void writeToFile (string const& path, PHPtr ph);

        /**
          * @brief saves as a PNG the representation of the PH file in the window
          * @param PHPtr the PH object of the active window
          * @param QString the name of the file saved
          *
          */
		static void exportToPNG (PHPtr ph, QString name);
	
	private:
		PHIO(){}

        /**
          * @brief parses the file coming from PHC
          * @param string the path of the data
          * @return PHPtr the PH object parsed
          *
          */
        static PHPtr parse (string const& input);

};
