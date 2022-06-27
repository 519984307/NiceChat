#ifndef IM_H
#define IM_H

#include <QObject>
#include <QWebSocket>
#include <ByteBuf.h>
#include <proto/result.pb.h>
#include <proto/user.pb.h>
#include <proto/friends.pb.h>
#include <proto/message.pb.h>
#include <proto/messages.pb.h>
#include <google/protobuf/util/json_util.h>
#include <QtConcurrent>
#include <database/IMDataBase.h>

class QIM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString userInfo READ userInfo WRITE setUserInfo NOTIFY userInfoChanged)
    Q_PROPERTY(QString friends READ friends WRITE setFriends NOTIFY friendsChanged)
public:
    explicit QIM(QObject *parent = nullptr);
    ~QIM();


    Q_SIGNAL void stateChanged();
    void setState(int state){
        m_state = state;
        Q_EMIT stateChanged();
    }
    [[nodiscard]] int state() const{
        return m_state;
    }


    Q_SIGNAL void userInfoChanged();
    void setUserInfo(QString const& userInfo){
        m_userInfo = userInfo;
        Q_EMIT userInfoChanged();
    }
    [[nodiscard]] QString userInfo() const{
        return m_userInfo;
    }

    Q_SIGNAL void friendsChanged();
    void setFriends(QString const& friends){
        m_friends = friends;
        Q_EMIT friendsChanged();
    }
    [[nodiscard]] QString friends() const{
        return m_friends;
    }


    Q_INVOKABLE void login(const QString& url,const QString& accid,const QString& token);
    Q_SIGNAL void errorMessage(const QString& error);
    Q_SIGNAL void loginFail();
    Q_SIGNAL void loginSuccess();

    void heartBeat();
    void heartBeatCount();
    void reconnect();

    Q_INVOKABLE void startHeartBeat();
    Q_INVOKABLE void stopHeartBeat();

    Q_INVOKABLE void sendTextMessage(const QString& from,const QString& to,const QString& message);
    Q_INVOKABLE void sendSyncMessage();
private:
    void initDataBase(const QString &text);

private:
    QWebSocket *socket;
    QString m_userInfo = "";
    QString m_friends = "{}";
    QString m_ws ="";

    QTimer *m_timer_heart;
    QTimer *m_timer_heart_count;
    QTimer *m_timer_reconnect;
    int m_heart_count = 0;

    IMDataBase m_databse;

    QString m_login_accid;
    QString m_login_token;

    int m_state = -1;
};

#endif // IM_H
