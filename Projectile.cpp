#include "Projectile.hpp"

void Projectile::setEnvironment(SDL_Renderer* renderer) {
	Projectile::renderer = renderer;
}

void Projectile::createProjectile(int start_x, int start_y, int end_x, int end_y, SDL_Texture* projectile_texture, float projectile_speed, bool is_color_1) {
	collider.x = start_x;
	collider.y = start_y;
	position_vector = Vector2(collider.x, collider.y);
	direction_vector = Vector2((end_x - start_x), (end_y - start_y));
	direction_vector.normalize();

	this->projectile_texture = projectile_texture;

	SDL_QueryTexture(projectile_texture, NULL, NULL, &collider.w, &collider.h);
	SDL_GetRendererInfo(Projectile::renderer, &renderer_info);
	info.projectile_speed = projectile_speed;
	info.is_color_1 = is_color_1;
	info.is_active = true;
}

void Projectile::update(float delta_time) {
	if (info.is_active) {
		moveProjectile(delta_time);
	}
	deactivateProjectile();
}

void Projectile::moveProjectile(float delta_time) {
	position_vector = position_vector + direction_vector * delta_time * info.projectile_speed;

	collider.x = position_vector.x;
	collider.y = position_vector.y;
}

void Projectile::deactivateProjectile() {
	if (collider.x < 0 || collider.y < 0 || collider.x > (renderer_info.max_texture_width) || collider.y > (renderer_info.max_texture_height)) {
		info.is_active = false;
	}
}

void Projectile::render() {
	SDL_RenderCopy(Projectile::renderer, projectile_texture, NULL, &collider);
	//SDL_BlitSurface(projectile_texture, NULL, window_surface, &collider);
}

void Projectile::clean() {

}

SDL_Renderer* Projectile::renderer;