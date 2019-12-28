#include "main.h"
#include "mainwindow.h"
#include "genetic.h"


genetic::genetic(int n, int p, int k, int m)
{
    N = n;
    M = m;
    K = k;
    P = p;

    Cost = new double[uint(M+2)];

    g = new int*[uint(N+P)];
    for(int i=0;i<N+P;i++)
        g[i] = new int[uint(M+2)];

    tab = new int[uint(N)];
    query = new int[uint(N)];
}

genetic::~genetic(){
    delete [] Cost;

    for(int i=0;i<N+P;i++)
        delete [] g[i];

    delete [] g;

    delete [] tab;

    delete [] query;
}

void genetic::execute()
{
    init();
    for(int t =0;t<1000;t++){
        linemutation();
    }
}

int genetic::pickbest()
{
    int bm = 0;
    for(int m=1;m<M;m++)
        bm = MinID(bm,m,Cost[bm],Cost[m]);
    return bm;
}

int genetic::rpick()
{
    int k=0;
    for(int n=0;n<N;n++)
        if(tab[n]>0)
            query[k++] = n;
    return query[rand()%k];
}

void genetic::tabinit(){
    for(int n=0;n<N;n++)
        tab[n] = 1;
    tab[tsp.getorigin()] = P;
}

void genetic::init(){
    int n;
    for(int m=0;m<M;m++)
    {
        tabinit();

        g[0][m] = tsp.getorigin();
        tab[tsp.getorigin()]--;

        for(n=1;n<N+P-1;n++){
            g[n][m] = rpick();
            tab[g[n][m]]--;
        }

        if(P>0){
            g[n][m] = tsp.getorigin();
        }
        else {
            g[n][m] = rpick();
        }
        evaluate(m);
    }
}

void genetic::evaluate(int m){
    Cost[m]=0;
    for(int n=0;n<N+P-1;n++){
        Cost[m] += tsp.getdist(g[n][m],g[n+1][m]);
    }
    qDebug("%f",Cost[m]);
}

bool genetic::match(int i, int m, int k){
    int l = 0;
    for(int n=0;n<i;n++){
        if(g[n][m] == k)
            l++;
    }
    if(l>0){
        if(k!=tsp.getorigin())
            return false;
        else if(g[i-1][m]==k)
            return false;
        else if(l<P+1)
            return true;
        else return false;
    }
    return true;
}

void genetic::copychm(int obj, int sub)
{
    for(int n=0;n<N;n++){
        g[n][obj] = g[n][sub];
    }
    Cost[obj] = Cost[sub];
}

void genetic::crossover(){
    int *que = new int[uint(2*N)];
    int n;
    int i,j;
    //int r = rand()%M;
    //for(int m=0;m<M;m++)
    {
        for(n=0;n<N+P;n++){
            if(rand()%2==0){
                que[n*2] = g[n][0];
                que[n*2+1] = g[n][1];
            }
            else {
                que[n*2] = g[n][1];
                que[n*2+1] = g[n][0];
            }
        }
        i=0;    j=0;
        for(n=0;n<2*(N+P);n++){
            if(match(i,M,que[n]))
                g[i++][M] = que[n];
            else{
                g[j++][M+1] = que[n];
            }
        }
        evaluate(M);
        evaluate(M+1);

        if(Cost[M]<Cost[0])
            copychm(0,M);
        if(Cost[M+1]<Cost[1])
            copychm(1,M+1);
    }
    delete [] que;
}



void genetic::linemutation(){
    int k1,k2;
    for(int m=0;m<M;m++)
    {
        for(int i=0;i<20;i++){
            k1=rand()%(N+P-1);
            k2=rand()%(N+P-1);
            while(k1-k2<=1&&k2-k1<=1)
                k2 = rand()%(N+P-1);

            if(IntersectingLine(*tsp.getpoint(g[k1][m]),*tsp.getpoint(g[k1+1][m]),
                                *tsp.getpoint(g[k2][m]),*tsp.getpoint(g[k2+1][m]))){
                if(k1>k2) Swap(&k1,&k2);
                while(k1+1<k2){
                    Swap(&(g[k1+1][m]),&(g[k2][m]));
                    k1++;
                    k2--;
                }
            }
        }
        evaluate(m);
    }
}

void genetic::pointmutation()
{
    int k1,k2;
    double d1,d2;
    for(int m=0;m<M;m++)
    {
        for(int i=0;i<20;i++){
            k1=rand()%(N+P-2)+1;
            k2=rand()%(N+P-2)+1;
            while(k1==k2)
                k2 = rand()%(N+P-2)+1;

            d1 = tsp.getdist(g[k1-1][m],g[k1][m]) + tsp.getdist(g[k1][m],g[k1+1][m])
                    + tsp.getdist(g[k2-1][m],g[k2][m]) + tsp.getdist(g[k2][m],g[k2+1][m]);

            d2 = 0;

            if(d2 < d1){
                if(k1>k2) Swap(&k1,&k2);
                while(k1+1<k2){
                    Swap(&(g[k1][m]),&(g[k2][m]));
                    k1++;
                    k2--;
                }
            }
        }
        evaluate(m);
    }
}
