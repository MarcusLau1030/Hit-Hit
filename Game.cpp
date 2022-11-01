#include "Game.hpp"

Game::Game() {

}

void Game::createGame(Window& window, Player &player) {
	this->window = window;
	this->player = player;
	Projectile::setEnvironment(window.renderer);
}

void Game::handleEvent(SDL_Event& event) {
	//std::cout << "Event" << std::endl;
	window.handleEvent(event);
	player.handleEvent(event);
}

void Game::render() {
	SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
	SDL_RenderClear(window.renderer);

	player.render();

	for (auto projectile = projectile_list.begin(); projectile != projectile_list.end(); ++projectile) {
		(*projectile)->render();
	}

	window.render();

	displayTimer();
	displayPoints();

	SDL_RenderPresent(window.renderer);
}

void Game::displayTimer() {
	std::string timer_string = std::to_string(total_time);
	std::size_t period = timer_string.find(".");
	timer_string = timer_string.substr(0, period) + timer_string.substr(period, 3);
	TextureManager::displayText("./Fonts/times.ttf", 30, "Time: " + timer_string, {0, 0, 0, 255}, 0, 0);
}
void Game::displayPoints() {
	std::string points_string = std::to_string(points);
	TextureManager::displayText("./Fonts/times.ttf", 30, "Points: " + points_string, {0, 0, 0, 255}, 0, 40);
}

void Game::update(float delta_time) {

	time_passed += delta_time;
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
				std::cout << "Points!" << std::endl;
				++points;
			}
			else if ((*projectile)->info.is_color_1 == !player.is_color_1 && player.playerHit((*projectile)->collider)) {
				delete* projectile;
				projectile = projectile_list.erase(projectile);
				std::cout << "You lose!" << std::endl;
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