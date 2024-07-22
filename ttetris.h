#ifndef TTETRIS_H
#define TTETRIS_H

#include "figuretetris.h"

class TTetris : public FigureTetris
{
public:
    TTetris();
    ~TTetris() override {};
    void rotate(std::vector<std::vector<int>> v) override;
    void setCoords(int x1, int y1) override;
    vector < pair < int, int > > getCoords() override;
    QColor getColor() override;
    void fall() override;
    void moveHorizontally(int x, std::vector<std::vector<int>> v) override;
    int getIntType()override{return 7;};
private:
    int xc, yc;
};

#endif // TTETRIS_H
