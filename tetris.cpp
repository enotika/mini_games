#include "tetris.h"
#include "ui_tetris.h"

#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <QtDebug>
#include "squaretetris.h"
#include "sticktetris.h"
#include "stetris.h"
#include "ztetris.h"
#include "ltetris.h"
#include "lttetris.h"
#include "ttetris.h"

#include <QMessageBox>
Tetris::Tetris(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tetris)
{
    ui->setupUi(this);
    field.resize(20, std::vector<int>(10, 0));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Tetris::draw);
    timer->start(1000 / 5);
    colors.push_back(Qt::white);
    colors.push_back(QColor::fromRgb(0xDC143C)); // Crimson
    colors.push_back(QColor::fromRgb(0xFF69B4)); // HotPink
    colors.push_back(QColor::fromRgb(0xA0522D)); // Sienna
    colors.push_back(QColor::fromRgb(0xFFFF00)); // Yellow
    colors.push_back(QColor::fromRgb(0x8A2BE2)); // BlueViolet
    colors.push_back(QColor::fromRgb(0x00FF00)); // Lime
    colors.push_back(QColor::fromRgb(0xFF7F50)); // Coral

}

Tetris::~Tetris()
{
    delete ui;
}

void Tetris::paintEvent(QPaintEvent *event)
{
    QPainter ptr(this);
    ptr.setPen(Qt::black);
    int cellSize = qMin(width() / 10, height() / 20);
    int fieldWidth = cellSize * 10;
    int fieldHeight = cellSize * 20;
    int fieldX = (width() - fieldWidth) / 2;
    int fieldY = (height() - fieldHeight) / 2;

    // Рисуем горизонтальные линии
    for (int y = 0; y <= 20; y++) {
        int yPos = fieldY + y * cellSize;
        ptr.drawLine(fieldX, yPos, fieldX + fieldWidth, yPos);
    }

    // Рисуем вертикальные линии
    for (int x = 0; x <= 10; x++) {
        int xPos = fieldX + x * cellSize;
        ptr.drawLine(xPos, fieldY, xPos, fieldY + fieldHeight);
    }
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            if(field[i][j] != 0){
                drawSquare(&ptr, i, j, 1, 1, colors[field[i][j]]);
            }
        }
    }

    if(!falling){
        falling = true;
        xF = 18;
        yF = 4;
        QRandomGenerator* generator = QRandomGenerator::global();
        int type = generator->bounded(0 , 7);
        switch (type) {
            case 0:
                figure = new SquareTetris();
                break;
            case 1:
                figure = new StickTetris();
                break;
             case 2:
                figure = new STetris();
                break;
            case 3:
               figure = new ZTetris();
               break;
            case 4:
               figure = new LTetris();
               break;
            case 5:
                   figure = new LtTetris();
                   break;
            case 6:
                   figure = new TTetris();
                   break;
        }

        figure->setCoords(xF, yF);
        for(auto to : figure->getCoords()){
            int i = to.first;
            int j = to.second;
            if(field[i][j] != 0){
                field.resize(20, std::vector<int>(10, 0));
                QMessageBox msgBox;
                msgBox.setWindowTitle("Конец игры!");
                msgBox.setText("\nНачать заново?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                int result = msgBox.exec();

                if (result == QMessageBox::Yes) {
                    endGame();
                } else if (result == QMessageBox::No) {
                    this->close();
                }
                return;
            }
        }
        for(auto to : figure->getCoords()){
            drawSquare(&ptr, to.first, to.second, 1, 1, figure->getColor());
        }
        falling = true;
    } else {
            for(auto to : figure->getCoords()){
                int i = to.first - 1;
                int j = to.second;
                if(i < 0 || field[i][j] != 0){
                    falling = false;
                }
            }
            if(falling)figure->fall();

            for(auto to : figure->getCoords()){
                drawSquare(&ptr, to.first, to.second, 1, 1, figure->getColor());
            }
            if(!falling){
                for(auto to : figure->getCoords()){
                    int i = to.first;
                    int j = to.second;
                    field[i][j] = figure->getIntType();
                }
            }
    }

    updateField();
    lefting = false;
}

void Tetris::drawSquare(QPainter *ptr, int x, int y, int w, int h, QColor color)
{

    int cellSize = qMin(width() / 10, height() / 20);
    int fieldWidth = cellSize * 10;
    int fieldHeight = cellSize * 20;
    int fieldX = (width() - fieldWidth) / 2;
    int fieldY = (height() - fieldHeight) / 2;

    int squareCol = y;
    int squareRow = x;
    int squareWidth = w; // Ширина квадрата в клетках
    int squareHeight = h; // Высота квадрата в клетках
    int squareX = fieldX + squareCol * cellSize;
    int squareY = fieldY + (fieldHeight - (squareRow + squareHeight) * cellSize);
    ptr->fillRect(squareX+1, squareY+1, squareWidth * cellSize-1, squareHeight * cellSize-1, color);
}

void Tetris::draw()
{
    repaint();
}

void Tetris::keyPressEvent(QKeyEvent *e)
{
    if(lefting)return;
    switch (e->key()) {
        case Qt::Key_A:
            figure->moveHorizontally(-1, field);
            lefting = true;
            break;
        case Qt::Key_D:
            figure->moveHorizontally(+1, field);
            lefting = true;
            break;
        case Qt::Key_W:
            figure->rotate(field);
            break;
        case Qt::Key_Escape:
            this->close();
            break;
    }
}

void Tetris::updateField()
{
    for(int i = 0; i < 20; i++){
        int cnt = 0;
        for(int j = 0; j < 10; j++){
            if(field[i][j] == 0)break;
            cnt++;
        }
        if(cnt == 10){
            for(int j = 0; j < 10; j++){
                field[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < 19; i++){
        int cnt = 0;
        for(int j = 0; j < 10; j++){
            if(field[i][j] != 0)break;
            cnt++;
        }
        if(cnt == 10){
            for(int j = 0; j < 10; j++){
                field[i][j] = field[i + 1][j];
                field[i + 1][j] = 0;
            }
        }
    }
}

void Tetris::endGame()
{
    field.clear();
    field.resize(20, std::vector<int>(10, 0));
    lefting = false;
    falling = false;
    xF = 18;
    yF = 4;
}
