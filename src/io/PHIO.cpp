#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QImage>
#include <QPainter>
#include <Qt>
#include "axe.h"
#include "Exceptions.h"
#include "Action.h"
#include "IO.h"
#include "PH.h"
#include "PHIO.h"
#include "Sort.h"

using boost::make_shared;
using std::string;
using std::vector;

//Actual parsing, finally
typedef const char* CCHAR;
PHPtr PHIO::parse (string const& input) {
	
	using namespace axe;	
	PHPtr res = make_shared<PH>();
	
	//Debug tool
	/*auto coutRule = [](CCHAR i1, CCHAR i2) {
		std::cout << std::string(i1, i2) << std::endl;
	};*/
	
	//Error
	auto error = r_fail([](CCHAR i1, CCHAR i2) {});
	
	//Comment
	r_rule<const char*> comment;
	comment = r_lit("(*") & *(r_any() - r_lit("*)") - r_lit("(*") | comment) & r_lit("*)"); // does not work with malformed comments like (*aaa(*bb*)
	
	//White space
	auto space = *(r_any(" \t") | comment);
	auto endl = r_lit("\n");
	auto trailing_spaces = space & endl;
	
	//Infinity
	auto infinity = r_lit("Inf");
	
	//Process declaration
	string sortName;
	int processes;
	auto sort_name = (r_alpha() | r_char('_')) & *(r_any("_'") | r_alnum());
	auto sort_declaration = (r_str("process") & space & (sort_name >> sortName) & space & r_ufixed(processes)) >> e_ref([&](CCHAR i1, CCHAR i2) {
		SortPtr s = Sort::make(sortName, processes);
		res->addSort(s);		
	});
	auto sort_declaration_line = sort_declaration & trailing_spaces;
	
	//Action declaration
	string actSort1, actSort2;
	uint actProc1, actProc2, actProc3;
	double actRate;
	int	actStoch;
	bool infiniteActRate = false;
	auto action_required = (sort_name >> actSort1) & space & r_ufixed(actProc1) & space & r_lit("->") & space & (sort_name >> actSort2) & space & r_ufixed(actProc2) & space & r_ufixed(actProc3);
	auto action_rate = 	(	(infinity >> [&](CCHAR i1, CCHAR i2) { infiniteActRate = true; })
						| 	(r_double(actRate) >> [&](CCHAR i1, CCHAR i2) { infiniteActRate = false; })
						);
	auto action_with_rate 	= action_required & space & r_lit("@") & space & action_rate;
	auto action_with_stoch 	= (action_with_rate & space & r_lit("~") & space & r_ufixed(actStoch));
	auto action = 			action_with_stoch >> e_ref([&](CCHAR i1, CCHAR i2) {
								ActionPtr action = make_shared<Action>(	res->getSort(actSort1)->getProcess(actProc1)
																	,	res->getSort(actSort2)->getProcess(actProc2)
																	,	res->getSort(actSort2)->getProcess(actProc3)
																	,	infiniteActRate, actRate, actStoch);
								res->addAction(action);
						})
						|	action_with_rate >> e_ref([&](CCHAR i1, CCHAR i2) {
								ActionPtr action = make_shared<Action>(	res->getSort(actSort1)->getProcess(actProc1)
																	,	res->getSort(actSort2)->getProcess(actProc2)
																	,	res->getSort(actSort2)->getProcess(actProc3)
																	,	infiniteActRate, actRate
																	,	res->getStochasticityAbsorption());
								res->addAction(action);
						})
						|	action_required >> e_ref([&](CCHAR i1, CCHAR i2) { 
								ActionPtr action = make_shared<Action>(	res->getSort(actSort1)->getProcess(actProc1)
																	,	res->getSort(actSort2)->getProcess(actProc2)
																	,	res->getSort(actSort2)->getProcess(actProc3)
																	,	res->getInfiniteDefaultRate(), res->getDefaultRate()
																	,	res->getStochasticityAbsorption());
								res->addAction(action);
						});
	auto action_line = action & trailing_spaces;						
	
	//Body
	auto body_line = sort_declaration_line | action_line | trailing_spaces ;
	
	//Footer
	vector<string> initSorts;
	vector<int> initProc;
	auto initial_state = 	(
							r_lit("initial_state") & space
							& r_many((sort_name >> e_push_back(initSorts)) & space & (r_ufixed() >> e_push_back(initProc)), space & r_lit(",") & space)
							& trailing_spaces
						) >> e_ref([&](CCHAR i1, CCHAR i2) {
							for (unsigned int i=0; i < initSorts.size(); i++)
								res->getSort(initSorts[i])->setActiveProcess(initProc[i]);
							initSorts.clear();
							initProc.clear();
						});
	auto footer_line = initial_state | trailing_spaces;
	
	//Complete file	
	auto body = *body_line;
	auto footer = *footer_line;
	auto ph = (body & footer & r_end()) | error;
	auto result = ph(input.c_str(), input.c_str() + input.length());
	
	if (!result.matched)
		throw ph_parse_error();
	
	return res;
}

//Parse file
PHPtr PHIO::parseFile (string const& path) {

	//Dump content using phc -l dump
	QString phc = "phc";
	QStringList args;
	args << "-l" << "dump" << "-i" << QString::fromUtf8(path.c_str()) << "--no-debug";
	QProcess *phcProcess = new QProcess();
	phcProcess->start(phc, args);
	if (!phcProcess->waitForStarted())
		throw pint_program_not_found() << file_info("phc");	
		
	//Read result
	QByteArray stderr;
	QByteArray stdout;
	while (!phcProcess->waitForFinished()) {
		stderr += phcProcess->readAllStandardError();
		stdout += phcProcess->readAllStandardOutput();
	}
	stderr += phcProcess->readAllStandardError();
	stdout += phcProcess->readAllStandardOutput();
	delete phcProcess;
	
	//Parse dump
	if (!stderr.isEmpty())
		throw pint_phc_crash() << parse_info(QString(stderr).toStdString());
		
	return parse(QString(stdout).toStdString());
}

//Can parse a ph file?
bool PHIO::canParseFile (string const& path) {
    try {
        parseFile(path);
    } catch (exception_base& x) {
        return false;
    }
	return true;
}

//Write PH file
void PHIO::writeToFile (string const& path, PHPtr ph) {
	IO::writeFile(path, ph->toString());
}

//Save PH as PNG image
void PHIO::exportToPNG(PHPtr ph, QString name) {
	
	// Create the image and render it...
	QImage* image = new QImage(ph->getGraphicsScene()->width()+4, ph->getGraphicsScene()->height()+4, QImage::Format_ARGB32_Premultiplied);
	QPainter* p = new QPainter();
	p->begin(image);
	p->setRenderHint(QPainter::Antialiasing);
	ph->getGraphicsScene()->render(p);
	p->end();
	
	// Add .png to the name if necessary
	if (name.indexOf(QString(".png"), 0, Qt::CaseInsensitive) < 0)
		name += ".png";
		
	//Save it
	image->save(name, "PNG");
}
