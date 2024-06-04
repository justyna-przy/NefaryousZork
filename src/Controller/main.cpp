// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <QQmlContext>
#include <QQuickWindow>
#include "../Model/Exit.h"
#include "../Model/Room.h"
#include "../Model/InventoryBase.h"
#include "Game.h"
#include "../Model/Player.h"


Game game;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    constexpr const char* uri = "com.nefaryous.game";
    constexpr int versionMajor = 1;
    constexpr int versionMinor = 0;
    constexpr const char* qmlName = "Game";

    qmlRegisterType<Game>(uri, versionMajor, versionMinor, qmlName);
    qmlRegisterType<Exit>("com.nefaryous.game", 1, 0, "Exit");
    qmlRegisterType<Room>("com.nefaryous.game", 1, 0, "Room");
    qmlRegisterUncreatableType<InventoryBase>("com.nefaryous.game", 1, 0, "InventoryBase",
                                              QStringLiteral("InventoryBase cannot be created in QML"));
    QQmlApplicationEngine engine;



    engine.rootContext()->setContextProperty("game", &game);
    engine.rootContext()->setContextProperty("player", &Player::instance());


    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    QQuickWindow *window = qobject_cast<QQuickWindow *>(engine.rootObjects().first());
    if (window) {
        window->setMinimumSize(QSize(740, 740));
        window->setMaximumSize(QSize(740, 740));
    }

    return app.exec();
}
