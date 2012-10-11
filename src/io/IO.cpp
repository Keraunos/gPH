#include <boost/filesystem.hpp>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "Exceptions.h"
#include "IO.h"

//Read file content as string
string IO::readFile (string const& path) {

	using namespace boost::filesystem;
	IO::fileLocationCheck(path);
	
	//Open file
	QFile file(QString::fromUtf8(path.c_str()));
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw io_error() << file_info(path);
	QTextStream in(&file);
	
	return in.readAll().toStdString();
	
}

//Check that file exists
void IO::fileLocationCheck (string const& path) {

	using namespace boost::filesystem;
	
	//Sanity checks
	if (!exists(path)) 		
		throw file_not_exist() << file_info(path);	
	if (!is_regular_file(path))
		throw not_regular_file() << file_info(path);
		
}

//Write string as file
void IO::writeFile (string const& path, string const& content) {

	QFile file(QString::fromUtf8(path.c_str()));
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << QString::fromUtf8(content.c_str());
    file.close(); 
	
}