#pragma once

#include "InventoryBase.h"
#include "Item.h"
#include "Key.h"
#include <memory>
#include <vector>
#include <algorithm>

template<typename T>
class Inventory : public InventoryBase {
public:
    explicit Inventory(QObject *parent = nullptr) : InventoryBase(parent) {}

    Q_INVOKABLE void addItem(std::shared_ptr<T> item) {
        // Check if the inventory is already full
        if(items.size() < 4) {
            items.push_back(std::move(item));
            emit countChanged();
        }
    }

    Q_INVOKABLE void addItem(QPointer<T> item) {
        if (item) {
            if(items.size() < 4) {
                items.push_back(std::shared_ptr<T>(item.data(), [](T*){}));
                emit countChanged();
            }
        }
    }


    Q_INVOKABLE QObject* getItem(int index) const {
        if (index >= 0 && index < static_cast<int>(items.size())) {
            return dynamic_cast<QObject*>(items[index].get());
        }
        return nullptr;
    }

    int count() override { return items.size(); }

    std::shared_ptr<T> removeItem(const std::shared_ptr<T>& item) {
        // auto is used to automatically determine the type of the variable
        for (auto i = items.begin(); i != items.end(); ++i) {
            if (*i == item) {
                items.erase(i);
                emit countChanged();
                return item;
            }
        }
        return nullptr;
    }

    bool isFull(){
        if(items.size() >= 4) {
            return true;
        }
        return false;
    }

    void removeUsedKeys() {
        for (auto it = items.begin(); it != items.end(); /* no increment here */) {
            // Dynamic cast to Key* to check if this item is a Key
            Key* key = dynamic_cast<Key*>((*it).get());

            if (key && key->getProperty()) {
                it = items.erase(it);
                emit countChanged();
            } else {
                ++it;
            }
        }
    }

signals:
    void countChanged();

private:
    std::vector<std::shared_ptr<T>> items;
};

template<typename T>
void Inventory<T>::countChanged() {
    InventoryBase::countChanged();
}


// Using the template to create an Item Inventory
using ItemInventory = Inventory<Item>;