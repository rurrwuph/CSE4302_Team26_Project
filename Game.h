#pragma once
#include <iostream>
#include "raylib.h"
#include "Player.h"
#include "Background.h"
#include "Bullet.h"
#include "raymath.h"
#include "Enemy.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
using namespace std;

class Game
{
private:
    Player _player;
    vector<Bullet> bullets;
    Texture2D playerBulletTexture;
    Texture2D lower_background_texture;
    Texture2D upper_background_texture;
    Texture2D enemyTexture;
    Texture2D enemy_bullet_texture;
    Texture2D health_bar;
    Texture2D health;
    Texture2D gameover_Screen;
    Rectangle source_health;
    Rectangle dest_health;  
    Background background;
    vector<Enemy> enemies;
    vector<Bullet> enemyBullets;
    const float backgroundSpeed = 10;
    float enemySpawnrate;
    float cuurentTime = 0;
    int hit_count;
    bool running = true;
    float health_bar_width;
    const float bullet_fire_rate = 0.1;
    float cuurent_fire_time;
    Font custom_font;
    int score;
    float damage;
    int high_score;
    Sound Collision_sound;

public:
    Game();
    ~Game();
    void update();
    void check_collision();
    void check_bound();
    void init();
    Vector2 getPlayerPOstion();
    void handleInput();
    bool get_running_stat();
    int check_HighScore();
    void Gameover();
    Music back_music;
   
};

