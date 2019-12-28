
#include "main.h"
#include "mainwindow.h"

Mythread::~Mythread()
{
    delete alg;
    qDebug("My thread clear!");
}

Mythread::Mythread(algorithm *al)
{
    alg = al;
}

void Mythread::run(){
    qsrand(uint(QTime(0,0,0).msecsTo(QTime::currentTime())));
    if(alg) alg->execute();
}

Rethread::Rethread(){

}

Rethread::~Rethread(){
    qDebug("Refresh thread deleted!");
}

void Rethread::run(){
    while(!obj->isFinished()){
        if(drawable){
            drawable = false;
            emit display(rps,tsp.getlength(),tsp.getvar(),tsp.getover(),tsp.getcost());
        }
    }
    emit display(rps,tsp.getlength(),tsp.getvar(),tsp.getover(),tsp.getcost());
}
