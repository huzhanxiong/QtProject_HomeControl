#ifndef signUp_H
#define signUp_H

#include <QWidget>

namespace Ui {
class signUp;
}

class signUp : public QWidget
{
    Q_OBJECT

public:
    explicit signUp(QWidget *parent = 0);
    ~signUp();

private:
    Ui::signUp *ui;

signals:
    void rotateWindow();
    void closeWindow();
    void minimizeWindow();

private slots:
    void on_Btn_back_clicked();
    void on_minimize_clicked();
    void on_close_clicked();

    void on_Btn_singUp_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_isPressed = false;
    QPoint m_startMovePos;
};

#endif // signUp_H
