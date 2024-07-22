#ifndef FINDPAIR_H
#define FINDPAIR_H

#include <QMainWindow>
#include <vector>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "clickablelabel.h"
#include <QMutex>
#include <QTimer>
#include <QtDebug>
#include <set>
namespace Ui {
class FindPair;
}

class FindPair : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindPair(QWidget *parent = nullptr);
    ~FindPair();

public slots:
//    void onLabelClicked(ClickableLabel* label);
    void onLabelClickedWithoutLabel();
    void resizeEvent(QResizeEvent* event) {
        if(idOpened != -1){
            cards[idOpened]->setPixmap(QPixmap());

            QTimer::singleShot(50, [this]() {
                    // Выполнить некоторые действия
//                    qDebug() << "Здравствуй, мир!";
                    cards[idOpened]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                    cards[idOpened]->setScaledContents(true);
                    // Установка изображения
                    cards[idOpened]->setPixmap(QPixmap(images[pairs[idOpened]]).scaled(cards[idOpened]->size()));
                    cards[idOpened]->setAlignment(Qt::AlignVCenter);
//                    qDebug() << "EEEEEENNNNNDDD";
                });
        }
        for(auto to : openedCards){
            cards[to]->setPixmap(QPixmap());
        }
        QTimer::singleShot(50, [this]() {
            for(auto to : openedCards){
                // Выполнить некоторые действия
//                    qDebug() << "Здравствуй, мир!";
                cards[to]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                cards[to]->setScaledContents(true);
                // Установка изображения
                cards[to]->setPixmap(QPixmap(images[pairs[to]]).scaled(cards[to]->size()));
                cards[to]->setAlignment(Qt::AlignVCenter);
//                    qDebug() << "EEEEEENNNNNDDD";

            }

            });
    }
    void helpToWait();
private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_actionsz_triggered();

private:
    Ui::FindPair *ui;
    std::vector<ClickableLabel*> cards;
    QGridLayout * mainLayout;
    std::vector<std::vector < int>> nums;
    std::vector<QString> images;
    std::vector <int > pairs;
    int idOpened = -1;
    std::vector < int > openedCards;
    QMutex mutex;
    std::set<int> allOpened;
    bool isWating = false;
    int hodov = 0;

signals:
    void functionCompleted();

};

#endif // FINDPAIR_H
