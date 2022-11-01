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
	SDL_RenderPresent(window.renderer);
}

void Game::update(float delta_time) {

	time_passed += delta_time;
	if (time_passed > .25) {
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
	bool is_on_ground;
	one_to_four = rand() % 4;
	if (one_to_four == 0) {
		start_x = 0;
		start_y = rand() % (window.window_height + 1);
		std::cout << start_x << ":" << start_y << std::endl;
	}
	else if (one_to_four == 1) {
		start_x = window.window_width;
		start_y = rand() % (window.window_height + 1);
		std::cout << start_x << ":" << start_y << std::endl;
	}
	else if (one_to_four == 2) {
		start_x = rand() % (window.window_width + 1);
		start_y = 0;
		std::cout << start_x << ":" << start_y << std::endl;
	}
	else {
		start_x = rand() % (window.window_width + 1);
		start_y = window.window_height + 1;
		std::cout << start_x << ":" << start_y << std::endl;
	}

	projectile_speed = rand() % 100 + 100;

	end_x = 1 + (rand() % (window.window_width - 1));
	end_y = 1 + (rand() % (window.window_height - 1));

	is_on_ground = rand() % 2;

	Projectile* projectile = new Projectile();
	if (is_on_ground) {
		projectile->createProjectile(start_x, start_y, end_x, end_y, TextureManager::load("./PNG/GroundBullet.png"), projectile_speed, is_on_ground);
	}
	else {
		projectile->createProjectile(start_x, start_y, end_x, end_y, TextureManager::load("./PNG/SkyBullet.png"), projectile_speed, is_on_ground);
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
			if ((*projectile)->info.is_on_ground == true && !player.is_moving && player.playerHit((*projectile)->collider)) {
				delete* projectile;
				projectile = projectile_list.erase(projectile);
				std::cout << "Player Hit" << std::endl;
			}
			else if ((*projectile)->info.is_on_ground == false && player.is_moving && player.playerHit((*projectile)->collider)) {
				delete* projectile;
				projectile = projectile_list.erase(projectile);
				std::cout << "Player Hit" << std::endl;
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