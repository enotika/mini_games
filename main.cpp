#include "mainwindow.h"
#include "minor.h"
#include "findpair.h"
#include "startwindow.h"

#include <tetris.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;
    w.show();
    return a.exec();
}
