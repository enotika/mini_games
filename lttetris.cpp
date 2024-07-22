#include "lttetris.h"

LtTetris::LtTetris()
{
    color = QColor::fromRgb(0x00FF00);
}

void LtTetris::rotate(std::vector<std::vector<int>> v)
{
    sort(coords.rbegin(), coords.rend());
    int x = xc, y = yc;
    for(int i = 0; i < coords.size(); i++){
        int xN = x + y - coords[i].second;
        int yN = coords[i].first + y - x;
        if(xN > 19 || xN  < 0 || yN > 9 || yN  < 0)return;
        if(v[xN][yN] != 0)return;

    }
    for(int i = 0; i < coords.size(); i++){
        int xN = x + y - coords[i].second;
        int yN = coords[i].first + y - x;
        coords[i].first = xN;
        coords[i].second = yN;
    }
}

void LtTetris::setCoords(int x1, int y1)
{

    coords.push_back({x1, y1});
    coords.push_back({x1 - 1, y1});
    coords.push_back({x1 + 1, y1});
    coords.push_back({x1 + 1, y1 + 1});
    xc = x1;
    yc = y1;
}

vector<pair<int, int> > LtTetris::getCoords()
{
    return coords;
}

QColor LtTetris::getColor()
{
    return color;
}

void LtTetris::fall()
{
    for(int i = 0; i < coords.size(); i++){
        coords[i].first -= 1;
    }
    xc -= 1;
}

void LtTetris::moveHorizontally(int x, std::vector<std::vector<int>> v)
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
    yc += x;
}
