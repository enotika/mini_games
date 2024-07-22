#ifndef TETRIS_H
#define TETRIS_H

#include <QMainWindow>
#include <vector>
#include "figuretetris.h"

namespace Ui {
class Tetris;
}

class Tetris : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tetris(QWidget *parent = nullptr);
    ~Tetris();

private:
    void paintEvent(QPaintEvent *event);
    void drawSquare(QPainter * ptr, int x, int y, int w, int h, QColor color);
    void draw();
    void keyPressEvent(QKeyEvent *e);
    void updateField();
    void endGame();
private:
    bool lefting = false;
    Ui::Tetris *ui;
    std::vector<std::vector<int>> field;
    QTimer          *timer;
    bool falling = false;
    int xF = 18, yF = 4;
    QString type = "square";
    FigureTetris* figure;
    std::vector <QColor > colors;
};

#endif // TETRIS_H
