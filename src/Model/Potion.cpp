#include "Potion.h"
#include "src/Controller/Game.h"

Potion::Potion(string name, string description, int strength, string imageName, PotionType type) :
        Item(name, description, imageName), strength(strength), potionType(type)
{
}

Potion::~Potion() = default;

void Potion::use() {
    QString message = "You take the potion out of your inventory. You unscrew the top and scare at the glistening liquid. Without a second thought, you tilt your head back and take a swig.";
    game.addToGameLog(message);
    Player* player = &Player::instance();
    if(this->potionType == HEALING) {
        player->heal(strength);
    }
    else if(this->potionType == DAMAGING) {
        player->receiveDamage(strength);
    }

}

int Potion::getProperty() {
    return strength;
}