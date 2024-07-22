#ifndef SQUARETETRIS_H
#define SQUARETETRIS_H

#include "figuretetris.h"

class SquareTetris : public FigureTetris
{
public:
    SquareTetris();
    ~SquareTetris() override {};
    void rotate(std::vector<std::vector<int>> v) override;
    void setCoords(int x1, int y1) override;
    vector < pair < int, int > > getCoords() override;
    QColor getColor() override;
    void fall() override;
    void moveHorizontally(int x, std::vector<std::vector<int>> v) override;
    int getIntType()override{return 1;};


};

#endif // SQUARETETRIS_H
