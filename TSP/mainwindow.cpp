#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ref = new Rethread();
    mydlg = new Dialog();
    connect(mydlg,&Dialog::sendxy,[=](int xx,int yy){
        if(!tsp.existed(QPoint(xx,yy))){
            tsp.addpoint(xx,yy);
            tsp.setdata();
            TableUpdate();
            ui->SpinO->setMaximum(tsp.getN());
            qDebug("%d,%d added!",xx,yy);
        }
        else {
            QMessageBox msg;
            msg.setText("Existed same point, fail to add point!");
            msg.exec();
        }
    });

    timer = new QTimer();

    QObject::connect(timer,&QTimer::timeout,[=](){
        ui->lcd_Timer->display(ui->lcd_Timer->value()+0.1);
        if(rps==R)
            timer->stop();
    });

    QObject::connect(ref,SIGNAL(display(int,double,double,double,double)),
                     this,SLOT(display(int,double,double,double,double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Btn_Load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(nullptr,
                                                    "Open tsp file",
                                                    ".",
                                                    "*.tsp"
                                                    );
    if(filename!=nullptr){
        QFile file(filename);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            qDebug("Read failure");
        }
        else {
            QTextStream readfile(&file);
            QString line;
            QString num1,num2;
            tsp.resetdata();
            while(!readfile.atEnd())
            {
                readfile>>line>>num1>>num2;
                if(!tsp.existed(QPoint(num1.toInt(),num2.toInt()))){
                    tsp.addpoint(num1.toInt(),num2.toInt());
                }
            }
            tsp.setdata();

            ui->SpinO->setMinimum(1);
            ui->SpinO->setMaximum(tsp.getN());
            ui->NLCD->display(tsp.getN());
            TableUpdate();
            file.close();
        }
    }
}

void MainWindow::on_Btn_Solution_clicked()
{
    if(tsp.getN()>1)
    {
        ui->lcd_Timer->display(0);
        tsp.setoptimal(INFINITE);
        R = ui->SpinR->value();
        ui->BarP->setValue(0);
        ui->BarP->setMaximum(R);

        antcolony *aco = new antcolony(tsp.getN(),tsp.getP(),tsp.getK(),
                                       ui->SpinAnt->value(),
                                       ui->SpinK1->value(),
                                       ui->SpinK2->value(),
                                       ui->SpinV->value());
        Mythread *t = new Mythread(aco);
        ref->obj = t;
        QObject::connect(t,SIGNAL(finished()),t,SLOT(deleteLater()));

        connect(t,&Mythread::finished,[=](){
            ui->Solution->setRowCount(tsp.getN()+tsp.getP());
            for(int n=0;n<tsp.getN()+tsp.getP();n++){
                ui->Solution->setItem(n,0,new QTableWidgetItem(QString::number(tsp.getpath(n))));
                ui->Solution->setItem(n,1,new QTableWidgetItem(QString::number(tsp.getpasstime(n))));
                ui->Solution->setItem(n,2,new QTableWidgetItem(QString::number(tsp.gettime(tsp.getpath(n)))));
            }});

        timer->start(100);
        t->start();
        ref->start();
    }
}

void MainWindow::on_Btn_Reset_clicked()
{
    tsp.resetdata();
    TableUpdate();
    ui->Map->repaint();

    ui->NLCD->display(0);
}

void MainWindow::on_SpinP_valueChanged(int arg1)
{
    tsp.setP(arg1);
}

void MainWindow::display(int pg, double lt, double df, double ov, double ct){
    ui->Map->repaint();
    QString text = QString("length:%1 |var:%2 |over:%3 |cost: %4").arg(QString::number(lt),
                                                                       QString::number(df),
                                                                       QString::number(ov),
                                                                       QString::number(ct));
    ui->label_Result->setText(text);
    ui->BarP->setValue(pg);
}

void MainWindow::on_SpinO_valueChanged(int arg1)
{
    tsp.setorigin(arg1-1);
    ui->Map->repaint();
}

void MainWindow::on_Btn_Add_clicked()
{
    mydlg->exec();
}

void MainWindow::on_Btn_Export_clicked()
{
    QString filename = QFileDialog::getSaveFileName(nullptr,"Export","./tspdata","TSP File(*.tsp);;All(*)");
    if(""!=filename){
        QFile file(filename);
        if(file.open(QFile::WriteOnly)){
            file.close();
        }
        else cout<<"fail to create file "<<filename;
    }
}

void MainWindow::TableUpdate()
{
    ui->DataTable->setRowCount(tsp.getN());
    for(int n=0;n<tsp.getN();n++){
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(tsp.getpoint(n)->x())+","+QString::number(tsp.getpoint(n)->y()));
        ui->DataTable->setItem(n,0,item);
        item->setFlags(Qt::ItemFlag::ItemIsEditable);
    }
}

void MainWindow::on_DataTable_cellClicked(int row, int column)
{
    if(0<column)
        ui->Map->select = row;
    else ui->Map->select = -1;

    ui->Map->repaint();
}

void MainWindow::on_DataTable_itemChanged(QTableWidgetItem *item)
{
    if(1==item->column()){
        QString text = item->text();
        int num = text.toInt();
        int i = item->row();
        tsp.settime(i,num);
        if(0==num)
            item->setText("");
    }
}
