#ifndef IMDATABASE_H
#define IMDATABASE_H

#include <QObject>
#include <QDebug>
#include "precompiled.h"
#include "Message.h"
#include "proto/im.pb.h"
#include "Session.h"
#include "Convert.h"

class IMDataBase : public QObject {
    Q_OBJECT
public:
    explicit IMDataBase(QObject *parent = nullptr);

    ~IMDataBase() override;

    static void initDb(const QString &base64);

    static void initMessageStatus();

    static QSqlError insertMessage(const Message &it);

    static uint64_t getMessageLastTime();

    static QSqlError saveOrUpdateMessage(const Message &it);

    static QSqlError saveOrUpdateSession(const Session &it);

    static Message getMsgByUuid(const QString &uuid);

    static Session getSessionById(const QString &id);

    static QList<Message> getMessageListById(const QString &accid);

    static QList<Session> getSessionList();

    static QList<Message> getUnreadMessageList(const QString &sessionId,const QString &accid);
};

#endif // IMDATABASE_H
