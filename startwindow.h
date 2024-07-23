#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "tetris.h"
#include "mainwindow.h"
#include "minor.h"
#include "findpair.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_findPairButton_clicked();

    void on_tetrisButton_clicked();

    void on_minorButton_clicked();

    void on_snakeButton_clicked();

private:
    Ui::StartWindow *ui;
    Tetris * tetrisWindow;
    MainWindow * snakeWindow;
    minor * minorWindow;
    FindPair * findPairWindow;
};

#endif // STARTWINDOW_H
