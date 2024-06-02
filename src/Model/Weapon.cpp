#include <iostream>
#include "Weapon.h"

Weapon::Weapon(string name, string description, int damage, string itemName) : Item(name, description, itemName), damage(damage)
{
}

Weapon::~Weapon()
{
}

void Weapon::use() {
    std::cout << "Using Sword! " + damage <<endl;
}

int Weapon::getProperty() {
    return damage;
}



