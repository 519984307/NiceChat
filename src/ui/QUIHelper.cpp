#include "QUIHelper.h"

Q_GLOBAL_STATIC(QUIHelper, uiHelper)

QUIHelper* QUIHelper::instance()
{
    return uiHelper();
}

QUIHelper::QUIHelper(QObject *parent)
    : QObject{parent}
{
    initFileIcon();
}

QUIHelper::~QUIHelper()
{

}

void QUIHelper::initFileIcon(){
    m_fileIconMap.insert("xls", "qrc:/image/file_ic_detail_excel.png");
    m_fileIconMap.insert("ppt", "qrc:/image/file_ic_detail_ppt.png");
    m_fileIconMap.insert("doc", "qrc:/image/file_ic_detail_word.png");
    m_fileIconMap.insert("xlsx", "qrc:/image/file_ic_detail_excel.png");
    m_fileIconMap.insert("pptx", "qrc:/image/file_ic_detail_ppt.png");
    m_fileIconMap.insert("docx", "qrc:/image/file_ic_detail_word.png");
    m_fileIconMap.insert("pdf", "qrc:/image/file_ic_detail_pdf.png");
    m_fileIconMap.insert("html", "qrc:/image/file_ic_detail_html.png");
    m_fileIconMap.insert("htm", "qrc:/image/file_ic_detail_html.png");
    m_fileIconMap.insert("txt", "qrc:/image/file_ic_detail_txt.png");
    m_fileIconMap.insert("rar", "qrc:/image/file_ic_detail_rar.png");
    m_fileIconMap.insert("zip", "qrc:/image/file_ic_detail_zip.png");
    m_fileIconMap.insert("7z", "qrc:/image/file_ic_detail_zip.png");
    m_fileIconMap.insert("mp4", "qrc:/image/file_ic_detail_mp4.png");
    m_fileIconMap.insert("mp3", "qrc:/image/file_ic_detail_mp3.png");
    m_fileIconMap.insert("png", "qrc:/image/file_ic_detail_png.png");
    m_fileIconMap.insert("gif", "qrc:/image/file_ic_detail_gif.png");
    m_fileIconMap.insert("jpg", "qrc:/image/file_ic_detail_jpg.png");
    m_fileIconMap.insert("jpeg", "qrc:/image/file_ic_detail_jpg.png");
}

bool QUIHelper::isImage(const QString& ext){
    if(ext == "png" || ext == "jpg" || ext == "jpeg"){
        return true;
    }
    return false;
}

QString QUIHelper::getFileIcon(const QString& ext){
    QString icon = m_fileIconMap.value(ext);
    if(icon.isEmpty()){
        return "qrc:/image/file_ic_detail_unknow.png";
    }
    return icon;
}

void QUIHelper::setCode()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
}

//获取当前屏幕索引
int QUIHelper::getScreenIndex()
{
    //需要对多个屏幕进行处理
    int screenIndex = 0;
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    int screenCount = qApp->screens().count();
#else
    int screenCount = qApp->desktop()->screenCount();
#endif

    if (screenCount > 1) {
        //找到当前鼠标所在屏幕
        QPoint pos = QCursor::pos();
        for (int i = 0; i < screenCount; ++i) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
            if (qApp->screens().at(i)->geometry().contains(pos)) {
#else
            if (qApp->desktop()->screenGeometry(i).contains(pos)) {
#endif
                screenIndex = i;
                break;
            }
        }
    }
    return screenIndex;
}

//获取当前屏幕尺寸区域
QRect QUIHelper::getScreenRect(bool available)
{
    QRect rect;
    int screenIndex = QUIHelper::getScreenIndex();
    if (available) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        rect = qApp->screens().at(screenIndex)->availableGeometry();
#else
        rect = qApp->desktop()->availableGeometry(screenIndex);
#endif
    } else {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        rect = qApp->screens().at(screenIndex)->geometry();
#else
        rect = qApp->desktop()->screenGeometry(screenIndex);
#endif
    }
    return rect;
}

void QUIHelper::textClipboard(const QString &text){
    qApp->clipboard()->setText(text);
}

QString QUIHelper::toBase64(const QString &text){
    return text.toUtf8().toBase64();
}

QString QUIHelper::fromBase64(const QString &text){
    return QByteArray::fromBase64(text.toUtf8());
}

QString QUIHelper::md5(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Md5).toHex();
}

QString QUIHelper::sha1(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha1).toHex();
}

QString QUIHelper::sha224(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha224).toHex();
}

QString QUIHelper::sha256(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha256).toHex();
}

QString QUIHelper::sha384(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha384).toHex();
}

QString QUIHelper::sha512(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha512).toHex();
}

QString QUIHelper::readFile(const QString &fileName)
{
    QString content;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        content = stream.readAll();
    }
    return content;
}

void QUIHelper::setQuitOnLastWindowClosed(bool quit){
    QGuiApplication::setQuitOnLastWindowClosed(quit);
}

void QUIHelper::checkUpdate(){
    QString program("./maintenancetool.exe");
    QStringList checkArgs;
    checkArgs << "--checkupdates";
    // 检测更新
    QProcess process;
    process.start(program, checkArgs);
    // 等待检测完成
    if (!process.waitForFinished()) {
        LOG(INFO)<<"Error checking for updates.";
        Q_EMIT checkUpdateResult(-1);
        return;
    }
    QString data = process.readAllStandardOutput();
    if (data.isEmpty()) {
        LOG(INFO)<<"No updates available.";
        Q_EMIT checkUpdateResult(0);
        return;
    }

    if(data.contains("no updates available")){
        LOG(INFO)<<"No updates available.";
        Q_EMIT checkUpdateResult(0);
        return;
    }

    if(data.contains("Warning:")){
        LOG(INFO)<<"No updates available.";
        Q_EMIT checkUpdateResult(-1);
        return;
    }

    QStringList updaterArgs;
    updaterArgs << "--updater";
    bool success = QProcess::startDetached(program, updaterArgs);
    if (!success) {
        qDebug() << "Program startup failed.";
        return;
    }

    LOG(INFO)<<data.toStdString();
    Q_EMIT checkUpdateResult(1);
}

QString QUIHelper::htmlToPlainText(const QString& html){
    QTextDocument doc;
    doc.setHtml(html);
    return doc.toPlainText();
}

qint64 QUIHelper::currentTimeMillis(){
    return QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
}

void QUIHelper::restart(){
    qApp->exit(931);
}
