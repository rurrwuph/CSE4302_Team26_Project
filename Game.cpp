#include "Game.h"

Game::Game()
{
    playerBulletTexture = LoadTexture("assets/projectiles/projectile2.png");
    enemy_bullet_texture = LoadTexture("assets/projectiles/projectile3.png");
    lower_background_texture = LoadTexture("assets/background1.png");
    upper_background_texture = LoadTexture("assets/background4.png");
    back_music = LoadMusicStream("assets/videoplayback.wav");
    Collision_sound = LoadSound("assets/shoot.flac");
    health_bar = LoadTexture("assets/healthBar.png");
    health = LoadTexture("assets/health.png");
    gameover_Screen = LoadTexture("assets/Gameover.png");
    background = Background(lower_background_texture, upper_background_texture);
    enemyTexture = LoadTexture("assets/spaceShip/ships/brown.png");
    enemies.push_back(Enemy(enemyTexture, 0, 0, enemy_bullet_texture));
    enemySpawnrate = 1;
    cuurent_fire_time = 0;
    source_health = { 0,0,(float)health.width,(float)health.height };
    dest_health = { (float)(GetScreenWidth() - health_bar.width * 2.5 - 10),10 ,(float)health.width * 2.5f,(float)health.height * 2.2f };
    custom_font = LoadFontEx("assets/CommodorePixeled.ttf", 30, NULL, 0);
    damage = 10;
    high_score = 0;
    PlayMusicStream(back_music);
}

int Game::check_HighScore()
{
    ifstream infile("highscore.txt");
    infile >> high_score;
    
    if (score > high_score)
    {
        ofstream file("highscore.txt");
        high_score = score;
        file << high_score;
    }
    return high_score;
}

void Game::Gameover()
{
    DrawTextureEx(gameover_Screen, { 0,0 }, 0.0f, 1, WHITE);
    char highscore_text[40];
    char Gameover_text[20];
    snprintf(highscore_text, sizeof(highscore_text), "High Score: %d", check_HighScore());
    snprintf(Gameover_text, sizeof(Gameover_text), "Game Over!!!!");
    DrawTextEx(custom_font, Gameover_text , {10,(float)GetScreenHeight()/2-200}, custom_font.baseSize*2.5, 2, RAYWHITE);
    DrawTextEx(custom_font, highscore_text , {(float)GetScreenWidth()/2-150,(float)GetScreenHeight()/2}, custom_font.baseSize, 2, RAYWHITE);
}

void Game::update()
{
    background.draw();
    if (_player.getHealth() <= 0)
    {
        running = false;
    }
     if (!running)
    {
         Gameover();
         return;
    }

    cout << hit_count << "\n";
    for (auto it = bullets.begin();it != bullets.end();)
    {
        it->draw();
        if (Vector2Distance(it->getPosition(), _player.getPosition()) > 800)
        {
            it = bullets.erase(it);
        }
        else it++;
    }
    for (auto it = enemyBullets.begin(); it != enemyBullets.end();)
    {
        it->draw();

        if (Vector2Distance(it->getPosition(), _player.getPosition()) > 800)
            it = enemyBullets.erase(it);
        else it++;

    }
    for (auto& enemy : enemies)
    {
        enemy.Draw();
        enemy.Update(getPlayerPOstion());
        if (IsKeyDown(KeyboardKey::KEY_A))
        {
            enemy.MoveHorizontal(backgroundSpeed);
        }

        if (IsKeyDown(KeyboardKey::KEY_D))
        {
            enemy.MoveHorizontal(-backgroundSpeed);
        }

        if (IsKeyDown(KeyboardKey::KEY_W))
        {
            enemy.MoveVertical(backgroundSpeed);
        }

        if (IsKeyDown(KeyboardKey::KEY_S))
        {
            enemy.MoveVertical(-backgroundSpeed);
        }

        for (auto it = enemy.getEnemyBullets().begin();it != enemy.getEnemyBullets().end();)
        {
            it->draw();
            if (IsKeyDown(KeyboardKey::KEY_A))
            {
                it->moveWithBackground(backgroundSpeed, 0);
            }

            if (IsKeyDown(KeyboardKey::KEY_D))
            {
                it->moveWithBackground(-backgroundSpeed, 0);
            }

            if (IsKeyDown(KeyboardKey::KEY_W))
            {
                it->moveWithBackground(0, backgroundSpeed);
            }

            if (IsKeyDown(KeyboardKey::KEY_S))
            {
                it->moveWithBackground(0, backgroundSpeed);
            }

            if (Vector2Distance(it->getPosition(), _player.getPosition()) > 800)
            {
                it = enemy.getEnemyBullets().erase(it);
            }

            else it++;
        }
        check_collision();

    }
    if (GetTime() - cuurentTime > enemySpawnrate)
    {
        int x = rand() % 1500 + _player.getPosition().x;
        int y = rand() % 1500 + _player.getPosition().y;
        enemies.push_back(Enemy(enemyTexture, x, y, enemy_bullet_texture));
        cuurentTime = GetTime();
    }
    _player.draw();
    _player.update();
    health_bar_width = ((float)_player.getHealth() / 100) * health.width * 2.5;
    dest_health.width = health_bar_width;
    DrawTextureEx(health_bar, { (float)(GetScreenWidth() - health_bar.width * 2.5 - 12),9 }, 0, 2.5, WHITE);
    DrawTexturePro(health, source_health, dest_health, { 0,0 }, 0, WHITE);
    char score_text[40];
    snprintf(score_text, sizeof(score_text), "Score:  %d", score);
    
    DrawTextEx(custom_font, score_text , {10,10}, custom_font.baseSize, 2, WHITE);
    

}

