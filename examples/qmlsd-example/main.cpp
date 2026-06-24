#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlExtensionPlugin>
#include <QtResource>
#include <qdiriterator.h>

#include <qsdutils.h>

Q_IMPORT_QML_PLUGIN(QSdPlugin)
Q_IMPORT_QML_PLUGIN(QHFPlugin)

static void debugQRCPaths()
{
    qDebug() << "================= QRC TREE INSPECTION =================";
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString path = it.next();
        // Filter down to our modules to keep the logs clean
        if (path.contains("QSd", Qt::CaseInsensitive) || path.contains("QHF", Qt::CaseInsensitive)) {
            qDebug() << "Found QRC Asset:" << path;
        }
    }
    qDebug() << "=======================================================";
}


int main(int argc, char *argv[])
{


    QGuiApplication app(argc, argv);


    QSdUtils::createDefaultDirs();



    Q_INIT_RESOURCE(qmake_QSd);
    Q_INIT_RESOURCE(qmake_QHF);
    QQmlApplicationEngine engine;

    if(QSdUtils::dirExists(QSdUtils::pluginsDir))
        engine.addPluginPath(QSdUtils::pluginsDir);

    if(QSdUtils::dirExists(QSdUtils::extraQmlDir))
        engine.addImportPath(QSdUtils::extraQmlDir);

    engine.addImportPath(QStringLiteral("qrc:/"));

    // debugQRCPaths();

    const QUrl url(QStringLiteral("qrc:/QMLSDEXAMPLE/main.qml"));


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
