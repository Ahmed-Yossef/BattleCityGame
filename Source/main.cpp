#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "game.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Game* game = new Game();

    return app.exec();
}
