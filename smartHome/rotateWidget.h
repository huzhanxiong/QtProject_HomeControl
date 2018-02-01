#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QStackedWidget>


class signIn;
class signUp;

class RotateWidget : public QStackedWidget
{
    Q_OBJECT

public:
    RotateWidget(QWidget *parent = 0);
    ~RotateWidget();

private:
    void RotateWidget_init();
    void paintEvent(QPaintEvent* event);

private slots:
    void RotateWidget_start();
    void RotateWidget_finesh();

private:
    bool goto_signIn = 0;
    bool m_isRotateing;
    int m_nextPageIndex;
    signIn* m_signIn;
    signUp* m_signUp;
};

#endif // ROTATEWIDGET_H
