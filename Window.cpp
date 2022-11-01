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

        if (TTF_Init() == 0) {
            std::cout << "Initialized SDL_ttf library" << std::endl;
        }

        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            std::cout << "Initialized SDL_image library" << std::endl;
        }

        is_running = true;
    }
    else {
        is_running = false;
    }

    window_width = width;
    window_height = height;
    window_center_x = window_width / 2;
    window_center_y = window_height / 2;
    window_size_changed = false;
}
void Window::handleEvent(SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    is_running = false;
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
    TTF_Quit();
    SDL_Quit();
    std::cout << "Window Cleaned" << std::endl;
}

bool Window::running() {
    return is_running;
}
