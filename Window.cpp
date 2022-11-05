#include "Window.hpp"

void Window::getWindowResolution(int& horizontal, int& vertical) {
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

void Window::createWindow(const char* title, int posx, int posy, int width, int height, Uint32 flags) {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized SDL library" << std::endl;

        window = SDL_CreateWindow(title, posx, posy, width, height, flags);

        if (window) {
            std::cout << "Window Created" << std::endl;
            window_surface = SDL_GetWindowSurface(window);
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer) {
            std::cout << "Renderer Created" << std::endl;
        }
        SDL_RenderSetScale(renderer, 1920, 1080);
        SDL_RenderSetLogicalSize(renderer, 1920, 1080);

        is_running = true;
    }
    else {
        is_running = false;
    }

    window_width = width;
    window_height = height;
    window_center_x = window_width / 2;
    window_center_y = window_height / 2;
}
void Window::handleEvent(SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    std::cout << "Escape" << std::endl;
                    escape_box_active = true;
                    //is_running = false;
                    break;
            }
        default:
            break;
    }
}
void Window::update(float delta_time) {
    //std::cout << ++count << std::endl;

}
void Window::render() {
    //SDL_UpdateWindowSurface(window);
}

void Window::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    //SDL_FreeSurface(window_surface);
    SDL_Quit();
    std::cout << "Window Cleaned" << std::endl;
}

void Window::displayEscape() {
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 50);
    SDL_RenderClear(renderer);

    SDL_Rect escape_box;
    escape_box.x = window_center_x - (window_width/12);
    escape_box.y = window_center_y - (window_height/8);
    escape_box.w = window_width / 6;
    escape_box.h = window_height / 4;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &escape_box);

    TextureManager::createText("./Fonts/times.ttf", 80, "Exit?", {0, 0, 0, 255});
    int pos_x = escape_box.x + (escape_box.w - TextureManager::location_rect.w) / 2;
    int pos_y = escape_box.y + TextureManager::location_rect.h / 2;
    TextureManager::displayText(pos_x, pos_y);

    TextureManager::createText("./Fonts/times.ttf", 50, "Yes", { 0, 0, 0, 255 });
    pos_x = window_center_x - ((float)escape_box.w * 3.0f / 8.0f);
    pos_y = window_center_y + (escape_box.h / 8);
    
    SDL_Rect border_box = TextureManager::location_rect;
    border_box.x = pos_x - 1;
    border_box.y = pos_y - 1;
    border_box.w += 2;
    border_box.h += 2;

    yes_button = border_box;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &border_box);
    TextureManager::displayText(pos_x, pos_y);

    TextureManager::createText("./Fonts/times.ttf", 50, "No", { 0, 0, 0, 255 });
    pos_x = window_center_x + ((float)escape_box.w * 1.0f / 8.0f);
    pos_y = window_center_y + (escape_box.h / 8);

    border_box = TextureManager::location_rect;
    border_box.x = pos_x - 1;
    border_box.y = pos_y - 1;
    border_box.w += 2;
    border_box.h += 2;

    no_button = border_box;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &border_box);
    TextureManager::displayText(pos_x, pos_y);

    SDL_RenderPresent(renderer);
}