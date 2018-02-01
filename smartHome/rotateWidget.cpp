#include "rotateWidget.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QPixmap>
#include <math.h>
#include "signIn.h"
#include "signUp.h"


RotateWidget::RotateWidget(QWidget *parent) :
                QStackedWidget(parent),
                    m_isRotateing(false),
                    m_nextPageIndex(0)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
                            | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setProperty("rotateValue", 0);
    RotateWidget_init();
}

RotateWidget::~RotateWidget()
{

}


void RotateWidget::RotateWidget_init()
{
    m_signIn = new signIn(this);
    connect(m_signIn, SIGNAL(rotateWindow()), this, SLOT(RotateWidget_start()));
    connect(m_signIn, SIGNAL(closeWindow()), this, SLOT(close()));
    connect(m_signIn, SIGNAL(minimizeWindow()), this, SLOT(showMinimized()));

    m_signUp = new signUp(this);
    connect(m_signUp, SIGNAL(rotateWindow()), this, SLOT(RotateWidget_start()));
    connect(m_signUp, SIGNAL(closeWindow()), this, SLOT(close()));
    connect(m_signUp, SIGNAL(minimizeWindow()), this, SLOT(showMinimized()));

    this->addWidget(m_signIn);
    this->addWidget(m_signUp);

    this->setFixedSize(QSize(m_signIn->width(), m_signIn->height()*sqrt(2)));
}


void RotateWidget::RotateWidget_start()
{
    if(m_isRotateing)
        return;

    m_isRotateing = true;
    m_nextPageIndex = (currentIndex() + 1) >= count() ? 0 : (currentIndex() + 1);
    QPropertyAnimation *rotateAnimation = new QPropertyAnimation(this, "rotateValue");
    //设置旋转持续时间
    rotateAnimation->setDuration(1000);
    //设置旋转角度变化趋势
    rotateAnimation->setEasingCurve(QEasingCurve::InCubic);
    //设置旋转角度范围
    rotateAnimation->setStartValue(0);
    rotateAnimation->setEndValue(180);
    connect(rotateAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(repaint()));
    connect(rotateAnimation, SIGNAL(finished()), this, SLOT(RotateWidget_finesh()));

    currentWidget()->hide();
    rotateAnimation->start();
}


void RotateWidget::RotateWidget_finesh()
{
    m_isRotateing = false;
    setCurrentWidget(widget(m_nextPageIndex));
    repaint();
}


void RotateWidget::paintEvent(QPaintEvent* event)
{
    if(m_isRotateing)
    {
        int rotateValue = this->property("rotateValue").toInt();
        if(rotateValue <= 90)
        {
            QPixmap rotatePixmap(currentWidget()->size());
            currentWidget()->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width()/2, 0);
            transform.rotate(rotateValue, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1*width() / 2, 0, rotatePixmap);
        }
        else
        {
            QPixmap rotatePixmap(widget(m_nextPageIndex)->size());
            widget(m_nextPageIndex)->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(rotateValue + 180, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1 * width() / 2, 0, rotatePixmap);
        }
    }
    //else
        //return __super::paintEvent(event);
}
