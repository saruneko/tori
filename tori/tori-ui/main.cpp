#include <QApplication>
#include <QMainWindow>
#include "qmlapplicationviewer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow window(0, Qt::FramelessWindowHint);
    QDeclarativeView view;
    QPalette palette;

    // We'd sure like this window to be translucent if we're able
    window.setAttribute(Qt::WA_TranslucentBackground, true);
    view.setAttribute(Qt::WA_TranslucentBackground);
    palette.setColor(QPalette::Base, Qt::transparent);
    // The only thing we show is the declarative view.
    window.setCentralWidget(&view);
    view.setPalette(palette);
    view.setSource(QUrl("qml/toriui/main.qml"));
    window.show();
    // Pass control to Qt's event loop
    return app.exec();
}
