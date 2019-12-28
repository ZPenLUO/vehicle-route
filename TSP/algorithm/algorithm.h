#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QVector>
#include "math.h"

class Path{
public:
    Path();
    ~Path();
    void display();
    void init();
    void estimate();
    void cost_cal();
    void over_cal(int i, int l);
    Path& operator = (const Path &path2);

    static int N; // number of points
    static int P; // number of sub path

    int *p; // path - point id sequence
    int *subdiv; // sub dividing points
    double *sublength; // length of sub path
    double cost; // total cost
    double over; // over cost
};

class algorithm
{
public:
    algorithm();
    virtual ~algorithm();
    virtual void execute();
};

#endif // ALGORITHM_H
