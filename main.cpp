#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowMaximized();
    w.setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    w.setWindowState(Qt::WindowFullScreen);
    w.showMaximized();

    w.show();
    return a.exec();
}
