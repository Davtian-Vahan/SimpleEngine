#include "Game.h"
#include <vector>
#include <chrono>
#include <thread>

int Game::Run(const size_t window_height, const size_t window_width)
{
	Game* game_instance = new Game(sf::VideoMode(window_height, window_width));
	// main loop
	while (game_instance->Update()) {}
	delete game_instance;
	return 1;
}

Game::Game(const sf::VideoMode& in_videomode)
	: render_window(in_videomode, ""),
	video_mode(in_videomode)
{
	// Test object inits
	RectActor = sf::RectangleShape({ 50, 50 });
	RectActor.setPosition(video_mode.width / 2.f, video_mode.height / 2.f);
	RectActor.setFillColor(sf::Color::Red);

}

bool Game::Update()
{
	if (!render_window.isOpen()) return false;

	PollEvent();
	Draw();
	Show();

	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	return true;
}

void Game::Draw()
{
	// clear and draw
	render_window.clear(sf::Color::White);
	render_window.draw(RectActor);
}

void Game::PollEvent()
{
	sf::Vector2f displace{ 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		displace.x -= 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		displace.x += 10;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		displace.y -= 10;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		displace.y += 10;
	}

	RectActor.move(displace);
}

void Game::Show()
{
	render_window.display();
}
