#include "mainwindow.h"
#include "minor.h"
#include "findpair.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    minor w;
    w.show();
    return a.exec();
}
