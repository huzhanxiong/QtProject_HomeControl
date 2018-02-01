#include "signUp.h"
#include "ui_signUp.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMouseEvent>


signUp::signUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signUp)
{
    ui->setupUi(this);

    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_passwordx->setEchoMode(QLineEdit::Password);
}

signUp::~signUp()
{
    delete ui;
}


void signUp::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }
}

void signUp::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos() + movePoint;
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x(), widgetPos.y());
    }
}

void signUp::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
}


void signUp::on_Btn_back_clicked()
{
    ui->lineEdit_user->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_passwordx->clear();

    emit rotateWindow();
}

void signUp::on_minimize_clicked()
{
    emit minimizeWindow();
}

void signUp::on_close_clicked()
{
    emit closeWindow();
}

void signUp::on_Btn_singUp_clicked()
{
    if((ui->lineEdit_user->text().length()>10) || (ui->lineEdit_password->text().length()>10))
    {
        QMessageBox::information(this,tr("提示信息"),tr("用户名和密码的长度最多为10位"));
        return;
    }
    if(ui->lineEdit_user->text().length()<3 || ui->lineEdit_password->text().length()<5)
    {
        QMessageBox::information(this,tr("提示信息"),tr("用户名最短为3位，密码为6位"));
        return;
    }
    if(ui->lineEdit_password->text() != ui->lineEdit_passwordx->text())
    {
        QMessageBox::information(this,tr("提示信息"),tr("两次密码不一样，请重新输入"));
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
        QMessageBox::information(this,tr("提示信息"),tr("数据连接异常，用户注册失败"));
    }
    QSqlQuery query(base);
    query.exec("select * from usertable");

    while(query.next())
    {
        if(query.value(0).toString()==ui->lineEdit_user->text())
        {
            QMessageBox::information(this,tr("提示信息"),tr("用户已存在，请重新填写"));
            return;
        }
    }

    query.prepare("insert into usertable values(?,?)");
    query.addBindValue(ui->lineEdit_user->text());
    query.addBindValue(ui->lineEdit_password->text());
    query.exec();

    QMessageBox::information(this,tr("提示信息"),tr("用户注册成功"));
}
