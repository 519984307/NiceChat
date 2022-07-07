#ifndef QUIHELPER_H
#define QUIHELPER_H

#include <QObject>
#include <QGuiApplication>
#include <QCursor>
#include <QScreen>
#include <QDebug>
#include <QClipboard>
#include <QCryptographicHash>
#include <QTextCodec>
#include <QPixmap>
#include <QImage>
#include <QProcess>
#include <QFile>
#include <QDateTime>
#include <QTextDocument>
#include "glog/logging.h"

class QUIHelper : public QObject
{
    Q_OBJECT
public:
    explicit QUIHelper(QObject *parent = nullptr);
    ~QUIHelper();

    static QUIHelper* instance();

    void setCode();
    Q_INVOKABLE QString appVersion(){
        return QGuiApplication::applicationVersion();
    };
    Q_INVOKABLE QString appName(){
        return QGuiApplication::applicationName();
    };
    Q_INVOKABLE QString orgName(){
        return QGuiApplication::organizationName();
    };
    Q_INVOKABLE QString orgDomain(){
        return QGuiApplication::organizationDomain();
    };
    Q_INVOKABLE void checkUpdate();
    Q_INVOKABLE int getScreenIndex();
    Q_INVOKABLE QRect getScreenRect(bool available);
    Q_INVOKABLE void textClipboard(const QString &text);
    Q_INVOKABLE QString toBase64(const QString&);
    Q_INVOKABLE QString fromBase64(const QString&);
    Q_INVOKABLE QString md5(const QString&);
    Q_INVOKABLE QString sha1(const QString&);
    Q_INVOKABLE QString sha224(const QString&);
    Q_INVOKABLE QString sha256(const QString&);
    Q_INVOKABLE QString sha384(const QString&);
    Q_INVOKABLE QString sha512(const QString&);
    Q_INVOKABLE QString readFile(const QString &fileName);
    Q_INVOKABLE void setQuitOnLastWindowClosed(bool quit);

    Q_INVOKABLE QString htmlToPlainText(const QString& html);

    Q_INVOKABLE qint64 currentTimeMillis();

    Q_SIGNAL void checkUpdateResult(int status);

};

#endif // QUIHELPER_H
