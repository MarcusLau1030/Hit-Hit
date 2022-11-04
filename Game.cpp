#include "Game.hpp"

Game::Game() {

}

void Game::createGame(Window& window, Player &player) {
	this->window = window;
	this->player = player;
	Projectile::setEnvironment(window.renderer);
}

void Game::handleEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT && isClicked(replay_button)) {
				mouse_button_down = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (mouse_button_down && event.button.button == SDL_BUTTON_LEFT && isClicked(replay_button)) {
				mouse_button_down = false;
				resetGame();
			}
			break;
		}
	window.handleEvent(event);
	player.handleEvent(event);
}

void Game::render() {
	if (is_running) {
		SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
		SDL_RenderClear(window.renderer);

		player.render();

		for (auto projectile = projectile_list.begin(); projectile != projectile_list.end(); ++projectile) {
			(*projectile)->render();
		}

		window.render();

		displayTimer(0,0, high_total_time, "Highest Time: ");
		displayPoints(0, 40, high_points, "High Score: ");
		displayTimer(0, 80, total_time, "Time: ");
		displayPoints(0, 120, points, "Score: ");

	}
	else if (is_lose_screen) {
		displayLose();
		displayReplay();
		displayTimer(TextureManager::location_rect.x, TextureManager::location_rect.y + TextureManager::location_rect.h + 20, high_total_time, "Higest Time: ");
		displayPoints(TextureManager::location_rect.x, TextureManager::location_rect.y + TextureManager::location_rect.h + 20, high_points, "High Score: ");
	}

	SDL_RenderPresent(window.renderer);
}

void Game::displayTimer(int x, int y, float time, std::string message) {
	std::string timer_string = std::to_string(time);
	std::size_t period = timer_string.find(".");
	timer_string = timer_string.substr(0, period) + timer_string.substr(period, 3);
	TextureManager::createText("./Fonts/times.ttf", 30, message + timer_string, { 0, 0, 0, 255 });
	TextureManager::displayText(x, y);
}

void Game::displayPoints(int x, int y, int points, std::string message) {
	std::string points_string = std::to_string(points);
	TextureManager::createText("./Fonts/times.ttf", 30, message + points_string, { 0, 0, 0, 255 });
	TextureManager::displayText(x, y);
}

void Game::displayLose() {
	TextureManager::createText("./Fonts/times.ttf", 100, "You Lose", { 0, 0, 0, 255 });
	int pos_x = (window.window_width / 2) - (TextureManager::location_rect.w / 2);
	int pos_y = (float)window.window_height  * (1.0f/3.0f) - (TextureManager::location_rect.h / 2);
	TextureManager::displayText(pos_x, pos_y);
}

void Game::displayReplay() {
	TextureManager::createText("./Fonts/times.ttf", 50, "Play Again", { 0, 0, 0, 255 });
	int pos_x = (window.window_width / 2) - (TextureManager::location_rect.w / 2);
	int pos_y = (float)window.window_height * (11.0f/24.0f) - (TextureManager::location_rect.h / 2);
	TextureManager::location_rect.x = pos_x;
	TextureManager::location_rect.y = pos_y;
	SDL_Rect box = TextureManager::location_rect;
	box.x -= 1;
	box.y -= 1;
	box.w += 2;
	box.h += 2;
	SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(window.renderer, &box);
	SDL_SetRenderDrawColor(window.renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(window.renderer, &TextureManager::location_rect);
	TextureManager::displayText(pos_x, pos_y);
	replay_button = TextureManager::location_rect;
}

bool Game::isClicked(SDL_Rect button) {
	int mouse_position_x, mouse_position_y;
	SDL_GetMouseState(&mouse_position_x, &mouse_position_y);
	if (mouse_position_x >= button.x && mouse_position_x <= button.x + button.w && mouse_position_y >= button.y && mouse_position_y <= button.y + button.h) {
		return true;
	}
	return false;
}

void Game::resetGame() {

	is_running = true;
	is_lose_screen = false;
	for (auto projectile = projectile_list.begin(); projectile != projectile_list.end(); ) {
		delete* projectile;
		projectile = projectile_list.erase(projectile);
	}
	
	player.playerReset();

	high_points = (high_points > points) ? high_points : points;
	points = 0;
	time_passed = 0;
	high_total_time = (high_total_time > total_time) ? high_total_time : total_time;
	total_time = 0;
}

void Game::update(float delta_time) {
	if (is_running) {
		time_passed += delta_time;
		if (high_total_time <= total_time) {
			high_total_time = total_time + delta_time;
		}
		total_time += delta_time;
		if (time_passed > .1) {
			time_passed -= time_passed;
			projectileGenerator();
		}

		window.update(delta_time);
		player.update(delta_time);

		for (auto projectile = projectile_list.begin(); projectile != projectile_list.end(); ++projectile) {
			(*projectile)->update(delta_time);
		}

		handleProjectiles();
	}

}

void Game::projectileGenerator() {
	int start_x, start_y, end_x, end_y, one_to_four;
	float projectile_speed;
	bool is_color_1;
	one_to_four = rand() % 4;
	if (one_to_four == 0) {
		start_x = 0;
		start_y = rand() % (window.window_height + 1);
	}
	else if (one_to_four == 1) {
		start_x = window.window_width;
		start_y = rand() % (window.window_height + 1);
	}
	else if (one_to_four == 2) {
		start_x = rand() % (window.window_width + 1);
		start_y = 0;
	}
	else {
		start_x = rand() % (window.window_width + 1);
		start_y = window.window_height + 1;
	}

	projectile_speed = rand() % projectile_speed_range + projectile_base_speed;

	end_x = 1 + (rand() % (window.window_width - 1));
	end_y = 1 + (rand() % (window.window_height - 1));

	is_color_1 = rand() % 2;

	Projectile* projectile = new Projectile();
	if (is_color_1) {
		projectile->createProjectile(start_x, start_y, end_x, end_y, TextureManager::load("./PNG/Bullet1.png"), projectile_speed, is_color_1);
	}
	else {
		projectile->createProjectile(start_x, start_y, end_x, end_y, TextureManager::load("./PNG/Bullet2.png"), projectile_speed, is_color_1);
	}

	projectile_list.push_back(projectile);

}

void Game::handleProjectiles() {
	for (auto projectile = projectile_list.begin(); projectile != projectile_list.end(); ) {
		if (!((*projectile)->info.is_active)) {
			delete* projectile;
			projectile = projectile_list.erase(projectile);
		}
		else {
			if ((*projectile)->info.is_color_1 == player.is_color_1 && player.playerHit((*projectile)->collider)) {
				delete* projectile;
				projectile = projectile_list.erase(projectile);
				if (high_points == points) {
					++high_points;
				}
				++points;
			}
			else if ((*projectile)->info.is_color_1 == !player.is_color_1 && player.playerHit((*projectile)->collider)) {
				delete* projectile;
				projectile = projectile_list.erase(projectile);
				is_running = false;
				is_lose_screen = true;
			}
			else {
				++projectile;
			}
		}
	}
}

void Game::clean() {

	for (auto projectile = projectile_list.begin(); projectile != projectile_list.end(); ) {
		delete* projectile;
		projectile = projectile_list.erase(projectile);
	}
	
	player.clean();
	TextureManager::clean();
	window.clean();
}