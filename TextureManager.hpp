#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>

class TextureManager {
public:
	TextureManager();
	static void createTextureManager(SDL_Renderer* renderer);
	static SDL_Texture* load(std::string path);
	static void clean();
	static SDL_Renderer* renderer;

private:
	static std::map<std::string, SDL_Texture*> texture_map;

};