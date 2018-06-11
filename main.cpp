#include "mainwindow.h"
#include <QApplication>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
