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
    bool is_moving = false;

    SDL_Rect player_rect;

private:
    SDL_Texture* player_texture;
    SDL_Rect boundary_rect;
    SDL_Renderer* renderer;

    float delta_time;

};

