#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include "squares.h"
#include "squarehandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    squares* sq = new squares(w);
    w->setGeometry(100,100,900,650);
    w->setWindowIcon(QIcon(":/other/resources/small-red-apple-hi.png"));
    w->show();
    return a.exec();
}


