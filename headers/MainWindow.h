#pragma once
#include <QMainWindow>
#include "MyArea.h"

/**
  * @file MainWindow.h
  * @brief header for the MainWindow class
  * @author PAPPL_2012
  *
  */


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    QMdiArea* getCentraleArea();
    std::vector<QString> getAllPaths();

    //method for the menu computation
    void compute(QString program, QStringList arguments, QString fileName="");

    //enableMenu (in relation with the slot disableMenu)
    void enableMenu();

protected:
    QMdiArea* centraleArea;

    // QMenu
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuComputation;
    QMenu *menuHelp;

    // actions for the menu File
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSaveas;
    QMenu *menuExport;
    QAction *actionPng;
    QAction *actionClose;
    QAction *actionQuit;

    // action for the menu Edit
    QAction *actionUndo;
    QAction *actionRedo;

    // action for the menu View
    QAction *actionShowInit;
    QAction *actionHighlight;
    QAction *actionHide;
    QAction *actionDisplayDetailed;

    // action for the menu Computation
    QAction *actionFindFixpoints;
    QAction *actionComputeReachability;
    QAction *actionRunStochasticSimulation;
    QAction *actionCheckModelType;
    QAction *actionStatistics;

    // action for the menu Help
    QAction *actionHelp;

signals:

public slots:
    //menu file
    MyArea* openTab();
    void save();
    void closeTab();

    void exportPng();

    //menu computation
    void findFixpoints();
    void computeReachability();
    void runStochasticSimulation();
    void checkModelType();
    void statistics();

    void disableMenu(QMdiSubWindow* subWindow);
};
