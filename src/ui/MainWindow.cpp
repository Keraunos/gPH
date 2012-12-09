#include <QApplication>
#include <QtGui>
#include "MainWindow.h"
#include "MyArea.h"
#include "PHIO.h"
#include "Exceptions.h"
#include "Area.h"
#include "QProgressIndicator.h"

MainWindow::MainWindow() {

    // title
    setWindowTitle("gPH");

    // icon
    setWindowIcon(QIcon("gph.png"));

    // menu
    menuFile =          menuBar()->addMenu("&File");
    menuEdit =          menuBar()->addMenu("&Edit");
    menuView =          menuBar()->addMenu("&View");
    menuComputation =   menuBar()->addMenu("&Computation");
    menuHelp =          menuBar()->addMenu("&Help");

    // actions for the menus:

    // actions for the menu File
    actionNew = menuFile->addAction("New");
    actionOpen = menuFile->addAction("Open...");
    menuFile->addSeparator();
    actionSaveas = menuFile->addAction("Save as...");
    menuExport = menuFile->addMenu("Export");
    actionPng = menuExport->addAction("png");
    actionDot = menuExport->addAction("dot");
    menuFile->addSeparator();
    actionClose = menuFile->addAction("Close");
    actionQuit = menuFile->addAction("Quit");

    // disable what does not work well
    actionNew->setEnabled(false);

    // shortcuts for the menu File
    actionNew->setShortcut(     QKeySequence(Qt::CTRL + Qt::Key_N));
    actionOpen->setShortcut(    QKeySequence(Qt::CTRL + Qt::Key_O));
    actionSaveas->setShortcut(  QKeySequence(Qt::CTRL + Qt::Key_S));
    actionQuit->setShortcut(    QKeySequence(Qt::CTRL + Qt::Key_Q));

    // connect the menu File
    QObject::connect(actionQuit,    SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpen,    SIGNAL(triggered()), this, SLOT(openTab()));
    QObject::connect(actionSaveas,  SIGNAL(triggered()), this, SLOT(save()));
    QObject::connect(actionPng,     SIGNAL(triggered()), this, SLOT(exportPng()));
    QObject::connect(actionClose,   SIGNAL(triggered()), this, SLOT(closeTab()));
    QObject::connect(actionDot, SIGNAL(triggered()), this, SLOT(exportDot()));

    // actions for the menu Edit
    actionUndo = menuEdit->addAction("Undo");
    actionRedo = menuEdit->addAction("Redo");

    // disable what does not work well
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);

    // actions for the menu View
    actionAdjust = menuView->addAction("Adjust View");
    actionZoomIn = menuView->addAction("Zoom In");
    actionZoomOut = menuView->addAction("Zoom Out");
    menuView->addSeparator();
    menuPreferences = menuView->addMenu("Preferences");
    actionBackgroundColor = menuPreferences->addAction("Set background color");
    actionSortColor = menuPreferences->addAction("Set sorts color");
    menuDefaultStyles = menuPreferences->addMenu("Default Styles");
    actionNaturalStyle = menuDefaultStyles->addAction("Positive contrast");
    actionNegativeStyle = menuDefaultStyles->addAction("Negative contrast");
    actionPrintStyle = menuDefaultStyles->addAction("Print");    
    menuText = menuPreferences->addMenu("Text Preferences");
    actionHideShowText = menuText->addAction("Hide / Show Text");
    actionHideShowText->setCheckable(true);
    actionChangeTextBackgroundColor = menuText->addAction("Change Text Background Color");
    menuTree = menuPreferences->addMenu("Tree Preferences");
    actionHideShowTree = menuTree->addAction("Hide / Show Tree");
    actionHideShowTree->setCheckable(true);
    actionShowInit = menuView->addAction("Show initial state");
    actionHighlight = menuView->addAction("Highlight possible actions");
    actionHide = menuView->addAction("Hide actions");
    actionDisplayDetailed = menuView->addAction("Display detailed cooperativities");


    actionShowInit->setCheckable(true);
    actionHighlight->setCheckable(true);

    // connect the menu View
    QObject::connect(actionAdjust,    SIGNAL(triggered()), this, SLOT(adjust()));
    QObject::connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    QObject::connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    QObject::connect(actionBackgroundColor, SIGNAL(triggered()), this, SLOT(changeBackgroundColor()));    
    QObject::connect(actionSortColor, SIGNAL(triggered()), this, SLOT(changeSortColor()));
    QObject::connect(actionNaturalStyle, SIGNAL(triggered()), this, SLOT(positiveContrast()));
    QObject::connect(actionNegativeStyle, SIGNAL(triggered()), this, SLOT(negativeContrast()));
    QObject::connect(actionPrintStyle, SIGNAL(triggered()), this, SLOT(printStyle()));
    QObject::connect(actionHideShowText, SIGNAL(triggered()), this, SLOT(hideShowText()));
    QObject::connect(actionChangeTextBackgroundColor, SIGNAL(triggered()), this, SLOT(changeTextBackgroundColor()));
    QObject::connect(actionHideShowTree, SIGNAL(triggered()), this, SLOT(hideShowTree()));

    // shortcuts for the menu View
    actionAdjust->setShortcut(     QKeySequence(Qt::CTRL + Qt::Key_L));
    actionZoomIn->setShortcut(  QKeySequence(Qt::CTRL + Qt::Key_Plus));
    actionZoomOut->setShortcut(  QKeySequence(Qt::CTRL + Qt::Key_Minus));

    // disable what does not work
    actionShowInit->setEnabled(false);
    actionHighlight->setEnabled(false);
    actionHide->setEnabled(false);
    actionDisplayDetailed->setEnabled(false);

    // actions for the menu Computation
    actionFindFixpoints = menuComputation->addAction("Find fixpoints...");
    actionComputeReachability = menuComputation->addAction("Compute reachability...");
    actionRunStochasticSimulation = menuComputation->addAction("Run stochastic simulation...");
    actionCheckModelType = menuComputation->addAction("Check model type (binary or multivalued)");
    actionStatistics = menuComputation->addAction("Statistics...");

    // disable what does not work well
    actionComputeReachability->setEnabled(false);
    actionCheckModelType->setEnabled(false);

    // connect the menu Computation
    QObject::connect(actionFindFixpoints, SIGNAL(triggered()), this, SLOT(findFixpoints()));
    QObject::connect(actionComputeReachability, SIGNAL(triggered()), this, SLOT(computeReachability()));
    QObject::connect(actionRunStochasticSimulation, SIGNAL(triggered()), this, SLOT(runStochasticSimulation()));
    QObject::connect(actionCheckModelType, SIGNAL(triggered()), this, SLOT(checkModelType()));
    QObject::connect(actionStatistics, SIGNAL(triggered()), this, SLOT(statistics()));

    // action for the menu Help
    actionHelp = menuHelp->addAction("Helpz !");

    // disable what does not work well
    actionHelp->setEnabled(false);

    // main area
    this->centraleArea = new QMdiArea();
    setCentralWidget(centraleArea);
    centraleArea->setViewMode(QMdiArea::TabbedView);

    // management of the menus (enabled/disabled)
    QObject::connect(this->centraleArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(disableMenu(QMdiSubWindow*)));

    if(this->getCentraleArea()->subWindowList().isEmpty()){
        this->actionClose->setEnabled(false);
        this->actionSaveas->setEnabled(false);
        this->actionPng->setEnabled(false);
        this->actionDot->setEnabled(false);
        this->actionAdjust->setEnabled(false);
        this->actionZoomOut->setEnabled(false);
        this->actionZoomIn->setEnabled(false);
        this->actionBackgroundColor->setEnabled(false);
        this->actionSortColor->setEnabled(false);
        this->actionNaturalStyle->setEnabled(false);
        this->actionNegativeStyle->setEnabled(false);
        this->actionPrintStyle->setEnabled(false);
        this->actionHideShowText->setEnabled(false);
        this->actionChangeTextBackgroundColor->setEnabled(false);
        this->actionHideShowTree->setEnabled(false);
        this->actionFindFixpoints->setEnabled(false);
        this->actionRunStochasticSimulation->setEnabled(false);
        this->actionStatistics->setEnabled(false);
    }

