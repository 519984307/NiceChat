#include "QLogHelper.h"

Q_GLOBAL_STATIC(QLogHelper, logHelper)

QLogHelper* QLogHelper::instance()
{
    return logHelper();
}

QLogHelper::QLogHelper(QObject *parent)
    : QObject{parent}
{

}

QLogHelper::~QLogHelper()
{
    google::ShutdownGoogleLogging();
}

void QLogHelper::initGoogleLog(char* argv[])
{
    google::InitGoogleLogging(argv[0]);
    google::EnableLogCleaner(3);
    google::SetStderrLogging(google::GLOG_INFO);
    auto appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    appDataDir.append("/log");
    QDir logDir = appDataDir;
    if (!logDir.exists(appDataDir))
        logDir.mkpath(appDataDir);
    QByteArray byteLogDir = appDataDir.toUtf8();
    FLAGS_log_dir = byteLogDir.data();
#ifdef Q_IS_DEBUG
    FLAGS_logtostderr = true;
#else
    FLAGS_logtostderr = false;
#endif
    FLAGS_logbufsecs = 0;
    FLAGS_max_log_size = 10;
    FLAGS_stop_logging_if_full_disk = true;
    LOG(INFO) << "===================================================";
    LOG(INFO) << "[Product] DoTool";
    LOG(INFO) << "[DeviceId] " << QString(QSysInfo::machineUniqueId()).toStdString();
    LOG(INFO) << "[OSVersion] " << QSysInfo::prettyProductName().toStdString();
    LOG(INFO) << "[LogDir] " << appDataDir.toStdString();
    LOG(INFO) << "===================================================";
    qInstallMessageHandler([](QtMsgType, const QMessageLogContext &context, const QString &message){
        if (context.file && !message.isEmpty())
        {
            LOG(INFO) << "[" << context.file << ":" << context.line << "] " << message.toStdString();
        }
    });
}
