#include "Enemy.h"


Enemy::Enemy(Texture2D texture, int x, int y, Texture2D bullet)
{
    _texture = texture;
    _Bullettexture = bullet;
    _position.x = x;
    _position.y = y;
    distance = 0;
    scale = 4;
    speed = 5;
    width = texture.width * scale;
    height = texture.height * scale;
    source = { 0, 0, (float)texture.width, (float)texture.height };
    destination = { _position.x, _position.y, scale * texture.width, scale * texture.height };
    origin = { (float)(_texture.width * scale) / 2, (float)(_texture.height * scale) / 2 };
    fireRate = 0.5;
    _distance = GetRandomValue(100, 700);
}

void Enemy::Update(Vector2 playerPosition)
{
    direction = Vector2Subtract(_position, playerPosition);
    Vector2 dir = Vector2Normalize(direction);
    angle = ((atan2f(_position.y - playerPosition.y + 32, _position.x - playerPosition.x + 32)) * 180) / 3.14;
    float distance = Vector2Distance(_position, playerPosition);
    if (distance > _distance)
    {
        _position.x -= dir.x * speed;
        _position.y -= dir.y * speed;

    }
    if (GetTime() - current > fireRate && bullets.size() <= 5)
    {
        current = GetTime();
        bullets.push_back(Bullet({ _position.x + height / 2,_position.y + height / 2 }, angle - 90, _Bullettexture));
    }
}

void Enemy::Draw()
{
    DrawTextureEx(_texture, _position, angle + 90, scale, WHITE);
}

void Enemy::MoveHorizontal(float speed)
{
    _position.x += speed;
}

void Enemy::MoveVertical(float speed)
{
    _position.y += speed;
}

Vector2 Enemy::getPosition()
{
    return _position;
}

float Enemy::getAngle()
{
    return angle;
}

float Enemy::getWidth()
{
    return width;
}

float Enemy::getHeight()
{
    return height;
}

vector<Bullet>& Enemy::getEnemyBullets()
{
    return bullets;
}

Rectangle Enemy::get_rect_enemy()
{
    return { _position.x,_position.y,width,height };
}














