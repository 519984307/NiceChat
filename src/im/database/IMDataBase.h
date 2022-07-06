#ifndef IMDATABASE_H
#define IMDATABASE_H

#include <QObject>
#include <QDebug>
#include "./precompiled.h"
#include "./Message.h"
#include "./proto/im.pb.h"

typedef ::google::protobuf::RepeatedPtrField<im::protocol::Message> ptrf;

class IMDataBase : public QObject {
Q_OBJECT
public:
    explicit IMDataBase(QObject *parent = nullptr);

    ~IMDataBase() override;

    static void initDb(const QString &base64);

    static void syncMessage(const ptrf &messages);

    static QSqlError insertMsg(const im::protocol::Message &it);

    static uint64_t getMsgLastTime();

    static std::shared_ptr<Message> proto2message(const im::protocol::Message &it);

    static QSqlError saveOrUpdateMsg(const im::protocol::Message &it);

    Message getMsgByUuid(const QString &basicString);

    QList<Message> getMessageListById(const QString &accid);
};

#endif // IMDATABASE_H
