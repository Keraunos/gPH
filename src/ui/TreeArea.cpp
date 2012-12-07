#include "TreeArea.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QErrorMessage>
#include <QMenu>

TreeArea::TreeArea(QWidget *parent): QWidget(parent)
{
    this->setMinimumWidth(250);
    this->setMaximumWidth(250);

    this->sortsTree = new QTreeWidget(this);
    this->sortsTree->setContextMenuPolicy(Qt::CustomContextMenu);
    this->sortsTree->setHeaderLabel("Sorts");
    this->sortsTree->setSelectionMode(QAbstractItemView::MultiSelection);
    QPalette p = this->sortsTree->palette();
    p.setColor(QPalette::Base, QColor(207, 226, 243));
    this->sortsTree->setPalette(p);

    QWidget *search = new QWidget(this);
    search->setMinimumWidth(250);
    search->setMaximumWidth(250);
    search->setMinimumHeight(50);
    search->setMaximumHeight(50);
    this->searchBox = new QLineEdit(search);
    this->searchBox->setAlignment(Qt::AlignLeft);
    this->searchBox->setMinimumWidth(125);
    this->searchBox->setMaximumWidth(125);
    this->searchBox->setMinimumHeight(30);
    this->searchBox->setMaximumHeight(30);
    this->searchButton = new QPushButton("Search", search);
    this->searchButton->setMinimumWidth(60);
    this->searchButton->setMaximumWidth(60);
    this->searchButton->setMinimumHeight(30);
    this->searchButton->setMaximumHeight(30);
    this->cancelSearchButton = new QPushButton("X", search);
    this->cancelSearchButton->setMinimumWidth(20);
    this->cancelSearchButton->setMaximumWidth(20);
    this->cancelSearchButton->setMinimumHeight(30);
    this->cancelSearchButton->setMaximumHeight(30);

    QHBoxLayout *layoutsearch = new QHBoxLayout;
    layoutsearch->addWidget(this->searchBox);
    layoutsearch->addWidget(this->searchButton);
    layoutsearch->addWidget(this->cancelSearchButton);
    search->setLayout(layoutsearch);

    QWidget *sortsToGroup = new QWidget(this);
    sortsToGroup->setMinimumWidth(250);
    sortsToGroup->setMaximumWidth(250);
    sortsToGroup->setMinimumHeight(50);
    sortsToGroup->setMaximumHeight(50);
    this->addToGroupButton = new QPushButton("Add to", sortsToGroup);
    this->addToGroupButton->setMinimumWidth(220);
    this->addToGroupButton->setMaximumWidth(220);
    this->addToGroupButton->setMinimumHeight(30);
    this->addToGroupButton->setMaximumHeight(30);

    QHBoxLayout *layoutSortsToGroup = new QHBoxLayout;
    layoutSortsToGroup->addWidget(this->addToGroupButton);
    sortsToGroup->setLayout(layoutSortsToGroup);

    QWidget *group = new QWidget(this);
    group->setMinimumWidth(250);
    group->setMaximumWidth(250);
    group->setMinimumHeight(50);
    group->setMaximumHeight(50);
    this->addGroupButton = new QPushButton("Add group", group);
    this->addGroupButton->setMinimumWidth(100);
    this->addGroupButton->setMaximumWidth(100);
    this->addGroupButton->setMinimumHeight(30);
    this->addGroupButton->setMaximumHeight(30);
    this->removeGroupButton = new QPushButton("Remove", group);
    this->removeGroupButton->setMinimumWidth(110);
    this->removeGroupButton->setMaximumWidth(110);
    this->removeGroupButton->setMinimumHeight(30);
    this->removeGroupButton->setMaximumHeight(30);

    QHBoxLayout *layoutGroup = new QHBoxLayout;
    layoutGroup->addWidget(this->addGroupButton);
    layoutGroup->addWidget(this->removeGroupButton);
    group->setLayout(layoutGroup);

    this->groupsTree = new QTreeWidget(this);
    this->groupsTree->setContextMenuPolicy(Qt::CustomContextMenu);
    this->groupsTree->setHeaderLabel("Groups");
    this->groupsTree->setSelectionMode(QAbstractItemView::SingleSelection);
    QPalette f = this->groupsTree->palette();
    f.setColor(QPalette::Base, QColor(207, 226, 243));
    this->groupsTree->setPalette(f);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(search);
    layout->addWidget(this->sortsTree);
    layout->addWidget(sortsToGroup);
    layout->addWidget(this->groupsTree);
    layout->addWidget(group);
    this->setLayout(layout);

    QObject::connect(this->searchButton, SIGNAL(clicked()), this, SLOT(searchSort()));
    QObject::connect(this->cancelSearchButton, SIGNAL(clicked()), this, SLOT(cancelSearch()));

    QObject::connect(this->addGroupButton, SIGNAL(clicked()), this, SLOT(addGroup()));
    QObject::connect(this->removeGroupButton, SIGNAL(clicked()), this, SLOT(remove()));
    QObject::connect(this->addToGroupButton, SIGNAL(clicked()), this, SLOT(addToGroup()));

    QObject::connect(this->sortsTree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(sortsItemClicked(const QPoint&)));
    QObject::connect(this->groupsTree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(groupsItemClicked(const QPoint&)));

}

