#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include "algorithm.h"

class antcolony : public algorithm{
public:
    antcolony(int n, int p, int k, int AN, int k1, int k2, double v);
    ~antcolony();
    //variables
    int N;  // number of points
    int P;  // number of path divisions
    int K;  // distance length cardinal number
    int AN; // number of ants
    int K1; // pheromone coefficient - decide pheromone impact when travesing
    int K2; // heuristic coefficient - decide heuristic impact when travesing
    double V; // pheromone volatilization

    Path *path; // result of multiple ants

    int *tab; // tabu table - record points not traversed

    double **phe; // 2D pheromone matrix
    double Maxphe; // record maximum pheromone value
    double Minphe; // record minimum pheromone value

    //functions
    void execute();
    void init();
    void search_init(int m);

    int next(int pre);
    int getmaxphe(int pre);

    void set_phe_limit();
    bool search();
    void layphe(Path& p);
    void updatephe();
    void optimize();
    void mutate();
};

#endif // ANTCOLONY_H
