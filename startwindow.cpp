#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    tetrisWindow = new Tetris();
    snakeWindow = new MainWindow();
    minorWindow = new minor();
    findPairWindow = new FindPair();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_findPairButton_clicked()
{
    findPairWindow->show();
}


void StartWindow::on_tetrisButton_clicked()
{
    tetrisWindow->show();
}


void StartWindow::on_minorButton_clicked()
{
    minorWindow->show();
}


void StartWindow::on_snakeButton_clicked()
{
    snakeWindow->show();
}

