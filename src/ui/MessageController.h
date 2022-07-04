#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <QObject>
#include <GlobalStatic.h>

class MessageController : public QObject
{
    Q_OBJECT

public:
    explicit MessageController(QObject *parent = nullptr);

};

#endif // MESSAGECONTROLLER_H
