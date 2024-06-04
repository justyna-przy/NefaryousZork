#pragma once

#include "Item.h"

class Key : public Item {
    Q_OBJECT
public:
    Key(string name, string description, string itemName);
    Key(const Key& key);
    ~Key() override;
    Q_INVOKABLE void use() override;
    int getProperty() override;
    ItemType getType() override { return type; }

private:
    bool used;
    const ItemType type = KEY;

signals:
    void keyUsed();
};