//    this->indicator = new QProgressIndicator(this);
}


MainWindow::~MainWindow() {
    delete centraleArea;
}


QMdiArea* MainWindow::getCentraleArea() {
    return this->centraleArea;
}


// get all open files' paths
std::vector<QString> MainWindow::getAllPaths() {
    int size = this->getCentraleArea()->subWindowList().size();
    std::vector<QString> allPaths;
    QString path;
    for(int n=0; n<size; n++) {
        path = ((MyArea*) this->getCentraleArea()->subWindowList()[n]->widget())->getPath();
        allPaths.push_back(path);
    }
    return allPaths;
}


// open a new tab
MyArea* MainWindow::openTab() {

//        QProgressBar* progressBar = new QProgressBar(this);
//        progressBar->setMaximumHeight(16);
//        progressBar->setMaximumWidth(200);
//        progressBar->setTextVisible(false);
//        progressBar->setRange(0,0);
//        progressBar->setValue(1);
//        this->statusBar()->addPermanentWidget(progressBar);
//        this->statusBar()->showMessage("Opening PH file...");
//        this->show();

        // OpenFile dialog
        QFileDialog* filedialog = new QFileDialog(this);
        QString file = filedialog->getOpenFileName(this, "Open...");

//        QObject::connect(filedialog, SIGNAL(accepted()), this->indicator, SLOT(startAnimation()));



        // TODO refactor using early returns
        if(file!=NULL) {


            QFileInfo pathInfo(file);
            std::vector<QString> allPath = this->getAllPaths();
            int size = allPath.size();
            bool alreadyOpen = false;

            // check if the file is already open
            for(int i=0;i<size;i++) {
                if(allPath[i]==file) {
                   alreadyOpen = true;
                    break;
                }
            }

            if(!alreadyOpen) {

                //need a std::string instead of a QString
                std::string path =	file.toStdString();                

                // parse file
                Area *area = new Area();
                area->mainWindow = this;


                try {

                    // render graph
                    PHPtr myPHPtr = PHIO::parseFile(path);
                    area->myArea->setPHPtr(myPHPtr);
					myPHPtr->render();
                    PHScenePtr scene = myPHPtr->getGraphicsScene();
                    area->myArea->setScene(&*scene);

                    // set the pointer of the treeArea
                    area->treeArea->myPHPtr = myPHPtr;
                    //set the pointer of the treeArea
                    area->treeArea->myArea = area->myArea;
                    // build the tree in the treeArea
                    area->treeArea->build();

                    // call the PH string and write it in the text area
                    //std::string string(myPHPtr->toString());
                    //area->textArea->setPlainText(QString::fromStdString(string));

                    // call the PH file and write it in the text area (same as .ph)
                    QFile fichier(file);
                    fichier.open(QIODevice::ReadOnly);
                    QByteArray data;
                    data = fichier.readAll();
                    QString ligne(data);
                    area->textArea->setPlainText(ligne);

                    // make the subwindow for the new tab
                    QMdiSubWindow *theNewTab = this->getCentraleArea()->addSubWindow(area);
                    QString fileName(pathInfo.fileName());
                    theNewTab->setWindowTitle(fileName);
                    this->enableMenu();


                    return area->myArea;



                } catch(exception_base& argh) {
                    QMessageBox::critical(this, "Error", "Extension not recognized. Only ph files are accepted.");
                    return NULL;
                }
            }


            else {
                QMessageBox::critical(this, "Error", "This file is already opened !");
                return NULL;
            }



        } else {
            return NULL;
        }

        this->statusBar()->hide();
}


