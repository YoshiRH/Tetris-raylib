#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid()
:numRows{20},numCols{10},cellSize{30}
{
    initialize();
    colors = get_cell_color();
}

void Grid::initialize(){
    for(int row{0}; row<numRows;row++){

        for(int column{0}; column<numCols; column++){
            grid[row][column] = 0;
        }

    }
}

void Grid::print(){
        for(int row{0}; row<numRows;row++){

        for(int column{0}; column<numCols; column++){
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}


void Grid::draw(){
    for(int row{0}; row<numRows;row++){

        for(int column{0}; column<numCols; column++){
            int cell_value = grid[row][column];
            DrawRectangle(column*cellSize+11,row*cellSize+11,cellSize-1,cellSize-1,colors[cell_value]);
        }
        
    }
}

bool Grid::is_cell_outside(int row,int columns){
    if(row >= 0 && row < numRows && columns>=0 && columns < numCols){
        return false;
    }
    return true;
}

bool Grid::is_cell_empty(int row,int column){
    if(grid[row][column]==0){
        return true;
    }
    return false;
}

bool Grid::is_row_full(int row){
    for(int column=0; column < numCols; column++){
        if(grid[row][column] == 0){
            return false;
        }
    }
    return true;
}

void Grid::clear_row(int row){
    for(int column=0; column < numCols; column++){
        grid[row][column] = 0;
    }
}

void Grid::move_row_down(int row,int num_rows){
    for(int column=0; column < numCols; column++){
        grid[row+num_rows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

int Grid::clear_full_rows(){
    int completed {0};

    for(int row = numRows-1; row >=0; row--){
        if(is_row_full(row)){
            clear_row(row);
            completed++;
        }
        else if(completed > 0){
            move_row_down(row,completed);
        }
    }
    return completed;
}


    