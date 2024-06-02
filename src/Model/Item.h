#pragma once

#include <QObject>
#include "Entity.h"
#include "Exit.h"

union ItemProperty {
    int damage;
    int healing;
    const char* color;  // Using C-style string for simplicity in the union
};

class Item: public Entity {

public:
    explicit Item(string name, string description, string imageName) : Entity(name, description){
        this->imageName = QString::fromStdString("qrc:/qt/qml/content/images/" + imageName);
    }
    virtual ~Item() override {

    }
    string getName() const { return name;}
    string getDescription() const { return description;}
    // Pure virtual functions
    virtual void use() = 0;
    virtual int getProperty() = 0;

private:
    QString imageName;
};
