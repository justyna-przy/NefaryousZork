#pragma once

#include <QObject>
#include "Entity.h"
#include "../Controller/Game.h"
#include <QDebug>
class Key;

class Interactable : public QObject, public Entity{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)

public:
    Interactable(string name, string description) : Entity(std::move(name), std::move(description)){}

    Q_INVOKABLE void interact() {
        if (this->name == "Use Alter") {
            Key *key = game.playerGetKey();
            if(key) {
                game.addToGameLog("Under the eerie moonlight, you place the key on the ancient altar. The shadows around you seem to stir slightly as the key touches the stone surface.");
                game.cloningSpell(*key);
                game.addToGameLog("");
            }
            else {
                game.addToGameLog("You have nothing to clone.. maybe go find something shiny?");
            }
        }
        else {
            game.addToGameLog("There is nothing to interact with here");
        }
        return;
    }
    QString getName() const { return QString::fromStdString(name);}
    QString getDescription() const { return QString::fromStdString(description);}

};



