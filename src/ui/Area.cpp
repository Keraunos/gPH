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
