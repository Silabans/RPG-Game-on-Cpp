#pragma once
#include "combat.h"
#include <stdexcept> // For std::out_of_rannge
#include <algorithm>
#include <limits>

// The idea is that there will 2 grids - one for diplaying to the player (there will be hidden 
// elements that need to be discovered to be seen) and one for keeping the actual values of each position
class Grid {
private:
    int rows;
    int columns;
    std::vector<char> grid;

    // converts row and column values into the index position of the cell
    int position(int r, int c) const {
        return r * columns + c;
    }

    void checkRange (int r, int c) const {
        if (r < 0 || r >= rows || c < 0 || c >= columns)
            throw std::out_of_range("Coordinates are out of bounds.");
    }

public:
    Grid(int r, int c, char fill = '~') : rows(r), columns(c), grid(r * c, fill) {}

    char get(int r, int c) const {
        checkRange(r, c);
        return grid[position(r, c)];
    }

    void set(int r, int c, char newChar) {
        checkRange(r, c);
        grid[position(r, c)] = newChar;
    }

    int getRow() const { return rows; }
    int getColumn() const { return columns; }

    void display() {
        std::cout << '\n';
        std::cout << "  ";
        for (int x = 0; x < columns; x++) {
            std::cout << x << ' ';
        }
        for (int i = 0; i < rows; i++) {
            std::cout << '\n';
            std::cout << i << ' ';
            for (int j = 0; j < columns; j++) {
                std::cout << get(i, j) << ' ';
            }
        }
        std::cout << "\nSelect your next move (right, left, up, down): ";
    }
};


class Chamber {
private:
    int rows;
    int cols;
    int currentDepth;
    int playerStartC;
    Grid masterGrid;
    Grid displayGrid;

    static int calcRows(int depth) { return randomInt(2 + depth / 2, 3 + depth); } // minimum value rises every 2 chambers
    static int calcCols(int depth) { return randomInt(2 + depth / 2, 3 + depth); }

    void placeRandom(char symbol) {
        int r, c;
        do {
            r = randomInt(0, rows - 1);
            c = randomInt(0, cols - 1);
        } while (masterGrid.get(r, c) != '.');

        masterGrid.set(r, c, symbol);
    }

    void generate(int depth) {
        playerStartC = randomInt(0, cols - 1);


        int enemies = (rows * cols) / 4;
        int potions = randomInt(0, (rows * cols) / 6);

        masterGrid.set(0, playerStartC, 'P'); // entrance
        masterGrid.set(rows - 1, randomInt(0, cols - 1), 'O'); // exit

        for (int i = 0; i < enemies; i++) {
            placeRandom('!');
        }

        for (int i = 0; i < potions; i++) {
            placeRandom('?');
        }
    }

public:
    Chamber(int depth)
        : rows(calcRows(depth)), 
          cols(calcCols(depth)),
          currentDepth(depth),
          masterGrid(rows, cols, '.'), 
          displayGrid(rows, cols, '~')
    {
        generate(depth);
    }

    void reveal(int r, int c) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            displayGrid.set(r, c, masterGrid.get(r, c));
        }
    }

    void display() { displayGrid.display(); }

    void update(int r, int c, char symbol) {
        masterGrid.set(r, c, symbol); displayGrid.set(r, c, symbol);
    }

    void traverse(Player& player) {
        int startR = player.getPosition()[0];
        int startC = player.getPosition()[1];

        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++)
                reveal(startR + dr, startC + dc);
        
        displayGrid.display();

        while (player.isAlive()) {
            int r_coor = player.getPosition()[0];
            int c_coor = player.getPosition()[1];

            std::string move;
            std::cin >> move;

            // if std::std fails due a stream corruption (due to accidental closure of the 
            // standard input stream) or the end of file is reached for some reason.
            if (!(std::cin >> move)) {
                std::cin.clear(); // Clear the error flags
                std::string dummy;
                std::getline(std::cin, dummy); // Flush out the remaining broken buffer
                std::cout << "Input stream error! Retrying...\n";
                continue;
            }
            
            int nr = r_coor, nc = c_coor;
            if (move == "d") { nc += 1; }
            else if (move == "a") { nc -= 1; }
            else if (move == "w") { nr -= 1; }
            else if (move == "s") { nr += 1; }
            else { 
                std::cout << "Invalid move\n"; 
                // Clear any leftover characters on the line so they don't trigger the loop again
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue; 
            }

            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                std::cout << "You can't go that way!\n";
            }
            else {
                player.updatePosition(nr - r_coor, nc - c_coor);
            
                char cell = masterGrid.get(nr, nc);

                if (cell == '!') { 
                    Enemy enemy = spawnEnemy(currentDepth);
                    combat(player, enemy);
                }
                else if (cell == '?') { 
                    Item hpotion = {"health potion", randomInt(15, 25), "potion"};
                    player.addInventory(hpotion);
                }
                else if (cell == 'O') { break; }

                if (player.isAlive() && cell != 'O') {
                    masterGrid.set(r_coor, c_coor, '.');
                    masterGrid.set(nr, nc, 'P');
                }

                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++)
                        reveal(nr + dr, nc + dc);
                displayGrid.display();
            }
        }
        if (player.isAlive()) {
            std::string placeholder;
            std::cout << "\n\nYou found this chamber's exit! Key in anything to proceed...";
            std::cin >> placeholder;
            std::cout << '\n';
        }

    }

    // repositions the player to the first row after entering a new chamber
    void placePlayer(Player& player) {
        const std::vector<int>& pos = player.getPosition();
        player.updatePosition(-pos[0], playerStartC - pos[1] );
    }

};
