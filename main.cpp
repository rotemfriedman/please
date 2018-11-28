//
// Created by ron on 28/05/18.
//

#include <sstream>
#include <cstring>
#include <string>

#include "Weapon.h"
#include "Player.h"
#include "Game.h"
#include "test_utilities.h"
#include "mtm_exceptions.h"
//#include "Warrior.h"
//#include "Wizard.h"
//#include "Troll.h"

using std::cout;
using std::endl;
using std::string;
using mtm::IllegalWeapon;
using mtm::InvalidParam;
using mtm::NameAlreadyExists;
using mtm::GameFull;
using mtm::NameDoesNotExist;

bool weaponTest() {
    Weapon w1("Lazer Gun", LIFE, 5);
    Weapon w2("Assault Riglt", STRENGTH, 10);
    Weapon w3("Plastic Hammer", LEVEL, 1);

    ASSERT_TEST(w1.getTarget() == LIFE);
    ASSERT_TEST(w2.getTarget() == STRENGTH);
    ASSERT_TEST(w3.getTarget() == LEVEL);

    ASSERT_TEST(w1.getHitStrength() == 5);
    ASSERT_TEST(w2.getHitStrength() == 10);
    ASSERT_TEST(w3.getHitStrength() == 1);

    ASSERT_TEST(w1.getValue() == 3*5);
    ASSERT_TEST(w2.getValue() == 2*10);
    ASSERT_TEST(w3.getValue() == 1*1);

    ASSERT_TEST(w1 != w2);
    ASSERT_TEST(w2 != w3);
    ASSERT_TEST(w1 != w3);

    ASSERT_TEST(w1 < w2);
    ASSERT_TEST(w2 > w1);

    Weapon w4("Different Lazer Gun", LIFE, 5);
    ASSERT_TEST(w1 == w4);

    Weapon w5("Strong Plastic Hammer", LEVEL, 15);
    ASSERT_TEST(w1 == w5);

    Weapon w6(w1);
    ASSERT_TEST(w6 == w1);

    Weapon w7 = w1 = w1;
    ASSERT_TEST(w7 == w1);

    return true;
}

bool warriorTest() {
    Weapon sword = Weapon("Sword", LIFE, 3);
    Weapon weak_sword = Weapon("Weak Sword", LIFE, 1);
    Warrior w1 = Warrior("Jerry", sword, false);
    Warrior w2 = Warrior("George", sword, true);
    ASSERT_TEST(w1.isAlive());
    ASSERT_TEST(!w1.fight(w2));
    w2 = Warrior("George", weak_sword, true);
    ASSERT_TEST((w1.fight(w2)));
    ASSERT_TEST(!w2.isAlive());
    w2 = Warrior("George", weak_sword, true);
    w2.makeStep();
    ASSERT_TEST(!w1.fight(w2));
    ASSERT_TEST(!w2.fight(w1));
    for (int i = 0; i < 4; ++i) {
        w1.makeStep();
        ASSERT_TEST(!w1.fight(w2));
        ASSERT_TEST(!w2.fight(w1));
    }
    w1.makeStep();

    Weapon level_gun = Weapon("Level Gun", LEVEL, 5);
    ASSERT_THROW(Warrior w3 = Warrior("Kramer", level_gun, false);, IllegalWeapon);

    return true;
}

bool wizardTest() {
    Weapon sword = Weapon("Sword", LIFE, 3);
    Weapon staff = Weapon("Staff", LEVEL, 5);
    Weapon wand = Weapon("Wand", LEVEL, 3);

    ASSERT_THROW(Wizard w1 = Wizard("Jerry", sword, 5);, IllegalWeapon);

    Wizard w1 = Wizard("Jerry", staff, 5);
    Wizard w2 = Wizard("George", wand, 3);
    ASSERT_TEST(!w2.fight(w1));
    ASSERT_TEST(w1.isAlive());
    ASSERT_TEST(w2.isAlive());
    ASSERT_TEST(!w1.fight(w2));
    ASSERT_TEST(w1.isAlive());
    ASSERT_TEST(w2.isAlive());

    w2 = Wizard("George", wand, 10);
    for (int i = 0; i < 10; ++i) {
        w2.makeStep();
    }
    ASSERT_TEST(!w2.fight(w1));
    ASSERT_TEST(!w1.fight(w2));

    w1 = Wizard("Jerry", staff, 20);
    ASSERT_TEST(w2.fight(w1));

    ASSERT_TEST(!w2.isAlive());
    ASSERT_TEST(w1.isAlive());

    w1 = Wizard("Jerry", wand, 20);
    w2 = Wizard("George", staff, 10);
    for (int i = 0; i < 15; ++i) {
        w2.makeStep();
    }
    ASSERT_TEST(!w2.fight(w1));
    ASSERT_TEST(!w1.fight(w2));
    for (int i = 0; i < 5; ++i) {
        w1.makeStep();
    }
    ASSERT_TEST(w2.fight(w1));
    ASSERT_TEST(w1.fight(w2));


    return true;
}

