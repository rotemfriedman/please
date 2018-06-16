#include <cstring>
#include <iostream>
#include "Weapon.h"
#include "Player.h"
using std::string;



Player::Player(const string name, const Weapon &weapon) :
        name(name), level(1), strength(1),life(1),
        weapon_of_player(weapon), position_of_player(0) {
    //strcpy(this->name, name);
}

/*
Player::Player(const Player &player) : name(name), level(player.level),
                                       life(player.life),
                                       strength(player.strength),
                                       weapon_of_player(
                                               player.weapon_of_player),
                                       position_of_player
                                               (player.position_of_player) {
    //strcpy(this->name, player.name);
}


Player::~Player() {
}
*/

void Player::nextLevel() {
    this->level++;
}


bool Player::isPlayer(const string playerName) const {
    if (playerName==this->name)
        return true;
    else
        return false;
}

void Player::makeStep() {
    this->position_of_player++;
}

void Player::addLife() {
    this->life++;
}

void Player::addStrength(int strenghToAdd) {
    this->strength = this->strength + strenghToAdd;
}

bool Player::isAlive() const {
    if (this->level > 0 && this->strength > 0 && this->life > 0) {
        return true;
    } else {
        return false;
    }
}

bool Player::weaponIsWeak(int weaponMinStrength) const {
    int value = this->weapon_of_player.getValue();
    if (value < weaponMinStrength)
        return true;
    else
        return false;
}


bool Player::operator<(const Player &player2) const {
    if (this->name<player2.name)
        return true;
    else
        return false;
}


bool Player::operator>(const Player &player2) const {
    if (this->name>player2.name)
        return true;
    else
        return false;
}


ostream &operator<<(ostream &os, const Player &player) {
    return os << "{player name: " << player.name << ", weapon: "
              << player.weapon_of_player << "}";
}

/*
Player &Player::operator=(const Player &player) {
    if (this == &player)
        return *this;
    name=player.name;
    level = player.level;
    life = player.life;
    strength = player.strength;
    weapon_of_player = player.weapon_of_player;
    position_of_player = player.position_of_player;
    return *this;
}
*/

bool Player::fight(Player &player) {
    Weapon &weapon1 = player.weapon_of_player;
    Weapon &weapon2 = this->weapon_of_player;
    if (player.canAttack(*this)){
        Target target1 = weapon1.getTarget();
        int damage = player.weapon_of_player.getHitStrength();
        help_fight(*this, damage, target1);
        return true;
    } else if (this->canAttack(player)) {  //weapon of this stronger then player
        Target target2 = weapon2.getTarget();
        int damage = this->weapon_of_player.getHitStrength();
        help_fight(player, damage, target2);
        return true;
    }else
    return false;
}

void Player::help_fight(Player &player, int damage, Target target) {
    if (target == LEVEL) {
        player.level -= damage;
        if (player.level < 0)
            player.level = 0;
    } else if (target == LIFE) {
        player.life -= damage;
        if (player.life < 0)
            player.life = 0;
    } else if (target == STRENGTH) {
        player.strength -= damage;
        if (player.strength < 0)
            player.strength = 0;
    }
    return;
}


int Player::distance(int position1,int position2){
    if(position1>position2)
        return position1-position2;
    else
        return position2-position1;
}

bool Player::canAttack(Player& player1)const{
  if (position_of_player!=player1.position_of_player)
      return false;
    if(weapon_of_player==player1.weapon_of_player)
        return false;
    if(weapon_of_player>player1.weapon_of_player)
      return true;
    else
        return false;
}

 int Player::getPosition(Player& player){
    return player.position_of_player;
}

 Weapon Player::getWeapon(Player& player){
    return player.weapon_of_player;

}

bool Wizard::canAttack(Player& player)const  {
int x=player.getPosition(player);
if(this->position_of_player==x)
return false;
if(distance(this->position_of_player,x)>this->range)
return false;
Weapon weapon=player.getWeapon(player);
if(weapon_of_player>weapon)
return true;
else
return false;
}