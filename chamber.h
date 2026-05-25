#pragma once
#include "combat.h"
#include <stdexcept> // For std::out_of_rannge
#include <algorithm>

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
    Grid masterGrid;
    Grid displayGrid;
    int rows;
    int cols;
    int currentDepth;

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
        int enemies = (rows * cols) / 4;
        int potions = randomInt(0, (rows * cols) / 6);

        masterGrid.set(0, randomInt(0, cols - 1), 'P'); // entrance
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
        displayGrid.set(r, c, masterGrid.get(r, c));
    }

    void display() { displayGrid.display(); }

    void update(int r, int c, char symbol) {
        masterGrid.set(r, c, symbol); displayGrid.set(r, c, symbol);
    }

    void traverse(int r, int c, Player& player) {
        while (masterGrid.get(player.getPosition()) {
            std::string move;
            std::cin >> move;

            if (masterGrid.get(r, c) == '!') { 
                Enemy enemy = spawnEnemy(currentDepth);
                combat(player, enemy);
            }

            if (move == "right") { player.updatePosition(0, 1); }
            else if (move == "left") { player.updatePosition(0, -1); }
            else if (move == "up") { player.updatePosition(1, 0); }
            else if (move == "down") { player.updatePosition(-1, 0); }
        }
        
    }


};
