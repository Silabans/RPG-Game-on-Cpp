#include <char_creation>

int main() {
    std::cout << "=== The Dungeon of dih ===\n\n";
    Player player = createCharacter();

    Item sword = {"Health Potion", 20, "potion"};
    player.addInventory(sword);
    player.displayStats();

    return 0;
}