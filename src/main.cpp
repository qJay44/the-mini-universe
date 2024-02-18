#include "StarSystem.hpp"

#define WIDTH 1200
#define HEIGHT 720
#define HEIGHT_3 (int)(HEIGHT / 3)

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

          if (mouseSector.x == x && mouseSector.y == y) {
            // Creating another circle shape to make spacing between the outline and a star
            sf::CircleShape starCircleOutline(starCircle);
            starCircleOutline.setFillColor(sf::Color::Transparent);
            starCircleOutline.setOutlineColor(sf::Color::Yellow);
            starCircleOutline.setOutlineThickness(1.f);
            starCircleOutline.setRadius(12.f);
            starCircleOutline.setOrigin(12.f, 12.f);

            window.draw(starCircleOutline);
          }

          window.draw(starCircle);
        }
      }
    }

      // Draw a star system window details
    if (bStarSelected) {
      static const sf::Vector2f initAreaPos{1.f, HEIGHT - HEIGHT_3 - 1.f};
      static const sf::Vector2f initAreaSize{WIDTH - 2.f, HEIGHT_3};
      StarSystem starSystem(vStarSelected.x, vStarSelected.y, true);

      // Draw area
      // Setting offset of 1 from every side to make the outline visible
      sf::RectangleShape area(initAreaSize);
      area.setPosition(initAreaPos);
      area.setFillColor(sf::Color(0x101010ff));
      area.setOutlineColor(sf::Color(0x505050ff));
      area.setOutlineThickness(1.f);
      window.draw(area);

      // Draw the system bodies
      for (const sf::CircleShape& c : starSystem.createSystemShapes(initAreaPos, initAreaSize))
        window.draw(c);
    }

    window.display();
  }

  return 0;
}

