#include "Player.h"


Player& Player::instance() {
    static Player instance;
    return instance;
}


void Player::receiveDamage(int amount) {
    if (amount < 0) {
        return;
    }

    int newHealth = health.current - amount;
    if (newHealth < 0) {
        newHealth = 0;
    }

    health.current = newHealth;
    emit healthChanged();
}

void Player::heal(int amount) {
    if (amount < 0) {
        return;
    }

    int newHealth = health.current + amount;
    if (newHealth > 255) {
        newHealth = 255;
    }

    health.current = newHealth;
    emit healthChanged();
}


void Player::setCurrentHealth(int newHealth) {
    if (newHealth < 0) {
        newHealth = 0;
    } else if (newHealth > health.maximum) {
        newHealth = health.maximum;
    }
    if (health.current != newHealth) {
        health.current = newHealth;
        emit healthChanged();
    }
}