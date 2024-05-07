// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "Room.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello" <<endl;
    Room* bedroom = new Room("Room 5b", "The chinchillas eagerly await your entry.");
    Room* hallway = new Room("Hallway", "Small but bright hallway");
    Room* kitchen = new Room("Kitchen", "Stinky ah kitchen");

    Exit* hallwayDoor = new Exit("White door", "Heavy but with a new lock", bedroom, hallway, false);
    Exit* bedroomDoor = new Exit("White door", "b", hallway, bedroom, false);
    Exit* a = new Exit("White door", "a", hallway, nullptr, true);
    Exit* d = new Exit("White door", "d", hallway, nullptr, true);
    Exit* c = new Exit("White door", "c", hallway, nullptr, true);
    Exit* hallwayKDoor = new Exit("Kitchen door", "Grey", hallway, kitchen, false);
    Exit* kitchenHDoor = new Exit("Kitchen door", "Grey", kitchen, hallway, false);


    bedroom->addExit(hallwayDoor);
    hallway->addExit(bedroomDoor);
    hallway->addExit(a);
    hallway->addExit(d);
    hallway->addExit(c);
    hallway->addExit(hallwayKDoor);
    kitchen->addExit(kitchenHDoor);

    Room* currentRoom = bedroom;
    int i = 100;
    while(i > 0) {
        currentRoom->Look();
        int choice;  // Declare the variable first
        std::cout << "Where do you want to go?: ";  // Prompt the user for input
        std::cin >> choice;

        if(choice == 9) {
            break;
        }
        currentRoom = currentRoom->getExits().at(choice)->getDestination();
        i--;
    }


    set_qt_environment();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