// close a tab
void MainWindow::closeTab() {

    // if there is at least one subwindow, close the current one
    if(!this->getCentraleArea()->subWindowList().isEmpty()) {
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        subWindow->close();
    } else {
        QMessageBox::critical(this, "Error", "No file opened !");
    }
}


// save a graph
void MainWindow::save() {

    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        // SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Save file");

        // need a std::string instead of a QString
        std::string path =	fichier.toStdString();

        // need the PHPtr which is associated with the subwindow
        PHPtr ph= ((MyArea*) subWindow->widget())->getPHPtr();

        // save file
        PHIO::writeToFile (path, ph);
    } else {
        QMessageBox::critical(this, "Error", "No file opened !");
    }
}


// export methods

void MainWindow::exportPng() {
	
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        // SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Export as .png file", QString(), "*.png");

        // need the PHPtr which is associated with the subwindow
        PHPtr ph= ((Area*) subWindow->widget())->myArea->getPHPtr();

        // save as PNG
		PHIO::exportToPNG(ph, fichier);
		
    } else QMessageBox::critical(this, "Error", "No file opened !");
	
}

void MainWindow::exportDot() {

    /*if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        // SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Export as .dot file", QString(), "*.png");

        // need the String file of the Dot
        QString str= ((Area*) subWindow->widget())->myArea->getPHPtr()->toDotString()->(QString::fromStdString());



        // add .dot to the name if necessary
        if (fichier.indexOf(QString(".dot"), 0, Qt::CaseInsensitive) < 0)
            fichier += ".dot";

        // save it
        image->save(fichier, "DOT");

    } else QMessageBox::critical(this, "Error", "No file opened !");*/

}

