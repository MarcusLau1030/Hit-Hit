#include "Player.hpp"

void Player::createPlayer(int boundary_width, int boundary_height, SDL_Renderer* renderer) {

	player_rect.w = 50;
	player_rect.h = 50;
	player_rect.x = (boundary_width / 2) - player_rect.w;
	player_rect.y = (boundary_height / 2) - player_rect.h;
	boundary_rect.x = 0;
	boundary_rect.y = 0;
	boundary_rect.w = boundary_width;
	boundary_rect.h = boundary_height;
	this->renderer = renderer;

}

void Player::handleEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT && mouse_on_player()) {
				is_moving = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT && mouse_on_player()) {
				is_moving = false;
			}
			break;
		}
}

void Player::update(float delta_time) {
	setDeltaTime(delta_time);

	move(is_moving);

}

void Player::setDeltaTime(float delta_time) {
	this->delta_time = delta_time;
}

void Player::move(bool is_moving) {
	if (is_moving) {
		int mouse_position_x, mouse_position_y;
		SDL_GetMouseState(&mouse_position_x, &mouse_position_y);
		player_rect.x = mouse_position_x - (player_rect.w / 2);
		player_rect.y = mouse_position_y - (player_rect.h / 2);
	}
}

bool Player::mouse_on_player() {
	int mouse_position_x, mouse_position_y;
	SDL_GetMouseState(&mouse_position_x, &mouse_position_y);
	if (mouse_position_x > player_rect.x && mouse_position_x < player_rect.x + player_rect.w
		&& mouse_position_y > player_rect.y && mouse_position_y < player_rect.y + player_rect.h) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::playerHit(SDL_Rect collider) {
	if (SDL_HasIntersection(&collider, &player_rect) == SDL_TRUE) {
		return true;
	}
	else {
		return false;
	}
}

void Player::render() {
	if (is_moving) {
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	} 
	else {
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 242, 140, 40, 255);
	}

	SDL_RenderFillRect(renderer, &player_rect);
	//SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);
}

void Player::clean() {
	SDL_DestroyTexture(player_texture);
}
