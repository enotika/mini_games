#include "findpair.h"
#include "ui_findpair.h"
#include <QPainter>
#include <QtDebug>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include <math.h>
#include <set>
#include <QRandomGenerator>
#include <QPicture>
#include <QFuture>
#include "clickablelabel.h"
#include <QtConcurrent>
#include <QMessageBox>
FindPair::FindPair(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindPair)
{
    ui->setupUi(this);

    // Создаем основной вертикальный layout
    QVBoxLayout* mainLayout = new QVBoxLayout(ui->centralwidget);

    // Добавляем ui->spinBox в верхнюю часть layout
    mainLayout->addWidget(ui->spinBox);
    mainLayout->addWidget(ui->resultLabel);
    // Создаем сетчатый layout для метки
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);

    // Добавляем сетчатый layout в основной layout
    mainLayout->addLayout(gridLayout);

    // Устанавливаем политику растяжения для виджета, содержащего gridLayout
    ui->centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->resultLabel->hide();
    // Обновляем mainLayout в классе
    this->mainLayout = gridLayout;
    images.push_back(":/findPair/resources/18331653_5954489.svg");
    images.push_back(":/findPair/resources/pokemons2.png");
    images.push_back(":/findPair/resources/pokemons3.png");
    images.push_back(":/findPair/resources/pokemons4.png");
    images.push_back(":/findPair/resources/pokemons5.png");
    images.push_back(":/findPair/resources/pokemons6.png");
    images.push_back(":/findPair/resources/pokemons7.png");
    images.push_back(":/findPair/resources/pokemons8.png");
    images.push_back(":/findPair/resources/pokemons9.png");
    images.push_back(":/findPair/resources/pokemons10.png");


}

FindPair::~FindPair()
{
    for (ClickableLabel* label : cards)
            delete label;
    delete ui;
}


void FindPair::on_spinBox_valueChanged(int arg1)
{
    allOpened.clear();
    openedCards.clear();
    idOpened = -1;
    hodov = 0;
    ui->resultLabel->show();
    ui->resultLabel->setText("Ходов: 0");
    // Удаляем старые метки
    for (ClickableLabel* label : cards)
    {
        mainLayout->removeWidget(label);
        delete label;
    }
    pairs.clear();
    pairs.resize(arg1*2);
    cards.clear();
    int gridSize = std::ceil(std::sqrt(2*arg1));

    // Создаем новые метки
    for (int i = 0; i < 2*arg1; i++)
    {
        ClickableLabel* label = new ClickableLabel("",ui->centralwidget);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label->setStyleSheet("ClickableLabel { background-color: lightgray; }");
        label->setAlignment(Qt::AlignAbsolute);
        label->setMinimumSize(20,20);


        QObject::connect(label, SIGNAL(clicked()), this, SLOT(onLabelClickedWithoutLabel()));
        cards.push_back(label);
        mainLayout->addWidget(label, i / gridSize, i % gridSize);
    }
    std::set < int> st;

    QRandomGenerator* generator = QRandomGenerator::global();
    for(int i = 0; i < arg1; i++){
        int fImg = generator->bounded(0, arg1*2);
        int sImg = generator->bounded(0, arg1*2);
        while(st.count(fImg)){
            fImg = generator->bounded(0, arg1*2);
        }
        st.insert(fImg);
        while(st.count(sImg)){
            sImg = generator->bounded(0, arg1*2);
        }
        st.insert(sImg);
        pairs[fImg] = i;
        pairs[sImg] = i;
        qDebug() << i << " : " << fImg << " " << sImg;
    }
}
void FindPair::helpToWait(){
    QLabel* label = qobject_cast<QLabel*>(sender());
    if(isWating)return;

            int index = -1;
            for (int i = 0; i < cards.size(); i++)
            {
                if (cards[i] == label)
                {
                    index = i;
                    break;
                }
            }
            if(index == idOpened)return;
            hodov++;
            ui->resultLabel->setText("Ходов: " + QString::number(hodov));

            if(idOpened == -1){
                // Установка политики размера метки
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                label->setScaledContents(true);
    //             Установка изображения
                label->setPixmap(QPixmap(images[pairs[index]]).scaled(label->size()));

                idOpened = index;
                allOpened.insert(index);

            } else if(idOpened != -1) {
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                label->setScaledContents(true);
    //             Установка изображения
                label->setPixmap(QPixmap(images[pairs[index]]).scaled(label->size()));
                if(pairs[index] == pairs[idOpened] ){
                    openedCards.push_back(index);
                    openedCards.push_back(idOpened);
                    if(openedCards.size() == ui->spinBox->value() * 2){
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Победа");
                        msgBox.setText("Вы победили!\nНачать заново?");
                        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                        int result = msgBox.exec();

                        if (result == QMessageBox::Yes) {
                            on_spinBox_valueChanged(ui->spinBox->value());

                        } else if (result == QMessageBox::No) {
                            this->close();

                        }
                    }
                    idOpened = -1;
                    allOpened.erase(index);
                    allOpened.erase(idOpened);
                    return;
                } else {
                    isWating = true;
                    QTimer::singleShot(1000, [this, index]() {
                        isWating = false;
                            // Выполнить некоторые действия

                                cards[idOpened]->setPixmap(QPixmap());
                                cards[index]->setPixmap(QPixmap());
                                idOpened = -1;
                                allOpened.erase(index);
                                allOpened.erase(idOpened);
                        });
                }

            }
            emit functionCompleted();
}
void FindPair::onLabelClickedWithoutLabel()
{
    helpToWait();

    QEventLoop eventLoop;
    connect(this, &FindPair::functionCompleted, &eventLoop, &QEventLoop::quit);


}


void FindPair::on_actionsz_triggered()
{
    this->resize(500, 500);
            if(idOpened != -1){

    //        Установка политики размера метки
                cards[idOpened]->setPixmap(QPixmap());
                QTimer::singleShot(100, [this]() {
                        // Выполнить некоторые действия
                        qDebug() << "Здравствуй, мир!";

                        cards[idOpened]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                        cards[idOpened]->setScaledContents(true);
                        // Установка изображения
                        cards[idOpened]->setPixmap(QPixmap(images[pairs[idOpened]]).scaled(cards[idOpened]->size()));
                        qDebug() << "EEEEEENNNNNDDD";
                    });

            }
}

