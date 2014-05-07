#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "snakecanvas.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<SnakeCanvas>("Snake", 1, 0, "SnakeCanvas");
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/Snake/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
