#pragma once

#include <QObject>
#include "Entity.h"
#include "Exit.h"
#include "Enums.h"

union ItemProperty {
    int damage;
    int healing;
    const char* color;  // Using C-style string for simplicity in the union
};

class Item: public QObject, public Entity {
    Q_OBJECT
    Q_PROPERTY(QString imageName READ getImage CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)

public:
    explicit Item(string name, string description, string imageName) : Entity(name, description){
        this->imageName = QString::fromStdString("qrc:/qt/qml/content/images/" + imageName);
    }

    Item(const Item& item) : Entity(item.name, item.description){
        this->imageName = item.imageName;
    }

    virtual ~Item() override = default;
    QString getName() const { return QString::fromStdString(name);}
    QString getDescription() const { return QString::fromStdString(description);}
    virtual ItemType getType()  { return type; }

    // Pure virtual functions
    Q_INVOKABLE virtual void use() = 0;
    virtual int getProperty() = 0;
    QString getImage() const { return imageName; }

signals:
    void nameChanged();

protected:
    QString imageName;

private:
    ItemType type;

};

