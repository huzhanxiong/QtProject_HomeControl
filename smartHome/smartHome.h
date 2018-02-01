#ifndef SMARTHOME_H
#define SMARTHOME_H

#include <QMainWindow>
#include <QMovie>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class smartHome;
}

class smartHome : public QMainWindow
{
    Q_OBJECT

public:
    explicit smartHome(QWidget *parent = 0);
    ~smartHome();

private slots:
    void on_Btn_startTrans_clicked();
    void Read_Data();

    void on_Btn_TV_clicked();

    void on_Btn_sound_clicked();

    void on_Btn_air_clicked();

    void on_Btn_light_clicked();

    void on_slider_window_sliderMoved(int position);

    void on_Btn_clear_clicked();

private:
    Ui::smartHome *ui;

private:
    QMovie *movie_wave;
    QSerialPort *serialPort;
};

#endif // SMARTHOME_H
