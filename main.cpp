#include "Game.h"
#include "test_utilities.h"
#include "mtm_exceptions.h"

using std::cout;

int main() {
 //   Weapon weapon=Weapon("M-16", STRENGTH, 10);
 // Warrior warrior1=Warrior("SHAKED",weapon,true);
    Game game=Game(20);
    game.addWarrior("SHAKED", "M-16", LEVEL, 12, true);//error

    game.addWarrior("SHAKED", "M-16", LIFE, 12, true);
    game.makeStep("SHAKED");
    game.addTroll("Avihai","mag",STRENGTH,6,-4);//error
    game.addTroll("Avihai","mag",STRENGTH,6,1);

       game.addWizard("shoshana", "glok", LIFE, 12, 10);//error
        game.addWizard("shoshana", "glok", STRENGTH, 12, 1);
    GameStatus status=game.fight("shoshana","Avihai");

    return 0;
}
