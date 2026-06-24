#ifndef QSDPATH_H
#define QSDPATH_H

#include <QObject>
#include <QQmlEngine>

#include "property-macros.h"
#include "pointer-macros.h"
#include "qmlstringlist.h"

class QSdPath : public QObject
{
    Q_OBJECT
    QP_RW(QString,              currentModel,           "" )
    QP_PTR_RO(QmlStringList,    modelDirs)
    QP_PTR_RO(QmlStringList,    availableModels)
    QML_ELEMENT
public:
    explicit QSdPath(QObject *parent = nullptr);

signals:
};

#endif // QSDPATH_H
