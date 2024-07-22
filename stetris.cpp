#include "stetris.h"

STetris::STetris()
{
    color = QColor::fromRgb(0xA0522D);
}

void STetris::rotate(std::vector<std::vector<int>> v)
{
    sort(coords.begin(), coords.end());
    int x = coords[0].first, y = coords[0].second;
    for(int i = 0; i < coords.size(); i++){
        int a = coords[i].first - x;
        int b = coords[i].second - y;
        if(x + b > 19 || x + b < 0 || y + a > 9 || y + a < 0)return;
        if(v[x+b][y+a]!=0)return;
    }
    for(int i = 0; i < coords.size(); i++){
        int a = coords[i].first - x;
        int b = coords[i].second - y;
        coords[i].first = x + b;
        coords[i].second = y + a;
    }
}

void STetris::setCoords(int x1, int y1)
{
    coords.push_back({x1, y1});
    coords.push_back({x1, y1 - 1});
    coords.push_back({x1 + 1, y1 + 1});
    coords.push_back({x1 + 1, y1});
}

vector<pair<int, int> > STetris::getCoords()
{
    return coords;
}

QColor STetris::getColor()
{
    return color;
}

void STetris::fall()
{
    for(int i = 0; i < coords.size(); i++){
        coords[i].first -= 1;
    }
}

void STetris::moveHorizontally(int x, std::vector<std::vector<int>> v)
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
