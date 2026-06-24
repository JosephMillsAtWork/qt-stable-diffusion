#ifndef QSDDOWNLOADER_H
#define QSDDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QTime>

#include <QTimer>
#include <QString>
#include <QQueue>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>


#include <QQmlEngine>

#include <qmlstringlist.h>
#include <property-macros.h>
#include <qsdutils.h>

#include "huggingfacepackagemanifest.h"

class HuggingFaceDownloader : public QObject
{
    Q_OBJECT
    QP_RO(int, current,             0)
    QP_RO(int, total,               0)

    QP_RO(qint32,  threadCount,         1)

    QP_RW(QString, outDir,              QSdUtils::diffusionDir)

    QP_RO(qint64,  progressCurrent,     0)
    QP_RO(qint64,  progressMax,         0)

    QP_RO(QString, speed, "")

    QML_ELEMENT
public:
    explicit HuggingFaceDownloader(QObject *parent = nullptr);

    // FIXME add reference once this all comes together
    Q_INVOKABLE void download(ObjectListModel<HuggingFacePackageManifest> *packages)
    {
        if(!packages->isEmpty()){
            QStringList urls{};
            for(auto *package : packages->toList()){
                for (auto packfile : package->get_siblings()->toList()){
                    if(packfile->get_installed()){
                        QString url = QString("https://huggingface.co/%1/resolve/%3/%4")
                                          .arg(package->get_uid())
                                          .arg(package->get_branches()->at(0)->get_ref())
                                          .arg(packfile->get_rfilename());
                        urls.append(url);
                    }
                }
            }
            append(urls);
        }
    }

    // Q_INVOKABLE void download(HuggingFacePackageManifest *package)
    // {
    //     if (m_que.isEmpty())
    //         QTimer::singleShot(0, this, SLOT(downloadNext()));
    //     m_que.enqueue(package);
    //     set_total(m_total + 1);
    // }




    QString saveFileName(const QUrl &url)
    {
        QString path = url.path();
        QString basename = QFileInfo(path).fileName();

        if (basename.isEmpty())
            basename = "download";

        if (QFile::exists(basename)) {
            // already exists, don't overwrite
            int i = 0;
            basename += '.';
            while (QFile::exists(basename + QString::number(i)))
                ++i;

            basename += QString::number(i);
        }
        return basename;
    }



Q_SIGNALS:
    void finished();

private Q_SLOTS:
    void downloadNext(){
        if (m_que.isEmpty()) {
            qDebug() << m_current <<  m_total << " files downloaded successfully";
            Q_EMIT finished();
            return;
        }

        QUrl url; m_que.dequeue();

        QString filename = saveFileName(url);
        m_file.setFileName(filename);
        if (!m_file.open(QIODevice::WriteOnly)) {
            fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
                    qPrintable(filename), url.toEncoded().constData(),
                    qPrintable(m_file.errorString()));

            downloadNext();
            return;                 // skip this download
        }

        QNetworkRequest request(url);
        m_reply = m_nam.get(request);
        connect(m_reply, &QNetworkReply::downloadProgress,
                this, &HuggingFaceDownloader::downloadProgress);
        connect(m_reply, &QNetworkReply::finished,
                this, &HuggingFaceDownloader::downloadFinished);
        connect(m_reply, &QNetworkReply::readyRead,
                this, &HuggingFaceDownloader::downloadReadyRead);

        // prepare the output
        qDebug() <<  "Downloadingn" <<  url.toEncoded();
        m_downloadTime.start();

    }

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal){

        set_progressCurrent(bytesReceived);
        set_progressMax(bytesTotal);

        // calculate the download speed
        double speed = bytesReceived * 1000.0 / m_downloadTime.elapsed();
        QString unit;
        if (speed < 1024) {
            unit = "bytes/sec";
        } else if (speed < 1024*1024) {
            speed /= 1024;
            unit = "kB/s";
        } else {
            speed /= 1024*1024;
            unit = "MB/s";
        }

        set_speed(QString::fromLatin1("%1 %2") .arg(speed, 3, 'f', 1).arg(unit));
    }
    void downloadFinished(){
        set_progressCurrent(0);
        set_progressMax(0);
        m_file.close();
        m_file.flush();

        if (m_reply->error()) {
            // download failed
            qDebug() <<  "Failed to download the file:" << qPrintable(m_reply->errorString());
            // what if this is a redirection ?

            // TooManyRedirectsError InsecureRedirectError

        } else {
            printf("Succeeded.\n");
            ++downloadedCount;
        }

        m_reply->deleteLater();
        downloadNext();
    }
    void downloadReadyRead()
    {
        m_file.write(m_reply->readAll());
    }

private:
    void append(const QStringList &urls){
        for(const QString &url : urls)
            append(QUrl::fromEncoded(url.toLocal8Bit()));

        if (m_que.isEmpty())
            QTimer::singleShot(0, this, SIGNAL(finished()));
    }

    void append(const QUrl &url){
        if (m_que.isEmpty())
            QTimer::singleShot(0, this, SLOT(startNextDownload()));

        m_que.enqueue(url);
        set_total(m_total + 1);
    }






    QNetworkAccessManager                          m_nam;
    QNetworkReply                                  *m_reply = nullptr;
    QQueue<QUrl>            m_que;
    int downloadedCount;
    QElapsedTimer m_downloadTime;
    QFile m_file;
};

#endif // QSDDOWNLOADER_H
