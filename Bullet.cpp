#include "Bullet.h"

Bullet:: Bullet(Vector2 pos, float angle, Texture2D texture) {
    _position = pos;
    _angle = angle - 90;
    _texture = texture;
    source = { 0,0,(float)_texture.width,(float)_texture.height };
    _width = _texture.width;
    _height = _texture.height;
    _des = { _position.x, _position.y, _width * _scale, _height * _scale };
    Vector2 direction = { cos(_angle * PI / 180), sin(_angle * PI / 180) };
    _xSpeed = direction.x * _speed;
    _ySpeed = direction.y * _speed;
}

void Bullet:: draw()
{
    DrawTextureEx(_texture, _position, _angle + 90, _scale, WHITE);
    update();
}

void Bullet:: update()
{
    _position.x += _xSpeed;
    _position.y += _ySpeed;
}

float Bullet::  getWidth()
{
    return _width;
}

float Bullet::  getHeight()
{
    return _height;
}

Vector2 Bullet:: getPosition()
{
    return _position;
}

void Bullet:: MoveVertical(float speed)
{
    _position.y += speed;
}

void Bullet::  moveWithBackground(float xSpeed, float ySpeed)
{
    _position.x += xSpeed;
    _position.y += ySpeed;
}

Rectangle Bullet:: get_rect_bullet() 
{
    return { _position.x,_position.y,_width * _scale,_height * _scale };
}

Bullet:: ~Bullet()
{

}

