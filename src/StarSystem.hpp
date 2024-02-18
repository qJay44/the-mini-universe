#include "RandNumGenerator.hpp"
#include <list>
#include <stdint.h>
#include <vector>

class StarSystem {
  static constexpr uint32_t starColors[8] = {
    0xffffffff, 0xffd9ffff, 0xffa3ffff, 0xffffc8c8,
    0xffffcb9d, 0xff9f9fff, 0xff415eff, 0xff28199d
  };

  struct Star {
    bool exists;
    sf::Vector2f position;
    uint32_t color;
    float radius;
  };

  struct Planet {
    float distance = 0.f;
    float diameter = 0.f;
    float foliage = 0.f;
    float minerals = 0.f;
    float water = 0.f;
    float gases = 0.f;
    float temperature = 0.f;
    float population = 0.f;
    bool ring = false;
    std::vector<float> moons; // Moons sizes
  };

  Star star;
  std::vector<Planet> planets;

public:
  StarSystem(uint32_t x, uint32_t y, bool fullSystem = false) {
    RandNumGenerator rng{(x & 0xffff) << 16 | (y & 0xffff)};
    star.exists = rng.generate(0, 20) == 1;

    if (star.exists) {
      star.position = sf::Vector2f(x * 16 + 8, y * 16 + 8);
      star.color = starColors[rng.generate(0, 8)];
      star.radius = rng.generate(10.f, 40.f) / 8.f;
    }

    if (fullSystem) {
      float distanceFromStar = rng.generate(60.f, 200.f);
      for (int i = 0; i < rng.generate(0, 10); i++) {
        Planet p;
        p.distance = distanceFromStar;
        distanceFromStar += rng.generate(20.f, 200.f);
        p.diameter = rng.generate(4.f, 20.f);
        p.temperature = rng.generate(-200.f, 300.f);

        p.foliage  = rng.generate(0.f, 1.f);
        p.minerals = rng.generate(0.f, 1.f);
        p.gases    = rng.generate(0.f, 1.f);
        p.water    = rng.generate(0.f, 1.f);

        float sum = 1.f / (p.foliage + p.minerals + p.gases + p.water);
        p.foliage  *= sum;
        p.minerals *= sum;
        p.gases    *= sum;
        p.water    *= sum;

        p.population = std::max(rng.generate(-50000000, 20000000), 0);
        p.ring = rng.generate(0, 10) == 1;
        for (int i = 0; i < std::max(rng.generate(-5, 5), 0); i++)
          p.moons.push_back(rng.generate(1.f, 5.f));

        planets.push_back(p);
      }
    };
  }

  explicit operator bool() {
    return star.exists;
  }

  // Simply create drawable star
  sf::CircleShape createStarShape(uint32_t x, uint32_t y) const {
    sf::CircleShape cs(star.radius);
    cs.setPosition(x * 16 + 8, y * 16 + 8);
    cs.setFillColor(sf::Color(star.color));
    cs.setOrigin(star.radius, star.radius);

    return cs;
  }

  // Create drawable of every body of the system for the star system window
  std::list<sf::CircleShape> createSystemShapes(sf::Vector2f initAreaPos, sf::Vector2f initAreaSize) const {
    std::list<sf::CircleShape> shapesList;
    sf::Vector2f body{initAreaPos.x + initAreaSize.x * 0.1f, initAreaPos.y + initAreaSize.y * 0.5f};
    float r = star.radius * 12.f;
    body.x += r;

    // The star
    sf::CircleShape s(r);
    s.setFillColor(sf::Color(star.color));
    s.setPosition(body);
    s.setOrigin(r, r);
    shapesList.push_back(s);
    body.x += r + 8.f;

    // The planets
    for (const Planet& planet : planets) {
      body.x += planet.diameter;
      sf::CircleShape p(planet.diameter);
      p.setFillColor(sf::Color::Green);
      p.setPosition(body);
      p.setOrigin(planet.diameter, planet.diameter);
      shapesList.push_back(p);

      // The moons
      sf::Vector2f moonBody = body;
      moonBody.y += planet.diameter + 10.f;
      for (const float& moon : planet.moons) {
        moonBody.y += moon;
        sf::CircleShape m(moon);
        m.setFillColor(sf::Color(0x272727ff));
        m.setPosition(moonBody);
        m.setOrigin(moon, moon);
        shapesList.push_back(m);
        moonBody.y += moon + 10.f;
      }

      body.x += planet.diameter + 8.f;
    }

    return shapesList;
  }
};

