#include"raylib.h"
#include"raymath.h"
#include <iostream>
#include<vector>
#include "Game.h"
using namespace std;

const int windowWidth = 800;
const int windowHeight = 800;

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(windowWidth, windowHeight, "test");
    InitAudioDevice();
    SetTargetFPS(60);
    Game game;
    Vector2 origin = { 0,0 };
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.back_music);
      
        ClearBackground(BLACK);
        BeginDrawing();
        game.update();
        game.handleInput();
        
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}