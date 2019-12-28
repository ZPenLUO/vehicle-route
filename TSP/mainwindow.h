#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTime>
#include <QTimer>
#include "mythread.h"
#include "dialog.h"
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Rethread *ref;
    Dialog *mydlg;
    void TableUpdate();
    explicit MainWindow(QWidget *parent = nullptr);
    QTimer *timer;
    ~MainWindow();

private slots:

    void on_Btn_Load_clicked();

    void on_Btn_Solution_clicked();

    void on_Btn_Reset_clicked();

    void on_SpinP_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
private slots:
    void display(int pg, double lt, double df, double ov, double ct);
    void on_SpinO_valueChanged(int arg1);
    void on_Btn_Add_clicked();
    void on_Btn_Export_clicked();
    void on_DataTable_cellClicked(int row, int column);
    void on_DataTable_itemChanged(QTableWidgetItem *item);
};

#endif // MAINWINDOW_H
