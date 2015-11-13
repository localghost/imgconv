#include <QApplication>
#include <QObject>
#include <QUrl>
#include <QString>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQuickView>

class Helpers : public QObject
{
   Q_OBJECT
public:
   Q_INVOKABLE QString urlToPath(const QUrl& url) const
   {
      return url.path();
   }
};

static QJSValue example_qjsvalue_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)

//    static int seedValue = 5;
    QJSValue example = scriptEngine->newQObject(new Helpers);
//    example.setProperty("someProperty", seedValue++);
    return example;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QQmlApplicationEngine engine;
    qmlRegisterSingletonType("Qt.extension", 1, 0, "Helpers", example_qjsvalue_singletontype_provider);

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

//    QGuiApplication app(argc, argv);

//    qmlRegisterSingletonType("Qt.extension", 1, 0, "Helpers", example_qjsvalue_singletontype_provider);

//    QQuickView view;
//    view.setSource(QUrl("qrc:Main.qml"));
//    view.show();

    return app.exec();
}

#include "main.moc"
