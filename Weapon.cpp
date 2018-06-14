#include <iostream>
#include <cstring>
#include "Weapon.h"
#include "Player.h"
using std::string;

Weapon::Weapon(const string name, Target target, int hit_strength) :
        name(name), target(target),hit_strength(hit_strength) {
    this->name=name;
}
/*
Weapon::Weapon(const Weapon &weapon) : name(name),
                                       target(weapon.target),
                                       hit_strength(weapon.hit_strength) {
    //strcpy(this->name, weapon.name);
}

Weapon::~Weapon() {
}

*/
Target Weapon::getTarget() const {
    return this->target;
}

int Weapon::getHitStrength() const {
    return this->hit_strength;
}

int Weapon::getValue() const {
    if (this->target == LEVEL)
        return this->hit_strength;
    if (this->target == STRENGTH)
        return (this->hit_strength) * 2;
    if (this->target == LIFE)
        return (this->hit_strength) * 3;

    return 0;
}


bool operator==(const Weapon &weapon1, const Weapon &weapon2) {
    return weapon1.getValue() == weapon2.getValue();
}


bool operator!=(const Weapon &weapon1, const Weapon &weapon2) {
    return weapon1.getValue() != weapon2.getValue();
}


bool operator<(const Weapon &weapon1, const Weapon &weapon2) {
    return weapon1.getValue() < weapon2.getValue();
}


bool operator>(const Weapon &weapon1, const Weapon &weapon2) {
    return weapon1.getValue() > weapon2.getValue();
}



/*
Weapon &Weapon::operator=(const Weapon &weapon) {
    if (this == &weapon) {
        return *this;
    }
    name=weapon.name;
    target = weapon.target;
    hit_strength = weapon.hit_strength;
    return *this;
}

*/

std::ostream &operator<<(std::ostream &fl, const Weapon &weapon) {
    return fl << "{weapon name: " << weapon.name << ""
            ", weapon value:" << weapon.getValue() << "}";
}