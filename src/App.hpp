#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"

class App {
public:
  App();
  void run();

private:
  void handleEvents();
  void update(float dt);
  void render();

  sf::RenderWindow window;
  sf::Clock frameClock;
  bool paused = false;

  Game game;
};
