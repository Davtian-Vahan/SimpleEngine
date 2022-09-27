#include "Game.h"
#include "mathdefs.h"
#include <chrono>
#include <thread>
#include <ctime>

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
	SpawnShapes();

}

// Spawns random amount of shapes, at random *clamped locations
void Game::SpawnShapes()
{
	int shape_count = 4 + rand() % 15; // random number of shapes to be spawned
	for (int it = 0; it < shape_count; ++it)
	{
		float rand_radius = 5 + rand() % 30;

		sf::CircleShape* new_shape = new sf::CircleShape(rand_radius);
		if (!it) new_shape->setRadius(30.f);
		do
		{
			sf::Vector2f rand_pos = GetRandomPosition();

			new_shape->setPosition(GetPositionClamped(rand_pos));
			// set origin to be center
			new_shape->setOrigin(new_shape->getRadius(), new_shape->getRadius());

		} while (CollisionExists(new_shape));
	


		new_shape->setFillColor(sf::Color(2, 48, 32));

		Actors.push_back(new_shape);
	}

	ControlledActor = Actors.front();
}

// Generic clamped position, collision not checked yet
sf::Vector2f Game::GetPositionClamped(const sf::Vector2f& new_pos)
{
	sf::Vector2f res_pos = new_pos;

	if (res_pos.x > video_mode.width) res_pos.x = 0;
	if (res_pos.x < 0) res_pos.x = video_mode.width;

	if (res_pos.y > video_mode.height) res_pos.y = 0;
	if (res_pos.y < 0) res_pos.y = video_mode.height;

	return res_pos;
}

// Generic move, collision not checked yet
void Game::TryMove(sf::Shape* Actor, sf::Vector2f offset)
{
	sf::Vector2f CachedPos = Actor->getPosition();
	sf::Vector2f ResultPos = GetPositionClamped(Actor->getPosition() + offset);

	Actor->setPosition(ResultPos);

	sf::CircleShape* MyActor = dynamic_cast<sf::CircleShape*>(Actor);
	sf::CircleShape* CollidedActor = dynamic_cast<sf::CircleShape*>(CollisionExists(Actor));

	if (CollidedActor)
	{
		// if im not bigger than enemy, block collision
		if (MyActor->getRadius() < CollidedActor->getRadius())
		{
			Actor->setPosition(CachedPos);
			return;
		}

		// Eat collided actor
		Actors.remove(CollidedActor);

		// Play getting bigger animation
		float radius_sum = MyActor->getRadius() + CollidedActor->getRadius();
		float radius_iter_anim = MyActor->getRadius();

		while (radius_iter_anim < radius_sum)
		{
			MyActor->setRadius(radius_iter_anim);
			Draw();
			Show();
			radius_iter_anim += 1.f;

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		
		delete CollidedActor;
	}
}

// Return if given actor collides with any other known actor
sf::Shape * Game::CollisionExists(sf::Shape * Actor)
{
	// Checks for circle collision only for now
	for (sf::Shape* IterActor : Actors)
	{
		sf::CircleShape* C1 = dynamic_cast<sf::CircleShape*>(Actor);
		sf::CircleShape* C2 = dynamic_cast<sf::CircleShape*>(IterActor);

		// no collision with itself
		if (C1 == C2) { continue; }

		const sf::Vector2f  center_a = C1->getPosition();
		const sf::Vector2f  center_b = C2->getPosition();

		const float radius_a = C1->getRadius();
		const float radius_b = C2->getRadius();

		if (circle_collision(center_a, center_b, radius_a, radius_b))
		{
			return C2;
		}
	}

	return nullptr;
}

// Checks collision between two circles
bool Game::circle_collision(sf::Vector2f a, sf::Vector2f b, float r1, float r2)
{
	// if r1 + r2 <= dist(c1, c2)
	// (x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
	float part1 = SQR((b.x - a.x)) + SQR((b.y - a.y));
	float part2 = SQR((r1 + r2));
	return part1 <= part2;
}

// Returns distance between 2 vectors (SFML didn't bother)
float Game::vector_distance(sf::Vector2f vec_1, sf::Vector2f vec_2)
{
	return std::sqrt(SQR(vec_2.x - vec_1.x) + SQR(vec_2.y - vec_1.y));
}

// Returns a random non clamped position on the screen
sf::Vector2f Game::GetRandomPosition()
{
	return sf::Vector2f(rand() % video_mode.width, rand() % video_mode.height);
}

// Frame updater
bool Game::Update()
{
	if (!render_window.isOpen()) return false;
	PollEvent();
	Draw();
	Show();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return true;
}

// Draw each frame
void Game::Draw()
{
	// clear and draw
	render_window.clear(sf::Color(128, 128, 128));

	for (sf::Shape* Actor : Actors)
	{
		render_window.draw(*Actor);
	}
}

// Poll each frame
void Game::PollEvent()
{
	sf::Vector2f displace{ 0.f, 0.f };

	sf::Event event;
	while (render_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			render_window.close();
	}
	
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
	

	TryMove(ControlledActor, displace);
}

void Game::Show()
{
	render_window.display();
}

Game::~Game()
{
	for (const sf::Shape* Actor : Actors)
	{
		delete Actor;
	}
}