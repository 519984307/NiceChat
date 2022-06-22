#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQmlApplicationEngine>
#include <QGuiApplication>

class Q_DECL_EXPORT MainWindow {
public:
    explicit MainWindow(char *argv[]);

    ~MainWindow();

    void show();

protected:
    QQmlApplicationEngine m_engine;
};
#endif
