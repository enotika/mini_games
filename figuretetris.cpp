#include "figuretetris.h"

FigureTetris::FigureTetris()
{

}

FigureTetris::~FigureTetris()
{

}

void FigureTetris::rotate(std::vector<std::vector<int>> v)
{

}

void FigureTetris::setCoords(int x1, int y1)
{

}
vector<pair<int, int> > FigureTetris::getCoords()
{
    return coords;
}

QColor FigureTetris::getColor()
{
    return color;
}

void FigureTetris::fall()
{
    for(auto to: coords){
        to.first -= 1;
    }
}
