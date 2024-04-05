#pragma once
#include <vector>
#include <raylib.h>

class Grid{
private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    void clear_row(int row);
    void move_row_down(int row, int num_rows);

public:
    int grid[20][10];
    Grid();
    void initialize();
    void print();
    void draw();
    bool is_cell_outside(int rom,int column);
    bool is_cell_empty(int row,int column);
    bool is_row_full(int row);
    int clear_full_rows();
};