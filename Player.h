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


    /**
    * help function to fight metoda.
    * check hows the target and lower it in damage
    * @param player
    * @param damage
    * @param target
    */
    void help_fight(Player &player, int damage, Target target);


protected:
    int life;
    Weapon weapon_of_player;
    int position_of_player;


    /**
 * constractur for the player calss
 * @param name - allocate a name
 * @param weapon - initialize this value to the player
 * update the other fields in the value 1 or 0
 */
    Player(const string name, const Weapon &weapon);

    /**
     * the constructor of the players
     */
    Player() = default;


    /**
     * the function get a player and return his position
     * @param player
     * @return position of player
     */
    static int getPosition(Player &player);

    /**
     * the function get a player and return his weapon
     * @param player
     * @return weapon of player
     */
    static Weapon getWeapon(Player &player);

    /**
     * the dunction check what the distance between 2 position
     * in abs
     * @param position1
     * @param position2
     * @return int distance
     */
    static int distance(int position1, int position2);


public:


    /**
 * the function destroy class Player
 */
    virtual ~Player() throw() = default;

    //copy constractor
    Player(const Player &player) = default;

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
    virtual void addLife();

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
    bool fight(Player &player);

    /**
     * the operator do Placement  between 2 players
     * @param player
     * @return
     */
    Player &operator=(const Player &player)= default;

/**
 * check if the player can attack in the fight
 * virtual becuse we use the function in different way with wizard player
 * @param player1
 * @return true if the player can attack the other player and false else.
 */
    virtual bool canAttack(Player &player1) const;
};

/**
 * this function print the name and the weapon of the player
 * @param os
 * @param player - the player to print
 */
ostream &operator<<(ostream &os, const Player &player);


class Warrior : public Player {
    bool rider;
public:
    /**
     * the warrior constructor
     * @param name
     * @param weapon
     * @param rider
     */
    Warrior(string const &name, Weapon const &weapon, bool rider);

    /**
     * warrior destructor
     */
    ~Warrior() throw() override = default;

    /**
     * the function check if rider= true add to position of player 5, ans else
     * add 1
     */
    void makeStep() override;
};


class Troll : public Player {
    int max_life;

public:
/**
 * Troll constructor
 * @param name
 * @param weapon
 * @param maxLife
 */
    Troll(string const &name, Weapon const &weapon, int maxLife);

    /**
     * Troll distructor
     */
    ~Troll() throw() override = default;

    /**
     * the function add 2 to thr troll position of player and check if
     * life<maxlife, if yes add 1 to his life
     */
    void makeStep() override;


    /**
     * the function add life to the troll. if the maxlife==life of the troll,
     * we will stop to add life
     */
    void addLife() override ;

};


class Wizard : public Player {
    int range;
public:
/**
 * wiazrd constructor
 * @param name
 * @param weapon
 * @param range
 */
    Wizard(string const &name, Weapon const &weapon, int range);

    /**
     * wizard destructor
     */
    ~Wizard() throw() override = default;

/**
 * the function check if the wizard can attack (check the range,position and
 * mor)
 * @param player
 * @return
 */
    bool canAttack(Player &player) const override;
};


#endif //HW4_PLAYER_H