#include "Area.h"
#include "QHBoxLayout"

Area::Area(QWidget *parent) :
    QWidget(parent)
{
    this->textArea = new TextArea(this);
    this->textArea->setReadOnly(true);
    this->myArea = new MyArea(this, "");
    this->treeArea = new TreeArea(this);

    this->treeButtonArea = new QWidget(this);
    this->treeButtonArea->setMinimumWidth(12);
    this->treeButtonArea->setMaximumWidth(12);
    this->textButtonArea = new QWidget(this);
    this->textButtonArea->setMinimumWidth(12);
    this->textButtonArea->setMaximumWidth(12);

    this->leftButton = new QPushButton("<", this->treeButtonArea);
    this->leftButton->setMaximumWidth(12);
    this->leftButton->setMinimumHeight(70);

    this->rightButton = new QPushButton(">", this->textButtonArea);
    this->rightButton->setMaximumWidth(12);
    this->rightButton->setMinimumHeight(70);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(this->treeArea);
    layout->addWidget(this->treeButtonArea);
    layout->addWidget(this->myArea);
    layout->addWidget(this->textButtonArea);
    layout->addWidget(this->textArea);
    this->setLayout(layout);

    QObject::connect(this->leftButton, SIGNAL(clicked()), this, SLOT(hideOrShowTree()));
    QObject::connect(this->rightButton, SIGNAL(clicked()), this, SLOT(hideOrShowText()));
}

void Area::hideText(){
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->textArea->hide();
    }
}

void Area::showText(){
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->textArea->show();
    }
}

void Area::hideTree(){
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->treeArea->hide();
    }
}

void Area::showTree(){
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->treeArea->show();
    }
}

void Area::hideOrShowTree(){
    if(!this->treeArea->isHidden()){
        this->hideTree();
        this->leftButton->setText(">");
    }
    else  {
        this->showTree();
        this->leftButton->setText("<");
    }
}

void Area::hideOrShowText(){
    if(!this->textArea->isHidden()){
        this->hideText();
        this->rightButton->setText("<");
    }
    else {
        this->showText();
        this->rightButton->setText(">");
    }
}
