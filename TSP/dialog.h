#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void sendxy(int x,int y);
private slots:
    void on_Btn1_clicked();

    void on_Btn2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
