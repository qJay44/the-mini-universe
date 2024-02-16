#include "pch.h"
#include "StarSystem.hpp"

#define WIDTH 1200
#define HEIGHT 720

int main() {
  sf::RenderWindow window;
  sf::Vector2i universeOffset{0, 0};

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Mini universe", sf::Style::Close);
  window.setFramerateLimit(90);

  constexpr int sectorsX = WIDTH / 16;
  constexpr int sectorsY = HEIGHT / 16;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyReleased)
        switch (event.key.code) {
          case sf::Keyboard::Q:
            window.close();
            break;
          default:
            break;
        }
    }

    // Don't really know how to make it smooth with floating point values
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) universeOffset.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) universeOffset.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) universeOffset.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) universeOffset.x += 1;

    window.clear();

    for (int x = 0; x < sectorsX; x++)
      for (int y = 0; y < sectorsY; y++)
        window.draw(StarSystem({x, y}, universeOffset));

    window.display();
  }

  return 0;
}

