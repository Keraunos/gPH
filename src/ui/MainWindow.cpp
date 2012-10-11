#include <QApplication>
#include <QtGui>
#include "MainWindow.h"
#include "MyArea.h"
#include "PHIO.h"
#include "Exceptions.h"

MainWindow::MainWindow() {

    //title
    setWindowTitle("gPH");

    //icone
    setWindowIcon(QIcon("gph.png"));

    // menu
    menuFile = menuBar()->addMenu("&File");
    menuEdit = menuBar()->addMenu("&Edit");
    menuView = menuBar()->addMenu("&View");
    menuComputation = menuBar()->addMenu("&Computation");
    menuHelp = menuBar()->addMenu("&Help");

    // actions for the menu

    // actions for the menu File
    actionNew = menuFile->addAction("New");
    actionOpen = menuFile->addAction("Open...");
    menuFile->addSeparator();
    actionSaveas = menuFile->addAction("Save as...");
    menuExport = menuFile->addMenu("Export");
    actionPng = menuExport->addAction("png");
    menuFile->addSeparator();
    actionClose = menuFile->addAction("Close");
    actionQuit = menuFile->addAction("Quit");

    //enable what does not work well
    actionNew->setEnabled(false);

    //Shortcuts for the menu File
    actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actionSaveas->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actionQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    // connect the menu File
    QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpen, SIGNAL(triggered()), this, SLOT(openTab()));
    QObject::connect(actionSaveas, SIGNAL(triggered()), this, SLOT(save()));
    QObject::connect(actionPng, SIGNAL(triggered()), this, SLOT(exportPng()));
    QObject::connect(actionClose, SIGNAL(triggered()), this, SLOT(closeTab()));

    // action for the menu Edit
    actionUndo = menuEdit->addAction("Undo");
    actionRedo = menuEdit->addAction("Redo");

    //enable what does not work well
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);

    // action for the menu View
    actionShowInit = menuView->addAction("Show initial state");
    actionHighlight = menuView->addAction("Highlight possible actions");
    actionHide = menuView->addAction("Hide actions");
    actionDisplayDetailed = menuView->addAction("Display detailed cooperativities");

    actionShowInit->setCheckable(true);
    actionHighlight->setCheckable(true);

    //enable what does not work
    actionShowInit->setEnabled(false);
    actionHighlight->setEnabled(false);
    actionHide->setEnabled(false);
    actionDisplayDetailed->setEnabled(false);

    // action for the menu Computation
    actionFindFixpoints = menuComputation->addAction("Find fixpoints...");
    actionComputeReachability = menuComputation->addAction("Compute reachability...");
    actionRunStochasticSimulation = menuComputation->addAction("Run stochastic simulation...");
    actionCheckModelType = menuComputation->addAction("Check model type (binary or multivalued)");
    actionStatistics = menuComputation->addAction("Statistics...");

    //enable what does not work well
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

    //enable what does not work well
    actionHelp->setEnabled(false);

    // main area
    this->centraleArea = new QMdiArea();
    setCentralWidget(centraleArea);
    centraleArea->setViewMode(QMdiArea::TabbedView);

    // management of the menu (enabled/disenabled)
    QObject::connect(this->centraleArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(disableMenu(QMdiSubWindow*)));

    if(this->getCentraleArea()->subWindowList().isEmpty()){
        this->actionClose->setEnabled(false);
        this->actionSaveas->setEnabled(false);
        this->actionPng->setEnabled(false);
        this->actionFindFixpoints->setEnabled(false);
        this->actionRunStochasticSimulation->setEnabled(false);
        this->actionStatistics->setEnabled(false);
    }
}

MainWindow::~MainWindow(){
    delete centraleArea;
}

QMdiArea* MainWindow::getCentraleArea(){
    return this->centraleArea;
}

//get all open files (with their path)
std::vector<QString> MainWindow::getAllPaths(){
    int size = this->getCentraleArea()->subWindowList().size();
    std::vector<QString> allPaths;
    QString path;
    for(int n=0;n<size;n++){
        path = ((MyArea*) this->getCentraleArea()->subWindowList()[n]->widget())->getPath();
        allPaths.push_back(path);
    }
    return allPaths;
}

//open a new tab
MyArea* MainWindow::openTab() {

        //OpenFile dialog
        QString fichier = QFileDialog::getOpenFileName(this, "Open...");

        if(fichier!=NULL){
            QFileInfo pathInfo(fichier);
            std::vector<QString >allPath = this->getAllPaths();
            int size = allPath.size();
            bool alreadyOpen = false;

            for(int i=0;i<size;i++){
                if(allPath[i]==fichier){
                   alreadyOpen = true;
                    break;
                }
            }

            if(!alreadyOpen){
                //need a std::string instead of a QString
                std::string path =	fichier.toStdString();

                //parseFile
                MyArea *area = new MyArea(fichier);
                try{
                    PHPtr myPHPtr=PHIO::parseFile(path);
                    area->setPHPtr(myPHPtr);
					myPHPtr->render();
                    PHScenePtr scene = myPHPtr->getGraphicsScene();
                    area->setScene(&*scene);

                    //make the subwindow for the new tab
                    QMdiSubWindow *theNewTab = this->getCentraleArea()->addSubWindow(area);
                    QString fileName(pathInfo.fileName() );
                    theNewTab->setWindowTitle(fileName);
                    this->enableMenu();

                    return area;
                } catch(exception_base& argh) {
                    QMessageBox::critical(this, "Error", "Extension not recognized. Only ph files are accepted.");
                    return NULL;
                }
            } else {
                QMessageBox::critical(this, "Error", "This file is already opened !");
                return NULL;}

        }
        else {return NULL;}
}

