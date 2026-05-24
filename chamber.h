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

    int rows() { return rows; }
    int columns() { return columns; }

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

void traverse(Grid masterGrid, int r, int c, Player player, int depth) {
    std::string move;
    if (masterGrid.get(r, c) == '!') { 
        Enemy enemy = spawnEnemy(depth);
        combat(player, enemy);
     }

    std::cin >> move;
    if (move == "right") { player.updatePosition(0, 1);}
    else if (move == "left") { player.updatePosition(0, -1); }
    else if (move == "up") { player.updatePosition(1, 0); }
    else if (move == "down") { player.updatePosition(-1, 0); }
    
}

void createChamber(Grid masterGrid) {
    int enemies = (masterGrid.rows() * masterGrid.columns()) / 4;
    std::vector<int> takenPos;
    masterGrid.set(0, randomInt(0, masterGrid.columns() - 1), 'P');
    masterGrid.set(randomInt(masterGrid.rows() - 1, randomInt(0, masterGrid.columns() - 1)), 'O');

    for (int i = 0; i < enemies + 0; i++) {
        int row = randomInt(0, masterGrid.rows() - 1);
        int column = randomInt(0, masterGrid.columns() - 1);
        //auto it = std::find(takenPos.begin(), takenPos.end(), {row, column});
        //while (it == takenPos.end()) { 
        //    int random = randomInt(0, 1)
        //    if (row == masterGrid.columns() - 1) { row += }
        // }
        if (masterGrid.get(row, column) == 'P') row += 1;
        else if (masterGrid.get(row, column) == 'O') row -= 1;
        //else if

        masterGrid.set(row, column, 'X');
        takenPos.push_back((column * masterGrid.columns()) + row)

    }

}