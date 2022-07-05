#ifndef IMDATABASE_H
#define IMDATABASE_H

#include <QObject>
#include <QDebug>
#include "./precompiled.h"
#include "./Message.h"
#include "./proto/im.pb.h"


typedef ::google::protobuf::RepeatedPtrField<im::protocol::Message> ptrf;

class IMDataBase : public QObject
{
    Q_OBJECT
public:
    explicit IMDataBase(QObject *parent = nullptr);
    ~IMDataBase();

    void init(const QString& base64);

    void syncMessage(const ptrf &messages);

    void insertMsg(im::protocol::Message *msg);

    uint64_t getMsgLastTime();
};

#endif // SAMPLEDATABASE_H
