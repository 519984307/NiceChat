#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <database.h>

class Message : public Nut::Table
{
    Q_OBJECT

    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(int, id, id, setId)

    NUT_DECLARE_FIELD(QString, uuid, uuid, setUuid)
    NUT_DECLARE_FIELD(QString, from_accid, fromAccid, setFromAccid)
    NUT_DECLARE_FIELD(QString, to_accid, toAccid, setToAccid)
    NUT_DECLARE_FIELD(QString, body, body, setBody)
    NUT_DECLARE_FIELD(QString, ex, ex, setEx)
    NUT_DECLARE_FIELD(QString, time, time, setTime)
    NUT_DECLARE_FIELD(int, scene, scene, setScene)
    NUT_DECLARE_FIELD(int, type, type, setType)

    public:
        Q_INVOKABLE explicit Message(QObject *parent  = Q_NULLPTR);
};

Q_DECLARE_METATYPE(Message*)

#endif // MESSAGE_H