void TreeArea::build(){
    // Get all the sorts of the PH file
    list<SortPtr> allSorts = this->myPHPtr->getSorts();
    for(SortPtr &s : allSorts){
        // Add a new item to the QTReeWidget, named after the sort
        QTreeWidgetItem* a = new QTreeWidgetItem(this->sortsTree);
        a->setText(0, QString::fromStdString(s->getName()));
        // Insert the item at the end of the attribute: sorts
        this->sorts.push_back(a);
    }
}

void TreeArea::searchSort(){
    //Get the text entered in the searchBox
    QString text = this->searchBox->text();

    // Hide all the items
    QList<QTreeWidgetItem*> foundItems = this->sortsTree->findItems("", Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems){
        q->setHidden(true);
    }

    // Find the items which names begin with the text entered in the searchBox
    QList<QTreeWidgetItem*> foundItems2 = this->sortsTree->findItems(text, Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems2){
        // Show those items
        q->setHidden(false);
    }

}

void TreeArea::cancelSearch(){
    // Get all the items
    QList<QTreeWidgetItem*> foundItems2 = this->sortsTree->findItems("", Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems2){
        // Show them all
        q->setHidden(false);
    }
}

void TreeArea::addGroup(){
    // Classic method to show a new window with a TextBox
    bool ok;
    QString text = QInputDialog::getText(this, "Add group...", "Name:", QLineEdit::Normal, QString::null, &ok).trimmed();
    // If the user entered a text
    if(ok && !text.isEmpty()){
        // Check that there isnt another group with the same name
        if (this->groupsTree->findItems(text, Qt::MatchExactly,0).isEmpty()){
            // Create a new item named after the text entered
            QTreeWidgetItem* a = new QTreeWidgetItem(this->groupsTree);
            a->setText(0, text);
            // Insert the item at the end of the attribute: groups
            this->groups.push_back(a);
        }
        else {
                QErrorMessage* nameError = new QErrorMessage(this);
                nameError->showMessage("Name already chosen.");
    }
    }

}

void TreeArea::remove(){
    // The way this method is done is weird, but it is the only way to do it properly
    // Select the current item
    QTreeWidgetItem* item = this->groupsTree->currentItem();
    // Put it at the top
    int i = this->groupsTree->indexOfTopLevelItem(item);
    // Select the item at the top
    this->groupsTree->takeTopLevelItem(i);
    // Delete it
    delete item;
}

// The exception doesn't work
void TreeArea::addToGroup(){
    // Check that at least one sort and one group are selected
    if(!this->sortsTree->selectedItems().isEmpty() && !this->groupsTree->selectedItems().isEmpty()){
        QList<QTreeWidgetItem*> selected = this->sortsTree->selectedItems();
        // counter for the exception. Does not work
        int i = 0;
        for (QTreeWidgetItem* &a: selected){
            if (this->groupsTree->findItems(a->text(0), Qt::MatchExactly | Qt::MatchRecursive, 0).isEmpty() == false){
                i++;
            }
        }
        if (i == 0){
            // for all the TreeWidgetItems that have been selected in the SortsTree
            for (QTreeWidgetItem* &a: selected){
                // Create a new item named after those item, whose parent is the groupsTree
                QTreeWidgetItem* b = new QTreeWidgetItem(this->groupsTree->currentItem());
                b->setText(0, a->text(0));
            }
        }
        else {
            QErrorMessage* nameError = new QErrorMessage(this);
            nameError->showMessage("At least one sort you selected is already in a group.");
        }
    }
    else {
        QErrorMessage* nameError = new QErrorMessage(this);
        nameError->showMessage("You must select one group and at least one sort.");
    }

}

