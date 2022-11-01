#include "TextureManager.hpp"

TextureManager::TextureManager() {

}

void TextureManager::createTextureManager(SDL_Renderer* renderer) {
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Initialized SDL_image library" << std::endl;
    }
    TextureManager::renderer = renderer;
}

SDL_Texture* TextureManager::load(std::string path) {
    std::size_t found = path.find_last_of("/");
    std::string file = path.substr(found + 1);
    found = file.find_last_of(".");
    std::string filename = file.substr(0, found);
    if (TextureManager::texture_map.find(filename) == TextureManager::texture_map.end()) {
        SDL_Surface* image = IMG_Load(path.c_str());
        TextureManager::texture_map[filename] = SDL_CreateTextureFromSurface(TextureManager::renderer, image);
        SDL_FreeSurface(image);
    }

    return TextureManager::texture_map[filename];
}
void TextureManager::clean() {
    for (auto i = TextureManager::texture_map.begin(); i != TextureManager::texture_map.end();) {
        SDL_DestroyTexture(i->second);
        i = TextureManager::texture_map.erase(i);
    }
}

std::map<std::string, SDL_Texture*> TextureManager::texture_map;


SDL_Renderer* TextureManager::renderer;