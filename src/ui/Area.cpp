#include "Area.h"
#include "QHBoxLayout"

Area::Area(QWidget *parent) :
    QWidget(parent)
{
    // call the constructors of all the areas
    this->textArea = new TextArea(this);
    this->textArea->setReadOnly(true);
    this->myArea = new MyArea(this, "");
    this->treeArea = new TreeArea(this);

    // treeArea: create widgets containing the buttons
    this->treeButtonArea = new QWidget(this);
    this->treeButtonArea->setMinimumWidth(12);
    this->treeButtonArea->setMaximumWidth(12);
    this->textButtonArea = new QWidget(this);
    this->textButtonArea->setMinimumWidth(12);
    this->textButtonArea->setMaximumWidth(12);

    // create the buttons
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

    // set the global layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(this->treeArea);
    layout->addWidget(this->treeButtonArea);
    layout->addWidget(this->myArea);
    layout->addWidget(this->textButtonArea);
    layout->addWidget(this->textArea);
    this->setLayout(layout);

    // connect
    QObject::connect(this->leftButton, SIGNAL(clicked()), this, SLOT(hideOrShowTree()));
    QObject::connect(this->rightButton, SIGNAL(clicked()), this, SLOT(hideOrShowText()));
    QObject::connect(this->rightExpandButton, SIGNAL(clicked()), this, SLOT(expandOrReduceText()));
}

void Area::hideText(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // hide all the textAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->textArea->hide();
    }
}

void Area::showText(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // show all the textAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->textArea->show();
    }
}

void Area::hideTree(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // hide all the treeAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->treeArea->hide();
    }
}

void Area::showTree(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // show all the treeAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->treeArea->show();
    }
}

void Area::hideOrShowTree(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // if the current treeArea is hidden, all are hidden
    if(!this->treeArea->isHidden()){
        for (QMdiSubWindow* &a: tabs){
            // hide all the trees
            ((Area*)a->widget())->hideTree();
            // change the button
            ((Area*)a->widget())->leftButton->setText(">");
        }
    }
    else  {
        for (QMdiSubWindow* &a: tabs){
            // show all the trees
            ((Area*)a->widget())->showTree();
            // change the button
            ((Area*)a->widget())->leftButton->setText("<");
        }
    }
}

void Area::hideOrShowText(){
    // get all the subwindows in the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    if(!this->textArea->isHidden()){
        // if the current text area is hidden, all are hidden
        for (QMdiSubWindow* &a: tabs){
            // hide all the textAreas
            ((Area*)a->widget())->hideText();
            // change the button
            ((Area*)a->widget())->rightButton->setText("<");
            // hide the button to expand
            ((Area*)a->widget())->rightExpandButton->hide();
        }
    }
    else {
        for (QMdiSubWindow* &a: tabs){
            //show all the treeAreas
            ((Area*)a->widget())->showText();
            // change the button
            ((Area*)a->widget())->rightButton->setText(">");
            // show the button to expand
            ((Area*)a->widget())->rightExpandButton->show();
        }
    }
}

void Area::expandOrReduceText(){
    // get all the subwindows in the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    if (this->textArea->maximumWidth() == 200){
        // if this subwindow is not expanded
        for (QMdiSubWindow* &a: tabs){
            // expand it
            ((Area*)a->widget())->textArea->setMaximumWidth(500);
            ((Area*)a->widget())->textArea->setMinimumWidth(500);
            // hide the button to hide
            ((Area*)a->widget())->rightButton->hide();
            // change the button
            ((Area*)a->widget())->rightExpandButton->setText(">");
        }
    }
    else {
        for (QMdiSubWindow* &a: tabs){
            // reduce it
            ((Area*)a->widget())->textArea->setMaximumWidth(200);
            ((Area*)a->widget())->textArea->setMinimumWidth(200);
            // show the button to hide
            ((Area*)a->widget())->rightButton->show();
            // change the button
            ((Area*)a->widget())->rightExpandButton->setText("<");
        }
    }
}
