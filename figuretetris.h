#ifndef FIGURETETRIS_H
#define FIGURETETRIS_H

#include <bits/stl_pair.h>
#include <QColor>
#include <vector>
using namespace std;

class FigureTetris
{
public:
    FigureTetris();
    virtual ~FigureTetris();
    virtual void rotate(std::vector<std::vector<int>> v);
    virtual void setCoords(int x1, int y1);
    virtual vector < pair < int, int > > getCoords();
    virtual QColor getColor();
    virtual void fall();
    virtual void moveHorizontally(int x, std::vector<std::vector<int>> v){};
    virtual int getIntType(){return 1;};
protected:
    vector < pair < int, int > > coords;
    QColor color;
};

#endif // FIGURETETRIS_H
