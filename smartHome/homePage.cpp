#include "homePage.h"
#include "ui_homePage.h"
#include <QMessageBox>
#include <QDebug>


homePage::homePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homePage)
{
    ui->setupUi(this);

    movie_wave = new QMovie(":/image/wave.gif");
    ui->movie_wave1->setMovie(movie_wave);
    ui->movie_wave2->setMovie(movie_wave);
    movie_wave->start();
    movie_wave->stop();
    ui->BaudRateBox->setCurrentIndex(6);
    ui->DataBitBox->setCurrentIndex(3);

    //查看可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);

        //ui->SerialPortBox->addItem(" ");
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->SerialPortBox->addItem(serial.portName());
            serial.close();
        }
    }

    serialPort = new QSerialPort(this);
}

homePage::~homePage()
{  
    delete movie_wave;
    delete ui;
}

void homePage::on_Btn_startTrans_clicked()
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

            connect(serialPort, &QSerialPort::readyRead, this, &homePage::Read_Data);

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
        disconnect(serialPort, &QSerialPort::readyRead, this, &homePage::Read_Data);
        serialPort->clear();
        serialPort->close();
        //serialPort->deleteLater();

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


void homePage::Read_Data()
{
    QByteArray buf;
    buf = serialPort->readAll();

    if(buf!=NULL)
    {
    }
}

void homePage::on_Btn_livingroom_clicked()
{

}
