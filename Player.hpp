#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class Player {
public:
    void createPlayer(int boundary_width, int boundary_height, SDL_Renderer* renderer);
    void handleEvent(SDL_Event& event);
    void update(float delta_time);
    void setDeltaTime(float delta_time);
    void move(bool is_moving);
    bool mouse_on_player();
    bool playerHit(SDL_Rect collider);
    void render();
    void clean();
    void changeColors();
    void flicker();
    bool is_moving = false;
    bool is_color_1 = true;
    bool is_flicker = true;

    SDL_Rect player_rect;

private:
    SDL_Texture* player_texture;
    SDL_Rect boundary_rect;
    SDL_Renderer* renderer;
    SDL_Color color_1 = {242, 140, 40, 255};
    SDL_Color color_2 = {0, 0, 255, 255};
    SDL_Color current_color;

    struct time { float delta_time; float total_time = 0; float time_until_flickering = 10; float flickering_interval = 0; float flickering_rate = .2; float time_flickering = 3; int time_between_flickers = 10; };
    time time;
};