void TreeArea::sortsItemClicked(const QPoint& pos){
        // Add a menu
        QMenu menu(this->sortsTree);
        // Add the actions to the menu
        QAction* actionHide = menu.addAction("Hide Sort");
        QAction* actionShow = menu.addAction("Show Sort");
        QAction* actionColor = menu.addAction("Change Sort Color");
        // Connect the actions created with their slots
        QObject::connect(actionHide, SIGNAL(triggered()), this, SLOT(hideSort()));
        QObject::connect(actionShow, SIGNAL(triggered()), this, SLOT(showSort()));
        QObject::connect(actionColor, SIGNAL(triggered()), this, SLOT(changeSortColor()));
        // Show the menu at the current position
        menu.exec(QCursor::pos());
}


void TreeArea::hideSort(){
    // Get the current item
    QTreeWidgetItem* item = this->sortsTree->currentItem();
    // Set the item font to italic
    QFont f = item->font(0);
    f.setItalic(true);
    item->setFont(0, f);

    // Get the name of the item
    QString text = item->text(0);

    // Set the italic font for the items related to the same sort in the groupsTree
    QList<QTreeWidgetItem*> sortsInTheGroupTree = this->groupsTree->findItems(text, Qt::MatchContains | Qt::MatchRecursive, 0);
    for (QTreeWidgetItem* &a: sortsInTheGroupTree){
        QFont b = a->font(0);
        b.setItalic(true);
        a->setFont(0,b);
    }

    // Find the sort with the same name that the selected QTreeWidgetItem
    SortPtr sortFound = this->myArea->getPHPtr()->getSort(text.toStdString());
    // Hide the QGraphicsItem representing the sort
    this->myPHPtr->getGraphicsScene()->getGSort(text.toStdString())->getDisplayItem()->hide();

    // Hide all the actions related to the sort
    std::vector<GActionPtr> allActions = this->myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){
        if (a->getAction()->getSource()->getSort()->getName() == text.toStdString() || a->getAction()->getTarget()->getSort()->getName() == text.toStdString() || a->getAction()->getResult()->getSort()->getName() == text.toStdString()){
            a->getDisplayItem()->hide();
        }
    }
}

void TreeArea::showSort(){
    // Get the current item
    QTreeWidgetItem* item = this->sortsTree->currentItem();

    // Set the item font to normal
    QFont f = item->font(0);
    f.setItalic(false);
    item->setFont(0, f);

    // Get the name of the item
    QString text = item->text(0);

    // Set the normal font for the items related to the same sort in the groupsTree
    QList<QTreeWidgetItem*> sortsInTheGroupTree = this->groupsTree->findItems(text, Qt::MatchContains | Qt::MatchRecursive, 0);
    for (QTreeWidgetItem* &a: sortsInTheGroupTree){
        QFont b = a->font(0);
        b.setItalic(false);
        a->setFont(0,b);
    }

    // Find the sort with the same name
    SortPtr sortFound = this->myArea->getPHPtr()->getSort(text.toStdString());
    // Show the QGraphicsItem representing the sort
    this->myPHPtr->getGraphicsScene()->getGSort(text.toStdString())->getDisplayItem()->show();

    std::vector<GActionPtr> allActions = this->myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){
        if (a->getAction()->getSource()->getSort()->getName() == text.toStdString() || a->getAction()->getTarget()->getSort()->getName() == text.toStdString() || a->getAction()->getResult()->getSort()->getName() == text.toStdString()){
            a->getDisplayItem()->show();
        }
    }

}

void TreeArea::changeSortColor(){
    // Get the current item
    QTreeWidgetItem* item = this->sortsTree->currentItem();
    // Get its name
    QString text = item->text(0);
    // Find the sort in the myArea that has the same name
    GSortPtr sortFound = this->myPHPtr->getGraphicsScene()->getGSort(text.toStdString());

    // Open the Color Dialog
    QColor couleur = QColorDialog::getColor();

    if (!couleur.isValid()) {
        return ;
    } else {
            // Set the color of the sort's rect item with the chosen color
            sortFound->getDisplayItem()->getRect()->setBrush(QBrush(QColor(couleur)));
    }

    // Set the color of the item in the sortsTree to the same color
    item->setForeground(0, QBrush(QColor(couleur)));

    // Set the same color for the items related to the same sort in the groupsTree
    QList<QTreeWidgetItem*> sortsInTheGroupTree = this->groupsTree->findItems(text, Qt::MatchContains | Qt::MatchRecursive, 0);
    for (QTreeWidgetItem* &a: sortsInTheGroupTree){
        a->setForeground(0, QBrush(QColor(couleur)));
    }
}

