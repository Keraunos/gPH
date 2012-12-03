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
      * @brief pointer to the sorts QTreeWidget
      *
      */
    QTreeWidget* sortsTree;

    /**
      * @brief pointer to the groups QTreeWidget
      *
      */
    QTreeWidget* groupsTree;

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
      * @brief pointer to the addToGroup button
      *
      */
    QPushButton* addToGroupButton;

    /**
      * @brief pointer to the removeGroup button
      *
      */
    QPushButton* removeGroupButton;

    /**
      * @brief pointer to the addGroup button
      *
      */
    QPushButton* addGroupButton;

    /**
      * @brief list containing all the sorts. Built when the file is opened
      *
      */
    QList<QTreeWidgetItem*> sorts;

    /**
      * @brief list containing all the groups.
      *
      */
    QList<QTreeWidgetItem*> groups;

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

    /**
      * @brief cancel the search of the sort. Shows all the items in the tree
      *
      */
    void cancelSearch();

    /**
      * @brief add a group to the groupsTree
      *
      */
    void addGroup();

    /**
      * @brief remove the selected group from the groupsTree
      *
      */
    void remove();

    /**
      * @brief add a sort to a selected group
      *
      */
    void addToGroup();




};

#endif // TREEAREA_H
