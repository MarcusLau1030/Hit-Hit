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
	current_color = color_1;

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

	changeColors();

	move(is_moving);

}

void Player::setDeltaTime(float delta_time) {
	time.delta_time = delta_time;
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

void Player::changeColors() {
	time.total_time += time.delta_time;
	if (time.total_time > time.time_until_flickering) {

		if (time.total_time > time.time_until_flickering + time.time_flickering) {
			time.total_time = 0;
			time.time_until_flickering = (rand() % time.time_between_flickers) + 10;
			time.flickering_interval = 0;
			is_color_1 = !is_color_1;
			if (is_color_1) {
				current_color = color_1;
			}
			else {
				current_color = color_2;
			}
		}
		else {
			time.flickering_interval += time.delta_time;
			if (time.flickering_interval > time.flickering_rate) {
				flicker();
				time.flickering_interval = 0;
			}
		}

	}
}

void Player::flicker() {
	if (is_flicker) {
		current_color = color_2;
	}
	else {
		current_color = color_1;
	}
	is_flicker = !is_flicker;
}

void Player::render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, current_color.r, current_color.g, current_color.b, current_color.a);
	SDL_RenderFillRect(renderer, &player_rect);
	//SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);
}

void Player::clean() {
	SDL_DestroyTexture(player_texture);
}