//close a tab
void MainWindow::closeTab(){
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        subWindow->close();

    } else {
        QMessageBox::critical(this, "Error", "No file opened !");
    }
}

void MainWindow::save(){
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        //SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Save file");

        //need a std::string instead of a QString
        std::string path =	fichier.toStdString();

        //need the PHPtr which is associated with the subwindow
        PHPtr ph= ((MyArea*) subWindow->widget())->getPHPtr();

        //writeToFile
        PHIO::writeToFile (path, ph);
    } else {
        QMessageBox::critical(this, "Error", "No file opened !");
    }
}

// export methods

void MainWindow::exportPng(){
	
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        //SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Export as .png file", QString(), "*.png");

        //need the PHPtr which is associated with the subwindow
        PHPtr ph= ((MyArea*) subWindow->widget())->getPHPtr();

        //need my png file nao !!!
		PHIO::exportToPNG(ph, fichier);
		
    } else QMessageBox::critical(this, "Error", "No file opened !");
	
}

// main method for the computation menu
void MainWindow::compute(QString program, QStringList arguments, QString fileName){
    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);

    if (!myProcess->waitForStarted())
        throw pint_program_not_found() << file_info("phc");

    //Read result
    QByteArray err;
    QByteArray out;
    while (!myProcess->waitForFinished()) {
        err += myProcess->readAllStandardError();
        out += myProcess->readAllStandardOutput();
    }
    err += myProcess->readAllStandardError();
    out += myProcess->readAllStandardOutput();
    delete myProcess;

    //pop up for the errors
    if(!err.isEmpty()){
        //correct a false error message for ph-stable
        if(program==QString("ph-stable")){
            if(!(QString(err).contains(fileName))||fileName.isEmpty()){
                QMessageBox::critical(this, program+".error", err);
            }
        } else {
            //correct a false error message for ph-exec
            if(program!=QString("ph-exec")){
                QMessageBox::critical(this, program+".error", err);
            }
        }
    }

    //pop up for the output
    if(!out.isEmpty()){
        QMessageBox::information(this, program+".output", out);
    }

}

void MainWindow::findFixpoints(){
    QString program = "ph-stable";
    QStringList arguments;

    // get the file name associated to the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0){ // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((MyArea*) subWindow->widget())->getPath();
    } else {
        fileName = "";
    }

    // give the arguments
    arguments << "--no-debug" << "-i" << fileName;

    //call MainWindow::compute
    this->compute(program, arguments, fileName);
}

//DO NOT WORK - and I don't know why, whyyyyyyyyy ???
void MainWindow::computeReachability(){
    QString program = "ph-reach";
    QStringList arguments;

    // get the file name associated to the current subWindow
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

void MainWindow::runStochasticSimulation(){
    QString program = "ph-exec";
    QStringList arguments;

    // get the file name associated to the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0){ // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((MyArea*) subWindow->widget())->getPath();
    } else {
        fileName = "";
    }
    //ask to the user duration and outputdirectory
    bool ok1 = false;
    QString duration = QInputDialog::getText(this, "stochastic simulation", "Give a duration", QLineEdit::Normal, QString(), &ok1);

    if(ok1 && !duration.isEmpty()){
        QString outputdirectory = QFileDialog::getExistingDirectory(this, "output directory");

        if (!outputdirectory.isEmpty()) {
            // give the arguments
            arguments << "--no-debug" << "-i" << fileName << duration << outputdirectory;

            //call MainWindow::compute
            this->compute(program, arguments);
        }
    }
}

void MainWindow::checkModelType(){
    QString program = "";
    QStringList arguments;
    arguments << "gruik" << "gruik";
    this->compute(program, arguments);
}

void MainWindow::statistics(){
    QString program = "ph-stat";
    QStringList arguments;

    // get the file name associated to the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0){ // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((MyArea*) subWindow->widget())->getPath();
    } else {
        fileName = "";
    }

    // give the arguments
    arguments << "--no-debug" << "-i" << fileName;

    //call MainWindow::compute
    this->compute(program, arguments);
}

void MainWindow::disableMenu(QMdiSubWindow* subwindow){
    if(subwindow==0&&this->getCentraleArea()->subWindowList().isEmpty()){
        this->actionClose->setEnabled(false);
        this->actionSaveas->setEnabled(false);
        this->actionPng->setEnabled(false);
        this->actionFindFixpoints->setEnabled(false);
        this->actionComputeReachability->setEnabled(false);
        this->actionRunStochasticSimulation->setEnabled(false);
        this->actionStatistics->setEnabled(false);
    }
}

void MainWindow::enableMenu(){
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        this->actionClose->setEnabled(true);
        this->actionSaveas->setEnabled(true);
        this->actionPng->setEnabled(true);
        this->actionFindFixpoints->setEnabled(true);
        this->actionRunStochasticSimulation->setEnabled(true);
        this->actionStatistics->setEnabled(true);
    }
}
