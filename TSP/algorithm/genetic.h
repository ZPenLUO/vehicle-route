#ifndef GENETIC_H
#define GENETIC_H

#include "algorithm.h"

class genetic : public algorithm
{
public:
    genetic(int n, int p, int k, int m);
    ~genetic();
    int **g;
    double *Cost;
    int N;
    int K;
    int M;
    int P;
    int *tab;
    int *query;

    void execute();
    int pickbest();
    int rpick();
    bool match(int i, int m, int k);
    void copychm(int obj,int sub);
    void init();
    void tabinit();
    void crossover();
    void linemutation();
    void pointmutation();
    void evaluate(int m);
};

#endif // GENETIC_H
