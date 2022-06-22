#ifndef QLOGHELPER_H
#define QLOGHELPER_H

#include <glog/logging.h>
#include <QObject>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QTextCodec>


class QLogHelper : public QObject
{
    Q_OBJECT
public:
    explicit QLogHelper(QObject *parent = nullptr);
    ~QLogHelper();
    void initGoogleLog(char* argv[]);
};

#endif // QLOGHELPER_H