bool trollTest() {
    Weapon club = Weapon("Club", STRENGTH, 6);
    Weapon sword = Weapon("Sword", LIFE, 3);
    Weapon staff = Weapon("Staff", LEVEL, 5);

    Troll t1 = Troll("Danny Devito", sword, 5);
    t1 = Troll("Danny Devito", staff, 5);
    t1 = Troll("Danny Devito", sword, 5);
    Troll t2 = Troll("Ron Kantorovich", staff, 5);
    for (int i = 0; i < 30; ++i) {
        t1.makeStep();
        t2.makeStep();
    }

    ASSERT_TEST(t1.fight(t2));
    ASSERT_TEST(t1.isAlive());
    ASSERT_TEST(t2.isAlive());
    ASSERT_TEST(t1.fight(t2));
    ASSERT_TEST(t1.isAlive());
    ASSERT_TEST(!t2.isAlive());

    return true;
}

bool gameTest() {
    Game g1(4);
    ASSERT_TEST(g1.addPlayer("Jerry", "Sword", LIFE, 6) == SUCCESS);
    ASSERT_TEST(g1.addPlayer("Jerry", "not Sword", STRENGTH, 3) == NAME_ALREADY_EXISTS);
    ASSERT_TEST(g1.addPlayer("George", "Sword", LIFE, 1) == SUCCESS);
    ASSERT_TEST(g1.addPlayer("Elaine", "Sword", LIFE, 6) == SUCCESS);
    ASSERT_TEST(g1.addPlayer("Kramer", "Sword", LIFE, 6) == SUCCESS);
    ASSERT_TEST(g1.addPlayer("Newman", "Sword", LIFE, 3) == GAME_FULL);
    ASSERT_TEST(g1.addPlayer("warrior", "level weapon", LEVEL, 4) == GAME_FULL);
    ASSERT_TEST(g1.removeAllPlayersWithWeakWeapon(5) == true);
    ASSERT_TEST(g1.addPlayer("Newman", "Sword", LIFE, 3) == SUCCESS);
    ASSERT_TEST(g1.addPlayer("Newman", "Sword", LIFE, 3) == NAME_ALREADY_EXISTS);
    ASSERT_TEST(g1.addPlayer("George", "Sword", LIFE, 3) == GAME_FULL);
    Game g2(4);
    ASSERT_TEST(g2.addPlayer("warrior", "level weapon", LEVEL, 4) == ILLEGAL_WEAPON);

    Game g3(3);
    g3.addWarrior("Jerry", "Sword", LIFE, 3, true);
    g3.addWizard("George", "Staff", LEVEL, 4, 3);
    g3.addTroll("Kramer", "Club", STRENGTH, 3, 5);
    ASSERT_THROW(g3.addWarrior("Jerry", "Sword", STRENGTH, 5, false);, mtm::NameAlreadyExists);
    ASSERT_THROW(g3.addWarrior("Elaine", "Sword", STRENGTH, 5, false);, mtm::GameFull);

    Game g4(100);
    g4.addWarrior("Jerry", "Sword", LIFE, 3, true);
    g4.addWizard("George", "Staff", LEVEL, 4, 3);
    g4.addTroll("Kramer", "Club", STRENGTH, 3, 5);
    ASSERT_THROW(g4.addWarrior("Jerry", "Sword", STRENGTH, 5, false);, mtm::NameAlreadyExists);
    ASSERT_THROW(g4.addWarrior("Elaine", "Sword", LEVEL, 5, false);, mtm::IllegalWeapon);
    ASSERT_THROW(g4.addTroll("Elaine", "Sword", LEVEL, 4, -5);, mtm::InvalidParam);
    ASSERT_THROW(g4.addWizard("Elaine", "Sword", LEVEL, 4, -3);, mtm::InvalidParam);

    Game g5(4);
    g5.addWizard("George", "Staff", LEVEL, 5, 1);
    g5.addWarrior("Jerry", "Sword", LIFE, 3, true);
    g5.addTroll("Kramer", "Sword", LIFE, 3, 4);
    g5.makeStep("George");
    ASSERT_TEST(g5.makeStep("I dont exist") == NAME_DOES_NOT_EXIST);
    ASSERT_TEST(g5.fight("Jerry", "George") == FIGHT_FAILED);
    g5.addWizard("Elaine", "Staff", STRENGTH, 5, 10);
    for (int i = 0; i < 11; ++i) {
        g5.makeStep("Elaine");
    }
    ASSERT_TEST(g5.fight("Kramer", "Elaine") == FIGHT_FAILED);
    ASSERT_THROW(g5.addWarrior("Kramer", "Sword", STRENGTH, 5, false);, mtm::NameAlreadyExists);
    ASSERT_THROW(g5.addWarrior("Newman", "Sword", LIFE, 5, false);, mtm::GameFull);
    g5.makeStep("Kramer");
    ASSERT_TEST(g5.fight("Kramer", "Elaine") == SUCCESS);
    ASSERT_TEST(g5.makeStep("Kramer") == NAME_DOES_NOT_EXIST);
    g5.addWarrior("Newman", "Sword", LIFE, 5, false);
    for (int i = 0; i < 5; ++i) {
        g5.makeStep("Elaine");
    }
    ASSERT_TEST(g5.fight("Elaine", "Jerry") == FIGHT_FAILED);
    g5.makeStep("Jerry");
    ASSERT_TEST(g5.fight("Elaine", "Jerry") == FIGHT_FAILED);
    g5.makeStep("Jerry");
    ASSERT_TEST(g5.fight("Elaine", "Jerry") == SUCCESS);
    ASSERT_TEST(g5.makeStep("Jerry") == NAME_DOES_NOT_EXIST);

    return true;
}

