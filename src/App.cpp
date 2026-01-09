#include "App.hpp"
#include <cmath>
#include <algorithm>

static void drawThickLine(sf::RenderWindow& window,
                          sf::Vector2f a, sf::Vector2f b,
                          float thickness, sf::Color color)
{
	const sf::Vector2f d = b - a;
	const float len = std::sqrt(d.x * d.x + d.y * d.y);
	if (len <= 0.0001f) return;

	sf::RectangleShape line({len, thickness});
	line.setFillColor(color);
	line.setOrigin({0.f, thickness / 2.f});
	line.setPosition(a);
	line.setRotation(sf::degrees(std::atan2f(d.y, d.x) * 180.f / 3.14159265f));
	window.draw(line);
}

static void drawX(sf::RenderWindow& window, sf::FloatRect rect)
{
	const float pad = std::min(rect.size.x, rect.size.y) * 0.18f;
	const float t   = std::min(rect.size.x, rect.size.y) * 0.08f;

	const sf::Vector2f a(rect.position.x + pad,               rect.position.y + pad);
	const sf::Vector2f b(rect.position.x + rect.size.x - pad, rect.position.y + rect.size.y - pad);
	const sf::Vector2f c(rect.position.x + rect.size.x - pad, rect.position.y + pad);
	const sf::Vector2f d(rect.position.x + pad,               rect.position.y + rect.size.y - pad);

	drawThickLine(window, a, b, t, sf::Color(235,235,235));
	drawThickLine(window, c, d, t, sf::Color(235,235,235));
}

static void drawO(sf::RenderWindow& window, sf::FloatRect rect)
{
	const float pad = std::min(rect.size.x, rect.size.y) * 0.18f;
	const float t   = std::min(rect.size.x, rect.size.y) * 0.08f;

	const float r = (std::min(rect.size.x, rect.size.y) / 2.f) - pad;

	sf::CircleShape circle(r);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(t);
	circle.setOutlineColor(sf::Color(235,235,235));
	circle.setPosition({rect.position.x + rect.size.x/2.f - r, rect.position.y + rect.size.y/2.f - r});

	window.draw(circle);
}


static const char* playerName(Cell p) {
	return (p == Cell::X) ? "X" : "O";
}

static std::string makeTitle(const Game& game) {
	switch (game.state()) {
		case GameState::Playing:
			return std::string("TicTacToe - Turn: ") + playerName(game.currentPlayer());
		case GameState::X_wins:
			return "TicTacToe - X wins!";
		case GameState::O_wins:
			return "TicTacToe - O wins!";
		case GameState::Draw:
			return "TicTacToe - Draw!";
	}
	return "TicTacToe";
}

App::App()
: window(sf::VideoMode(sf::Vector2u{800, 600}), "SFML Template")
{
	window.setVerticalSyncEnabled(true);
}

void App::run() {
	window.setTitle(makeTitle(game));
	while (window.isOpen()) {
		handleEvents();

		const float dt = frameClock.restart().asSeconds();
		if (!paused) update(dt);

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
				if (game.state() != GameState::Playing) {
					game.reset();
					window.setTitle(makeTitle(game));
				}
			}
		}

		// mouse click
		if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (game.state() != GameState::Playing) continue;

			if (mouse->button == sf::Mouse::Button::Left) {
				
				const float W = static_cast<float>(window.getSize().x);
				const float H = static_cast<float>(window.getSize().y);

				const float x = static_cast<float>(mouse->position.x);
				const float y = static_cast<float>(mouse->position.y);

				const int row = static_cast<int>(y / (H/3.f));
				const int col = static_cast<int>(x / (W/3.f));

				if (game.handleMove(row, col)) {
					window.setTitle(makeTitle(game));
				}
			}
		}
	}
}

void App::update(float /*dt*/) {
	// future simulation logic
}

void App::render() {
	window.clear(sf::Color(30, 30, 30));

	const float W = static_cast<float>(window.getSize().x);
	const float H = static_cast<float>(window.getSize().y);

	// Lines

	sf::VertexArray lines(sf::PrimitiveType::Lines, 8);

	auto setLine = [&](int idx, sf::Vector2f a, sf::Vector2f b) {
		lines [idx*2].position = a;
		lines [idx*2+1].position = b;
	};

	setLine( 0, {W/3.f, 0.f},    {W/3.f, H}    );
	setLine( 1, {2*W/3.f, 0.f},  {2*W/3.f, H}  );
	setLine( 2, {0.f, H/3.f},    {W, H/3.f}    );
	setLine( 3, {0.f, 2*H/3.f},  {W, 2*H/3.f}  );

	window.draw(lines);

	// X and O

	const float cellW = W / 3.f;
	const float cellH = H / 3.f;

	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			Cell cell = game.board().at(r, c);
			if (cell == Cell::Empty) continue;

			sf::FloatRect rect({c * cellW, r * cellH}, {cellW, cellH});

			if (cell == Cell::X) drawX(window, rect);
			else if (cell == Cell::O) drawO(window, rect);
		}
	}

	// todo
	// Game Over

	window.display();
}
