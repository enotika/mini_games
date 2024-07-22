#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QtDebug>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QPushButton>
#include <QColorDialog>
#include <set>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vec.push_back({0, 0});
    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
    scene->setSceneRect(-250,-250,500,500); /// Устанавливаем область графической сцены
    scene->addLine(-250,0,250,0,QPen(Qt::black));   /// Добавляем горизонтальную линию через центр
    scene->addLine(0,-250,0,250,QPen(Qt::black));   /// Добавляем вертикальную линию через центр
    /* Дополнительно нарисуем органичение территории в графической сцене */
    scene->addLine(-250,-250, 250,-250, QPen(Qt::black));
    scene->addLine(-250, 250, 250, 250, QPen(Qt::black));
    scene->addLine(-250,-250,-250, 250, QPen(Qt::black));
    scene->addLine( 250,-250, 250, 250, QPen(Qt::black));
    // Генерация случайного целого числа в диапазоне [0, 99]
    QRandomGenerator* generator = QRandomGenerator::global();
    xa = generator->bounded(left / 20, right/20+1) * 20;
    ya = generator->bounded(up / 20, down / 20 + 1) * 20;
    /* Инициализируем таймер и вызываем слот обработки сигнала таймера
     * у Треугольника 20 раз в секунду.
     * Управляя скоростью отсчётов, соответственно управляем скоростью
     * изменения состояния графической сцены
     * */
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::draw);
    timer->start(1000 / 10);
    timerSpace = new QTimer();
    connect(timerSpace, &QTimer::timeout, this, &MainWindow::spaceTimerTimeout);
    timerSpace->start(1000/5);
    ui->actionWalls->setDisabled(false);
    ui->actionNo_walls->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool spacePressed = false;
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_W:
            if(dir != -1 || vec.size() == 1)dir = 1;
            break;
        case Qt::Key_S:
            if(dir != 1 || vec.size() == 1)dir = -1;
            break;
        case Qt::Key_A:
            if(dir != -2 || vec.size() == 1)dir = 2;
            break;
        case Qt::Key_D:
            if(dir != 2 || vec.size() == 1)dir = -2;
            break;
        case Qt::Key_Space:
        if (!spacePressed) {
            spacePressed = true;
        }
            break;
        case Qt::Key_Escape:
            this->close();
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Space:
        if (spacePressed) {
            spacePressed = false;
        }
    }
}

