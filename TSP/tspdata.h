#ifndef TSPDATA_H
#define TSPDATA_H

#define INFINITE 9999999
#define MAXN 1000
#define MAXP 10

#include <QPoint>

struct TSPData
{
private:
    int N; // number of points
    int P; // number of paths
    int K; // cardinal number of each distance
    int origin; //original point
    int path[MAXN+MAXP]; //optimal path
    double cost; //optimal cost of algorithm
    double length; // total length
    double var; // variance of sub path
    double over; // time over cost
    double d[MAXN][MAXN];// distance matrix
    QPoint *p[MAXN];
    int time[MAXN];
public:
    TSPData(){
        origin=0;
        P=1;
    }
    //function
    int getN();
    int getP();
    int getK();
    int getorigin();
    int getpath(int i);
    double getcost();
    double getlength();
    double getvar();
    double getdist(int i,int j);
    QPoint *getpoint(int i);
    int gettime(int i);
    double getpasstime(int i);
    double getover();

    void setP(int i);
    void setorigin(int i);
    void setoptimal(double c,double l = 0,double v = 0,double o = 0,int *p = nullptr);
    void settime(int i,int t);

    bool existed(const QPoint ep);
    void setdata();//
    void addpoint(int x,int y);
    void delpoint();
    void resetdata();//
};

#endif // TSPDATA_H
