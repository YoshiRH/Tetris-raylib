#include <random>
#include "game.h"

Game::Game(){
    grid = Grid();
    blocks = get_all_blocks();
    current_block = get_random_block();
    next_block = get_random_block();
    game_over = false;
    score = 0;
}

Block Game::get_random_block(){
    if(blocks.empty()){
        blocks = get_all_blocks();
    }

    int random_index = rand() % blocks.size();
    Block block = blocks.at(random_index);
    blocks.erase(blocks.begin()+random_index);

    return block;
}

std::vector<Block> Game::get_all_blocks(){
    return {IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),ZBlock(),TBlock()};
}

void Game::draw(){
    grid.draw();
    current_block.draw(11,11);
    
    switch (next_block.id)
    {
    case 3:
        next_block.draw(255,290);
        break;
    case 4:
        next_block.draw(255,280);
        break;
    
    default:
        next_block.draw(270,270);
    }
}

void Game::handle_input(){
    int key_pressed = GetKeyPressed();

    if(game_over && key_pressed !=0){
        game_over = false;
        reset();
    }

    switch (key_pressed){
    case KEY_LEFT:
        move_block_left();
        break;
    case KEY_RIGHT:
        move_block_right();
        break;
    case KEY_DOWN:
        move_block_down();
        update_score(0,1);
        break;
    case KEY_UP:
        rotate_block();
        break;
    
    default:
        break;
    }
}

void Game::move_block_left(){
    if(!game_over){

        current_block.move(0,-1);
        if(is_block_outside() || block_fits() == false){
            current_block.move(0,1);
        }

    }
}
void Game::move_block_right(){
    if(!game_over){

        current_block.move(0,1);
        if(is_block_outside() || block_fits() == false){
            current_block.move(0,-1);
        }

    }
}
void Game::move_block_down(){
    if(!game_over){

        current_block.move(1,0);
        if(is_block_outside() || block_fits()==false){
            current_block.move(-1,0);
            lock_block();
        }
        
    }
}

bool Game::is_block_outside(){
    std::vector<Position> tiles = current_block.get_cell_positions();
    for(Position item:tiles){
        if(grid.is_cell_outside(item.row,item.column)){
            return true;
        }
    }
    return false;
}

void Game::rotate_block(){
    if(!game_over){

        current_block.rotate();
        if(is_block_outside()){
            current_block.undo_rotation();
        }

    }
}

void Game::lock_block(){
    std::vector<Position> tiles = current_block.get_cell_positions();
    for(Position item:tiles){
        grid.grid[item.row][item.column] = current_block.id;
    }
    current_block = next_block;

    if(block_fits() == false){
        game_over = true;
    }

    next_block = get_random_block();
    int rows_cleared = grid.clear_full_rows();
    update_score(rows_cleared,0);
}

bool Game::block_fits(){
    std::vector<Position> tiles = current_block.get_cell_positions();

    for(Position item:tiles){
        if(grid.is_cell_empty(item.row,item.column) == false){
            return false;
        }
    }
    return true;
}

void Game::reset(){
    grid.initialize();
    blocks = get_all_blocks();
    current_block = get_random_block();
    next_block = get_random_block();
    score = 0;
}

void Game::update_score(int lines_cleared, int move_down_points){
    switch (lines_cleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += move_down_points;
}