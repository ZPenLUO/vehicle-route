#include "mainwindow.h"
#include <QApplication>
#include "main.h"
#include <ctime>
#include <cstdlib>

TSPData tsp;
int R=1000;
int rps;
bool drawable = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qsrand(uint(QTime(0,0,0).msecsTo(QTime::currentTime())));

    w.show();
    return a.exec();
}

bool IntersectingLine(const QPoint &A1, const QPoint &A2,
                      const QPoint &B1, const QPoint &B2)
{
    if(A1==B1||A1==B2||A2==B1||A2==B2) return false;

    int T1 = cross(A1,A2,B1);
    int T2 = cross(A1,A2,B2);
    int T3 = cross(B1,B2,A1);
    int T4 = cross(B1,B2,A2);

    if(T1==0&&T2==0){
        int Axup = Max(A1.x(),A2.x());
        int Axlow = Min(A1.x(),A2.x());
        int Bxup = Max(B1.x(),B2.x());
        int Bxlow = Min(B1.x(),B2.x());
        return ((Axup>Bxlow)&&(Axlow<Bxlow))||((Bxup>Axlow)&&(Bxlow<Axup));
    }
    return !(double(T1)*double(T2)>0.0000001||double(T3)*double(T4)>0.0000001);
}

