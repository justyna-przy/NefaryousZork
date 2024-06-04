#include "Key.h"

Key::Key(string name, string description, string itemName) : Item(name, description, itemName), used(false)
{
}

Key::Key(const Key& key) : Item(key.name, key.description, key.imageName.toStdString()){
    this->imageName = key.imageName;
    this->used = key.used;
}

Key::~Key() = default;

void Key::use() {
    emit keyUsed();

    this->used = true;
}

int Key::getProperty() {
    return used;
}

