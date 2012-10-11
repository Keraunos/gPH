#include <QApplication>
#include <QtGui>
#include "MainWindow.h"

#include <iostream>
#include "IO.h"
#include "GVGraph.h"
#include "PHIO.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();

}
