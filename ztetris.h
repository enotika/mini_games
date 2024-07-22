#ifndef ZTETRIS_H
#define ZTETRIS_H

#include "figuretetris.h"

class ZTetris : public FigureTetris
{
public:
    ZTetris();
    ~ZTetris() override {};
    void rotate(std::vector<std::vector<int>> v) override;
    void setCoords(int x1, int y1) override;
    vector < pair < int, int > > getCoords() override;
    QColor getColor() override;
    void fall() override;
    void moveHorizontally(int x, std::vector<std::vector<int>> v) override;
    int getIntType()override{return 4;};

private:
    int xc, yc;
};

#endif // ZTETRIS_H
