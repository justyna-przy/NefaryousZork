#pragma once

#include "Item.h"
#include "Enums.h"

class Potion : public Item {


public:
    Potion(string name, string description, int strength, string imageName, PotionType type);
    ~Potion() override;
    void use() override;
    int getProperty() override;
    ItemType getType() override { return type; }

private:
    int strength;
    PotionType potionType;
    const ItemType type = POTION;
};