#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Player.hpp"
#include "Window.hpp"
#include "TextureManager.hpp"
#include "Projectile.hpp "


class Game {
public:
    Game();
    void createGame(Window& window, Player& player);
    void handleEvent(SDL_Event& event);
    void update(float delta_time);
    void projectileGenerator();
    void handleProjectiles();
    void render();
    void clean();
    void displayTimer();
    void displayPoints();
    Window window;
    Player player;
    std::vector <Projectile*> projectile_list;

private:
    int points;
    float delta_time;
    float time_passed;
    float total_time;
    int projectile_speed_range = 100;
    int projectile_base_speed = 200;
};