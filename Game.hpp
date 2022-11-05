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
    void displayMainMenu();
    void displayTimer(int x, int y, float time, std::string message);
    void displayPoints(int x, int y, int points, std::string message);
    void displayLose();
    void displayPlay(std::string message, SDL_Color border_color, SDL_Color filler_color);
    bool isClicked(SDL_Rect button);
    void resetGame();
    Window window;
    Player player;
    std::vector <Projectile*> projectile_list;
    bool is_main_screen = true;
    bool is_running = false;
    bool is_lose_screen = false;
    bool mouse_button_down = false;

private:
    int high_points = 0;
    int points = 0;
    float delta_time;
    float time_passed;
    float high_total_time = 0;
    float total_time = 0;
    int projectile_speed_range = 100;
    int projectile_base_speed = 200;
    SDL_Rect play_button;
};