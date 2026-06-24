#ifndef HUGGINGFACEAPI_H
#define HUGGINGFACEAPI_H

#include <QObject>
#include <QQmlEngine>
#include "apiclient.h"
class HuggingFaceApi : public ApiClient
{
    Q_OBJECT

public:
    explicit HuggingFaceApi(QObject *parent = nullptr);
    QFuture<QJsonObject> trending()
    {
        return request("trending");
    }
    QFuture<QJsonObject> login()
    {
        return request("whoami-v2");
    }
    QFuture<QJsonObject> modelsTagsByType(QStringList tags)
    {
        return request("models-tags-by-type");
    }
    QFuture<QJsonObject> models(int limit = 1000)
    {
        QString reqStr = QString("models");
        if(limit > 0 && limit < 100000 ){
            reqStr = QString("models?limit=%1").arg(QString::number(limit));
        }
        return request(reqStr);
    }

    QFuture<QJsonObject> searchModelsWithKeyWords(const QString &modelName, QStringList keywords, quint8 limit = 10)
    {
        QString reqStr = QString("models?search=%1?limit=%2?keywords=%3")
            .arg(modelName)
            .arg(QString::number(limit));

        if(!keywords.isEmpty()){
            QString keywordFStr = keywords.join(",");
            reqStr = QString("models?search=%1?limit=%2?keywords=%3")
                        .arg(modelName)
                        .arg(QString::number(limit)
                        .arg(keywordFStr));
        }
        return request(reqStr);
    }


    QFuture<QJsonObject> searchModels(const QString &modelName, quint8 limit = 10)
    {
        QString reqStr = QString("models?search=%1?limit=%2")
                             .arg(modelName)
                             .arg(QString::number(limit));
        return request(reqStr);
    }

    QFuture<QJsonObject> searchModelsByAuthor(const QString &modelAuthor, quint8 limit = 10){
        QString reqStr = QString("models?author=%1?limit=%2")
                             .arg(modelAuthor)
                             .arg(QString::number(limit));
        return request(reqStr);
    }


    QFuture<QJsonObject> repoByNS(const QString &ns, const QString &repo)
    {
        QString reqStr = QString("models/%1/%2")
            .arg(ns)
            .arg(repo);
        return request(reqStr);
    }

    QFuture<QJsonObject> repoRefs(const QString &ns, const QString &repo)
    {
        QString reqStr = QString("models/%1/%2/refs")
            .arg(ns)
            .arg(repo);
        return request(reqStr);
    }

    QFuture<QJsonObject> lfsFiles(const QString &ns, const QString &repo, qint8 limit = -1){
        // "models/{namespace}/{repo}/lfs-files
        QString reqStr = QString("models/%1/%2/lfs-files")
                             .arg(ns)
                             .arg(repo);

        if(limit != -1){
            QString reqStr = QString("models/%1/%2/lfs-files?limit=%3")
            .arg(ns)
                .arg(repo)
                .arg(QString::number(limit));

        }
        return request(reqStr);
    }


    QFuture<QJsonObject> requestAccess(const QString &ns, const QString &repo, QJsonObject data){
        // "models/{namespace}/{repo}/ask-access
        QString reqStr = QString("models/%1/%2/ask-access")
                             .arg(ns)
                             .arg(repo);
        return request(reqStr, ApiClient::Post, data);
    }


// curl 'https://huggingface.co/{namespace}/{repo}/ask-access' \
//     --request POST \
//     --header 'Content-Type: application/json' \
//     --header 'Authorization: Bearer BAD_KEY' \
//     --data '{}'

// keys=id,downloads,pipeline_tag
// "models/{namespace}/{repo}/treesize/{rev}/{path}
// "models/{namespace}/{repo}/commits/{rev}
// "models/{namespace}/{repo}/compare/{compare}
// "models/{namespace}/{repo}/xet-write-token/{rev}
// "models/{namespace}/{repo}/xet-read-token/{rev}


// "models/{namespace}/{repo}/resource-group
// "models/{namespace}/{repo}/tree/{rev}/{path}
// "models/{namespace}/{repo}/notebook/{rev}/{path}
// "models/{namespace}/{repo}/scan
// "models/{namespace}/{repo}/jwt


// "/{namespace}/{repo}/resolve/{rev}/{path}"
// "resolve-cache/models/{namespace}/{repo}/{rev}/{path}"
// "/{namespace}/{repo}/user-access-report"
// "models/{namespace}/{repo}/user-access-request/{status}"



Q_SIGNALS:

private:


};

#endif // HUGGINGFACEAPI_H