void TreeArea::groupsItemClicked(const QPoint& pos){
        // We assume that if the item clicked does not have any child, it is a group
        QTreeWidgetItem* item = this->groupsTree->currentItem();
        if (item->childCount() != 0){
            // Add a menu
            QMenu menu(this->groupsTree);
            // Add the actions to the menu
            QAction* actionHide = menu.addAction("Hide Group");
            QAction* actionShow = menu.addAction("Show Group");
            QAction* actionColor = menu.addAction("Change Group Color");
            // Connect the actions created with their slots
            QObject::connect(actionHide, SIGNAL(triggered()), this, SLOT(hideGroup()));
            QObject::connect(actionShow, SIGNAL(triggered()), this, SLOT(showGroup()));
            QObject::connect(actionColor, SIGNAL(triggered()), this, SLOT(changeGroupColor()));
            // Show the menu at the current position
            menu.exec(QCursor::pos());
        }
        else {
            // Add a menu
            QMenu menu(this->groupsTree);
            // Add the actions to the menu
            QAction* actionHide = menu.addAction("Hide Sort");
            QAction* actionShow = menu.addAction("Show Sort");
            QAction* actionColor = menu.addAction("Change Sort Color");
            // Connect the actions created with their slots
            QObject::connect(actionHide, SIGNAL(triggered()), this, SLOT(hideSortFromGroup()));
            QObject::connect(actionShow, SIGNAL(triggered()), this, SLOT(showSortFromGroup()));
            QObject::connect(actionColor, SIGNAL(triggered()), this, SLOT(changeSortColorFromGroup()));
            // Show the menu at the current position
            menu.exec(QCursor::pos());
        }

}

void TreeArea::showGroup(){
    // Get the current item
    QTreeWidgetItem* item = this->groupsTree->currentItem();
    // Get all the items of the tree
    QList<QTreeWidgetItem*> wholeTree = this->groupsTree->findItems("", Qt::MatchContains | Qt::MatchRecursive, 0);
    // Get all the items in the tree whose parent is the current item
    if (item->childCount() != 0){
        for (QTreeWidgetItem* &a: wholeTree){
            if (a->parent() == item){
                // Show the GraphicsItem
                this->myPHPtr->getGraphicsScene()->getGSort(a->text(0).toStdString())->getDisplayItem()->show();
                // Set the font to Normal
                QFont f = a->font(0);
                f.setItalic(false);
                a->setFont(0, f);

                // Set the italic font for the items related to the same sort in the sortsTree
                QList<QTreeWidgetItem*> sortsInTheSortsTree = this->sortsTree->findItems(a->text(0), Qt::MatchExactly, 0);
                for (QTreeWidgetItem* &a: sortsInTheSortsTree){
                    QFont b = a->font(0);
                    b.setItalic(false);
                    a->setFont(0,b);
                }
            }
      }
    }

    // Set the group font to italic
    QFont f = item->font(0);
    f.setItalic(false);
    item->setFont(0, f);

}

void TreeArea::hideGroup(){
    // Get the current item
    QTreeWidgetItem* item = this->groupsTree->currentItem();
    // Get all the items of the tree
    QList<QTreeWidgetItem*> wholeTree = this->groupsTree->findItems("", Qt::MatchContains | Qt::MatchRecursive, 0);
    // Get all the items in the tree whose parent is the current item
    if (item->childCount() != 0){
        for (QTreeWidgetItem* &a: wholeTree){
                if (a->parent() == item){
                    // Hide the GraphicsItem
                    this->myPHPtr->getGraphicsScene()->getGSort(a->text(0).toStdString())->getDisplayItem()->hide();
                    // Set the font to Italic
                    QFont f = a->font(0);
                    f.setItalic(true);
                    a->setFont(0, f);

                    // Set the italic font for the items related to the same sort in the sortsTree
                    QList<QTreeWidgetItem*> sortsInTheSortsTree = this->sortsTree->findItems(a->text(0), Qt::MatchExactly, 0);
                    for (QTreeWidgetItem* &a: sortsInTheSortsTree){
                        QFont b = a->font(0);
                        b.setItalic(true);
                        a->setFont(0,b);
                    }
                }
          }


        // Set the group font to italic
        QFont f = item->font(0);
        f.setItalic(true);
        item->setFont(0, f);
    }
}

