#include "signIn.h"
#include "ui_signIn.h"
#include "smartHome.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


signIn::signIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signIn)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    //初始化数据库
    QSqlDatabase base=QSqlDatabase::addDatabase("QSQLITE","mySql");
    base.setDatabaseName("UserData.db");
    base.setUserName("admin");
    base.setPassword("admin");
    if(!base.open())
    {
        QMessageBox::information(this,tr("提示信息"),tr("账号数据检验异常"));
    }

    QSqlQuery query(base);
    query.exec("create table usertable(username varchar(20) primary key,password varchar(20))");
}

signIn::~signIn()
{
    delete ui;
    qDebug() << "exit";
}


void signIn::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }
}

void signIn::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos() + movePoint;
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x(), widgetPos.y());
    }
}

void signIn::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
}


void signIn::on_Btn_signUp_clicked()
{
    emit rotateWindow();
}

void signIn::on_close_clicked()
{
    emit closeWindow();
}

void signIn::on_minimize_clicked()
{
    emit minimizeWindow();
}

void signIn::on_Btn_signIn_clicked()
{
    if(ui->lineEdit_user->text().length() <= 0)
    {
        QMessageBox::information(this,tr("提示信息"),tr("账号为空，请重新输入"));
        return;
    }
    else if(ui->lineEdit_password->text().length() <= 0)
    {
        QMessageBox::information(this,tr("提示信息"),tr("密码为空，请重新输入"));
        return;
    }

    QSqlDatabase base;
    if(QSqlDatabase::contains("mySql"))
      base = QSqlDatabase::database("mySql");
    else
      base = QSqlDatabase::addDatabase("QSQLITE");

    base.setDatabaseName("UserData.db");
    base.setUserName("admin");
    base.setPassword("admin");
    if(!base.open())
    {
        QMessageBox::information(this,tr("提示信息"),tr("账号数据检验异常"));
    }
    QSqlQuery query(base);
    query.exec("select * from usertable");

    while(query.next())
    {
        if(query.value(0).toString()==ui->lineEdit_user->text() &&
                query.value(1).toString()==ui->lineEdit_password->text())
        {
            //qDebug() << "signIn successed!";
            smartHome *smartHomeN = new smartHome;
            smartHomeN->show();
            emit closeWindow();
        }
        else
        {
            QMessageBox::information(this,tr("提示信息"),tr("用户名或密码有误，请重新输入"));
            return;
        }
    }
}