// method to adjust the view
void MainWindow::adjust()
{
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    view->myArea->fitInView(view->myArea->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

// method to zoom In
void MainWindow::zoomIn()
{
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    view->myArea->zoomIn();
}

// method to zoom out
void MainWindow::zoomOut()
{
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    view->myArea->zoomOut();
}

void MainWindow::searchSort()
{
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    view->treeArea->searchSort();
}


/* methods for Smooth Zoom
void MainWindow::scalingTime(qreal x)
{
    qreal factor = 1.0 + qreal(_numScheduledScalings) / 300;
    MyArea* view = (MyArea*) this->getCentraleArea()->currentSubWindow()->widget();
    view->scale(factor, factor);
}

void MainWindow::animFinished()
{
    if(_numScheduledScalings > 0)
        _numScheduledScalings--;
    else
        _numScheduledScalings++;
    MyArea* view = (MyArea*) this->getCentraleArea()->currentSubWindow()->widget();
    view->sender()->~QObject();
}

void MainWindow::wheelEvent(QwheelEvent * event)
{
    int numDegrees = event->dekta() / 8;
    int numSteps = numDegrees / 15;
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0)
        _numScheduledScalings = numSteps;

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL(valueChanged(qreal)), SLOT(scalingTime(qreal)));
    connect(anim, SIGNAL(finished()), SLOT(animFinished));
    anim->start();
}

*/


// method to change the background color
void MainWindow::changeBackgroundColor() {

    QColor couleur = QColorDialog::getColor();

    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();

    if(!couleur.isValid()){
        return ;
    } else {
        view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(couleur);
    }
}


// method to change the sorts color
void MainWindow::changeSortColor() {

    QColor color = QColorDialog::getColor();

    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    if (!color.isValid()) {
        return ;
    } else {
        map<string, GSortPtr>::iterator it;
        for(it=sortList.begin(); it!=sortList.end(); it++) {
            //it->second->getRect()->setPen(QPen(QColor(color)));
            it->second->getRect()->setBrush(QBrush(QColor(color)));
        }
    }
}


// method to set the default style: positive
void MainWindow::positiveContrast() {

    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(QColor(255,255,255));

    map<string, GSortPtr>::iterator it;
    for(it=sortList.begin(); it!=sortList.end(); it++) {
        it->second->getRect()->setPen(QPen(QColor(0,51,102)));
        it->second->getRect()->setBrush(QBrush(QColor(0,51,102)));
    }
}

// method to set the default style: negative
void MainWindow::negativeContrast() {

    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(QColor(31,31,31));

    map<string, GSortPtr>::iterator it;
    for(it = sortList.begin(); it != sortList.end(); it++) {
        it->second->getRect()->setPen(QPen(QColor(7,54,66)));
        it->second->getRect()->setBrush(QBrush(QColor(7,54,66)));
    }
}

// method to set the default style: print
void MainWindow::printStyle() {

    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(Qt::white);

    map<string, GSortPtr>::iterator it;
    for(it = sortList.begin(); it != sortList.end(); it++) {
        it->second->getRect()->setPen(QPen(Qt::black, 4));
        it->second->getRect()->setBrush(Qt::NoBrush);
    }

    std::vector<GProcessPtr> processes = view->myArea->getPHPtr()->getGraphicsScene()->getProcesses();
    for (GProcessPtr &a: processes){
        a->getEllipseItem()->setPen(QPen(Qt::black, 3));
        a->getEllipseItem()->setBrush(Qt::NoBrush);
    }


}

// hide / show the text area. Called by the signal actionHideShowText
void MainWindow::hideShowText(){
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    view->hideOrShowText();
}

// change the text background color in the text area. Called by the signal actionChangeTextBackgroundColor
void MainWindow::changeTextBackgroundColor(){
    QColor couleur = QColorDialog::getColor();
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    view->textArea->changeBackgroundColor(couleur);
}

// hide the tree area. Called by the signal actionHideTree
void MainWindow::hideShowTree(){
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    view->hideOrShowTree();
}

// main method for the computation menu
void MainWindow::compute(QString program, QStringList arguments, QString fileName) {

    // start process
    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);

    if (!myProcess->waitForStarted())
        throw pint_program_not_found() << file_info("phc");

    // read result
    QByteArray err;
    QByteArray out;
    while (!myProcess->waitForFinished()) {
        err += myProcess->readAllStandardError();
        out += myProcess->readAllStandardOutput();
    }
    err += myProcess->readAllStandardError();
    out += myProcess->readAllStandardOutput();
    delete myProcess;

    // pop up for the errors
    if(!err.isEmpty()){

        //correct a false error message for ph-stable
        if(program==QString("ph-stable")) {
            if( !(QString(err).contains(fileName)) || fileName.isEmpty() ) {
                QMessageBox::critical(this, program+".error", err);
            }
        } else {
            //correct a false error message for ph-exec
            if(program!=QString("ph-exec")) {
                QMessageBox::critical(this, program+".error", err);
            }
        }
    }

    //pop up for the output
    if(!out.isEmpty()){
        QMessageBox::information(this, program+".output", out);
    }

}


void MainWindow::findFixpoints() {

    QString program = "ph-stable";
    QStringList arguments;

    // get the filename associated with the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0) {
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((MyArea*) subWindow->widget())->getPath();
    } else {
        fileName = "";
    }

    // give the arguments
    arguments << "--no-debug" << "-i" << fileName;

    // call MainWindow::compute
    this->compute(program, arguments, fileName);
}


