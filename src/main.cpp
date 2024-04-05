#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double last_update_time {0};

bool event_triggered(double interval){
    double current_time = GetTime();
    if(current_time - last_update_time >= interval){
        last_update_time = current_time;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500,620,"Tetris - reylib");
    SetTargetFPS(60);

    Game game{};

    Font font = LoadFontEx("font/monogram.ttf",64,0,0);

    while(!WindowShouldClose())
    {
        game.handle_input();
        
        if(event_triggered(0.2)){
            game.move_block_down();
        }

        BeginDrawing();
        ClearBackground(dark_blue);
        
        DrawTextEx(font,"Score",{360,15},38,2,WHITE);
        DrawRectangleRounded({320,55,170,60}, 0.3,6,light_blue);
        
        char score_text[10];
        sprintf(score_text, "%d", game.score);
        Vector2 text_size = MeasureTextEx(font,score_text,38,2);


        DrawTextEx(font,score_text,{320 + (170-text_size.x)/2,65},38,2,WHITE);
        DrawTextEx(font,"Next",{370,175},38,2,WHITE);
        DrawRectangleRounded({320,215,170,180}, 0.3,6,light_blue);

        if(game.game_over){
            DrawTextEx(font,"GAME OVER",{320,450},38,2,WHITE);
        }
        
        game.draw();

        EndDrawing();
    }

    CloseWindow();
}