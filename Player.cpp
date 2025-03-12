#include "Player.h"

void Player:: calculateAngle()
{
    _angle = ((atan2f(GetMouseY() - _position.y - _height / 2, GetMouseX() - _position.x - _width / 2)) * 180) / 3.14;
    _angle += 90;
}

Player :: Player()
{
    _angle = 0;
    _position = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    _ship = LoadTexture("resources/spaceShip/ships/purple.png");
    _width = _ship.width;
    _height = _ship.height;
    _source = { 0, 0, (float)_width, (float)_height };
    _destination = { _position.x, _position.y, _width * _scale, _height * _scale };
    _origin = { (_width * _scale) / 2, (_height * _scale) / 2 };
    health = 100;
}

void Player::  draw()
{
    DrawTexturePro(_ship, _source, _destination, _origin, _angle, WHITE);
}

void Player:: update()
{
    calculateAngle();
}

double Player:: getAngle()
{
    return _angle;
}
float Player::getHealth()
{
    return health;
}
void Player::takeDamage(float damage)
{
    health -= damage;
}

Vector2 Player:: getPosition() 
{
    return _position; 
}

Rectangle Player:: get_rect_player() 
{
    return _destination;
}

Player :: ~Player()
{
    UnloadTexture(_ship);
}