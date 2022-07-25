#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include <QObject>
#include "SessionListModel.h"
#include "FileListModel.h"
#include "QUIHelper.h"
#include "QIM.h"

class SessionController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SessionListModel* sessionModel READ sessionModel)
    Q_PROPERTY(FileListModel* fileModel READ fileModel)
    Q_PROPERTY(QJsonObject current READ current NOTIFY currentChanged)
public:
    explicit SessionController(QObject *parent = nullptr);
    ~SessionController() override;

    Q_SIGNAL void currentChanged();
    Q_INVOKABLE void setCurrent(int index){
        m_current = m_sessionModel.getItem(index);
        Q_EMIT currentChanged();
    }
    [[nodiscard]] QJsonObject current() const{
        return m_current;
    }

    [[nodiscard]] SessionListModel* sessionModel(){
        return &m_sessionModel;
    }

    [[nodiscard]] FileListModel* fileModel(){
        return &m_fileModel;
    }

    Q_INVOKABLE void loadSessionModel();
    Q_INVOKABLE void jumpSession(const QString& accid);

    Q_INVOKABLE void loadFileList(const QVariant& var);
    Q_INVOKABLE void sendSelectedFile(const QString& sessionId,int scene);

    Q_SIGNAL void sessionIndexSelected(int index);

private:
    SessionListModel m_sessionModel;
    FileListModel m_fileModel;
    QJsonObject m_current;
};


#endif // SESSIONCONTROLLER_H
