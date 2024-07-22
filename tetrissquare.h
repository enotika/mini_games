#ifndef TETRISSQUARE_H
#define TETRISSQUARE_H

#include <bits/stl_pair.h>

#include <vector>

using namespace std;

class TetrisSquare:FigureTetris
{
public:
    TetrisSquare();
    void rotate();
private:
    vector< pair <int, int > > vec;

};

#endif // TETRISSQUARE_H
