#ifndef IMDATABASE_H
#define IMDATABASE_H

#include <QObject>
#include <QDebug>
#include "./precompiled.h"
#include "./Message.h"
#include "./proto/im.pb.h"
#include "./Session.h"

class IMDataBase : public QObject {
Q_OBJECT
public:
    explicit IMDataBase(QObject *parent = nullptr);

    ~IMDataBase() override;

    static void initDb(const QString &base64);

    static void initMessageStatus();

    static void syncMessage(const google::protobuf::RepeatedPtrField<im::protocol::Message>& messages);

    static QSqlError insertMsg(const im::protocol::Message &it);

    static uint64_t getMsgLastTime();

    static Message proto2message(const im::protocol::Message &it);

    static QSqlError saveOrUpdateMsg(const im::protocol::Message &it);

    static QSqlError saveOrUpdateMsg(const Message &it);

    static Session message2Session(const Message &it);

    Message getMsgByUuid(const QString &basicString);

    QList<Message> getMessageListById(const QString &accid);

    QList<Session> getSessionList();
};

#endif // IMDATABASE_H
