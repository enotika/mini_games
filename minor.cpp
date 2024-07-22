#include "minor.h"
#include "minor.h"
#include "ui_minor.h"

#include <QRandomGenerator>
#include <QTableWidgetItem>
#include <QDebug>
#include <queue>
#include <QMessageBox>
minor::minor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::minor)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    on_pushButton_clicked();
}

minor::~minor()
{
    delete ui;
}

void minor::on_pushButton_clicked()
{
    if(ui->minesBox->value() >= ui->rowsBox->value() * ui->colsBox->value()){
        QMessageBox::information(this, "Новая игра", "Мин не может быть больше чем ячеек!");
        return;
    }
    ui->tableWidget->clear();

    mines.clear();
    pole.clear();
    openPole.clear();
    userNumber.clear();
    openNumber.clear();

    minesCount = ui->minesBox->value();
    rows = ui->rowsBox->value();
    columns = ui->colsBox->value();
    pole.resize(rows, std::vector < int> (columns, 0));

    ui->tableWidget->setColumnCount(columns);
    ui->tableWidget->setRowCount(rows);
    for(int i = 0; i<rows; i++){
        ui->tableWidget->setRowHeight(i, 30);
    }
    for(int i = 0; i<columns; i++){
        ui->tableWidget->setColumnWidth(i, 30);
    }
    ui->tableWidget->setFixedSize(columns * 30 + 2, rows * 30 + 2);

    QRandomGenerator* generator = QRandomGenerator::global();
    //qDebug() << "\n\n\nNEW";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    for(int i = 0; i < minesCount; i++){
            // Генерируем случайное число в диапазоне [-14, 13]
        int ya = generator->bounded(0, columns);
        int xa = generator->bounded(0, rows);
        //qDebug() << "Try to set in " << xa << " " << ya;
        while(pole[xa][ya] == -1){
            ya = generator->bounded(0, columns);
            xa = generator->bounded(0, rows);
            //qDebug() << xa << " " << ya;
        }
        mines.insert(std::make_pair(xa, ya));
        pole[xa][ya] = -1;
    }

    for(auto to: mines){
        int mx = to.first;
        int my = to.second;
        if(mx - 1 >= 0){
            if(my - 1 >= 0 && mines.count({mx - 1, my - 1}) == 0){
                pole[mx - 1][my - 1] += 1;
                userNumber.insert({mx - 1, my - 1});
            }
            if(mines.count({mx - 1, my}) == 0){
                pole[mx - 1][my] += 1;
                userNumber.insert({mx - 1, my});
            }
            if(my + 1 < columns && mines.count({mx - 1, my + 1}) == 0){
                pole[mx - 1][my + 1] += 1;
                userNumber.insert({mx - 1, my + 1});
            }
        }
        if(mx + 1 < rows){
            if(my - 1 >= 0 && mines.count({mx + 1, my - 1}) == 0){
                pole[mx + 1][my - 1] += 1;
                userNumber.insert({mx + 1, my - 1});
            }
            if(mines.count({mx + 1, my}) == 0){
                pole[mx + 1][my] += 1;
                userNumber.insert({mx + 1, my});
            }
            if(my + 1 < columns && mines.count({mx + 1, my + 1}) == 0){
                pole[mx + 1][my + 1] += 1;
                userNumber.insert({mx + 1, my + 1});
            }
        }
        if(my - 1 >= 0 && mines.count({mx, my - 1}) == 0){
            pole[mx][my - 1] += 1;
            userNumber.insert({mx, my - 1});
        }
        if(my + 1 < columns && mines.count({mx, my + 1}) == 0){
            pole[mx][my + 1] += 1;
            userNumber.insert({mx, my + 1});
        }
    }

//    for(int i = 0; i < rows; i++){
//        for(int j = 0; j < columns; j++){
//            if(pole[i][j] == 0){
//                ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
//            } else {
//                ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(pole[i][j])));
//            }
//        }
//    }
}


void minor::on_tableWidget_cellClicked(int row, int column)
{
    //qDebug() << row << " " << column << " clicked";
    if(openPole.count({row, column})){
        return;
    }
    if(!flags.count({row, column})){
        QIcon icon(":/images/resources/flag.png");
        QTableWidgetItem* item = new QTableWidgetItem();
//                    item->setIcon(icon);
        item->setIcon(icon);
        ui->tableWidget->setIconSize(QSize(ui->tableWidget->columnWidth(column) - 1, ui->tableWidget->rowHeight(row) - 1));
        ui->tableWidget->setItem(row, column, item);
//        ui->tableWidget->setItem(row, column, new QTableWidgetItem("f"));
        flags.insert({row, column});
    } else if(flags.count({row, column})){
        ui->tableWidget->setItem(row, column, new QTableWidgetItem(""));
        flags.erase({row, column});
    }
}

