#include <QApplication>
#include "qmlapplicationviewer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{

    // UI Logic
//    QObject *root = dynamic_cast<QObject *>(view.rootObject());
//    QVariant msg = "Hello from C++";
//    QVariant msg2 = "@tvstalker";
//    QMetaObject::invokeMethod(root, "add_column",
//    //             Q_RETURN_ARG(QVariant, returnedValue),
//         Q_ARG(QVariant, msg), Q_ARG(QVariant, msg));

    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/toriui/main.qml"));
    viewer.setAttribute(Qt::WA_TranslucentBackground);
    viewer.showExpanded();

    return app->exec();
}
