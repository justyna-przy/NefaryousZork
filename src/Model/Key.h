#pragma once

#include "Item.h"

class Key : public Item {

public:
    Key(string name, string description, string itemName);
    Key(const Key& key);
    virtual ~Key() override;
    virtual void use() override;
    virtual int getProperty() override;

private:
    bool used;

signals:
    void keyUsed();
};