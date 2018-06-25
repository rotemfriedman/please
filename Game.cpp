#include "Game.h"
#include <algorithm>

using std::string;
using std::vector;
using std::cout;

Game::Game(int maxPlayer) :
        maxPlayer(maxPlayer),
        array_player(vector<Player *>(maxPlayer, nullptr)),
        last_player_in_the_array(-1) {
}


Game::~Game() {
    for (int i = 0; i <= last_player_in_the_array; i++) {
        delete array_player[i];
    }
}


Game::Game(const Game &game) : maxPlayer(game.maxPlayer),
                               array_player(
                                       vector<Player *>(maxPlayer, nullptr)),
                               last_player_in_the_array
                                       (game.last_player_in_the_array) {
    for (int i = 0; i <= this->last_player_in_the_array; i++) {
        (this->array_player[i]) = new Player(*game.array_player[i]);
    }
}


GameStatus Game::addPlayer(const string playerName, const string weaponName,
                           Target target, int hit_strength) {
    Player *player;
    for (int i = 0; i <= this->last_player_in_the_array; i++) {
        const bool
                check_if_the_player_exist = this->array_player[i]->isPlayer(
                playerName);
        if (check_if_the_player_exist == true)
            return NAME_ALREADY_EXISTS;
    }
    if (last_player_in_the_array == maxPlayer - 1)
        return GAME_FULL;
    Weapon weapon = Weapon(weaponName, target, hit_strength);
    try {
        player = new Warrior(playerName, weapon, false);
    }
    catch (mtm::IllegalWeapon &e) {
        return ILLEGAL_WEAPON;
    }
    this->last_player_in_the_array += 1;
    this->array_player[last_player_in_the_array] = player;
    return SUCCESS;
}


GameStatus Game::fight(const string playerName1, const string playerName2) {
    int player1_place_in_the_array = -1;
    int player2_place_in_the_array = -1;
    for (int i = 0; i <= this->last_player_in_the_array; i++) {
        const bool check_if_the_player1_exist = this->array_player[i]->isPlayer(
                playerName1);
        if (check_if_the_player1_exist == true)
            player1_place_in_the_array = i;
        const bool check_if_the_player2_exist = this->array_player[i]->isPlayer(
                playerName2);
        if (check_if_the_player2_exist == true)
            player2_place_in_the_array = i;
    }
        if (player1_place_in_the_array == -1 ||
            player2_place_in_the_array == -1)
            throw mtm::NameDoesNotExist();
        bool check_if_fight_success = this->
                array_player[player1_place_in_the_array]->fight(
                *this->array_player[player2_place_in_the_array]);
        this->fightCheckIfAlive();
        if (check_if_fight_success == false)
            return FIGHT_FAILED;
        else
            return SUCCESS;
    }


void Game::fightCheckIfAlive() {
    for (int i = 0; i <= (this->last_player_in_the_array); i++) {
        bool check_if_alive = this->array_player[i]->isAlive();
        if (check_if_alive == false) {
            delete array_player[i];
            array_player.erase(array_player.begin() + i);
            last_player_in_the_array--;
            i--;
            array_player.resize(maxPlayer, nullptr);
        }
    }
}

GameStatus Game::nextLevel(const string playerName) {
    for (int i = 0; i <= (this->last_player_in_the_array); i++) {
        bool check_player = (this->array_player[i])->isPlayer(playerName);
        if (check_player == true) {
            this->array_player[i]->nextLevel();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

GameStatus Game::makeStep(const string playerName) {
    for (int i = 0; i <= (this->last_player_in_the_array); i++) {
        bool check_player = (this->array_player[i])->isPlayer(playerName);
        if (check_player == true) {
            this->array_player[i]->makeStep();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}


GameStatus Game::addLife(const string playerName) {
    for (int i = 0; i <= (this->last_player_in_the_array); i++) {
        bool check_player = (this->array_player[i])->isPlayer(playerName);
        if (check_player == true) {
            this->array_player[i]->addLife();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

GameStatus Game::addStrength(const string playerName, int strengthToAdd) {
    if (strengthToAdd < 0)
        return INVALID_PARAM;
    for (int i = 0; i <= (this->last_player_in_the_array); i++) {
        bool check_player = (this->array_player[i])->isPlayer(playerName);
        if (check_player == true) {
            this->array_player[i]->addStrength(strengthToAdd);
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

bool Game::removeAllPlayersWithWeakWeapon(int weaponStrangth) {
    checkIfWeaponIsWeak weakWeapon(weaponStrangth);
    return (removePlayersIf(weakWeapon));
}


ostream &operator<<(ostream &os, Game &game) {
    game.max_sort();
    for (int i = 0; i <= (game.last_player_in_the_array); i++) {
        os << "player " << i << ": " << (*game.array_player[i]) << "," << endl;
    }
    return os;
}


void Game::max_sort() {
    int length;
    for (length = this->last_player_in_the_array + 1; length > 1; length--) {
        int index_max = index_of_max(length);
        swap((array_player[index_max]), (array_player[length - 1]));
    }
}


int Game::index_of_max(int length) const {
    int index_max = 0;
    for (int i = 1; i < (length); i++) {
        if (*(this->array_player[index_max]) < (*(this->array_player[i])))
            index_max = i;
    }
    return index_max;
}


Game &Game::operator=(const Game &game) {
    if (this == &game)
        return *this;
    for (int i = 0; i <= this->last_player_in_the_array; i++) {
        delete this->array_player[i];
    }
    array_player.resize(game.maxPlayer, nullptr);
    for (int i = 0; i <= game.last_player_in_the_array; i++) {
        (this->array_player[i]) = new Player(*game.array_player[i]);
    }
    this->last_player_in_the_array = game.last_player_in_the_array;
    this->maxPlayer = game.maxPlayer;
    return *this;
}

void Game::swap(Player* &player1, Player* &player2) {
    Player* temp_player = player1;
    player1 = player2;
    player2 = temp_player;
}


void Game::addTroll(string const &playerName, string const &weaponName,
                    Target target, int hitStrength, int maxLife) {
    Weapon weapon = Weapon(weaponName, target, hitStrength);
    Troll *troll = new Troll(playerName, weapon, maxLife);
    this->addPlayerWithDifferentType(troll, playerName);

}


void Game::addWarrior(string const &playerName, string const &weaponName,
                      Target target, int hitStrength, bool rider) {
    Weapon weapon = Weapon(weaponName, target, hitStrength);
    Warrior *warrior = new Warrior(playerName, weapon, rider);
    this->addPlayerWithDifferentType(warrior, playerName);
}


void Game::addWizard(string const &playerName, string const &weaponName,
                     Target target, int hitStrength, int range) {
    Weapon weapon = Weapon(weaponName, target, hitStrength);
    Wizard *wizard = new Wizard(playerName, weapon, range);
    this->addPlayerWithDifferentType(wizard, playerName);
}


void
Game::addPlayerWithDifferentType(Player *player, string const &playerName) {
    for (int i = 0; i <= this->last_player_in_the_array; i++) {
        const bool check_if_the_player_exist = this->array_player[i]->isPlayer(
                playerName);
        if (check_if_the_player_exist == true) {
            delete player;
            throw mtm::NameAlreadyExists();
        }
    }
    if (last_player_in_the_array == maxPlayer - 1) {
        delete player;
        throw mtm::GameFull();
    }
    this->last_player_in_the_array += 1;
    this->array_player[last_player_in_the_array] = player;
}