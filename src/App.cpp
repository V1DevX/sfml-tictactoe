#include "App.hpp"

App::App()
: window(sf::VideoMode(sf::Vector2u{800, 600}), "SFML Template")
{
	window.setVerticalSyncEnabled(true);
}

void App::run() {
	while (window.isOpen()) {
		handleEvents();

		const float dt = frameClock.restart().asSeconds();
		if (!paused)
			update(dt);

		render();
	}
}

void App::handleEvents() {
	while (auto event = window.pollEvent()) {

		// close event
		if (event->is<sf::Event::Closed>()) {
			window.close();
			continue;
		}

		// key pressed
		if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
			if (keyEvent->code == sf::Keyboard::Key::Escape) {
				window.close();
			}
			else if (keyEvent->code == sf::Keyboard::Key::Space) {
				paused = !paused;
			}
		}
	}
}

void App::update(float /*dt*/) {
	// future simulation logic
}

void App::render() {
	window.clear(sf::Color(30, 30, 30));
	window.display();
}
