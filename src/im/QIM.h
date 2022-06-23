#ifndef IM_H
#define IM_H

#include <QObject>
#include <QWebSocket>
#include <ByteBuf.h>
#include <proto/result.pb.h>

class QIM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int state READ state NOTIFY stateChanged)
public:
    explicit QIM(QObject *parent = nullptr);
    ~QIM();

    [[nodiscard]] int state() const{
        return m_state;
    }
    Q_SIGNAL void stateChanged();

    Q_INVOKABLE void login(const QString& url,const QString& accid,const QString& token);

    Q_SIGNAL void errorMessage(const QString& error);

    Q_SIGNAL void loginFail();
    Q_SIGNAL void loginSuccess();


private:
    void updateState(int state){
        m_state = state;
        Q_EMIT stateChanged();
    }

private:
    QWebSocket *socket;
    int m_state = -1;
};

#endif // IM_H
