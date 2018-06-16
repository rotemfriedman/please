#include "Game.h"
#include "test_utilities.h"


int main() {
 //   Weapon weapon=Weapon("M-16", STRENGTH, 10);
 // Warrior warrior1=Warrior("SHAKED",weapon,true);
    Game game=Game(20);
    game.addWarrior("SHAKED", "M-16", LIFE, 12, true);
    game.addTroll("Avihai","mag",STRENGTH,6,9);
    //game.addWizard()
    return 0;
}
