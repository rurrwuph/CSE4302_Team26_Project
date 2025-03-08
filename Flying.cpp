#include"raylib.h"
#include <iostream>
using namespace std;



class Player
{
private:
    Vector2 _position;
    Vector2 _origin;
    Texture2D _ship;
    double _angle;
    float _width;
    float _height;
    Rectangle _source;
    Rectangle _destination;
    float _scale = 5;
    void calculateAngle()
    {
        _angle= ((atan2f(GetMouseY() - _position.y-_height/2 , GetMouseX() - _position.x - _width / 2)) * 180) / 3.14;
        _angle += 90;
    }
public:

    Player() 
    {
        _angle = 0;
        _position = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
        _ship= LoadTexture("resources/spaceShip/ships/purple.png");
        _width = _ship.width;
        _height = _ship.height;
        _source = { 0, 0, (float)_width, (float)_height };
        _destination = { _position.x, _position.y, _width * _scale, _height * _scale };
        _origin = { (_width * _scale) / 2, (_height * _scale) / 2 };
    }
    void draw()
    {
        DrawTexturePro(_ship, _source, _destination, _origin, _angle, WHITE);       
    }
    void update()
    {
        calculateAngle();
    }
    ~Player()
    {
        UnloadTexture(_ship);
    }

};

class Game {
private:
    Player _player;

public:
    Game()
    {
        init();
    }
    void update() 
    {
        _player.draw();
        _player.update();  
    }

    void init()
    {

    }

    void handleInput()
    {

    }
};


int main()
{
    const int windowWidth = 800;
    const int windowHeight = 800;
    InitWindow(windowWidth, windowHeight, "test");
    SetTargetFPS(60);
    Game game;
    while (!WindowShouldClose()) 
    {
        ClearBackground(BLACK);
        BeginDrawing();

        game.update();

        EndDrawing();
    }

    return 0;
}

