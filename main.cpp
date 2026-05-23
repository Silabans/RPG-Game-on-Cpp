#include "combat.h"


int main() {
    std::cout << "=== The Dungeon of dih ===\n\n";
    Player player = createCharacter();

    Item hpotion = {"Health Potion", 20, "potion"};
    player.addInventory(hpotion);
    player.displayStats();

    return 0;
}