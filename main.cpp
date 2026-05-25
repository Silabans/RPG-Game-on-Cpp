#include "chamber.h"


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
        Chamber chamber(depth);
        chamber.traverse(player.getPosition()[0], player.getPosition()[1], player);
        depth++;
    }

    if (not player.isAlive()) std::cout << "\nNoob lah...\n";

    return 0;
}