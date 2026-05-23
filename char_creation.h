#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


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
    bool blocking = false;
    int block_value = 2;
    std::vector<Item> inventory;

public:
    // Constructor
    Player(const std::string playerName, const CharClass cls) {
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

    } // constructor & methods inside the class need no semicolons

    std::string getName() const { return name; }
    int getHp() const { return hp; }
    int getDamage() const { return dmg; }
    int getDefense() const { return defense; }
    void getInventory() {
        for (int i = 0; i < inventory.size(); i++) {
            std::cout << i + 1 << ". " << inventory[i].name << '\n';
        }
    }

    void takeDamage(int incomingDmg) {
        int actual = incomingDmg - static_cast<int>(defense * 0.1);
        if (actual < 1) actual = 1;
        hp -= actual;
        if (hp < 0) hp = 0;
    }

    int getBlock() { return block_value; }
    void setBlock(bool boolean) { blocking = boolean; }
    bool isBlocking() { return blocking; }

    void heal(int value) {
        hp += value;
        if (hp > maxHp) hp = maxHp; // hp will not exceed the max hp of the character
    }

    void addInventory(Item item) { 
        inventory.push_back(item);
        std::cout << item.name << " added to inventory!\n"; 
    }

    bool usePotion() {
        auto it =  std::find_if(inventory.begin(), inventory.end(), [](Item& item) {
            return item.type == "potion";
        });

        if (it != inventory.end()) {
            heal(it->value);
            std::cout << "You used a " << it->name << "! Recovered " << it->value << " HP\n";
            inventory.erase(it);
            return true;
        }
        std::cout << "No potions found in your inventory...\n";
        return false;

    }

    bool isAlive() const { return hp > 0; }

    void displayStats() {
        std::string className;
        if (charClass == CharClass::Warrior) className = "Warrior";
        else if (charClass == CharClass::Rogue ) className = "Rogue";
        else className = "Mage";

        std::cout << "\n=== " << name << " the " << className << " ===\n";
        std::cout << "Health: " << hp << '\n';
        std::cout << "Damage: " << dmg << '\n';
        std::cout << "Defense: " << defense << '\n';
        std::cout << "Item: " << inventory.size() << '\n';
        }

}; // class definitions must end with a semicolon

Player createCharacter() {
    std::string playerName;
    int classChoice;
    std::cout << "Enter your name: ";
    std::cin >> playerName;
    std::cout << "\nChoose one of the following classes:\n";
    std::cout << "1. Warrior\n" << "2. Rogue\n" << "3. Mage\n";
    std::cout << "Choice: ";
    std::cin >> classChoice;


    CharClass cls;
    if (classChoice == 1) cls = CharClass::Warrior;
    else if (classChoice == 2) cls = CharClass::Rogue;
    else cls = CharClass::Mage;

    Player player(playerName, cls);
    std::cout << "Welcome, " << playerName << "!\n";
    player.displayStats();
    return player;
}