void MainWindow::genApple(int & x, int & y){
    QRandomGenerator* generator = QRandomGenerator::global();
        // Генерируем случайное число в диапазоне [-14, 13]
    xa = generator->bounded(left / 20, right/20+1) * 20;
    ya = generator->bounded(up / 20, down / 20 + 1) * 20;
    bool snake = false;
    std::set<std::pair<int, int>>st;
    for(auto to : vec){
        st.insert(to);
    }
    while(st.count(std::make_pair(xa, ya))){
        xa = generator->bounded(left / 20, right/20+1) * 20;
        ya = generator->bounded(up / 20, down / 20 + 1) * 20;
    }
}
void MainWindow::draw()
{
    if (spacePressed) {
        timer->setInterval(1000/15);
    } else {
        timer->setInterval(1000/10);
    }
    if(dir == 1){
        for(int i = 0; i < vec.size(); i++){
            if(i != vec.size() - 1){
                vec[i] = vec[i + 1];
                if(std::make_pair(vec[vec.size() - 1].first, vec[vec.size() - 1].second -20) == vec[i]){
                    endGame(true);
                }

            } else {
                vec[i] = {vec[i].first, vec[i].second -20};
                if(vec[i].second < up){
                    if(!walls){
                        vec[i].second = down;
                    } else {
                        endGame(true);
                    }
                }
            }
        }
        if(vec[vec.size() - 1] == std::make_pair(xa, ya)){
            xa = INT_MIN;
            ya = INT_MIN;
        }
    }
    if(dir == -1){
        for(int i = 0; i < vec.size(); i++){
            if(i != vec.size() - 1){
                vec[i] = vec[i + 1];
                if(std::make_pair(vec[vec.size() - 1].first, vec[vec.size() - 1].second + 20) == vec[i]){
                    endGame(true);
                }
            } else {
                vec[i] = {vec[i].first, vec[i].second +20};
                if(vec[i].second > down){
                    if(!walls){
                        vec[i].second = up;
                    } else {
                        endGame(true);
                    }
                }
            }
        }
        if(vec[vec.size() - 1] == std::make_pair(xa, ya)){
            xa = INT_MIN;
            ya = INT_MIN;
        }
    }
    if(dir == 2){
        for(int i = 0; i < vec.size(); i++){
            if(i != vec.size() - 1){
                vec[i] = vec[i + 1];
                if(std::make_pair(vec[vec.size() - 1].first -20, vec[vec.size() - 1].second) == vec[i]){
                    endGame(true);
                }
            } else {
                vec[i] = {vec[i].first -20, vec[i].second };
                if(vec[i].first < left){
                    if(!walls){
                        vec[i].first = right;
                    } else {
                        endGame(true);
                    }
                }
            }
        }
        if(vec[vec.size() - 1] == std::make_pair(xa, ya)){
            xa = INT_MIN;
            ya = INT_MIN;
        }
    }
    if(dir == -2){
        for(int i = 0; i < vec.size(); i++){
            if(i != vec.size() - 1){
                vec[i] = vec[i + 1];
                if(std::make_pair(vec[vec.size() - 1].first +20, vec[vec.size() - 1].second) == vec[i]){
                    endGame(true);
                }
            } else {
                vec[i] = {vec[i].first +20, vec[i].second };
                if(vec[i].first > right){
                    if(!walls){
                        vec[i].first = left;
                    } else {
                        endGame(true);
                    }
                }
            }
        }
        if(vec[vec.size() - 1] == std::make_pair(xa, ya)){
            xa = INT_MIN;
            ya = INT_MIN;
        }
    }
    if(xa == INT_MIN){
        switch(dir){
            case 1:
                vec.push_back({vec[vec.size() - 1].first, vec[vec.size() - 1].second - 20});
                break;
            case -1:
                vec.push_back({vec[vec.size() - 1].first, vec[vec.size() - 1].second + 20});
                break;
            case 2:
                vec.push_back({vec[vec.size() - 1].first - 20, vec[vec.size() - 1].second});
                break;
            case -2:
                vec.push_back({vec[vec.size() - 1].first + 20, vec[vec.size() - 1].second});
                break;
        }
        genApple(xa, ya);
    }
    scene->clear();
    for(int i = 0; i < vec.size(); i++){
        auto to = vec[i];
        if(i != vec.size() - 1)scene->addEllipse(to.first, to.second, 20, 20, QPen(headColor), QBrush(bodyColor));
        else {
            if(imageHead == "")
                    scene->addEllipse(to.first, to.second, 20, 20, QPen(headColor), QBrush(headColor));
            else {
                QPixmap pixmap(imageHead);
                QGraphicsPixmapItem * img = scene->addPixmap(pixmap);
                img->setPos(to.first, to.second);
                img->setScale(20.0/pixmap.height());
            }
        }
    }
    if(xa != INT_MIN)scene->addEllipse(xa, ya, 20, 20, QPen(Qt::yellow), QBrush(Qt::blue));


}

void MainWindow::spaceTimerTimeout()
{

}

void MainWindow::endGame(bool f)
{
    vec.clear();
    dir = 0;
    vec.push_back({0, 0});
    xa = INT_MIN;
    ya = INT_MIN;
    QMessageBox msgBox;
        msgBox.setWindowTitle("Поражение");
        msgBox.setText("Вы хотите перезапустить игру?");
        msgBox.setIcon(QMessageBox::Question);

        QPushButton* yesButton = msgBox.addButton(tr("Перезапустить"), QMessageBox::YesRole);
        QPushButton* noButton = msgBox.addButton(tr("Выйти"), QMessageBox::NoRole);
        if(!f){
            msgBox.setWindowTitle("Перезапуск");
        }
        msgBox.exec();

        if (msgBox.clickedButton() == yesButton) {

        } else if (msgBox.clickedButton() == noButton) {

            this->close();
        }
}


void MainWindow::on_actionWalls_triggered()
{
    walls = true;
    endGame(false);
    ui->actionWalls->setDisabled(true);
    ui->actionNo_walls->setDisabled(false);
}


void MainWindow::on_actionNo_walls_triggered()
{
    walls = false;
    endGame(false);
    ui->actionWalls->setDisabled(false);
    ui->actionNo_walls->setDisabled(true);
}


void MainWindow::on_actionChange_snake_color_triggered()
{

    // Открыть диалоговое окно для выбора цвета
        QColor selectedColor = QColorDialog::getColor(Qt::white, this, "Choose a body Color", QColorDialog::ShowAlphaChannel);
        // Проверить, был ли цвет выбран
        if (selectedColor.isValid())
        {
            bodyColor = selectedColor;
        }
        selectedColor = QColorDialog::getColor(Qt::white, this, "Choose a head Color", QColorDialog::ShowAlphaChannel);
        // Проверить, был ли цвет выбран
        if (selectedColor.isValid())
        {
            headColor = selectedColor;
            imageHead = "";
        }
}


void MainWindow::on_actionAdd_image_on_head_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "Select a file", QDir::homePath(), "All files (*)");
            if (!fileName.isEmpty()) {
                imageHead = fileName;
            }
}

