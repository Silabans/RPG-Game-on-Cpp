#pragma once
#include "combat.h"
#include <stdexcept> // For std::out_of_rannge


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

    void checkRange(int r, int c) {
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

    void display() {
        std::cout << "\n";
        std::cout << "  ";
        for (int x = 0; x < columns; x++) {
            std::cout << x << ' ';
        }
        for (int i = 0; i < rows; i++) {
            std::cout << '\n';
            std::cout << i << " ";
            for (int j = 0; j < columns; j++) {
                std::cout << get(i, j) << ' ';
            }
        }
        std::cout << "\nSelect your next move (right, left, up, down): ";
    }
};

void traverse(Grid masterGrid, int r, int c) {
    std::string move;
    if (masterGrid.get(r, c)) == '!' { 
        spawnEnemy()
     };

    std::cin >> move
    if (move == "right") {}
}

