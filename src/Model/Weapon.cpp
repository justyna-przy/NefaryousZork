#include <iostream>
#include "Weapon.h"
#include "Player.h"
#include "../Controller/Game.h"

Weapon::Weapon(string name, string description, int damage, string itemName) : Item(name, description, itemName), damage(damage)
{

}


Weapon::~Weapon() = default;

void Weapon::use() {
    QString message = "You gently slice the blade across your finger and blood starts dripping out. You take " + QString::number(damage) + " damage from this";
    game.addToGameLog(message);
    Player* player = &Player::instance();
    player->receiveDamage(damage);
}

int Weapon::getProperty() {
    return damage;
}



