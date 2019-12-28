#ifndef MAP2D_H
#define MAP2D_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>

class Map2D : public QWidget
{
    Q_OBJECT
public:
    explicit Map2D(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    double scale = 1.0;
    int dx=0,mx;
    int dy=0,my;
    int select = -1;
    bool click=false;
    QColor col[6] = {{255,0,0},{0,255,0},{0,255,255},{255,255,0},{255,0,255},{0,0,0}};
signals:

public slots:
};

#endif // MAP2D_H
