#include <QGuiApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.show();

    return app.exec();
}
