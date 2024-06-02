#pragma once
#include "Entity.h"
#include "Exit.h"
#include <vector>
#include <QObject>
//#include <QString>
//#include <QMap>
//#include <QPixmap>

using namespace std;
class Exit;

// QObject must be first base class
// Determines the order in which constructors and destructors are called
class Room : public QObject, public Entity {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString description READ getDescription)
    Q_PROPERTY(QVector<QObject*> exits READ getExits NOTIFY exitsChanged)


public:
    Room(string name, string description, QObject *parent);
    ~Room() override;
    QString getName() const { return QString::fromStdString(name);}
    QString getDescription() const { return QString::fromStdString(description);}
    void addExit(Exit* exit);
    QVector<QObject*> getExits() const; // const prevents modification to the original vector


//    void addState(const QString& state, const QString& imagePath);
//    void setState(const QString& state);
//    QPixmap getCurrentImage();

private:
    // Automatically nullifies pointers if the pointed-to Exit objects are deleted elsewhere
    QVector<QPointer<Exit>> exits;

//    vector<Exit*> exits;
//    QMap<QString, QPixmap> roomImages;
//    QString currentState;

signals:
    void exitsChanged();
};