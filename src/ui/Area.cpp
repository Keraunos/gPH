#include "Area.h"
#include "QHBoxLayout"

Area::Area(QWidget *parent) :
    QWidget(parent)
{
    this->textArea = new TextArea(this);
    this->textArea->setReadOnly(true);
    this->myArea = new MyArea(this, "");
    this->treeArea = new TreeArea(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(this->treeArea);
    layout->addWidget(this->myArea);
    layout->addWidget(this->textArea);
    this->setLayout(layout);
}

void Area::hideText(){
    this->textArea->hide();
}

void Area::showText(){
    this->textArea->show();
}

void Area::hideTree(){
    this->treeArea->hide();
}

void Area::showTree(){
    this->treeArea->show();
}
