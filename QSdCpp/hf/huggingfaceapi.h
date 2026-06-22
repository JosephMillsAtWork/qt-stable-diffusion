#ifndef HUGGINGFACEAPI_H
#define HUGGINGFACEAPI_H

#include <QObject>
#include <QQmlEngine>
#include "apiclient.h"
class HuggingFaceApi : public ApiClient
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HuggingFaceApi(QObject *parent = nullptr);
    QFuture<QJsonObject> trending(){ return request("trending"); }
    QFuture<QJsonObject> whoAmI(){ return request("whoami-v2"); }
    QFuture<QJsonObject> modelsTagsByType(){ return request("models-tags-by-type"); }


// "models/{namespace}/{repo}/treesize/{rev}/{path}
// "models/{namespace}/{repo}/lfs-files
// "models/{namespace}/{repo}/commits/{rev}
// "models/{namespace}/{repo}/refs
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
