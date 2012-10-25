#pragma once
#include <QMainWindow>
#include "MyArea.h"

/**
  * @file MainWindow.h
  * @brief header for the MainWindow class
  * @author PAPPL_2012
  *
  */


/**
  * @class MainWindow
  * @brief Builds the main window of the program
    extends from QMainWindow
  *
  */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    /**
      * @brief constructor for MainWindow, creates the window, the menus and initializes the characteristics
      *
      */
    MainWindow();
    ~MainWindow();

    /**
      * @brief getter for CentraleArea
      *
      * @return a QMdiArea* pointer to the centrale zone of the window
      *
      */
    QMdiArea* getCentraleArea();

    /**
      * @brief gets all the paths of the PH files already opened
      *
      */
    std::vector<QString> getAllPaths();

    //method for the menu computation

    /**
      * @brief calls the pint function with the arguments chosen
      *
      * @param Qstring the program chosen
      * @param QStringList the arguments chosen
      * @param QString the name of the file (optionnal)
      *
      */
    void compute(QString program, QStringList arguments, QString fileName="");

    //enableMenu (in relation with the slot disableMenu)
    /**
      * @brief activates the menus that need a open an active tab
      *
      */
    void enableMenu();

protected:

    /**
      * @brief pointer to the centrale area of the window
      *
      */
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

    /**
      * @brief open a new tab
      *
      * @return a pointer to a MyArea newly created
      *
      */
    MyArea* openTab();

    /**
      * @brief save the file
      *
      */
    void save();

    /**
      * @brief close the active tab
      *
      */
    void closeTab();

    /**
      * @brief export the actual view to PNG file
      *
      */
    void exportPng();

    //menu computation

    /**
      * @brief calls ph-stable functionality of pint
      *
      */
    void findFixpoints();

    /**
      * @brief calls ph-reach functionality of pint
      *
      */
    void computeReachability();

    /**
      * @brief calls ph-exec functionality of pint
      *
      */
    void runStochasticSimulation();

    /**
      * @brief checks the type of the model
      *
      */
    void checkModelType();

    /**
      * @brief calls ph-stat functionality of pint
      *
      */
    void statistics();

    /**
      * @brief permits to disable a menu
      *
      * @param QMdiSubWindow* menu you want to disable
      *
      */
    void disableMenu(QMdiSubWindow* subWindow);
};
