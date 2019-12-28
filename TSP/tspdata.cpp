#include "tspdata.h"
#include "math.h"

double inline distance(const QPoint &p1,const QPoint &p2){
    return pow(pow(p1.x()-p2.x(),2)+pow(p1.y()-p2.y(),2),0.5);
}

int TSPData::getN()
{
    return N;
}

int TSPData::getP()
{
    return P;
}

int TSPData::getK()
{
    return K;
}

int TSPData::getorigin()
{
    return origin;
}

int TSPData::getpath(int i)
{
    return path[i];
}

double TSPData::getcost()
{
    return cost;
}

double TSPData::getlength()
{
    return length;
}

double TSPData::getvar()
{
    return var;
}

double TSPData::getdist(int i, int j)
{
    return d[i][j];
}

QPoint *TSPData::getpoint(int i)
{
    return p[i];
}

int TSPData::gettime(int i)
{
    return time[i];
}

double TSPData::getpasstime(int i)
{
    double t = 0;
    for(int n=0;n<i;n++){
        if(path[n] == origin) t = 0;
        t += d[path[n]][path[n+1]];
    }
    return t;
}

double TSPData::getover()
{
    return over;
}

void TSPData::setP(int i)
{
    P = i;
}

void TSPData::setorigin(int i)
{
    origin = i;
}

void TSPData::setoptimal(double c, double l, double v, double o, int *p)
{
    if(nullptr != p)
        for(int n=0;n<N+P;n++){
            path[n] = p[n];
        }
    cost = c;
    length = l;
    var = v;
    over = o;
}

void TSPData::settime(int i, int t)
{
    time[i] = t;
    qDebug("%d:%d",i,time[i]);
}

bool TSPData::existed(const QPoint ep)
{
    for(int n=0;n<N;n++)
        if(ep==*p[n])
            return true;
    return false;
}

void TSPData::setdata(){
    K=1;
    double max=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            d[i][j] = distance(*p[i],*p[j]);
            if(max<d[i][j]) max = d[i][j];
        }
        d[i][i] = INFINITE;
    }
    while(max>1){
        max/=10;
        K*=10;
    }
    qDebug("%f,%d",max,K);
}

void TSPData::addpoint(int x, int y)
{
    p[N] = new QPoint(x,y);
    time[N++] = 0;
}

void TSPData::resetdata(){
    for(int i = 0;i<N;i++)
        delete p[i];
    cost = INFINITE;
    N=0;
}
