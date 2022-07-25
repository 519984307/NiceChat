#ifndef CONVERT_H
#define CONVERT_H

#include <QObject>
#include "database/Message.h"
#include "database/Session.h"
#include "database/User.h"
#include "proto/im.pb.h"

class Convert : public QObject
{
public:
    explicit Convert(QObject *parent = nullptr);

    static Message proto2message(const im::protocol::Message &it);

    static im::protocol::Message* message2proto(const Message &it);

    static User proto2user(const im::protocol::User &it);

    static Session message2session(const Message &it);

signals:

};

#endif // CONVERT_H
