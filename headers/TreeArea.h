#ifndef TREEAREA_H
#define TREEAREA_H

#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QLineEdit>
#include "PH.h"

class TreeArea : public QWidget
{
    Q_OBJECT
public:

    /**
      * @brief constructor
      * @brief QWidget parent, the widget containing the TextArea, which is the Area
      *
      */
    TreeArea(QWidget *parent);

    /**
      * @brief pointer to the PH
      *
      */
    PHPtr myPHPtr;

    /**
      * @brief pointer to the QTreeWidget
      *
      */
    QTreeWidget* tree;

    /**
      * @brief pointer to the search button
      *
      */
    QPushButton* searchButton;

    /**
      * @brief pointer to the cancelSearch button
      *
      */
    QPushButton* cancelSearchButton;

    /**
      * @brief pointer to the search line edit
      *
      */
    QLineEdit* searchBox;

    /**
      * @brief pointer to the TreeWidgetItem father of all the sorts
      *
      */
    QTreeWidgetItem* sortsFather;

    /**
      * @brief pointer to the TreeWidgetItem father of all the groups
      *
      */
    QTreeWidgetItem* groupsFather;

    /**
      * @brief list containing all the sorts. Built when the file is opened
      *
      */
    QList<QTreeWidgetItem*> sorts;

signals:

public slots:

    /**
      * @brief build the base tree. Called on opening
      *
      */
    void build();

    /**
      * @brief search a sort. Slot linked with the search button signal
      *
      */
    void searchSort();

};

#endif // TREEAREA_H