// DOES NOT WORK for an unknown reason
// TODO make it work
void MainWindow::computeReachability() {

    QString program = "ph-reach";
    QStringList arguments;

    // get the filename associated with the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0){ // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((MyArea*) subWindow->widget())->getPath();
    } else {
        fileName = "";
    }

    //ask the user the state which is tested
    bool ok = false;
    QString state = QInputDialog::getText(this, "reachability", "Which state do you want to test ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !state.isEmpty()) {
        // give the arguments
        arguments << "--no-debug" << "-i" << fileName << state;
        //call MainWindow::compute
        this->compute(program, arguments);
    }
}


void MainWindow::runStochasticSimulation() {

    QString program = "ph-exec";
    QStringList arguments;

    // get the filename associated with the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0) { // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((MyArea*) subWindow->widget())->getPath();
    } else {
        fileName = "";
    }

    //ask the user for duration and output directory
    bool ok1 = false;
    QString duration = QInputDialog::getText(this, "stochastic simulation", "Give a duration", QLineEdit::Normal, QString(), &ok1);

    if(ok1 && !duration.isEmpty()) {
        QString outputdirectory = QFileDialog::getExistingDirectory(this, "output directory");

        if (!outputdirectory.isEmpty()) {
            // give the arguments
            arguments << "--no-debug" << "-i" << fileName << duration << outputdirectory;

            //call MainWindow::compute
            this->compute(program, arguments);
        }
    }
}


