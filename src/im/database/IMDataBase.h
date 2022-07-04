#ifndef IMDataBase_H
#define IMDataBase_H

#include <QObject>
#include <database.h>


class Message;
class IMDataBase :  public Nut::Database
{
    Q_OBJECT

    NUT_DB_VERSION(1)

    NUT_DECLARE_TABLE(Message, message)

    public:
        IMDataBase();

};

Q_DECLARE_METATYPE(IMDataBase*)

#endif // IMDataBase_H
