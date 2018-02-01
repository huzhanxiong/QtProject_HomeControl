#include <QApplication>
#include "rotateWidget.h"
#include <QIcon>
#include "signIn.h"
#include "signUp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/wali.ico"));

    RotateWidget w;
    w.show();

    return a.exec();
}
