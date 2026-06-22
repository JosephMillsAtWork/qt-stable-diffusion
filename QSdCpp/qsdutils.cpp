#include "qsdutils.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>
QSdUtils &QSdUtils::instance() {
    static QSdUtils instance;
    return instance;
}

void QSdUtils::debugPaths(){
    qDebug() << "Base Dir:              " << QSdUtils::baseDir;
    qDebug() << "Configuration Dir:     " << QSdUtils::configsDir;
    qDebug() << "Json Configuration Dir:" << QSdUtils::jsonConfigsDir;
    qDebug() << "YAML Configuration Dir:" << QSdUtils::yamlConfigsDir;
    qDebug() << "App Runtime Dir:       " << QSdUtils::appRuntimeDir;
    qDebug() << "Logs Dir:              " << QSdUtils::logsDir;
    qDebug() << "Out Dir:               " << QSdUtils::outDir;
    qDebug() << "Models Dir:            " << QSdUtils::modelsDir;
    qDebug() << "Checkpoint Dir:        " << QSdUtils::checkpointsDir;
    qDebug() << "Unet Dir:              " << QSdUtils::diffusionDir;
    qDebug() << "Text Encoder Dir:      " << QSdUtils::textEncoderDir;
    qDebug() << "LoRA's Dir:            " << QSdUtils::lorasDir;
    qDebug() << "Embeddings Dir:        " << QSdUtils::embeddingsDir;
    qDebug() << "Control Net Dir:       " << QSdUtils::controlNetDir;
    qDebug() << "Upscale Dir:           " << QSdUtils::upscaleModelDir;
    qDebug() << "VAE Dir:               " << QSdUtils::vaeDir;
    qDebug() << "Audio VAE Dir:         " << QSdUtils::audioVaeDir;

}

bool QSdUtils::createDefaultDirs(){
    int ret = 1;
    QStringList dirs;
    dirs.append(QSdUtils::baseDir);
    dirs.append(QSdUtils::configsDir);
    dirs.append(QSdUtils::jsonConfigsDir);
    dirs.append(QSdUtils::yamlConfigsDir);

    dirs.append(QSdUtils::appRuntimeDir);
    dirs.append(QSdUtils::logsDir);
    dirs.append(QSdUtils::outDir);

    dirs.append(QSdUtils::modelsDir);
    dirs.append(QSdUtils::checkpointsDir);
    dirs.append(QSdUtils::diffusionDir);
    dirs.append(QSdUtils::textEncoderDir);
    dirs.append(QSdUtils::lorasDir);
    dirs.append(QSdUtils::embeddingsDir);
    dirs.append(QSdUtils::controlNetDir);
    dirs.append(QSdUtils::upscaleModelDir);
    dirs.append(QSdUtils::vaeDir);
    dirs.append(QSdUtils::audioVaeDir);

    for (const QString &dir : dirs)
        if(createDir(dir))
            ret = ret + 1;

    return (ret == dirs.size());
}

bool QSdUtils::createDirFromFile(const QString &fileName){
    bool ret = false;
    QFileInfo fi(fileName);
    QDir d = fi.absoluteDir();
    if(!d.exists()){
        if(d.mkpath(d.absolutePath())){
            ret = true;
        }else{
            // LOG
        }
    }else{
        // we already have the dir return true
        ret = true;
    }
    return ret;
}

bool QSdUtils::createDir(const QString &dirName){
    bool ret = false;

    QDir d (dirName);
    if(!d.exists()){
        if(d.mkpath(dirName)){
            ret = true;
        }else{
            // LOG
        }
    }else{
        // we already have the dir return true
        ret = true;
    }
    return ret;
}

bool QSdUtils::writeTextFile(const QString &fileName, const QString &content)
{
    bool ret = false;

    if (QSdUtils::createDirFromFile(fileName)) {
        QFile f(fileName);
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&f);
            out << content;
            if (f.flush())
                ret = true;
            else
                qWarning() << "Failed to flush the file buffer:" << f.errorString();
            f.close();
            if (f.error() != QFile::NoError) {
                qWarning() << "Error after closing the file:" << f.errorString();
                ret = false;
            }
        } else {
            qWarning() << "Failed to open file for writing:" << f.errorString();
        }
    } else {
        qWarning() << "Failed to create directory for file:" << fileName;
    }
    return ret;
}


