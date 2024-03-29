﻿#include "MainWindow.h"

FRAMELESSHELPER_USE_NAMESPACE

MainWindow::MainWindow(char *argv[]) {

    //    QGuiApplication::setQuitOnLastWindowClosed(true);
    QFont font;
    font.setFamily("Microsoft YaHei");
    QGuiApplication::setFont(font);
    QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);
    QGuiApplication::setWindowIcon(QIcon(":/image/ic_logo.png"));
    QQuickStyle::setStyle("Default");

    QUIHelper *p_uiHelper = QUIHelper::instance();
    p_uiHelper->setCode();
    m_engine.rootContext()->setContextProperty("UIHelper",p_uiHelper);

    QLogHelper *p_logHelper = QLogHelper::instance();
    p_logHelper->initGoogleLog(argv);
    m_engine.rootContext()->setContextProperty("LogHelper",p_logHelper);


    m_engine.rootContext()->setContextProperty("IM",QIM::instance());

    qmlRegisterType<FramelessQuickHelper>("UI", 1, 0, "FramelessHelper");
    qmlRegisterType<EmojiModel>("UI", 1, 0, "EmojiModel");
    qmlRegisterType<TextDocument>("UI", 1, 0, "TextDocument");

    qmlRegisterType<LoginController>("Controller", 1, 0, "LoginController");
    qmlRegisterType<MessageController>("Controller", 1, 0, "MessageController");
    qmlRegisterType<SessionController>("Controller", 1, 0, "SessionController");
    qmlRegisterType<ContactController>("Controller", 1, 0, "ContactController");

}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/Login.qml"));
}
