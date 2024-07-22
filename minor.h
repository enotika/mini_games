#ifndef MINOR_H
#define MINOR_H

#include <QMainWindow>
#include <set>

namespace Ui {
class minor;
}

class minor : public QMainWindow
{
    Q_OBJECT

public:
    explicit minor(QWidget *parent = nullptr);
    ~minor();

public slots:
    void bfs(int startRow, int startCol);
private slots:
    void on_pushButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::minor *ui;
    std::set<std::pair<int, int> > mines;
    std::set<std::pair<int, int> > flags;
    std::set<std::pair<int, int> > userNumber;
    std::set<std::pair<int, int> > openNumber;
    std::set<std::pair<int, int> > openPole;
    std::vector< std::vector < int > > pole;
    int rows = 3, columns = 3;
    int minesCount = 1;

};

#endif // MINOR_H
