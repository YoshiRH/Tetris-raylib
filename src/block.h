#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block{
    private:
        int row_offset;
        int column_offset;
        int cell_size;
        int rotation_state;
        std::vector<Color> colors;

    public:
        Block();
        void draw(int x, int y);
        void move(int rows, int columns);
        std::vector<Position> get_cell_positions();
        int id;
        std::map<int,std::vector<Position>> cells;
        void rotate();
        void undo_rotation();
};