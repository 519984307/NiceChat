#ifndef IMDATABASE_H
#define IMDATABASE_H

#include <QObject>
#include <QDebug>
#include "./precompiled.h"
#include "./MessageDo.h"
#include "./proto/messages.pb.h"


typedef ::google::protobuf::RepeatedPtrField<im::proto::Message> ptrf;

class IMDataBase : public QObject
{
    Q_OBJECT
public:
    explicit IMDataBase(QObject *parent = nullptr);
    ~IMDataBase();

    void init(const QString& base64);

    void syncMessage(im::proto::MessageList messages);
};

#endif // SAMPLEDATABASE_H
