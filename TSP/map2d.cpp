#include "map2d.h"
#include "main.h"

Map2D::Map2D(QWidget *parent) : QWidget(parent)
{

}

void Map2D::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    drawable = false;
    QPainter pt(this);

    pt.setPen(QPen(QColor(255,100,100),5));
    pt.setBrush(QBrush(QColor(200,255,200)));
    pt.drawRect(0,0,this->width(),this->height());
    pt.setBrush(QBrush(QColor(0,0,200,20)));

    pt.setPen(QPen(QColor(0,0,0),5));
    pt.drawLine(50,height()-50,100,height()-50);
    pt.drawText(10,height()-45,"Scale");
    pt.drawText(110,height()-45,QString::number(50/scale));

    if(tsp.getN()>0){
        pt.setPen(QPen(QColor(255,0,255),5));
        for(int i=0;i<tsp.getN();i++){
            pt.drawPoint(QPoint(*(tsp.getpoint(i)))*scale+QPoint(dx,dy));
        }

        pt.setPen(QPen(QColor(255,0,0),10));
        pt.drawPoint(QPoint(*(tsp.getpoint(tsp.getorigin()))*scale+QPoint(dx,dy)));

        pt.setPen(QPen(QColor(0,0,255),2));
        if(tsp.getcost()<9999999){
            int j=0;
            for(int i=1;i<tsp.getN()+tsp.getP();i++){
                pt.drawLine(QPoint(*(tsp.getpoint(tsp.getpath(i-1))))*scale+QPoint(dx,dy),
                        QPoint(*(tsp.getpoint(tsp.getpath(i)))*scale+QPoint(dx,dy)));
                if(tsp.getpath(i) == tsp.getorigin())
                    pt.setPen(QPen(col[j++],2));
            }
        }

        if(select>-1){
            pt.setPen(QPen(QColor(255,0,0),10));
            pt.drawText(QPoint(*(tsp.getpoint(select))*scale+QPoint(dx-4,dy-8)),"↓");
            pt.setPen(QPen(QColor(0,0,255),10));
            pt.drawPoint(QPoint(*(tsp.getpoint(select))*scale+QPoint(dx,dy)));
        }
    }
    drawable = true;
}


void Map2D::mousePressEvent(QMouseEvent *e){
    if(!click&&e->button()==Qt::LeftButton){
        setCursor(QCursor(Qt::OpenHandCursor));
        click = true;
        mx = e->x();
        my = e->y();
    }
}

void Map2D::mouseMoveEvent(QMouseEvent *e){
    if(click){
        dx += e->x() - mx;
        dy += e->y() - my;
        mx = e->x();
        my = e->y();
        repaint();
    }
}

void Map2D::mouseReleaseEvent(QMouseEvent *e){
    setCursor(QCursor(Qt::ArrowCursor));
    if(e->button()==Qt::LeftButton)
        click = false;
}

void Map2D::wheelEvent(QWheelEvent *e){
    if(e->delta()>0)
        scale *= 1.25;
    else scale /= 1.25;
    repaint();
}
