#pragma once
#include "Item.h"

class Weapon : public Item {

public:
    Weapon(string name, string description, int damage, string itemName);
    virtual ~Weapon() override;
    virtual void use() override;
    virtual int getProperty() override;

private:
    int damage;
};
