#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>

namespace Ui {
class signIn;
}

class signIn : public QWidget
{
    Q_OBJECT

public:
    explicit signIn(QWidget *parent = 0);
    ~signIn();

private:
    Ui::signIn *ui;    

signals:
    void rotateWindow();
    void closeWindow();
    void minimizeWindow();

private slots:
    void on_Btn_signUp_clicked();
    void on_close_clicked();
    void on_minimize_clicked();

    void on_Btn_signIn_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_isPressed = false;
    QPoint m_startMovePos;
};

#endif // SIGNIN_H
