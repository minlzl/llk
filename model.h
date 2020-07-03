#ifndef MODEL_H
#define MODEL_H

#include<vector>

const int maxrow=15;
const int maxcol=20;
const int maxsize=16;
const int allsize=maxcol*maxrow;

enum Gamestate{
    PLAYING,
    OVER,
    WIN,
    PAUSE
};


enum Gamemodel{
    TIME,
    FUN,
    LONG
};

struct point{
    point(int _x,int _y):x(_x),y(_y){}
    int x;
    int y;
};

class model
{
public:
    model();
    ~model();
    Gamestate gamestate;
    Gamemodel gamemodel;
    bool iscanconnect(int x1,int y1,int x2,int y2);
    bool iscononeline(int x1,int y1,int x2,int y2);
    bool iscontwoline(int x1,int y1,int x2,int y2);
    bool isconthrline(int x1,int y1,int x2,int y2);
    void gamestart();
    void gamestart(Gamemodel gamemodel);
    int *getmap();
    Gamestate getstate();
    bool iscanline(int x1,int y1,int x2,int y2);
    bool isfozened();
    std::vector<point> points;
    bool iswin();
    int *gethit();
    void gamereset();
    int score;
private:
    int *gamemap;
    int *hitarr;
    bool isfozen;

};

#endif // MODEL_H
