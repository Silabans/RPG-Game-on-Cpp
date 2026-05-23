#pragma once
#include "char_creation.h"

struct Enemy {
    std::string name;
    int hp;
    int maxHp;
    int dmg;
    bool dodge;
}; // an encapsulation of the enemy stats

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1); // returns a random number between the min and max value
}; // rand() returns a huge integer, so the module restricts it to the range


Enemy spawnEnemy(int depth) {
    Enemy enemy;
    if (depth <= 2) {
        enemy.name = "Goblin"; 
        enemy.maxHp = 30 + randomInt(0, 10); enemy.dmg = 4 + randomInt(0, 5);
    }
    else if (depth <= 4) {
        enemy.name = "Ork"; 
        enemy.maxHp = 50 + randomInt(0, 15); enemy.dmg = 10 + randomInt(0, 10);
    }
    else if (depth == 5) {
        enemy.name = "Brian Joseph"; 
        enemy.maxHp = 99999; enemy.dmg = 99999;
    }
    enemy.hp = enemy.maxHp;

    return enemy;
}


void enemyMove(Enemy enemy, Player& player) {
    int move = randomInt(0, 10);
    enemy.dodge = false;

    if (move > 5) { 
        int dmg = enemy.dmg;
        if (player.isBlocking()) {
            dmg /= player.getBlock();
            std::cout << 'The ' << enemy.name << 'harms you but you blocked ' << dmg << ' damage!\n\n';
        }
        else {
            std::cout << 'The enemy strikes you, dealing' << dmg << ' damage!\n\n';
        }
        player.takeDamage(dmg);         
    }
    else { enemy.dodge = true; }

    player.setBlock(false);
}

void combat(Player& player, Enemy enemy) {
    std::cout << '\nA vicious ' << enemy.name << ' has challenged you!\n\n';
    while (player.isAlive() && enemy.hp > 0) {
        int move;
        int roll;
        if (player.isBlocking()) { player.setBlock(false); }
        roll = randomInt(0, 10);
        std::cout << "Choose your move:\n";
        std::cout << "1. Attack\n" << "2. Brace/Defend\n" << "3. Heal\n";
        std::cin >> move;

        if (move == 1) {
            if ((enemy.dodge && roll > 7) || (enemy.dodge == false && roll > 4)) {
                enemy.hp -= player.getDamage();
            }
            else if (enemy.dodge) {
                std::cout << "The enemy dodges you! No damage done...";
            }
            else {
                std::cout<< "Your attack misses! Clumsy boi...";
            }
        }
        else if (move == 2) {
            if (roll > 2) { 
                player.setBlock(true); 
                std::cout << 'You hunker down for defense!'
            }
            else {
                std::cout << "Uh oh...you tripped. Your brace fails!";
            }
        }
        else if (move == 3) {
            player.usePotion();
        }

        enemyMove(enemy, player);
        
    };
};