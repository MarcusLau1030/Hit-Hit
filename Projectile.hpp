#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include "Vector2.hpp"
#include "TextureManager.hpp"

class Projectile {
public:
	static void setEnvironment(SDL_Renderer* renderer);
	void createProjectile(int start_x, int start_y, int end_x, int end_y, SDL_Texture* projectile_texture, float projectile_speed, bool is_color_1);
	void update(float delta_time);
	void moveProjectile(float delta_time);
	void deactivateProjectile();
	void render();
	void clean();

	SDL_Rect collider;
	struct projectile_info { float projectile_speed; std::string team; bool is_active; bool is_color_1; };
	projectile_info info;

private:
	SDL_Texture* projectile_texture;
	Vector2 direction_vector;
	Vector2 position_vector;
	static SDL_Renderer* renderer;
	SDL_RendererInfo renderer_info;


};