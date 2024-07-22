#ifndef STETRIS_H
#define STETRIS_H

#include "figuretetris.h"

class STetris : public FigureTetris
{
public:
    STetris();
    ~STetris() override {};
    void rotate(std::vector<std::vector<int>> v) override;
    void setCoords(int x1, int y1) override;
    vector < pair < int, int > > getCoords() override;
    QColor getColor() override;
    void fall() override;
    void moveHorizontally(int x, std::vector<std::vector<int>> v) override;
    int getIntType()override{return 3;};

};

#endif // STETRIS_H
