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
        std::cin >> userInput;
    }
    std::cout << "\nNoob lah...\n";

    return 0;
}