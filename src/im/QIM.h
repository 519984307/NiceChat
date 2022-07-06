#ifndef IM_H
#define IM_H

#include <QObject>
#include <QWebSocket>
#include <ByteBuf.h>
#include <google/protobuf/util/json_util.h>
#include <QtConcurrent>
#include <proto/im.pb.h>
#include <QUuid>
#include <QList>
#include "./database/IMDataBase.h"
#include "./database/Message.h"

#define REGISTER(x) qDebug() << (#x) << "type id:" << qMetaTypeId<x*>()

class QIM : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString loginAccid READ loginAccid WRITE setLoginAccid NOTIFY loginAccidChanged)
    Q_PROPERTY(QString userInfo READ userInfo WRITE setUserInfo NOTIFY userInfoChanged)
    Q_PROPERTY(QString friends READ friends WRITE setFriends NOTIFY friendsChanged)
public:
    explicit QIM(QObject *parent = nullptr);
    ~QIM();

    static QIM* instance();

    Q_SIGNAL void loginAccidChanged();
    void setLoginAccid(QString const& accid){
        m_login_accid = accid;
        Q_EMIT loginAccidChanged();
    }
    [[nodiscard]] QString loginAccid() const{
        return m_login_accid;
    }


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

    Q_SIGNAL void receiveMessage(const Message &message);

    void heartBeat();
    void heartBeatCount();
    void reconnect();
    void resendMsg();

    QList<Message> getMessageListById(const QString& accid);
    QList<Session> getSessionList();

    Q_INVOKABLE void test();
    Q_INVOKABLE void startHeartBeat();
    Q_INVOKABLE void stopHeartBeat();

    Q_INVOKABLE void sendTextMessage(const QString& from,const QString& to,const QString& message);
    Q_INVOKABLE void sendSyncMessage();

    Q_INVOKABLE void getFriends();
    Q_INVOKABLE void getProfile();

    Q_INVOKABLE void updateMessageModel(const QString& accid);

private:
    void initDataBase(const QString &text);
    void handleMessageBuf(const Message &message);
private:
    QWebSocket *socket;
    QString m_userInfo = "";
    QString m_friends = "{}";
    QString m_ws ="";

    QTimer *m_timer_heart;
    QTimer *m_timer_heart_count;
    QTimer *m_timer_reconnect;
    QTimer *m_timer_resend_msg;

    int m_heart_count = 0;

    QString m_login_accid;
    QString m_login_token;

    QList<Message> m_msg_buf;

    IMDataBase m_db;

    int m_state = -1;
};

#endif // IM_H
