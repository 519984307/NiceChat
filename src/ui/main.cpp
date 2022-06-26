#include <QGuiApplication>
#include <QQuickWindow>
#include "MainWindow.h"
#include <QFont>
#include <QHotkey>


int main(int argc, char *argv[])
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
//    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);
    QGuiApplication::setApplicationName("NiceChat");
    QGuiApplication::setApplicationVersion("1.0.0.0");
    QGuiApplication::setOrganizationName("zzc");
    QGuiApplication::setOrganizationDomain("https://github.com/zhuzichu520/NiceChat");

    QGuiApplication app(argc, argv);
    QHotkey hotkey(QKeySequence("Ctrl+Alt+Q"), true, &app);
    QObject::connect(&hotkey, &QHotkey::activated, qApp, [&](){
        qApp->quit();
    });
    MainWindow window(argv);
    window.show();
    QGuiApplication::exec();
    return 0;
}
