#include "main.h"
#include "mainwindow.h"
#include "antcolony.h"


antcolony::antcolony(int n,int p,int k,int ant,int k1,int k2,double v) :
    N(n), P(p), K(k), AN(ant), K1(k1), K2(k2), V(v)
{
    phe = new double*[uint(N)];
    for(int n=0;n<N;n++)
        phe[n] = new double[uint(N)];

    tab = new int[uint(N)];

    path = new Path[uint(AN+1)];
}

antcolony::~antcolony(){
    for(int n=0;n<N;n++)
        delete [] phe[n];
    delete [] phe;

    delete [] tab;

    delete [] path;
}

void antcolony::execute()
{
    init();
    int i = 0;

    for(rps = 0; rps < R; rps++){
        if(search()){
            i++;
            if(i == 5){
                mutate(); // mutation strategy for unchanged iterations
            }
        }
        else {
            i = 0;
        }
        optimize();

        layphe(path[0]);

        updatephe();
    }
}

bool antcolony::search(){
    int min = 0;
    double mcost = INFINITE;
    int p = 0;
    for(int m = 1; m <= AN; m++){
        search_init(m);

        p = 0;

        for(int i = 1; i < N + P ; i++){
            if(rand() % 100 > 10)
                path[m].p[i] = getmaxphe(path[m].p[i - 1]);
            else path[m].p[i] = next(path[m].p[i - 1]);

            tab[path[m].p[i]]--;

            path[m].sublength[p] += tsp.getdist(path[m].p[i - 1], path[m].p[i]);

            path[m].over_cal(i, p);

            if(path[m].p[i] == tsp.getorigin()){
                p++;
                path[m].subdiv[p] = i;
            }
        }
        path[m].cost_cal();

        if(path[m].cost<mcost){
            mcost = path[m].cost;
            min = m;
        }
    }

    if(mcost < path[0].cost){
        path[0] = path[min];
        set_phe_limit();
        return false;
    }
    return true;
}

void antcolony::optimize(){
    int k1, k2;
    for(int i = 0; i < N / 5 * P; i++){
        k1 = rand()%(N + P - 1);
        k2 = k1;

        while(k1 - k2 <= 1 && k2 - k1 <= 1)
            k2 = rand() % (N + P - 1);

        if(IntersectingLine(*tsp.getpoint(path[0].p[k1]), *tsp.getpoint(path[0].p[k1+1]),
                            *tsp.getpoint(path[0].p[k2]), *tsp.getpoint(path[0].p[k2+1])))
        { // deal with intersecting route
            //if(samepart(opath, k1, k2)){
                if(k1 > k2) Swap(&k1, &k2);
                while(k1 + 1 < k2){
                    Swap(&(path[0].p[k1 + 1]), &(path[0].p[k2]));
                    k1++;
                    k2--;
                }
            //}
            //else {
            }
    }
    path[0].estimate();
    set_phe_limit();
}

void antcolony::mutate()
{
//    int head = rand()%(N+P-1);
//    int tail = rand()%(N+P-1-head);
//    for(int i = head; i < head+tail ;i++){
    //    phe[i-1][i] = Minphe;
    //}
    //path[0].estimate();
    //set_phe_limit();
}

void antcolony::search_init(int m){
    for(int i = 0; i < N; i++) // recover tabu table
        tab[i] = 1;
    tab[tsp.getorigin()] = P - 1;
    path[m].init();
}

void antcolony::layphe(Path &pt) // accumulate pheromone
{
    for(int i = 1; i < N + P; i++)
    {
#if 1
        if(rand()%(N+P)<P){ // pheromone reset probably
            phe[pt.p[i - 1]][pt.p[i]] = Minphe;
            phe[pt.p[i]][pt.p[i - 1]] = Minphe;
            continue;
        }
#endif
        phe[pt.p[i - 1]][pt.p[i]] += K / pt.cost;
        if(phe[pt.p[i - 1]][pt.p[i]] > Maxphe)
            phe[pt.p[i - 1]][pt.p[i]] = Maxphe;
        phe[pt.p[i]][pt.p[i - 1]] = phe[pt.p[i - 1]][pt.p[i]];
    }
}

int antcolony::next(int pre){ // get next point to traverse
    double tp = 0;
    int l = tsp.getorigin();
    for(int i = 0; i < N; i++){ // count total accessible point total weight
        if(tab[i]>0){
            tp += pow(phe[pre][i], K1) * pow((K / tsp.getdist(pre, i)), K2);
            l = i;
        }
    }
    if(tp > 0){
        double w = 0;
        double p = rand() / double(RAND_MAX); // pointer - point to a accessible point
        for(int i = 0; i < N; i++)
            if(tab[i] > 0){
                w += pow(phe[pre][i], K1) * pow((K / tsp.getdist(pre, i)), K2);
                if(w / tp > p)
                    return i;
            }
    }
    return l;
}

int antcolony::getmaxphe(int pre) // greedy strategy
{
    int maxid = tsp.getorigin();
    double maxv = 0; // record maximun value
    for(int i = 0; i < N; i++){
        if(tab[i]>0){
            double tp = pow(phe[pre][i], K1) * pow((K / tsp.getdist(pre, i)), K2);
            if(maxv < tp)
            {
                maxv = tp;
                maxid = i;
            }
        }
    }
    return maxid;
}

void antcolony::set_phe_limit() // update pheromone limit
{
    Maxphe = K / ((1 - V) * path[0].cost);
    Minphe = Maxphe / (2 * N);
}

void antcolony::updatephe() // volatilize
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            phe[i][j] *= V;
            if(phe[i][j] < Minphe)
                phe[i][j] = Minphe;
        }
}

void antcolony::init(){
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            phe[i][j] = 1/double(K);
}
