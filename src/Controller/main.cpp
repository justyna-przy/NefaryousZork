// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <QQmlContext>

#include "src/app_environment.h"
#include "src/import_qml_components_plugins.h"
#include "src/import_qml_plugins.h"
#include "src/Model/Room.h"
#include "src/Controller/Game.h"
#include "src/Model/Item.h"
#include "src/Model/Weapon.h"

class Game;

int main(int argc, char *argv[])
{
    Weapon* waepon = new Weapon("Sword", "Sharp!", 3, "cat.jpg");
    waepon->use();

    QGuiApplication app(argc, argv);

    constexpr const char* uri = "com.nefaryous.game";
    constexpr int versionMajor = 1;
    constexpr int versionMinor = 0;
    constexpr const char* qmlName = "Game";

    qmlRegisterType<Game>(uri, versionMajor, versionMinor, qmlName);
    qmlRegisterType<Exit>("com.nefaryous.game", 1, 0, "Exit");
    qmlRegisterType<Room>("com.nefaryous.game", 1, 0, "Room");

    QQmlApplicationEngine engine;

    // Create an instance of Game
    Game myGame;

    // Expose the instance to QML
    engine.rootContext()->setContextProperty("game", &myGame);

    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
//    qDebug() << "Image path:" << url << "/images/pxArt.png";
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