void Game::check_collision()
{
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
        bool bulletHit = false;

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            if (CheckCollisionRecs(bulletIt->get_rect_bullet(), enemyIt->get_rect_enemy())) {
                cout << "collison detected" << "\n";
                PlaySound(Collision_sound);
                score++;
                enemyIt = enemies.erase(enemyIt);
                bulletHit = true;
                break;  
            }

            else 
            {
                ++enemyIt;
            }
        }

        if (bulletHit) {
            bulletIt = bullets.erase(bulletIt);
            break;
        }
        else {
            ++bulletIt;
        }

    }
    for (auto& enemy : enemies)
    {
        bool bullethit = false;

        for (auto it = enemy.getEnemyBullets().begin();it != enemy.getEnemyBullets().end();)
        {
            if (CheckCollisionRecs(it->get_rect_bullet(), _player.get_rect_player()))
            {
                PlaySound(Collision_sound);
                it = enemy.getEnemyBullets().erase(it);

                bullethit = true;
            }
            else it++;
        }
        if (bullethit)
        {
            _player.takeDamage(damage);
        }
    }
}

void Game::check_bound()
{

}

Vector2 Game::getPlayerPOstion()
{
    return _player.getPosition();
}



void Game::handleInput()
{
    if (IsKeyDown(KeyboardKey::KEY_SPACE))
    {
        if (GetTime() - cuurent_fire_time > bullet_fire_rate)
        {
            bullets.push_back(Bullet({ (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 }, _player.getAngle(), playerBulletTexture));
            cuurent_fire_time = GetTime();
        }
    }
        

    if (IsKeyDown(KeyboardKey::KEY_A))
    {
        background.xUpdateMain(backgroundSpeed);
        for (auto& bullet : bullets)
            bullet.moveWithBackground(backgroundSpeed, 0);
    }

    if (IsKeyDown(KeyboardKey::KEY_D))
    {
        background.xUpdateMain(-backgroundSpeed);
        for (auto& bullet : bullets)
            bullet.moveWithBackground(-backgroundSpeed, 0);
    }

    if (IsKeyDown(KeyboardKey::KEY_W))
    {
        background.yUpdateMain(backgroundSpeed);
        for (auto& bullet : bullets)
            bullet.moveWithBackground(0, backgroundSpeed);
    }

    if (IsKeyDown(KeyboardKey::KEY_S))
    {
        background.yUpdateMain(-backgroundSpeed);
        for (auto& bullet : bullets)
            bullet.moveWithBackground(0, -backgroundSpeed);
    }
}

bool Game::get_running_stat()
{
    return running;
}

Game::~Game()
{
    UnloadTexture(playerBulletTexture);
    UnloadTexture(enemy_bullet_texture);
    UnloadTexture(lower_background_texture);
    UnloadTexture(upper_background_texture);
    UnloadTexture(enemyTexture);
    UnloadTexture(health_bar);
    UnloadTexture(health);
    UnloadTexture(gameover_Screen);
    UnloadMusicStream(back_music);
    UnloadSound(Collision_sound);
}






