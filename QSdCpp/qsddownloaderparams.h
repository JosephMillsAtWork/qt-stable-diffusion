#ifndef QSDDOWNLOADERPARAMS_H
#define QSDDOWNLOADERPARAMS_H

#include "qsdbaseparam.h"
#include <QObject>
#include <QQmlEngine>
#include "qsdenums.h"

class QSdDownloaderParams : public QSdBaseParam
{
    Q_OBJECT
    QP_RW(QString,                      name,   ""                  ) // human read
    QP_RW(QString,                      url,    ""                  )
    QP_RW(QSdEnums::QSdBackendModule,   type,   QSdEnums::Diffusion )
    QP_RW(QString,                      outDir, ""                  )
    QML_ELEMENT


public:
    explicit QSdDownloaderParams(QObject *parent = nullptr) :
        QSdBaseParam{parent}
    {}



Q_SIGNALS:


private:

};

#endif // QSDDOWNLOADERPARAMS_H
