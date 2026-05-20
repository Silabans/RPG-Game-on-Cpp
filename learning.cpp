#include <iostream>
#include <string>
#include <vector>


// contains the types of classes
enum class CharClass {
    Warrior,
    Mage,
    Rogue
};

// a struct is like class but is public
struct Item {
    std::string name;
    int value; // damage if weapon, heal if potion
    std::string type; // weapon or potion
};

class Player {
// manually set these attributes as private
private:
    std::string name;
    CharClass charClass;
    int hp;
    int maxHp;
    int dmg;
    int defense;
    std::vector<Item> Inventory;

public:
    // Constructor
    Player(std::string playerName, CharClass cls) {
        name = playerName;
        charClass = cls;

        if (cls == CharClass::Warrior) {
            hp = 120; dmg = 10; defense = 10;
        } else if (cls == CharClass::Rogue) {
            hp  = 85; dmg = 20; defense = 5;
        } else {
            hp = 110; dmg = 15; defense = 0;
        }
        maxHp = hp;

    }

    std::string getName() { return name; }
    int getHp() { return hp; }
    int getDamage() { return dmg; }
    int getDefense() { return defense; }

    void takeDamage(int dmg) {
        int actual = dmg - defense * 0.1;
        
        
    }

}




int main() {
    std::cout << "Game Start\n\n";
    return 0;
};