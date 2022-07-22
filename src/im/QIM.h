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
#include "Convert.h"
#include "HttpClient.h"
#include <QImage>
#include <QCryptographicHash>

#define REGISTER(x) qDebug() << (#x) << "type id:" << qMetaTypeId<x*>()

class QIM : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString loginAccid READ loginAccid WRITE setLoginAccid NOTIFY loginAccidChanged)
    Q_PROPERTY(QJsonObject profile READ profile NOTIFY profileChanged)
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


    Q_SIGNAL void profileChanged();
    void setProfile(User const& user){
        const QString &json = qx::serialization::json::to_string(user);
        m_profile = QJsonDocument::fromJson(json.toUtf8()).object();
        Q_EMIT profileChanged();
    }
    [[nodiscard]] QJsonObject profile() const{
        return m_profile;
    }


    Q_INVOKABLE void login(const QString& url,const QString& accid,const QString& token);
    Q_SIGNAL void errorMessage(const QString& error);
    Q_SIGNAL void loginFail();
    Q_SIGNAL void loginSuccess();

    Q_SIGNAL void receiveMessage(Message &message);

    Q_SIGNAL void updateSessionCompleted(Session &session);
    Q_SIGNAL void deleteSessionCompleted(const QString& accid);
    Q_SIGNAL void syncMessageCompleted();
    Q_SIGNAL void syncFriendCompleted();

    void heartBeat();
    void heartBeatCount();
    void reconnect();
    void resendMsg();
    void updateSessionByMessage(const Message& message);
    void syncMessage(const google::protobuf::RepeatedPtrField<im::protocol::Message> &messages);
    void syncFriends(const google::protobuf::RepeatedPtrField<im::protocol::User> &friends);
    void syncProfile(const im::protocol::User &profile);

    QList<Message> getMessageListById(const QString& accid);
    QList<Message> getMessageList(const QString& sessionId,const Message* anchor);
    QList<Session> getSessionList();
    QList<User> getFriendList();

    Q_INVOKABLE void test();
    Q_INVOKABLE void startHeartBeat();
    Q_INVOKABLE void stopHeartBeat();

    Q_INVOKABLE void sendTextMessage(const QString& from,const QString& to,const QString& message);
    Q_INVOKABLE void sendImageMessage(const QString& from,const QString& to,const QString& path);
    Q_INVOKABLE void sendSyncMessage();
    Q_INVOKABLE void sendReadMessageByUuids(const QString& uuids);

    Q_INVOKABLE void sendSyncFriend();
    Q_INVOKABLE void sendSyncProfile();

    Q_INVOKABLE void clearUnreadCount(const QString& sessionId);

    Q_INVOKABLE void updateMessageModel(const QString& accid);

    Q_INVOKABLE void topSession(const QString& accid,bool top);
    Q_INVOKABLE void deleteSession(const QString& accid);

    Q_INVOKABLE QString getUserName(const QString& accid);
    Q_INVOKABLE QJsonObject getUserObject(const QString& accid);

private:
    void initDataBase(const QString &text);
    void handleMessageBuf(const Message &message);
    QString buildTextBody(const QString &text);
    QString buildImageBody(const QString &path);
    QString buildFileBody(const QString &path);
    void sendMessage(const QString& from,const QString& to,int scene,int type,const QString& body);
private:
    QWebSocket *socket;

    QJsonObject m_profile;

    QString m_ws ="";

    QTimer *m_timer_heart;
    QTimer *m_timer_heart_count;
    QTimer *m_timer_reconnect;
    QTimer *m_timer_resend_msg;

    int m_heart_count = 0;

    QString m_login_accid;
    QString m_login_token;

    QList<Message> m_msg_buf;

    QMap<QString,User> m_user_cache;

    IMDataBase m_db;

    int m_state = -1;
};

#endif // IM_H
