#pragma once

#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
class Inventory {
public:
    void addItem(const std::shared_ptr<T>& item);
    void removeItem(const std::shared_ptr<T>& item);
private:
    std::vector<std::shared_ptr<T>> items;
    int itemCount;
};