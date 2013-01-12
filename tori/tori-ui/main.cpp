#include <QGuiApplication>
#include <QQuickView>
#include <QScreen>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setWindowTitle("Tori");
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    QScreen* screen = app.primaryScreen();
//    view.setGeometry(screen->availableGeometry().width() - view.width() - 20, 70, 300, 300);
    view.setX(screen->availableGeometry().width() - view.width() - 20);
    view.setY(70);
    view.show();

    return app.exec();
}
