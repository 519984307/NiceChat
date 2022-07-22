#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include "qfontdatabase.h"
#include "GlobalStatic.h"
#include "QLogHelper.h"
#include <QtQml>
#include <QQuickStyle>
#include <QIcon>
#include <framelessquickhelper.h>
#include "LoginController.h"
#include "MessageController.h"
#include "SessionController.h"
#include "ContactController.h"
#include <QQuickWindow>
#include "EmojiModel.h"
#include "TextDocument.h"
#include "QUIHelper.h"

class Q_DECL_EXPORT MainWindow {
public:
    explicit MainWindow(char *argv[]);

    ~MainWindow();

    void show();

protected:
    QQmlApplicationEngine m_engine;
};
#endif
