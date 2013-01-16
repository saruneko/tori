#include <QCoreApplication>
#include <tori_daemon.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tori::ToriDaemon* daemon = new tori::ToriDaemon();
    daemon->start();

    return a.exec();
}
