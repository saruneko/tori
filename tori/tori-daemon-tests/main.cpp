#include <QtWidgets/QApplication>
#include "test_runner.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    return RUN_ALL_QTESTS(argc, argv);
}

