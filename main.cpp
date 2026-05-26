#include "chamber.h"


int main() {
    std::cout << "=== The Dungeon of Madness ===\n\n";
    Player player = createCharacter();

    Item hpotion = {"Health Potion", 20, "potion"};
    player.addInventory(hpotion);
    player.displayStats();

    std::cout << "\n\nEnter anyting to start...";
    std::string userInput;
    std::cin >> userInput;
    int depth = 1;

    while (player.isAlive() && depth <= 5) {
        Chamber chamber(depth);
        chamber.placePlayer(player);
        chamber.traverse(player);
        depth++;
    }

    if (!player.isAlive()) std::cout << "\nNoob lah...\n" << "Depth reached: " << depth - 1;
    else std::cout << "Congratz! You won...ig";

    return 0;
}