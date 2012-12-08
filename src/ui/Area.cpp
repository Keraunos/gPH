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
    QVBoxLayout *layoutLeft = new QVBoxLayout;
    layoutLeft->addWidget(leftButton);
    layoutLeft->setContentsMargins(0,0,0,0);
    this->treeButtonArea->setLayout(layoutLeft);

    this->rightButton = new QPushButton(">", this->textButtonArea);
    this->rightButton->setMaximumWidth(12);
    this->rightButton->setMinimumHeight(70);
    this->rightExpandButton = new QPushButton("<", this->textButtonArea);
    this->rightExpandButton->setMaximumWidth(12);
    this->rightExpandButton->setMinimumHeight(70);
    QVBoxLayout *layoutRight = new QVBoxLayout;
    layoutRight->addWidget(this->rightButton);
    layoutRight->addWidget(this->rightExpandButton);
    layoutRight->setContentsMargins(0,0,0,0);
    this->textButtonArea->setLayout(layoutRight);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(this->treeArea);
    layout->addWidget(this->treeButtonArea);
    layout->addWidget(this->myArea);
    layout->addWidget(this->textButtonArea);
    layout->addWidget(this->textArea);
    this->setLayout(layout);

    QObject::connect(this->leftButton, SIGNAL(clicked()), this, SLOT(hideOrShowTree()));
    QObject::connect(this->rightButton, SIGNAL(clicked()), this, SLOT(hideOrShowText()));
    QObject::connect(this->rightExpandButton, SIGNAL(clicked()), this, SLOT(expandOrReduceText()));
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
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    if(!this->treeArea->isHidden()){
        for (QMdiSubWindow* &a: tabs){
            ((Area*)a->widget())->hideTree();
            ((Area*)a->widget())->leftButton->setText(">");
        }
    }
    else  {
        for (QMdiSubWindow* &a: tabs){
            ((Area*)a->widget())->showTree();
            ((Area*)a->widget())->leftButton->setText("<");
        }
    }
}

void Area::hideOrShowText(){
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    if(!this->textArea->isHidden()){
        for (QMdiSubWindow* &a: tabs){
            ((Area*)a->widget())->hideText();
            ((Area*)a->widget())->rightButton->setText("<");
            ((Area*)a->widget())->rightExpandButton->hide();
        }
    }
    else {
        for (QMdiSubWindow* &a: tabs){
            ((Area*)a->widget())->showText();
            ((Area*)a->widget())->rightButton->setText(">");
            ((Area*)a->widget())->rightExpandButton->show();
        }
    }
}

void Area::expandOrReduceText(){
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    if (this->textArea->maximumWidth() == 200){
        for (QMdiSubWindow* &a: tabs){
            ((Area*)a->widget())->textArea->setMaximumWidth(500);
            ((Area*)a->widget())->textArea->setMinimumWidth(500);
            ((Area*)a->widget())->rightButton->hide();
            ((Area*)a->widget())->rightExpandButton->setText(">");
        }
    }
    else {
        for (QMdiSubWindow* &a: tabs){
            ((Area*)a->widget())->textArea->setMaximumWidth(200);
            ((Area*)a->widget())->textArea->setMinimumWidth(200);
            ((Area*)a->widget())->rightButton->show();
            ((Area*)a->widget())->rightExpandButton->setText("<");
        }
    }
}