QString QSdUtils::readTextFile(const QString &fileName)
{
    QString ret;
    QFile f(fileName);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&f);
        ret = in.readAll();
        f.close();
    }else{
        // log
    }
    return ret;
}

bool QSdUtils::fileExists(const QString &filePath) {
    return QFile::exists(filePath) && QFileInfo(filePath).isFile();
}

bool QSdUtils::dirExists(const QString &dirPath) {
    return QFile::exists(dirPath) && QFileInfo(dirPath).isDir();
}

QString QSdUtils::hashFile(const QString &filePath, QCryptographicHash::Algorithm algo) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return QString();

    QCryptographicHash hash(algo);
    if (!hash.addData(&file))
        return QString();

    file.close();
    QByteArray result = hash.result();
    return QString(result.toHex());
}

QSdUtils::QSdUtils()
{
    appName                 = "qt-stable-diffusion";
    baseDir                 = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).append("/" + appName);

    configsDir              = QString("%1/configs").arg(QSdUtils::baseDir);
    jsonConfigsDir          = QString("%1/json").arg(QSdUtils::configsDir);
    yamlConfigsDir          = QString("%1/yaml").arg(QSdUtils::configsDir);

    appRuntimeDir           = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/" + appName);
    outDir                  = QString("%1/out").arg(QSdUtils::appRuntimeDir);
    logsDir                 = QString("%1/logs").arg(QSdUtils::appRuntimeDir);

    modelsDir               = QStandardPaths::writableLocation(QStandardPaths::CacheLocation).append("/" + appName + "/models");
    checkpointsDir          = QString("%1/checkpoints").arg(QSdUtils::modelsDir);
    diffusionDir            = QString("%1/unet").arg(QSdUtils::modelsDir);
    textEncoderDir          = QString("%1/textEncoders").arg(QSdUtils::modelsDir);
    lorasDir                = QString("%1/loras").arg(QSdUtils::modelsDir);
    embeddingsDir           = QString("%1/embeddings").arg(QSdUtils::modelsDir);
    controlNetDir           = QString("%1/controlNet").arg(QSdUtils::modelsDir);
    upscaleModelDir         = QString("%1/upscale").arg(QSdUtils::modelsDir);
    vaeDir                  = QString("%1/vae").arg(QSdUtils::modelsDir);
    audioVaeDir             = QString("%1/audioVae").arg(QSdUtils::modelsDir);
}

QString QSdUtils::appName               = "qt-stable-diffusion";
QString QSdUtils::baseDir               = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).append("/" + appName);

QString QSdUtils::configsDir            = QString("%1/configs").arg(baseDir);
QString QSdUtils::jsonConfigsDir        = QString("%1/json").arg(configsDir);
QString QSdUtils::yamlConfigsDir        = QString("%1/yaml").arg(configsDir);

QString QSdUtils::appRuntimeDir         = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append(  "/" + appName);
QString QSdUtils::outDir                = QString("%1/out").arg(appRuntimeDir);
QString QSdUtils::logsDir               = QString("%1/logs").arg(appRuntimeDir);

QString QSdUtils::modelsDir             = QStandardPaths::writableLocation(QStandardPaths::CacheLocation).append(    "/" + appName + "/models");
QString QSdUtils::checkpointsDir        = QString("%1/checkpoints").arg(modelsDir);
QString QSdUtils::diffusionDir          = QString("%1/unet").arg(modelsDir);
QString QSdUtils::textEncoderDir        = QString("%1/textEncoders").arg(modelsDir);
QString QSdUtils::lorasDir              = QString("%1/loras").arg(modelsDir);
QString QSdUtils::embeddingsDir         = QString("%1/embeddings").arg(modelsDir);
QString QSdUtils::controlNetDir         = QString("%1/controlNet").arg(modelsDir);
QString QSdUtils::upscaleModelDir       = QString("%1/upscale").arg(modelsDir);
QString QSdUtils::vaeDir                = QString("%1/vae").arg(modelsDir);
QString QSdUtils::audioVaeDir           = QString("%1/audioVae").arg(modelsDir);
