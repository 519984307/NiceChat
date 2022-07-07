#ifndef CONVERT_H
#define CONVERT_H

#include <QObject>
#include "database/Message.h"
#include "database/Session.h"
#include "proto/im.pb.h"

class Convert : public QObject
{
public:
    explicit Convert(QObject *parent = nullptr);

    static Message proto2message(const im::protocol::Message &it);

    static Session message2Session(const Message &it);

signals:

};

#endif // CONVERT_H
