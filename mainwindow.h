#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QTimer>
#include <QDebug>
#include <QHeaderView>
#include <QSettings>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <lib/QtAwesome/QtAwesome.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setWindowMaximized();



private:
    Ui::MainWindow *ui;

    QtAwesome* awesome;
    QSettings* cachedData;

    void initSidePanel();
    void initGUIelements();
    void initDashboard();
    void attachSidePanelSignals();
    void initAppCache();


private slots:

    void SiePanelClick(QString ButtonName);




    void on_id_cursorPositionChanged(int arg1, int arg2);
};
#endif // MAINWINDOW_H
