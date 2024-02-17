#include "pch.h"
#include "StarSystem.hpp"

#define WIDTH 1200
#define HEIGHT 720

int main() {
  sf::RenderWindow window;
  sf::Vector2i universeOffset{0, 0};
  sf::Vector2i mouseSector = sf::Mouse::getPosition(window) / 16;
  sf::Vector2i mouseSectorOffset = mouseSector + universeOffset;

  bool bStarSelected = false;
  sf::Vector2i vStarSelected{0, 0};

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Mini universe", sf::Style::Close);
  window.setFramerateLimit(90);

  constexpr int sectorsX = WIDTH / 16;
  constexpr int sectorsY = HEIGHT / 16;

  while (window.isOpen()) {
    sf::Event event;
    mouseSector = sf::Mouse::getPosition(window) / 16;
    mouseSectorOffset = mouseSector + universeOffset;

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
      if (event.type == sf::Event::MouseButtonPressed) {
        StarSystem starSystem(mouseSectorOffset.x, mouseSector.y);

        bStarSelected = bool(starSystem);
        vStarSelected = mouseSectorOffset;
      }
    }

    // Don't really know how to make it smooth with floating point values
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) universeOffset.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) universeOffset.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) universeOffset.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) universeOffset.x += 1;


    window.clear();

    for (uint32_t x = 0; x < sectorsX; x++) {
      for (uint32_t y = 0; y < sectorsY; y++) {
        StarSystem starSystem(x + universeOffset.x, y + universeOffset.y);

        if(starSystem) {
          sf::CircleShape starCircle(starSystem.createStarShape(x, y));
          // Creating another circle shape to make spacing between the outline and a star
          sf::CircleShape starCircleOutline(starCircle);

          if (mouseSector.x == x && mouseSector.y == y) {
            starCircleOutline.setFillColor(sf::Color::Transparent);
            starCircleOutline.setOutlineColor(sf::Color::Yellow);
            starCircleOutline.setOutlineThickness(1.f);
            starCircleOutline.setRadius(12.f);
            starCircleOutline.setOrigin(12.f, 12.f);
          }

          window.draw(starCircle);
          window.draw(starCircleOutline);
        }
      }
    }

    window.display();
  }

  return 0;
}

