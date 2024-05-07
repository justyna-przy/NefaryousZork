#pragma once
#include "Entity.h"
#include "Exit.h"
#include <vector>
//#include <QString>
//#include <QMap>
//#include <QPixmap>

using namespace std;

class Room : public Entity {
public:
    Room(string name, string description);
    ~Room();
    void Look();
    void addExit(Exit* exit);
    const vector<Exit*> getExits(); // const prevents modification to the original vector
//    void addState(const QString& state, const QString& imagePath);
//    void setState(const QString& state);
//    QPixmap getCurrentImage();

private:
    vector<Exit*> exits;
//    QMap<QString, QPixmap> roomImages;
//    QString currentState;
};