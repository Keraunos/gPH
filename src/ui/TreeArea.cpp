#include "TreeArea.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

TreeArea::TreeArea(QWidget *parent): QWidget(parent)
{
    this->setMinimumWidth(250);
    this->setMaximumWidth(250);

    this->tree = new QTreeWidget(this);
    QPalette p = this->tree->palette();
    p.setColor(QPalette::Base, QColor(207, 226, 243));
    this->tree->setPalette(p);

    QWidget *search = new QWidget(this);
    search->setMinimumWidth(250);
    search->setMaximumWidth(250);
    search->setMinimumHeight(50);
    search->setMaximumHeight(50);
    this->searchBox = new QLineEdit(search);
    this->searchBox->setAlignment(Qt::AlignLeft);
    this->searchBox->setMinimumWidth(135);
    this->searchBox->setMaximumWidth(135);
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

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(this->tree);
    layout->addWidget(search);
    this->setLayout(layout);

    QObject::connect(this->searchButton, SIGNAL(clicked()), this, SLOT(searchSort()));
    QObject::connect(this->cancelSearchButton, SIGNAL(clicked()), this, SLOT(cancelSearch()));

}

void TreeArea::build(){

    list<SortPtr> allSorts = this->myPHPtr->getSorts();
    for(SortPtr &s : allSorts){
        QTreeWidgetItem* a = new QTreeWidgetItem(this->tree);
        a->setText(0, QString::fromStdString(s->getName()));
        this->sorts.push_back(a);
    }
}

void TreeArea::searchSort(){
    QString text = this->searchBox->text();

    QList<QTreeWidgetItem*> foundItems = this->tree->findItems("", Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems){
        q->setHidden(true);
    }

       //this->tree->hideColumn(0);
       //this->tree->hideColumn(1);

    QList<QTreeWidgetItem*> foundItems2 = this->tree->findItems(text, Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems2){
        q->setHidden(false);
    }

}

void TreeArea::cancelSearch(){
    QList<QTreeWidgetItem*> foundItems2 = this->tree->findItems("", Qt::MatchStartsWith, 0);
    for (QTreeWidgetItem* &q: foundItems2){
        q->setHidden(false);
    }
}
