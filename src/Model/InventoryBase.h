#pragma once

#include <QObject>

// This class is purely here because Qt's MOC does not support template classes
// Inventory will inherit from this to be able to interact with the QML
class InventoryBase : public QObject {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)


public:
    explicit InventoryBase(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~InventoryBase() {}
    virtual int count() = 0;
    Q_INVOKABLE virtual QObject* getItem(int index) const = 0;

signals:
    void countChanged();
};
