#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include "Area.h"
#include "TextArea.h"
#include "TreeArea.h"
#include "MyArea.h"
#include "MainWindow.h"

class Area : public QWidget
{
    Q_OBJECT
public:
    /**
      * @brief constructor for Area
      * @param QWidget parent, the widget containing the Area, which is the TabbedView
      *
      */
    explicit Area(QWidget *parent = 0);

    /**
      * @brief pointer to the MyArea
      *
      */
    MyArea *myArea;

    /**
      * @brief pointer to the TextArea;
      *
      */
    TextArea *textArea;

    /**
      * @brief pointer to the treeArea;
      *
      */
    TreeArea *treeArea;

    /**
      * @brief pointer to the MainWindow;
      *
      */
    MainWindow* mainWindow;

    /**
      * @brief hides the text. Called from a signal in MainWindow
      *
      */
    void hideText();

    /**
      * @brief shows the text. Called from a signal in MainWindow
      *
      */
    void showText();

    /**
      * @brief hides the text. Called from a signal in MainWindow
      *
      */
    void hideTree();

    /**
      * @brief shows the text. Called from a signal in MainWindow
      *
      */
    void showTree();



    QWidget* textButtonArea;
    QWidget* treeButtonArea;

    QPushButton* leftButton;
    QPushButton* rightButton;
    QPushButton* rightExpandButton;

signals:

public slots:



    /**
      * @brief method to hide or show the text area clicking on the button
      *
      */
    void hideOrShowText();

    /**
      * @brief method to expand or reduce the text area clicking on the button
      *
      */
    void expandOrReduceText();

    /**
      * @brief method to hide or show the text area clicking on the button
      *
      */
    void hideOrShowTree();

};

#endif // AREA_H
