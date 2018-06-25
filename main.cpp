#include <cassert>
#include <sstream>
#include "Game.h"

using namespace std;
using namespace mtm;

void test1() {
    std::ostringstream stream; //saves the output

    // Part 1

    int catches = 0;
    Game g(4);
    // player
    try {
        assert(g.addPlayer("p2", "ak47", LIFE, 2) == SUCCESS);
        assert(g.addPlayer("p2", "ak47", LIFE, 2) == NAME_ALREADY_EXISTS);
        assert(g.addPlayer("p1", "ak47", LEVEL, 2) == ILLEGAL_WEAPON);
    } catch (...) {
        cout << endl << "error 01! :o" << endl;
        return;
    }


    // warrior
    try {
        g.addWarrior("p1", "grenade", LEVEL, 3, true);
    } catch (IllegalWeapon &e) {
        ++catches;
    }
    assert(catches == 1);
    try {
        g.addWarrior("p2", "grenade", STRENGTH, 3, true);
    } catch (NameAlreadyExists &e) {
        ++catches;
    }
    assert(catches == 2);
    try {
        g.addWarrior("p1", "grenade", STRENGTH, 3, true);
    } catch (...) {
        cout << endl << "error 02! :o" << endl;
        return;
    }


    // wizard
    try {
        g.addWizard("p4", "arrow", LIFE, 1, 2);
    } catch (IllegalWeapon &e) {
        ++catches;
    }
    assert(catches == 3);
    try {
        g.addWizard("p2", "arrow", LEVEL, 1, 2);
    } catch (NameAlreadyExists &e) {
        ++catches;
    }
    assert(catches == 4);
    try {
        g.addWizard("p4", "arrow", LEVEL, 1, -1);
    } catch (InvalidParam &e) {
        ++catches;
    }
    assert(catches == 5);
    try {
        g.addWizard("p4", "arrow", LEVEL, 1, 2);
    } catch (...) {
        cout << endl << "error 03! :o" << endl;
        return;
    }


    // troll
    try {
        g.addTroll("p2", "butterfly", LEVEL, 1, 2);
    } catch (NameAlreadyExists &e) {
        ++catches;
    }
    assert(catches == 6);
    try {
        g.addTroll("p3", "butterfly", LEVEL, 1, 0);
    } catch (InvalidParam &e) {
        ++catches;
    }
    assert(catches == 7);
    try {
        g.addTroll("p3", "f16", LEVEL, 1, 2);
    } catch (...) {
        cout << endl << "error 04! :o" << endl;
        return;
    }


    // game is full
    assert(g.addPlayer("p5", "sword", STRENGTH, 1) == GAME_FULL);
    try {
        g.addTroll("p5", "sword", STRENGTH, 1, 1);
    } catch (GameFull &e) {
        ++catches;
    }
    assert(catches == 8);
    try {
        g.addWarrior("p5", "sword", STRENGTH, 1, false);
    } catch (GameFull &e) {
        ++catches;
    }
    assert(catches == 9);
    try {
        g.addWizard("p5", "sword", STRENGTH, 1, 1);
    } catch (GameFull &e) {
        ++catches;
    }
    assert(catches == 10);


    // other: NameDoesNotExist
    try {
        assert(g.makeStep("p5") == NAME_DOES_NOT_EXIST);
        assert(g.addLife("p5") == NAME_DOES_NOT_EXIST);
        assert(g.nextLevel("p5") == NAME_DOES_NOT_EXIST);
        assert(g.addStrength("p5", 1) == NAME_DOES_NOT_EXIST);
    } catch (...) {
        cout << endl << "error 04! :o" << endl;
        return;
    }
  //  try {
  //      g.fight("p1", "p5");
  //  } catch (NameDoesNotExist &e) {
  //      ++catches;
  //  }
  //  assert(catches == 11);
   // try {
   //     g.fight("p5", "p1");
   // } catch (NameDoesNotExist &e) {
   //     ++catches;
   // }
   // assert(catches == 11);


    // fight
    try {
        assert(g.fight("p4", "p3") == FIGHT_FAILED); // both has same value
        assert(g.fight("p1", "p2") == FIGHT_FAILED); // both has same value

        // print current
        stream << endl << g; // lines 1-4:

        assert(g.makeStep("p4") == SUCCESS);
        assert(g.makeStep("p4") == SUCCESS);
        assert(g.makeStep("p4") == SUCCESS);
        assert(g.fight("p4", "p3") == FIGHT_FAILED);
        assert(g.makeStep("p3") == SUCCESS);
        assert(g.makeStep("p3") == SUCCESS);
        assert(g.fight("p4", "p3") == FIGHT_FAILED);
        assert(g.addStrength("p4", 1) == SUCCESS);
        assert(g.fight("p4", "p3") == FIGHT_FAILED);
        assert(g.fight("p1", "p3") == FIGHT_FAILED);
        assert(g.fight("p2", "p3") == FIGHT_FAILED);
        assert(g.fight("p1", "p4") == FIGHT_FAILED);
        assert(g.addLife("p3") == SUCCESS);
        assert(g.addLife("p3") == SUCCESS);
        assert(g.addLife("p3") == SUCCESS);
        assert(g.addLife("p3") == SUCCESS);
        assert(g.addLife("p3") == SUCCESS);

        assert(g.makeStep("p2") == SUCCESS);
        assert(g.makeStep("p2") == SUCCESS);
        assert(g.makeStep("p2") == SUCCESS);
        assert(g.makeStep("p2") == SUCCESS);
        assert(g.fight("p2", "p3") == SUCCESS);

        // print current: p3 is dead.
        stream << endl << g; // lines 5-8:

        assert(g.addLife("p4") == SUCCESS);
        assert(g.addLife("p4") == SUCCESS);
        assert(g.addLife("p4") == SUCCESS);
        assert(g.fight("p2", "p4") == FIGHT_FAILED);
        // nothing changed

        assert(g.makeStep("p1") == SUCCESS);
        assert(g.addLife("p4") == SUCCESS);
        assert(g.addLife("p4") == SUCCESS);
        assert(g.fight("p1", "p4") == FIGHT_FAILED);
        // nothing changed

        assert(g.makeStep("p4") == SUCCESS);
        assert(g.makeStep("p4") == SUCCESS);
        assert(g.addLife("p4") == SUCCESS);
        assert(g.fight("p4", "p1") == SUCCESS);
        // print current: p4 died.
        stream << endl << g; // lines 10-11:

    } catch (...) {
        cout << endl << "error 05! :o  " <<endl;
        return;
    }


    // Part 2:

    try {
        Game h(8);
        assert(h.addPlayer("e", "-", STRENGTH, 1) == SUCCESS);
        assert(h.addPlayer("a", "-", STRENGTH, 1) == SUCCESS);
        assert(h.addPlayer("r", "-", STRENGTH, 1) == SUCCESS);
        assert(h.addPlayer("c", "-", STRENGTH, 1) == SUCCESS);
        assert(h.addPlayer("u", "-", STRENGTH, 1) == SUCCESS);
        assert(h.addPlayer("k", "-", STRENGTH, 1) == SUCCESS);
        assert(h.addPlayer("f", "-", STRENGTH, 1) == SUCCESS);
        assert(h.addPlayer("g", "-", STRENGTH, 1) == SUCCESS);

        class Name {
            Warrior player;
        public:
            explicit Name(string const &name) : player(name, Weapon("atam", STRENGTH, 1), 0) {}

            bool operator()(Player const &player) const {
                return (player < this->player);
            }
        };

        Name d("d");
        h.removePlayersIf(d);
        stream << endl << h; // lines 13-18

        Name i("i");
        h.removePlayersIf(i);
        stream << endl << h; // lines 20-22
        Name j("j");
        h.removePlayersIf(j);
        stream << endl << h; // lines 24-27


        Name z("z");
        h.removePlayersIf(z);
        stream << endl << h; // line 28
    } catch (...) {
        cout << endl << "error 06! :o" << endl;
        return;
    }

    // final check
    string output = "\n" // lines 1-4:
                    "player 0: {player name: p1, weapon: {weapon name: grenade, weapon value:6}},\n"
                    "player 1: {player name: p2, weapon: {weapon name: ak47, weapon value:6}},\n"
                    "player 2: {player name: p3, weapon: {weapon name: f16, weapon value:1}},\n"
                    "player 3: {player name: p4, weapon: {weapon name: arrow, weapon value:1}},\n"
                    "\n" // lines 5-8:
                    "player 0: {player name: p1, weapon: {weapon name: grenade, weapon value:6}},\n"
                    "player 1: {player name: p2, weapon: {weapon name: ak47, weapon value:6}},\n"
                    "player 2: {player name: p4, weapon: {weapon name: arrow, weapon value:1}},\n"
                    "\n" // lines 10-11:
                    "player 0: {player name: p1, weapon: {weapon name: grenade, weapon value:6}},\n"
                    "player 1: {player name: p2, weapon: {weapon name: ak47, weapon value:6}},\n"
                    "\n" // lines 13-18:
                    "player 0: {player name: e, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 1: {player name: f, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 2: {player name: g, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 3: {player name: k, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 4: {player name: r, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 5: {player name: u, weapon: {weapon name: -, weapon value:2}},\n"
                    "\n" // lines 20-22:
                    "player 0: {player name: k, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 1: {player name: r, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 2: {player name: u, weapon: {weapon name: -, weapon value:2}},\n"
                    "\n" // lines 24-27:
                    "player 0: {player name: k, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 1: {player name: r, weapon: {weapon name: -, weapon value:2}},\n"
                    "player 2: {player name: u, weapon: {weapon name: -, weapon value:2}},\n\n";

    int index = 0, line = 0;
    for(char& c : stream.str()) {
        if (c == '\n') ++line;
        if (c != output[index++]) {
            cout << "error with line: " << line << ", wrong char: " << c << endl;
            cout << "should have been: " << output[index-1];
            return;
        }
    }
    cout << "okey dokey";
}

int main() {
    test1();
}