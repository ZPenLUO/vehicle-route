#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QThread>
#include "algorithm/algorithm.h"
#include "algorithm/genetic.h"
#include "algorithm/antcolony.h"

class Mythread: public QThread
{
    Q_OBJECT
public:
    algorithm *alg;

    Mythread();
    ~Mythread();
    Mythread(algorithm *al);
    void run();
};

class Rethread: public QThread
{
    Q_OBJECT
public:
    Mythread *obj;

    Rethread();
    ~Rethread();
    void run();
signals:
    void display(int pg,double lt,double dif,double ov,double ct);
};

#endif // MYTHREAD_H
