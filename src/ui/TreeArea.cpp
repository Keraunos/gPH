#include "TreeArea.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QErrorMessage>

TreeArea::TreeArea(QWidget *parent): QWidget(parent)
{
    this->setMinimumWidth(250);
    this->setMaximumWidth(250);

    this->sortsTree = new QTreeWidget(this);
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
    this->addToGroupButton = new QPushButton("v Add to", sortsToGroup);
    this->addToGroupButton->setMinimumWidth(100);
    this->addToGroupButton->setMaximumWidth(100);
    this->addToGroupButton->setMinimumHeight(30);
    this->addToGroupButton->setMaximumHeight(30);
    this->removeFromGroupButton = new QPushButton("Remove from ^", sortsToGroup);
    this->removeFromGroupButton->setMinimumWidth(110);
    this->removeFromGroupButton->setMaximumWidth(110);
    this->removeFromGroupButton->setMinimumHeight(30);
    this->removeFromGroupButton->setMaximumHeight(30);

    QHBoxLayout *layoutSortsToGroup = new QHBoxLayout;
    layoutSortsToGroup->addWidget(this->addToGroupButton);
    layoutSortsToGroup->addWidget(this->removeFromGroupButton);
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
    this->removeGroupButton = new QPushButton("Remove group", group);
    this->removeGroupButton->setMinimumWidth(110);
    this->removeGroupButton->setMaximumWidth(110);
    this->removeGroupButton->setMinimumHeight(30);
    this->removeGroupButton->setMaximumHeight(30);

    QHBoxLayout *layoutGroup = new QHBoxLayout;
    layoutGroup->addWidget(this->addGroupButton);
    layoutGroup->addWidget(this->removeGroupButton);
    group->setLayout(layoutGroup);

    this->groupsTree = new QTreeWidget(this);
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
    QObject::connect(this->removeGroupButton, SIGNAL(clicked()), this, SLOT(removeGroup()));
    QObject::connect(this->addToGroupButton, SIGNAL(clicked()), this, SLOT(addToGroup()));

}

void TreeArea::build(){

    list<SortPtr> allSorts = this->myPHPtr->getSorts();
    for(SortPtr &s : allSorts){
        QTreeWidgetItem* a = new QTreeWidgetItem(this->sortsTree);
        a->setText(0, QString::fromStdString(s->getName()));
        this->sorts.push_back(a);
    }
}

void TreeArea::searchSort(){
    QString text = this->searchBox->text();

    QList<QTreeWidgetItem*> foundItems = this->sortsTree->findItems("", Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems){
        q->setHidden(true);
    }

       //this->tree->hideColumn(0);
       //this->tree->hideColumn(1);

    QList<QTreeWidgetItem*> foundItems2 = this->sortsTree->findItems(text, Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems2){
        q->setHidden(false);
    }

}

void TreeArea::cancelSearch(){
    QList<QTreeWidgetItem*> foundItems2 = this->sortsTree->findItems("", Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems2){
        q->setHidden(false);
    }
}

void TreeArea::addGroup(){
    bool ok;
    QString text = QInputDialog::getText(this, "Add group...", "Name:", QLineEdit::Normal, QString::null, &ok);
    if(ok && !text.isEmpty()){
        if (this->groupsTree->findItems(text, Qt::MatchExactly,0).isEmpty()){
            QTreeWidgetItem* a = new QTreeWidgetItem(this->groupsTree);
            a->setText(0, text);
            this->groups.push_back(a);
        }
        else {
                QErrorMessage* nameError = new QErrorMessage(this);
                nameError->showMessage("Name already chosen.");
    }
    }

}

void TreeArea::removeGroup(){
    QTreeWidgetItem* item = this->groupsTree->currentItem();
    int i = this->groupsTree->indexOfTopLevelItem(item);
    this->groupsTree->takeTopLevelItem(i);
    delete item;
}

// The exception doesn't work
void TreeArea::addToGroup(){
    if(!this->sortsTree->selectedItems().isEmpty() && !this->groupsTree->selectedItems().isEmpty()){
        QList<QTreeWidgetItem*> selected = this->sortsTree->selectedItems();
        int i = 0;
        for (QTreeWidgetItem* &a: selected){
            if (this->groupsTree->findItems(a->text(0), Qt::MatchExactly, 0).isEmpty() == false){
                i++;
            }
        }
        if (i == 0){
            for (QTreeWidgetItem* &a: selected){
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

