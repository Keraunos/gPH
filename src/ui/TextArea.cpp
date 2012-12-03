#include "TextArea.h"

TextArea::TextArea(QWidget *parent) :
    QTextEdit(parent)
{
 this->setMinimumWidth(200);
 this->setMaximumWidth(200);

    QPalette p = this->palette();
    p.setColor(QPalette::Base, QColor(194, 132, 160));
    this->setPalette(p);
    this->setCurrentFont(QFont("TypeWriter", 10));
    this->setTextColor(QColor("white"));

}

void TextArea::changeBackgroundColor(QColor color){
    QPalette p = this->palette();
    p.setColor(QPalette::Base, color);
    this->setPalette(p);
}
