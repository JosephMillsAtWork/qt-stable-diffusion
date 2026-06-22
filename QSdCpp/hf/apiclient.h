#pragma once
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>

#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include <QPromise>
#include <QFuture>

#include "property-macros.h"
class ApiClient : public QObject {
    QP_RW(bool      , testing   , false     )
    QP_RW(bool      , anonymous , true      )
    QP_RW(bool      , busy      , false     )
    QP_RW(QString   , token     , "NONE"    )
    Q_OBJECT

public:
    explicit ApiClient(QObject *parent = nullptr);
    ~ApiClient();
    enum Method{
        Get,
        Post,
        Put,
        Delete,
        Custom
    };
    Q_ENUMS(Method)

    QFuture<QJsonObject> request(const QString &path,
                                 ApiClient::Method method = ApiClient::Get,
                                 const QJsonObject &data = QJsonObject()
                                 );

protected Q_SLOTS:
    void reqFinished();

private:
    QNetworkAccessManager   *m_nam;
    QNetworkRequest         m_req;
    QNetworkReply           *m_rep;

    QJsonObject m_errorJson;

    struct ReqItem {
        QString path;
        ApiClient::Method method;
        QJsonObject data;
        QPromise<QJsonObject> promise;
    };

    ReqItem *m_currentReqItem = nullptr;
    QQueue<ReqItem*> m_reqQueue;

    void processReq();
};

