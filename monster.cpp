#include "monster.h"

Monster::Monster(QString name, int maxHP)
: name_(name)
, maxHP_(maxHP)
, hp_(maxHP)
{}

QString Monster::name() {
    return name_;
}

void Monster::setName(QString name) {
    name_ = name;
}

int Monster::maxHP() {
    return maxHP_;
}

void Monster::setMaxHP(int maxHP) {
    maxHP_ = maxHP;
}

int Monster::hp() {
    return hp_;
}

void Monster::setHP(int hp) {
    hp_ = hp;
}

void Monster::changeHP(int deltaHP) {
    hp_ += deltaHP;
}

void Monster::setHPToMaximum() {
    hp_ = maxHP_;
}

bool Monster::isBloodied() {
    return (hp()*2 <= maxHP());
}

bool Monster::isDead() {
    return (hp() <= 0);
}

bool Monster::isAboveMaxHP() {
    return (hp_ > maxHP_);
}
