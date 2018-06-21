#ifndef HW4_GAME_H
#define HW4_GAME_H


#include <vector>
#include "Weapon.h"
#include "Player.h"
#include "mtm_exceptions.h"

using std::string;
using std::vector;
using std::swap;


enum GameStatus {
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    SUCCESS,
    NAME_DOES_NOT_EXIST,
    INVALID_PARAM,
    FIGHT_FAILED,
    ILLEGAL_WEAPON
};


class Game {
    int maxPlayer;
    vector<Player *> array_player;
    int last_player_in_the_array;

    /**
     * the function help the function fight to delete the user(if he dead)
     */
    void helpFight();

    /**
     * ths function checl if one of the players dead, if yes, we remove them.
     */
    void fightCheckIfAlive();

    /**
     * the function find the max index, sort by the playerName
     * @return - the max index
     */
    int index_of_max(int length) const;

/**
 * the function sort the array of the player by the playerName
 */
    void max_sort();


    /**
 * get 2 players and replace them;
 * @param player1
 * @param player2
 */
    void swap(Player &player1, Player &player2);


public:
/**
 * the functuin create a new classe game
 * @param maxPlayer
 */
    Game(int maxPlayer);

/**
 * the function delete the Game(free him)
 */

    ~Game();

/**
 * copy constructor of the game
 * @param game
 */
    Game(const Game &game);

/**
 *
 * @param playerName
 * @param weaponName
 * @param target
 * @param hit_strength
 * @return
 */
    GameStatus addPlayer(const string playerName, const string weaponName,
                         Target target, int hit_strength);

    /**
     * the metoda get name of a player, and increase his level
     * @param playerName- the name of the player
     * @return- if the player does not exist return - NAME_DOES_NOT_EXIST
     */
    GameStatus nextLevel(const string playerName);

/**
 *the function
 * @param playerName1
 * @param playerNamr1
 * @return
 */
    GameStatus fight(const string playerName1, const string playerName2);

/**
 * get a playerName and increase the position of the player
 * @param playerName- the name of the player
 * @return- NAME_DOES_NOT_EXIST if the name doesn't exist or SUCCESS
 */
    GameStatus makeStep(const string playerName);


/**
 * get a playerName and increase his life
 * @param playerName - the name of the player
 * @return- NAME_DOES_NOT_EXIST if the name doesn't exist or SUCCESS
 */
    GameStatus addLife(const string playerName);

/**
 * add the strength to the player
 * @param playerName - the player name
 * @param strengthToAdd - the strength that we need to add
 * @return- INVALID_PARAM if the strengthToAdd is minos, or NAME_DOES_NOT_EXIST
 * or SUCCESS
 */
    GameStatus addStrength(const string playerName, int strengthToAdd);

/**
 * remove all the players that thier weapon is weaker than the weaponStrangth.
 * @param weaponStrangth - the weaponStrangth to compare
 * @return true- if the players removed. else false
 */
    bool removeAllPlayersWithWeakWeapon(int weaponStrangth);

    /**
 * this function print all the players sorted by the lexikografi name
 * @param os
 * @param game-the game that we want to print the players from him
 */
    friend ostream &operator<<(ostream &os, Game &game);

    /**
     * operator hasama for the game class
     * @param game - the game that we want to give to "this"
     * @return - reference of the new game
     */
    Game &operator=(const Game &game);


    /**
     * the function is a help function for the add player
     * @param player - a pointer to a type Player
     */
    void addPlayerWithDifferentType(Player *player, string const &playerName);


    /**
     * the function add new troll to the game
     * @param playerName - the name of the player that will add to the troll
     * @param weaponName - the name of the player that will add to the troll
     * @param target -data for the creation of the weapon
     * @param hitStrength -data for the creation of the weapon
     * @param maxLife - will add to the new troll
     */
    void addTroll(string const &playerName, string const &weaponName,
                  Target target, int hitStrength, int maxLife);


    /**
     * the function add new warrior to the game
     * @param playerName-the name of the player that will add to the warrior
     * @param weaponName-the name of the player that will add to the warrior
     * @param target-data for the creation of the weapon
     * @param hitStrength-data for the creation of the weapon
     * @param rider - will add to the new warrior
     */
    void addWarrior(string const &playerName, string const &weaponName,
                    Target target, int hitStrength, bool rider);


/**
 * the function add new wizard to the game
 * @param playerName -the name of the player that will add to the wizard
 * @param weaponName -the name of the player that will add to the wizard
 * @param target -data for the creation of the weapon
 * @param hitStrength -data for the creation of the weapon
 * @param range - will add to the new wizard
 */
    void addWizard(string const &playerName, string const &weaponName,
                   Target target, int hitStrength, int range);


    /**
 * extend the function removeAllPlayersWithWeakWeapon
 * @param fcn - the function that according to her we will know if to remove
 * the player or not
 * @return true- if the players removed. else false
 */
    template<class FCN>
    bool removePlayersIf(FCN &fcn) {
        int check_if_remove = 0; //if change to 1, than we already remove players
        for (int i = 0; i <= last_player_in_the_array; i++) {
            if ((fcn(static_cast<Player const &> (*this->array_player[i])) == true) ){
                delete array_player[i];
                array_player.erase(array_player.begin() + i);
                last_player_in_the_array--;
                check_if_remove = 1;
                i--;
                array_player.resize(maxPlayer, nullptr);
            }
        }
        if (check_if_remove == 1)
            return true;
        else
            return false;
    }



/**
 * this class help to the function "removeAllPlayersWithWeakWeapon"
 */
    class checkIfWeaponIsWeak{
        int weaponStrength;
    public:
        checkIfWeaponIsWeak(int weaponStrength) : weaponStrength(weaponStrength){
        }
        bool operator()(Player const& player) const {
            return(player.weaponIsWeak(weaponStrength));
        }
    };

};



#endif //HW4_GAME_H