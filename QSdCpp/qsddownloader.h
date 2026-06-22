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

#include "qmlstringlist.h"
#include "property-macros.h"

#include "qsddownloaderparams.h"

class QSdDownloader : public QObject
{
    Q_OBJECT
    QP_RO(quint32, current, 0)
    QP_RO(quint32, total,   0)

    QML_ELEMENT
public:
    explicit QSdDownloader(QObject *parent = nullptr);

    Q_INVOKABLE void download(const QString &url);
    Q_INVOKABLE void download(const QmlStringList &urls);

Q_SIGNALS:
    void finished();

private slots:
    void downloadNext();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager   m_nam;
    QNetworkReply           *m_reply = nullptr;
    QQueue<QUrl>            m_que;


    void download(QSdDownloaderParams *params)
    {


    }

    QTime m_downloadTime;
};

#endif // QSDDOWNLOADER_H
