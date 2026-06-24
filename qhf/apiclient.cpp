#include "apiclient.h"
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QFuture>

#include <QDebug>

const QString HF_BASE_URL = "https://huggingface.co";

ApiClient::ApiClient(QObject *parent) :
    m_token("NONE"),
    QObject{parent},
    m_nam{new QNetworkAccessManager{this}}
{

    m_token = qEnvironmentVariable("HF_TOKEN", "NONE");

    m_req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_req.setAttribute(QNetworkRequest::RedirectPolicyAttribute,  QNetworkRequest::NoLessSafeRedirectPolicy);
    m_req.setRawHeader("Accept", "application/json");
    if(m_token != "NONE")
        m_req.setRawHeader("Authorization", QByteArray("Bearer " + m_token.toLocal8Bit()));

    m_req.setMaximumRedirectsAllowed(10);

    // Enable automated HTTP redirect handling natively for API metadata calls
    m_errorJson["status"] = "error";
    m_errorJson["respCode"] = 404;
    m_errorJson["errorString"] = "Unknown Error";

}

ApiClient::~ApiClient()
{
    delete m_nam;
}

QFuture<QJsonObject> ApiClient::request(const QString &path, ApiClient::Method method, const QJsonObject &data)
{
    QPromise<QJsonObject> promise;
    auto future = promise.future();
    m_reqQueue.enqueue(new ReqItem{path, method, data, std::move(promise)});
    if (!m_busy)
        processReq();
    return future;
}


void ApiClient::reqFinished()
{

    QJsonObject obj;
    int respCode = m_rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray respData = m_rep->readAll();

    QNetworkReply::NetworkError respError = m_rep->error();

    if (respError != QNetworkReply::NoError) {
        obj["respCode"] = respCode;
        obj["errorString"] = m_rep->errorString();

        // qDebug() << respError;
        // if(respError != QNetworkReply::ContentNotFoundError && respError != QNetworkReply::InternalServerError){
        //     set_offline(true);
        // }

    } else {
        QJsonParseError jerr;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(respData, &jerr);
        // qDebug() << jerr.errorString();
        obj = jsonDoc.isNull() ? QJsonObject{{"respCode", respCode}, {"errorString", jerr.errorString()}}
                               : jsonDoc.object();
    }

    m_currentReqItem->promise.addResult(obj, 0);
    m_currentReqItem->promise.finish();

    m_rep->deleteLater();
    delete m_currentReqItem;
    m_currentReqItem = nullptr;

    processReq();
}

void ApiClient::processReq()
{
    if (m_reqQueue.isEmpty()) {
        set_busy(false);
        return;
    }

    set_busy(true);
    m_currentReqItem = m_reqQueue.dequeue();
    QJsonObject obj = m_errorJson;

    QString currentToken = qEnvironmentVariable("HF_TOKEN", "NONE");
    set_token(currentToken);

    if (currentToken == "NONE") {
        set_anonymous(true);
        // m_req.

        m_req.setRawHeader("Authorization", QByteArray("Bearer " + m_token.toLocal8Bit()));

    } else {
        set_anonymous(false);
    }

    QString base = qEnvironmentVariable("HF_URL", HF_BASE_URL);
    QUrl url(QString("%1/api/%2").arg(base, m_currentReqItem->path));
    // QUrlQuery query;
    // query.addQueryItem("if", needed later);
    // url.setQuery(query);

    qDebug() << url.toString();
    m_req.setUrl(url);


    QJsonDocument jdoc;
    switch (m_currentReqItem->method) {
    case ApiClient::Get:
        m_rep = m_nam->get(m_req);
        break;
    case ApiClient::Post:
        jdoc.setObject(m_currentReqItem->data);
        m_rep = m_nam->post(m_req, jdoc.toJson());
        break;
    case ApiClient::Put:
        jdoc.setObject(m_currentReqItem->data);
        m_rep = m_nam->put(m_req, jdoc.toJson());
        break;
    case ApiClient::Delete:
        m_rep = m_nam->deleteResource(m_req);
        break;
    case ApiClient::Custom:
        m_rep = m_nam->get(m_req);//, "GET", );
        break;
    default:
        obj["errorString"] = "Unsupported HTTP method";
        delete m_currentReqItem;
        return;
    }
    connect(m_rep,&QNetworkReply::finished,this,&ApiClient::reqFinished);
}

