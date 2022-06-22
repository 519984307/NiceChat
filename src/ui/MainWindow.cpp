#include "MainWindow.h"
#include "qfontdatabase.h"
#include "GlobalStatic.h"
#include "QLogHelper.h"
#include <QtQml>
#include <QQuickStyle>
#include <QIcon>
#include <framelessquickhelper.h>

FRAMELESSHELPER_USE_NAMESPACE

MainWindow::MainWindow(char *argv[]) {

    QGuiApplication::setQuitOnLastWindowClosed(false);
    QFont font;
    font.setFamily("Microsoft YaHei");
    QGuiApplication::setFont(font);
    QGuiApplication::setWindowIcon(QIcon(":/image/ic_logo.png"));
    QQuickStyle::setStyle("Default");

    QUIHelper *p_uiHelper = uiHelper();
    p_uiHelper->setCode();
    m_engine.rootContext()->setContextProperty("UIHelper",p_uiHelper);

    QLogHelper *p_logHelper = logHelper();
    p_logHelper->initGoogleLog(argv);
    m_engine.rootContext()->setContextProperty("LogHelper",p_logHelper);

    qmlRegisterType<FramelessQuickHelper>("com.dotool.ui", 1, 0, "FramelessHelper");

}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/Login.qml"));
}
