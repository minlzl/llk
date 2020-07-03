

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "model.h"
model::model():
    gamestate(PLAYING)
{

}
model::~model()
{
    if(gamemap)
    {
        free(gamemap);
        free(hitarr);
        gamemap=NULL;
    }
}
void model::gamestart()
{
    gamemap=new int[allsize];
    this->score=0;
    for(int i=0;i<allsize;i++)
    {
        gamemap[i]=0;
    }
    hitarr=new int[4];
    for(int i=0;i<4;i++)
        hitarr[i]=0;
    gamestate=PLAYING;
    int icon=0;
    for(int i=0;i<allsize;i+=2)
    {
        gamemap[i]=icon%maxsize+1;
        gamemap[i+1]=icon%maxsize+1;
        icon++;
    }
    srand((unsigned)time(0));
    for(int i=0;i<allsize;i++)
    {
        int randid=rand()%allsize;
        std::swap(gamemap[i],gamemap[randid]);
    }
    isfozen=false;
    points.clear();
}
int * model::getmap()
{
    return gamemap;
}
bool model::isfozened()
{
    for(int i=0;i<allsize;i++)
    {
        for(int j=i+1;j<allsize;j++)
        {
            int x1=i/maxcol;
            int y1=i%maxcol;
            int x2=j/maxcol;
            int y2=j%maxcol;
            isfozen=true;
            if(iscanconnect(x1,y1,x2,y2))
            {
                hitarr[0]=x1;
                hitarr[1]=y1;
                hitarr[2]=x2;
                hitarr[3]=y2;
                isfozen=false;
                return false;
            }
        }
    }
    isfozen=false;
    return true;
}
bool model::iswin()
{
    for(int i=0;i<allsize;i++)
    {
        if(gamemap[i]!=0)
        {
            return false;
        }
    }
    gamestate=WIN;
    return true;
}
int *model::gethit()
{
    return hitarr;
}
bool model::iscononeline(int x1, int y1, int x2, int y2)
{
    if(x1==x2)
    {
        if(y1>y2)
            std::swap(y1,y2);
        for(int i=y1+1;i!=y2;i++)
        {
            if(gamemap[x1*maxcol+i]!=0)
            {
                return false;
            }
        }
        if(!isfozen)
        {
            point p1(x1,y1),p2(x2,y2);
            points.clear();
            points.push_back(p1);
            points.push_back(p2);
        }
        return true;
    }
    if(y1==y2)
    {
        if(x1>x2)
            std::swap(x1,x2);
        for(int i=x1+1;i!=x2;i++)
        {
            if(gamemap[i*maxcol+y1]!=0)
            {
                return false;
            }
        }
        if(!isfozen)
        {
            point p1(x1,y1),p2(x2,y2);
            points.clear();
            points.push_back(p1);
            points.push_back(p2);
        }
        return true;
    }
    return false;
}
bool model::iscontwoline(int x1, int y1, int x2, int y2)
{
    if(y1>y2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }
    if(x1<x2)
    {
        if(gamemap[x1*maxcol+y2]==0)
        {
            if(iscononeline(x1,y1,x1,y2)&&iscononeline(x1,y2,x2,y2))
            {
                if(!isfozen)
                {
                    point p1(x1,y1),p2(x1,y2),p3(x2,y2);
                    points.clear();
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p3);
                }
                return true;
            }
        }
        if(gamemap[x2*maxcol+y1]==0)
        {
            if(iscononeline(x1,y1,x2,y1)&&iscononeline(x2,y1,x2,y2))
            {
                if(!isfozen)
                {
                    point p1(x1,y1),p2(x2,y1),p3(x2,y2);
                    points.clear();
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p3);
                }
                return true;
            }
        }
    }
    else
    {
        if(gamemap[x2*maxcol+y1]==0)
        {
            if(iscononeline(x1,y1,x2,y1)&&iscononeline(x2,y1,x2,y2))
            {
                if(!isfozen)
                {
                    point p1(x1,y1),p2(x2,y1),p3(x2,y2);
                    points.clear();
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p3);
                }
                return true;
            }
        }
        if(gamemap[x1*maxcol+y2]==0)
        {
            if(iscononeline(x1,y1,x1,y2)&&iscononeline(x1,y2,x2,y2))
            {
                if(!isfozen)
                {
                    point p1(x1,y1),p2(x1,y2),p3(x2,y2);
                    points.clear();
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p3);
                }
                return true;
            }
        }
    }
    return false;
}
bool model::isconthrline(int x1, int y1, int x2, int y2)
{
    if(y1>y2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }
    for(int i=0;i<maxrow;i++)
    {
        if(i!=x1&&i!=x2)
        {
            if(gamemap[i*maxcol+y1]==0&&gamemap[i*maxcol+y2]==0)
            {
                if(iscononeline(x1,y1,i,y1)&&iscononeline(i,y1,i,y2)&&iscononeline(i,y2,x2,y2))
                {
                    if(!isfozen)
                    {
                        point p1(x1,y1),p2(i,y1),p3(i,y2),p4(x2,y2);
                        points.clear();
                        points.push_back(p1);
                        points.push_back(p2);
                        points.push_back(p3);
                        points.push_back(p4);
                    }
                    return true;
                }
            }
        }
    }
    for(int i=0;i<maxcol;i++)
    {
        if(i!=y1&&i!=y2)
        {
            if(gamemap[x1*maxcol+i]==0&&x2*gamemap[x2*maxcol+i]==0)
            {
                if(iscononeline(x1,y1,x1,i)&&iscononeline(x1,i,x2,i)&&iscononeline(x2,i,x2,y2))
                {
                    if(!isfozen)
                    {
                        point p1(x1,y1),p2(x1,i),p3(x2,i),p4(x2,y2);
                        points.clear();
                        points.push_back(p1);
                        points.push_back(p2);
                        points.push_back(p3);
                        points.push_back(p4);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
bool model::iscanconnect(int x1, int y1, int x2, int y2)
{
    if(x1==x2&&y1==y2)
        return false;
    if(gamemap[x1*maxcol+y1]==0||gamemap[x2*maxcol+y2]==0)
        return false;
    if(gamemap[x1*maxcol+y1]!=gamemap[x2*maxcol+y2])
    {
        return false;
    }
    if(iscononeline(x1,y1,x2,y2))
        return true;
    if(iscontwoline(x1,y1,x2,y2))
        return true;
    if(isconthrline(x1,y1,x2,y2))
        return true;
    return false;
}

bool model::iscanline(int x1, int y1, int x2, int y2)
{
    if(iscanconnect(x1,y1,x2,y2))
    {
        gamemap[x1*maxcol+y1]=0;
        gamemap[x2*maxcol+y2]=0;
        score+=10;
        return true;
    }
    return false;
}

void model::gamereset()
{
    srand((unsigned)time(0));
    int i=0;
    int j=allsize-1;
    while(i<j)
    {
        while(gamemap[i]==0)
            i++;
        while(gamemap[j]==0)
            j--;
        std::swap(gamemap[i],gamemap[j]);
        i++;
        j--;
    }
}






