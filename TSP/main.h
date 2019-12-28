#ifndef MAIN_H
#define MAIN_H

#include <QLine>
#include <QDebug>
#include "tspdata.h"

#define cout qDebug()<<__FILE__<<"\t"<<__LINE__<<":"

inline int cross(const QPoint &A,const QPoint &B,const QPoint &C){
    return ((C.x()-A.x())*(B.y()-A.y())-(C.y()-A.y())*(B.x()-A.x()));
}

template <typename T>
inline T const Max(const T d1, const T d2)
{
    return (d1>d2)?d1:d2;
}

template<typename T>
inline T const Min(const T d1, const T d2)
{
    return (d1<d2)?d1:d2;
}

template <typename T1,typename T2>
inline T1 const MaxID(T1 i1,T1 i2,T2 d1,T2 d2)
{
    return (d1>d2)?i1:i2;
}

template <typename T1,typename T2>
inline T1 const MinID(T1 i1,T1 i2,T2 d1,T2 d2)
{
    return (d1<d2)?i1:i2;
}

template <typename T>
inline void Swap(T *a1,T *a2){
    T a = *a1;
    *a1 = *a2;
    *a2 = a;
}

bool IntersectingLine(const QPoint &p11,const QPoint &p12,
                      const QPoint &p21,const QPoint &p22);

extern TSPData tsp;
extern int rps;
extern int R;
extern bool drawable;

#endif // MAIN_H
