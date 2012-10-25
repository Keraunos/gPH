#include <iostream>
#include <string>
#include <boost/exception/all.hpp>

/**
  * @file Exceptions.h
  * @brief header for the Exceptions class
  * @author PAPPL_2012
  *
  */

using std::string;
using boost::error_info;

struct exception_base: virtual std::exception, virtual boost::exception { };

//IO errors
typedef error_info<struct file_path, string> file_info;
struct io_error: virtual exception_base { };
struct file_not_exist: virtual io_error { };
struct not_regular_file: virtual io_error { };

//Parse errors
typedef error_info<struct parse_detail, string> parse_info;
struct ph_parse_error: virtual exception_base { };
struct pint_phc_crash: virtual ph_parse_error { };

//Pint errors
struct pint_program_not_found: virtual exception_base { };

//PH errors
typedef error_info<struct process_id, int> process_info;
typedef error_info<struct sort_name, string> sort_info;
struct ph_error: virtual exception_base { };
struct process_required : virtual ph_error { };
struct process_not_found : virtual ph_error { };
struct sort_not_found : virtual ph_error { };

//Graphviz error
struct gv_error: virtual exception_base { };
struct subgraph_not_found : virtual gv_error { };
