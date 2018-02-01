#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QMovie>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "smartHome.h"


namespace Ui {
class homePage;
}

class homePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit homePage(QWidget *parent = 0);
    ~homePage();

private slots:
    void on_Btn_startTrans_clicked();
    void Read_Data();

    void on_Btn_livingroom_clicked();

private:
    Ui::homePage *ui;

private:
    QMovie *movie_wave;
    QSerialPort *serialPort;
};


#endif // HOMEPAGE_H
