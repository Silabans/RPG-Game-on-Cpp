#include "combat.h"


int main() {
    std::cout << "=== The Dungeon of dih ===\n\n";
    Player player = createCharacter();
    std::string userInput;

    Item hpotion = {"Health Potion", 20, "potion"};
    player.addInventory(hpotion);
    player.displayStats();

    std::cout << "\n\nEnter anyting to start...";
    std::cin >> userInput;
    int depth = 1;

    while (player.isAlive()) {
        combat(player, spawnEnemy(depth)); depth++;
        std::cout << "\n\nBattle won! Key in anything to proceed to the next chamber: ";
        std::cin >> userInput;
    }
    std::cout << "\n\nYou lost! Noob lah...\n";

    return 0;
}