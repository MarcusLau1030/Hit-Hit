#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include "wtypes.h"

class Window {

public:
    //external class functions
    void getWindowResolution(int& horizontal, int& vertical);
    void createWindow(const char* title, int posx, int posy, int width, int height, Uint32 flags);
    void handleEvent(SDL_Event& event);
    void update(float delta_time);
    void render();
    void clean();
    bool running();

    //internal class functions

    //functions for Game
    SDL_Surface* window_surface;
    SDL_Window* window;
    SDL_Renderer* renderer;


    int window_width;
    int window_height;
    int window_center_x;
    int window_center_y;
    bool window_size_changed = false;


private:
    int count = 0;
    bool is_running;


};