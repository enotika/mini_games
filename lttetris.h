#ifndef LTTETRIS_H
#define LTTETRIS_H

#include "figuretetris.h"

class LtTetris : public FigureTetris
{
public:
    LtTetris();
    ~LtTetris() override {};
    void rotate(std::vector<std::vector<int>> v) override;
    void setCoords(int x1, int y1) override;
    vector < pair < int, int > > getCoords() override;
    QColor getColor() override;
    void fall() override;
    void moveHorizontally(int x, std::vector<std::vector<int>> v) override;
    int getIntType()override{return 6;};
private:
    int xc, yc;
};

#endif // LTTETRIS_H