// NOT IMPLEMENTED!
// TODO implement it
void MainWindow::checkModelType(){
    QString program = "";
    QStringList arguments;
    arguments << "gruik" << "gruik";
    this->compute(program, arguments);
}


void MainWindow::statistics(){

    QString program = "ph-stat";
    QStringList arguments;

    // get the filename associated with the current subWindow
    // TODO factorize the following lines (present in every pint program execution method)
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0) { // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((MyArea*) subWindow->widget())->getPath();
    } else {
        fileName = "";
    }

    // give the arguments
    arguments << "--no-debug" << "-i" << fileName;

    // call MainWindow::compute
    this->compute(program, arguments);
}


// disable menus when no open, active tabs
void MainWindow::disableMenu(QMdiSubWindow* subwindow){
    if(subwindow==0&&this->getCentraleArea()->subWindowList().isEmpty()) {
        this->actionClose->setEnabled(false);
        this->actionSaveas->setEnabled(false);
        this->actionPng->setEnabled(false);
        this->actionDot->setEnabled(false);
        this->actionAdjust->setEnabled(false);
        this->actionZoomIn->setEnabled(false);
        this->actionZoomOut->setEnabled(false);
        this->actionBackgroundColor->setEnabled(false);
        this->actionSortColor->setEnabled(false);
        this->actionNaturalStyle->setEnabled(false);
        this->actionNegativeStyle->setEnabled(false);
        this->actionPrintStyle->setEnabled(false);
        this->actionHideShowText->setEnabled(false);
        this->actionChangeTextBackgroundColor->setEnabled(false);
        this->actionHideShowTree->setEnabled(false);
        this->actionFindFixpoints->setEnabled(false);
        this->actionComputeReachability->setEnabled(false);
        this->actionRunStochasticSimulation->setEnabled(false);
        this->actionStatistics->setEnabled(false);
    }
}


// enable menus when at least one open, active tab
void MainWindow::enableMenu(){
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        this->actionClose->setEnabled(true);
        this->actionSaveas->setEnabled(true);
        this->actionPng->setEnabled(true);
        this->actionDot->setEnabled(true);
        this->actionAdjust->setEnabled(true);
        this->actionZoomIn->setEnabled(true);
        this->actionZoomOut->setEnabled(true);
        this->actionBackgroundColor->setEnabled(true);
        this->actionSortColor->setEnabled(true);
        this->actionNaturalStyle->setEnabled(true);
        this->actionNegativeStyle->setEnabled(true);
        this->actionPrintStyle->setEnabled(true);
        this->actionHideShowText->setEnabled(true);
        this->actionChangeTextBackgroundColor->setEnabled(true);
        this->actionHideShowTree->setEnabled(true);
        this->actionFindFixpoints->setEnabled(true);
        this->actionComputeReachability->setEnabled(true);
        this->actionRunStochasticSimulation->setEnabled(true);
        this->actionStatistics->setEnabled(true);
    }
}

