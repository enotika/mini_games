#ifndef LTETRIS_H
#define LTETRIS_H

#include "figuretetris.h"

class LTetris : public FigureTetris
{
public:
    LTetris();
    ~LTetris() override {};
    void rotate(std::vector<std::vector<int>> v) override;
    void setCoords(int x1, int y1) override;
    vector < pair < int, int > > getCoords() override;
    QColor getColor() override;
    void fall() override;
    void moveHorizontally(int x, std::vector<std::vector<int>> v) override;
    int getIntType()override{return 5;};
private:
    int xc, yc;
};

#endif // LTETRIS_H