void minor::bfs(int startRow, int startCol) {
    ///dejkstra
    std::vector<std::vector<int>> grid = pole;
    int rows = grid.size();
    int cols = grid[0].size();

    // Проверка, что начальная точка в пределах границ
    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
        return;
    }

    // Приоритетная очередь для хранения ячеек
    std::priority_queue<std::pair<int, std::pair<int, int>>> pq;
    pq.push({0, {startRow, startCol}});

    // Расстояния от стартовой ячейки
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INT_MAX));
    dist[startRow][startCol] = 0;

    // 8 направлений
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    while (!pq.empty()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        int d = -pq.top().first;
        pq.pop();

        // Если значение в текущей ячейке не 0, выходим из цикла
        if (pole[x][y] != 0) {
//            ui->tableWidget->item(x, y)->setText(QString::number(pole[x][y]));
            ui->tableWidget->setItem(x, y, new QTableWidgetItem(QString::number(pole[x][y])));
            openPole.insert({x, y});
            openNumber.insert({x, y});
            if(flags.count({x, y})){
                flags.erase({x, y});
            }
            grid[x][y] = -2;
            continue;
        }

        // Открываем текущую ячейку
        if (pole[x][y] == 0) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setBackground(Qt::green);
            ui->tableWidget->setItem(x, y, item);
            openPole.insert({x, y});
            if(flags.count({x, y})){
                flags.erase({x, y});
            }
        }

        // Отмечаем текущую ячейку как посещенную
        grid[x][y] = -2;

        // Обновляем расстояния соседних ячеек
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] != -2) {
                int newDist = d + 1;
                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                    pq.push({-newDist, {nx, ny}});
                }
            }
        }
    }
}

void minor::on_tableWidget_cellDoubleClicked(int row, int column)
{
    //qDebug() << row << " " << column << " double clicked";
//    QTextStream out(stdout);
    if(openPole.count({row, column})){
        return;
    }
////    out << trUtf8("Копирование:\n");

//    for(int i = 0; i < rows; i++){
//        for(int j = 0; j < columns; j++){
//            out << pole[i][j] << " ";
//        }
//        out << "\n";
//    }

    if(pole[row][column] == -1){
        qDebug() << "LOSE";
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                openPole.insert({i, j});
                if(pole[i][j] == 0){
                    QTableWidgetItem* item = new QTableWidgetItem();
                    item->setBackground(Qt::green);
                    ui->tableWidget->setItem(i, j, item);
                } else {
                    if(pole[i][j] != -1){
                        ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(pole[i][j])));
                    } else {
                        QIcon icon(":/images/resources/bomb.png");
                        QTableWidgetItem* item = new QTableWidgetItem();
    //                    item->setIcon(icon);
                        item->setIcon(icon);
                        ui->tableWidget->setIconSize(QSize(ui->tableWidget->columnWidth(j) - 1, ui->tableWidget->rowHeight(i) - 1));
                        ui->tableWidget->setItem(i, j, item);
                    }
                }
            }
        }
        return;
    }
    if(pole[row][column] == 0){
//        QIcon icon(":/images/resources/image(1).png");
//        QTableWidgetItem* item = new QTableWidgetItem();
//        item->setIcon(icon);
//        ui->tableWidget->setItem(row, column,item);
        bfs(row, column);
//        QTextStream out(stdout);
//        for(auto to : openNumber){
//            out << to.first << "," << to.second << " ";
//        }
//        out << "\n";
//        for(auto to : flags){
//            out << to.first << "," << to.second << " ";
//        }
//        out << "\n";
        if(openNumber == userNumber){
            qDebug() << "WINNER!!!!!";
//            QMessageBox::information(this, "Победа", "Вы победили!\nНачать заново?");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Победа");
            msgBox.setText("Вы победили!\nНачать заново?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            int result = msgBox.exec();

            if (result == QMessageBox::Yes) {
                on_pushButton_clicked();
                // Пользователь нажал "Да"
                // Добавьте здесь необходимые действия
            } else if (result == QMessageBox::No) {
                this->close();
                // Пользователь нажал "Нет"
                // Добавьте здесь необходимые действия
            }
        }
        return;
    }
    ui->tableWidget->setItem(row, column, new QTableWidgetItem(QString::number(pole[row][column])));
    openPole.insert({row, column});
    openNumber.insert({row, column});
//    for(auto to : openNumber){
//        out << to.first << "," << to.second << " ";
//    }
//    out << "\n";
//    for(auto to : flags){
//        out << to.first << "," << to.second << " ";
//    }
//    out << "\n";
    if(openNumber == userNumber){
        qDebug() << "WINNER!!!!!";
//        QMessageBox::information(this, "Победа", "Вы победили!\nНачать заново?");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Победа");
        msgBox.setText("Вы победили!\nНачать заново?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int result = msgBox.exec();

        if (result == QMessageBox::Yes) {
            on_pushButton_clicked();
            // Пользователь нажал "Да"
            // Добавьте здесь необходимые действия
        } else if (result == QMessageBox::No) {
            this->close();
            // Пользователь нажал "Нет"
            // Добавьте здесь необходимые действия
        }
    }
}

