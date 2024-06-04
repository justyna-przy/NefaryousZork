#pragma once

#include <QObject>

// Bit Structures!
struct Health {
    unsigned int current: 8;  // 8 bits for current health, range 0-255
    unsigned int maximum: 8;
};

// Classes cannot be static, so I designed Player as a singleton class, which allows global access
class Player : public QObject {
    Q_OBJECT
    Q_PROPERTY(int currentHealth READ getCurrentHealth NOTIFY healthChanged)
    Q_PROPERTY(int maximumHealth READ getMaximumHealth CONSTANT)

public:
    static Player& instance();
    int getCurrentHealth() const { return health.current; }
    int getMaximumHealth() const { return health.maximum; }
    void receiveDamage(int amount);
    void heal(int amount);
    void setCurrentHealth(int newHealth);

private:
    explicit Player(QObject *parent = nullptr) : QObject(parent), health({25, 40}) {}
    Health health;

    // Ensures Player object cannot be copied via a copy constructor or reassigned
    Player(const Player&) = delete;
    // Operator Overloading!
    Player& operator=(const Player&) = delete;

signals:
    void healthChanged();
};