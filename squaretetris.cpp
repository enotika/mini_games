#include "squaretetris.h"

SquareTetris::SquareTetris()
{
    color = QColor::fromRgb(0xDC143C);
}

void SquareTetris::rotate(std::vector<std::vector<int>> v)
{
    return;
}

void SquareTetris::setCoords(int x1, int y1)
{
    coords.push_back({x1, y1});
    coords.push_back({x1 + 1, y1});
    coords.push_back({x1, y1 + 1});
    coords.push_back({x1 + 1, y1 + 1});
}

vector<pair<int, int> > SquareTetris::getCoords()
{
    return coords;
}

QColor SquareTetris::getColor()
{
    return color;
}

void SquareTetris::fall()
{
    for(int i = 0; i < coords.size(); i++){
        coords[i].first -= 1;
    }
}

void SquareTetris::moveHorizontally(int x, std::vector<std::vector<int>> v)
{
    for(int i = 0; i < coords.size(); i++){
        if(coords[i].second + x < 0 || coords[i].second + x > 9)return;
    }
    for(int i = 0; i < coords.size(); i++){
        if(v[coords[i].first][coords[i].second + x] != 0)return;
    }
    for(int i = 0; i < coords.size(); i++){
        coords[i].second += x;
    }
}
