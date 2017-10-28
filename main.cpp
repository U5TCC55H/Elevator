#include "mainwindow.h"
#include <QApplication>

#include <stdlib.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Simulation s;
    w.setSimulation(s);

    return a.exec();
}
