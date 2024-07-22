#ifndef STICKTETRIS_H
#define STICKTETRIS_H

#include "figuretetris.h"

class StickTetris : public FigureTetris
{
public:
    StickTetris();
    ~StickTetris() override {};
    void rotate(std::vector<std::vector<int>> v) override;
    void setCoords(int x1, int y1) override;
    vector < pair < int, int > > getCoords() override;
    QColor getColor() override;
    void fall() override;
    void moveHorizontally(int x, std::vector<std::vector<int>> v) override;
    int getIntType()override{return 2;};

};

#endif // STICKTETRIS_H
