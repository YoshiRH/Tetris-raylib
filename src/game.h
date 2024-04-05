#pragma once
#include <vector>
#include "grid.h"
#include "blocks.cpp"


class Game
{
private:
    std::vector<Block> blocks;
    std::vector<Block> get_all_blocks();
    Block get_random_block();
    Block current_block;
    Block next_block;
    Grid grid;
    void rotate_block();
    void lock_block();
    void reset();
    void update_score(int lines_cleared, int move_down_points);
    void move_block_left();
    void move_block_right();
    bool is_block_outside();
    bool block_fits();

public:
    Game();

    int score;
    void draw();
    void handle_input();
    void move_block_down();
    bool game_over;

};