void TreeArea::changeGroupColor(){
    QColor couleur = QColorDialog::getColor();
    // Get the current item
    QTreeWidgetItem* item = this->groupsTree->currentItem();
    // Get all the items of the tree
    QList<QTreeWidgetItem*> wholeTree = this->groupsTree->findItems("", Qt::MatchContains | Qt::MatchRecursive, 0);
    if (item->childCount() != 0){
        if (!couleur.isValid()) {
            return ;
        } else {
            for (QTreeWidgetItem* &a: wholeTree){
                // If the sort is in the group, change rect color
                if (a->parent() == item){
                    GSortPtr sortFound = this->myPHPtr->getGraphicsScene()->getGSort(a->text(0).toStdString());

                    QPen p;
                    p.setBrush(QBrush(QColor(couleur)));
                    //sortFound->getRect()->setPen(p);
                }
            }

                // Set the color of the item in the sortsTree to the same color
                item->setForeground(0, QBrush(QColor(couleur)));
        }
    }

}

void TreeArea::hideSortFromGroup(){
    // Get the current item
    QTreeWidgetItem* item = this->groupsTree->currentItem();
    // Set the item font to italic
    QFont f = item->font(0);
    f.setItalic(true);
    item->setFont(0, f);

    // Get the name of the item
    QString text = item->text(0);

    // Set the italic font for the items related to the same sort in the sortsTree
    QList<QTreeWidgetItem*> sortsInTheSortsTree = this->sortsTree->findItems(text, Qt::MatchExactly, 0);
    for (QTreeWidgetItem* &a: sortsInTheSortsTree){
        QFont b = a->font(0);
        b.setItalic(true);
        a->setFont(0,b);
    }

    // Find the sort with the same name that the selected QTreeWidgetItem
    SortPtr sortFound = this->myArea->getPHPtr()->getSort(text.toStdString());
    // Hide the QGraphicsItem representing the sort
    this->myPHPtr->getGraphicsScene()->getGSort(text.toStdString())->getDisplayItem()->hide();

    // Hide all the actions related to the sort
    std::vector<GActionPtr> allActions = this->myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){
        if (a->getAction()->getSource()->getSort()->getName() == text.toStdString() || a->getAction()->getTarget()->getSort()->getName() == text.toStdString() || a->getAction()->getResult()->getSort()->getName() == text.toStdString()){
            a->getDisplayItem()->hide();
        }
    }

}

void TreeArea::showSortFromGroup(){
    // Get the current item
    QTreeWidgetItem* item = this->groupsTree->currentItem();

    // Set the item font to normal
    QFont f = item->font(0);
    f.setItalic(false);
    item->setFont(0, f);

    // Get the name of the item
    QString text = item->text(0);

    // Set the normal font for the items related to the same sort in the sortsTree
    QList<QTreeWidgetItem*> sortsInTheSortsTree = this->sortsTree->findItems(text, Qt::MatchExactly, 0);
    for (QTreeWidgetItem* &a: sortsInTheSortsTree){
        QFont b = a->font(0);
        b.setItalic(false);
        a->setFont(0,b);
    }

    // Find the sort with the same name
    SortPtr sortFound = this->myArea->getPHPtr()->getSort(text.toStdString());
    // Show the QGraphicsItem representing the sort
    this->myPHPtr->getGraphicsScene()->getGSort(text.toStdString())->getDisplayItem()->show();

    // Show all the actions related to the sort
    std::vector<GActionPtr> allActions = this->myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){
        if (a->getAction()->getSource()->getSort()->getName() == text.toStdString() || a->getAction()->getTarget()->getSort()->getName() == text.toStdString() || a->getAction()->getResult()->getSort()->getName() == text.toStdString()){
            a->getDisplayItem()->show();
        }
    }

}

void TreeArea::changeSortColorFromGroup(){
    // Get the current item
    QTreeWidgetItem* item = this->groupsTree->currentItem();
    // Get its name
    QString text = item->text(0);
    // Find the sort in the myArea that has the same name
    GSortPtr sortFound = this->myPHPtr->getGraphicsScene()->getGSort(text.toStdString());

    // Open the Color Dialog
    QColor couleur = QColorDialog::getColor();

    if (!couleur.isValid()) {
        return ;
    } else {
            // Set the color of the sort's rect item with the chosen color
            sortFound->getDisplayItem()->getRect()->setBrush(QBrush(QColor(couleur)));
    }

    // Set the color of the item in the sortsTree to the same color
    item->setForeground(0, QBrush(QColor(couleur)));

    // Set the same color for the items related to the same sort in the sortsTree
    QList<QTreeWidgetItem*> sortsInTheSortsTree = this->sortsTree->findItems(text, Qt::MatchExactly, 0);
    for (QTreeWidgetItem* &a: sortsInTheSortsTree){
        a->setForeground(0, QBrush(QColor(couleur)));
    }
}

