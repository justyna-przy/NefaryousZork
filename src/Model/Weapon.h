#pragma once
#include "Item.h"

class Weapon : public Item {
    Q_OBJECT
public:
    Weapon(string name, string description, int damage, string itemName);
    ~Weapon() override;
    void use() override;
    int getProperty() override;
    ItemType getType() override { return type; }

private:
    int damage;
    const ItemType type = WEAPON;
};
