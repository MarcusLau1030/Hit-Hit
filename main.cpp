#include <iostream>
#include <vector>
#include "Window.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Use & instead of no prefix because it does not create a shallow copy, and passes in through reference the class instance. 
// This is neccessary because the actual instance needs to be constantly updated for the player object to move

int WIDTH, HEIGHT;
Uint64 now = SDL_GetPerformanceCounter();
Uint64 last = 0;
float delta_time = 0;

int main(int argc, char* argv[]) {
    Window window;
    window.getWindowResolution(WIDTH, HEIGHT);
    window.createWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);
    TextureManager::createTextureManager(window.renderer);
    TextureManager::load("./PNG/GroundBullet.png");
    TextureManager::load("./PNG/SkyBullet.png");
    Player player;
    player.createPlayer(window.window_width, window.window_height, window.renderer);
    Game game;
    game.createGame(window, player);

    while (game.window.running()) {
        last = now;
        now = SDL_GetPerformanceCounter();
        delta_time = (float)((now - last) / (float)SDL_GetPerformanceFrequency());
        game.update(delta_time);
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            game.handleEvent(event);
        }
        game.render();
        SDL_Delay(1);
    }
    game.clean();

    std::cout << _CrtDumpMemoryLeaks() << std::endl;

    return EXIT_SUCCESS;
}

