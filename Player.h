#ifndef HW4_PLAYER_H
#define HW4_PLAYER_H

#include <iostream>
#include "Weapon.h"
#include <ostream>
#include "mtm_exceptions.h"

using std::string;




using std::ostream;
using std::endl;
using std::string;

class Player {
    string name;
    int level;
    int strength;

    void help_fight(Player &player, int damage, Target target);

protected:
    int life;
    Weapon weapon_of_player;
    int position_of_player;


static int distance(int position1,int position2);
    /**
 * help function to fight metoda.
 * check hows the target and lower it in damage
 * @param player
 * @param damage
 * @param target
 */

public:

    /**
    * constractur for the player calss
    * @param name - allocate a name
    * @param weapon - initialize this value to the player
    * update the other fields in the value 1 or 0
    */
    Player(const string name, const Weapon &weapon);
      Player() = default;

    /**
 * the function destroy class Player
 */
    ~Player()= default;

    //copy constractor
    Player(const Player &player)= default;

    /**
 * increase the field level in 1
 */
    void nextLevel();

    /**
     * check if the playerName is the name of the player
     * @param playerName - the name to check
     * @return - true if the playerName is the player, else false
     */

    bool isPlayer(const string playerName) const;


    /**
     * increase the position of the player
     */
    virtual void makeStep();

/**
 * increase the life of the player
 */
    void addLife();

/**
 * add the value to the strength of the player
 * @param strenghToAdd - the value that we need to add
 */
    void addStrength(int strenghToAdd);


/**
 * the metoda check if the player is alive
 * @return - true if: level, life, strength is biger then 0, else false
 */
    bool isAlive() const;


/**
 * the metoda check the value of the weapon.
 * @param weaponMinStrength - this value is for comparison
 * @return- true if value<weaponMinStrength . else return false
 */
    bool weaponIsWeak(int weaponMinStrength) const;


/**
 * operator <, make according to the name
 * @param player1 - the player number 1 that we check his name
 * @param player2 - the player number 2 that we check his name
 * @return true if the name of player1 is small lexikografit from player2
 */
    bool operator<(const Player &player2) const;


/**
 * perator >, make according to the name
 * @param player1 - the player number 1 that we check his name
 * @param player2 - the player number 2 that we check his name
 * @return true if the name of player1 is biger lexikografit from player2
 */
    bool operator>(const Player &player2) const;

    /**
     * the function print the player in the format that need
     * @param os
     * @param player
     * @return
     */
    friend ostream &operator<<(ostream &os, const Player &player);

/**
 *
 * @param player
 * @return true if the fight success end false else
 * if the 2 players not in the same position return false
 * if the players have the same strong in there weapon return false
 * else do the fight and lower the point of the weak player in damage;
 */
    virtual bool fight(Player &player);

    /**
     * the operator do Placement  between 2 players
     * @param player
     * @return
     */
    Player &operator=(const Player &player)= default;


    virtual bool canAttack(Player& player1)const ;
};

/**
 * this function print the name and the weapon of the player
 * @param os
 * @param player - the player to print
 */
ostream &operator<<(ostream &os, const Player &player);


class Warrior:public Player {
    bool rider;

public:
    Warrior(string const &name, Weapon const &weapon, bool rider):
            Player(name, weapon),rider(rider){
        if(weapon.getTarget()==LEVEL)
            throw mtm::IllegalWeapon();

    }

    ~Warrior() = default;

    void makeStep(){
        if(rider==true){
            position_of_player+=5;
        }
        else{
            position_of_player+=1;
        }
    }

};



class Troll:public Player {
    int max_life;

public:

    Troll(string const &name, Weapon const &weapon, int maxLife):
            Player(name,weapon),max_life(maxLife){
        if(max_life<=0)
            throw mtm::InvalidParam();
    }

    ~Troll() = default;

    void makeStep(){
        position_of_player += 2;
        if (life < max_life)
            this->addLife();
    }

};




class Wizard:public Player {
    int range;

public:
    Wizard(string const &name, Weapon const &weapon, int range):Player(name,
                                                                       weapon),
                                                                range(range){
        if(range<0)
            throw mtm::InvalidParam();
        if(weapon.getTarget()==LIFE)
            throw mtm::IllegalWeapon();
    }
    ~Wizard() = default;

    bool canAttack(Player& player)const override {
            if(this->position_of_player==player.position_of_player)
                return false;
        if(distance(this->position_of_player,player.position_of_player)<this->range)
            return false;
        return true;
    }
    };


/*
bool Player::fight(Player &player) {
    if (this->position_of_player != player.position_of_player)
        return false;
    Weapon &weapon1 = player.weapon_of_player;
    Weapon &weapon2 = this->weapon_of_player;
    if (weapon1 == weapon2)
        return false;
    if (weapon1 > weapon2) {   //weapon of player stronger then this
        Target target1 = weapon1.getTarget();
        int damage = player.weapon_of_player.getHitStrength();
        help_fight(*this, damage, target1);
        return true;
    } else if (weapon2 > weapon1) {  //weapon of this stronger then player
        Target target2 = weapon2.getTarget();
        int damage = this->weapon_of_player.getHitStrength();
        help_fight(player, damage, target2);
        return true;
    }
    return true;
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
*/

#endif //HW4_PLAYER_H