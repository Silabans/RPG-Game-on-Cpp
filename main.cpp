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
        combat(player, spawnEnemy(depth));
        depth += 1;
        std::cout << "\n\nBattle won! Key in anything to proceed: ";
        std::cin >> userInput;
    }
    std::cout << 'You lost! Noob lah...';

    return 0;
}