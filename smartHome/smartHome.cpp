#include "smartHome.h"
#include "ui_smartHome.h"
#include <QMessageBox>


smartHome::smartHome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::smartHome)
{
    ui->setupUi(this); 

    movie_wave = new QMovie(":/image/wave.gif");
    ui->movie_wave->setMovie(movie_wave);
    movie_wave->start();
    movie_wave->stop();
    ui->BaudRateBox->setCurrentIndex(6);
    ui->DataBitBox->setCurrentIndex(3);

    serialPort = new QSerialPort;

    //查看可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        //QSerialPort serial;
        serialPort->setPort(info);

        //ui->SerialPortBox->addItem(" ");
        if(serialPort->open(QIODevice::ReadWrite))
        {
            ui->SerialPortBox->addItem(serialPort->portName());
            serialPort->close();
        }
    }
}


smartHome::~smartHome()
{
    serialPort->deleteLater();

    delete movie_wave;
    delete ui;
}

void smartHome::on_Btn_startTrans_clicked()
{
    if(ui->Btn_startTrans->text() == tr("开始传输"))
    {
        serialPort->setPortName(ui->SerialPortBox->currentText());
        serialPort->setBaudRate(ui->BaudRateBox->currentText().toInt());

        qDebug() << ui->DataBitBox->currentText().toInt();
        switch(ui->DataBitBox->currentText().toInt())
        {
            case 5: serialPort->setDataBits(QSerialPort::Data5);
                break;
            case 6: serialPort->setDataBits(QSerialPort::Data6);
                break;
            case 7: serialPort->setDataBits(QSerialPort::Data7);
                break;
            case 8: serialPort->setDataBits(QSerialPort::Data8);
                break;
            default:
                break;
        }

        qDebug() << ui->StopBitBox->currentIndex();
        switch(ui->StopBitBox->currentIndex())
        {
            case 0: serialPort->setStopBits(QSerialPort::OneStop);
                break;
            case 1: serialPort->setStopBits(QSerialPort::OneAndHalfStop);
                break;
            case 2: serialPort->setStopBits(QSerialPort::TwoStop);
                break;
            default:
                break;
        }

        qDebug() << ui->ParityBox->currentIndex();
        switch (ui->ParityBox->currentIndex())
        {
            case 0: serialPort->setParity(QSerialPort::NoParity);
                break;
            case 1: serialPort->setParity(QSerialPort::EvenParity);
                break;
            case 2: serialPort->setParity(QSerialPort::OddParity);
                break;
            case 3: serialPort->setParity(QSerialPort::SpaceParity);
                break;
            case 4: serialPort->setParity(QSerialPort::MarkParity);
                break;
            default:
                break;
        }

        qDebug() << ui->FlowControlBox->currentIndex();
        switch(ui->FlowControlBox->currentIndex())
        {
            case 0: serialPort->setFlowControl(QSerialPort::NoFlowControl);
                break;
            case 1: serialPort->setFlowControl(QSerialPort::HardwareControl);
                break;
            case 2: serialPort->setFlowControl(QSerialPort::SoftwareControl);
                break;
            default:
                break;
        }

        if(serialPort->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this, tr("打开成功"), tr("已成功打开串口") +
                                ui->SerialPortBox->currentText(), QMessageBox::tr("确定"));

            ui->SerialPortBox->setEnabled(false);
            ui->BaudRateBox->setEnabled(false);
            ui->DataBitBox->setEnabled(false);
            ui->ParityBox->setEnabled(false);
            ui->StopBitBox->setEnabled(false);
            ui->FlowControlBox->setEnabled(false);
            ui->Btn_startTrans->setText(tr("关闭传输"));

            connect(serialPort, &QSerialPort::readyRead, this, &smartHome::Read_Data);

            //ui->textEdit_receive->clear();
            //ui->textEdit_send->clear();
            ui->textEdit_receive->append("\r\n");
            ui->textEdit_send->append("\r\n");

            movie_wave->start();
        }
        else
            QMessageBox::critical(this, tr("打开失败"), tr("未能打开串口") + ui->SerialPortBox->currentText() +
                                tr("\n该串口设备不存在或已被占用"), QMessageBox::tr("确定"));
    }
    else
    {
        disconnect(serialPort, &QSerialPort::readyRead, this, &smartHome::Read_Data);
        serialPort->clear();
        serialPort->close();

        ui->SerialPortBox->setEnabled(true);
        ui->BaudRateBox->setEnabled(true);
        ui->DataBitBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBitBox->setEnabled(true);
        ui->FlowControlBox->setEnabled(true);
        ui->Btn_startTrans->setText(tr("开始传输"));

        movie_wave->stop();
    }
}


void smartHome::Read_Data()
{
    QByteArray buf;
    buf = serialPort->readAll();

    if(buf!=NULL)
    {
    }
}

void smartHome::on_Btn_TV_clicked()
{
    if(ui->Btn_TV->text() == tr("打开电视"))
    {
        ui->Btn_TV->setText("关闭电视");
        ui->image_TV->setStyleSheet("border-image: url(:/image/tv2.png)");
    }
    else
    {
        ui->Btn_TV->setText("打开电视");
        ui->image_TV->setStyleSheet("border-image: url(:/image/tv1.png)");
    }
}

void smartHome::on_Btn_sound_clicked()
{
    if(ui->Btn_sound->text() == tr("打开音响"))
    {
        ui->Btn_sound->setText("关闭音响");
        ui->image_audio1->setStyleSheet("border-image: url(:/image/voice2.png)");
        ui->image_audio2->setStyleSheet("border-image: url(:/image/voice2.png)");
    }
    else
    {
        ui->Btn_sound->setText("打开音响");
        ui->image_audio1->setStyleSheet("border-image: url(:/image/voice1.png)");
        ui->image_audio2->setStyleSheet("border-image: url(:/image/voice1.png)");
    }
}

void smartHome::on_Btn_air_clicked()
{
    if(ui->Btn_air->text() == tr("打开空调"))
    {
        ui->Btn_air->setText("关闭空调");
        ui->image_air->setStyleSheet("border-image: url(:/image/air2.png)");
    }
    else
    {
        ui->Btn_air->setText("打开空调");
        ui->image_air->setStyleSheet("border-image: url(:/image/air1.png)");
    }
}

void smartHome::on_Btn_light_clicked()
{
    if(ui->Btn_light->text() == tr("打开电灯"))
    {
        ui->Btn_light->setText("关闭电灯");
        ui->image_light->setStyleSheet("border-image: url(:/image/liv_light2.png)");
    }
    else
    {
        ui->Btn_light->setText("打开电灯");
        ui->image_light->setStyleSheet("border-image: url(:/image/liv_light1.png)");
    }
}

void smartHome::on_slider_window_sliderMoved(int position)
{
    if(position <= 50)
        ui->image_window->setStyleSheet("border-image: url(:/image/window1.png)");
    else if(position > 50 && position <= 75)
        ui->image_window->setStyleSheet("border-image: url(:/image/window2.png)");
    else
        ui->image_window->setStyleSheet("border-image: url(:/image/window3.png)");
}

void smartHome::on_Btn_clear_clicked()
{
    if(ui->Btn_clear->text() == tr("启动清洁"))
    {
        ui->Btn_clear->setText("停止清洁");
        ui->image_clear->setStyleSheet("border-image: url(:/image/clear2.png)");
    }
    else
    {
        ui->Btn_clear->setText("启动清洁");
        ui->image_clear->setStyleSheet("border-image: url(:/image/clear1.png)");
    }
}
