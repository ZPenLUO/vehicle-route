#include "algorithm.h"
#include "main.h"
#include "mainwindow.h"
int Path::N;
int Path::P;

algorithm::algorithm()
{
    Path::N = tsp.getN();
    Path::P = tsp.getP();
}

algorithm::~algorithm(){
    qDebug("algorithm clear!");
}

void algorithm::execute(){
    qDebug("no algorithm");
}

Path::Path()
{
    subdiv = new int[uint(P+1)];

    p = new int[uint(N+P)];

    sublength = new double[uint(P)];

    cost = INFINITE;
}

Path::~Path()
{
    delete [] subdiv;
    delete [] p;
    delete [] sublength;
}

void Path::display()
{
    QString sout;
    for (int n=0;n<N+P;n++) {
        sout += QString::number(p[n]) + " ";
    }
    cout<<sout;
}

void Path::init()
{
    this->p[0] = tsp.getorigin(); // begin with original point
    this->subdiv[0] = 0;
    for (int n = 0;n < P;n++){
        this->sublength[n] = 0;
    }
    over = 0;
}

void Path::estimate()
{
    int t = 0;
    init();
    for(int i=1;i<N+P;i++){
        sublength[t] += tsp.getdist(p[i-1],p[i]); // get length of sub path

        over_cal(i,t);

        if(p[i] == tsp.getorigin()){
            t++;
            subdiv[t] = i;
        }
    }
    cost_cal();
}

void Path::cost_cal()
{
    double dif = 0,len = 0;
    for (int n = 0;n < P;n++){
        len += this->sublength[n];
    }

    for (int n = 0;n < P;n++){
        dif += pow(this->sublength[n] - len/P,2);
    }
    dif = pow(dif,0.5);

    cost = dif + len + over;
    if(cost < tsp.getcost()){
        tsp.setoptimal(cost,len,dif,over,p);
    }
}

void Path::over_cal(int i, int l) // calculate over time cost
{
    if(tsp.gettime(p[i])>0&&tsp.gettime(p[i])<sublength[l])
        over += sublength[l] - tsp.gettime(p[i]);
}

Path& Path::operator =(const Path &path2)
{
    for (int n = 0;n < N + P;n++) {
        this->p[n] = path2.p[n];
    }
    for (int n = 0;n < P;n++){
        this->sublength[n] = path2.sublength[n];
    }
    for (int n = 0;n < P + 1;n++){
        this->subdiv[n] = path2.subdiv[n];
    }
    this->cost = path2.cost;

    return *this;
}