bool isJerry(const Player& player) {
    return player.isPlayer("Jerry");
}

bool isNotJerry(const Player& player) {
    return !isJerry(player);
}

bool fcnTest() {
    Game g1(4);
    g1.addWarrior("Jerry", "sword", LIFE, 5, false);
    g1.addWarrior("Elaine", "sword", STRENGTH, 5, false);
    g1.addWizard("George", "axe", LEVEL, 5, 10);
    g1.addTroll("Kramer", "polearm", STRENGTH, 5, 10);
    ASSERT_THROW(g1.addWarrior("Newman", "sword", LIFE, 5, false);, mtm::GameFull);
    g1.removePlayersIf(isJerry);
    ASSERT_THROW(g1.fight("Jerry", "Elaine");, mtm::NameDoesNotExist);
    g1.addWarrior("Jerry", "sword", LIFE, 5, false);
    ASSERT_THROW(g1.addWarrior("Newman", "sword", LIFE, 5, false);, mtm::GameFull);
    g1.removePlayersIf(isNotJerry);
    ASSERT_THROW(g1.addWarrior("Jerry", "sword", LIFE, 5, false);, mtm::NameAlreadyExists);
    g1.addWarrior("Elaine", "sword", STRENGTH, 5, false);
    g1.addWarrior("George", "axe", LIFE, 5, false);
    g1.addWarrior("Kramer", "polearm", STRENGTH, 5, false);
    ASSERT_THROW(g1.addWarrior("Newman", "sword", LIFE, 5, false);, mtm::GameFull);

    return true;
}

int main() {

    RUN_TEST(weaponTest);
    RUN_TEST(gameTest);
    RUN_TEST(fcnTest);

    RUN_TEST(warriorTest);
    RUN_TEST(wizardTest);
    RUN_TEST(trollTest);

}