#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer          *timer;
    QTimer          *timerSpace;
    std::vector <std::pair<int, int>> vec;
    int xa=NULL;
    int ya=NULL;
     QGraphicsScene  *scene;     /// Объявляем графическую сцену
     int dir = 0;
     bool walls = false;
     int left = -300;
     int right = 280;
     int up = -280;
     int down = 260;
     QColor headColor = Qt::red;
     QColor bodyColor = Qt::green;
public slots:
     void keyPressEvent(QKeyEvent *e);
     void keyReleaseEvent(QKeyEvent *e);
     void draw();
     void spaceTimerTimeout();
     void endGame(bool f);

     void genApple(int &x, int &y);
private slots:
     void on_actionWalls_triggered();
     void on_actionNo_walls_triggered();
     void on_actionChange_snake_color_triggered();
};
#endif // MAINWINDOW_H
