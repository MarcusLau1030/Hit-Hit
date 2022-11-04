#include "TextureManager.hpp"

TextureManager::TextureManager() {

}

void TextureManager::createTextureManager(SDL_Renderer* renderer) {
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Initialized SDL_image library" << std::endl;
    }
    if (TTF_Init() == 0) {
        std::cout << "Initialized SDL_ttf library" << std::endl;
    }
    TextureManager::renderer = renderer;
}

SDL_Texture* TextureManager::load(std::string image_path) {
    std::size_t found = image_path.find_last_of("/");
    std::string file = image_path.substr(found + 1);
    found = file.find_last_of(".");
    std::string filename = file.substr(0, found);
    if (TextureManager::texture_map.find(filename) == TextureManager::texture_map.end()) {
        SDL_Surface* image = IMG_Load(image_path.c_str());
        TextureManager::texture_map[filename] = SDL_CreateTextureFromSurface(TextureManager::renderer, image);
        SDL_FreeSurface(image);
    }

    return TextureManager::texture_map[filename];
}

void TextureManager::createText(std::string font_path, int font_size, std::string message_text, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
    TextureManager::text_texture = SDL_CreateTextureFromSurface(TextureManager::renderer, text_surface);
    TTF_CloseFont(font);
    SDL_FreeSurface(text_surface);

    SDL_Rect location_rect;
    SDL_QueryTexture(TextureManager::text_texture, NULL, NULL, &location_rect.w, &location_rect.h);
    TextureManager::location_rect = location_rect;

    
}

void TextureManager::displayText(int x, int y) {
    
    TextureManager::location_rect.x = x;
    TextureManager::location_rect.y = y;

    SDL_RenderCopy(TextureManager::renderer, TextureManager::text_texture, NULL, &TextureManager::location_rect);

    SDL_DestroyTexture(TextureManager::text_texture);
}

void TextureManager::clean() {
    for (auto i = TextureManager::texture_map.begin(); i != TextureManager::texture_map.end();) {
        SDL_DestroyTexture(i->second);
        i = TextureManager::texture_map.erase(i);
    }

    SDL_DestroyTexture(TextureManager::text_texture);

    TTF_Quit();
}

std::map<std::string, SDL_Texture*> TextureManager::texture_map;
SDL_Renderer* TextureManager::renderer;

SDL_Texture* TextureManager::text_texture;
SDL_Rect TextureManager::location_rect;