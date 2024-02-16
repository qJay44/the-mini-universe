#include "pch.h"
#include "RandNumGenerator.hpp"

struct StarSystem : sf::CircleShape {
  StarSystem(sf::Vector2i pos, sf::Vector2i offset) {
    uint32_t offsetPosX = pos.x + offset.x;
    uint32_t offsetPosY = pos.y + offset.y;
    RandNumGenerator rng{(offsetPosX & 0xffff) << 16 | (offsetPosY & 0xffff)};

    if (rng.generate(0, 20) == 1) {
      setPosition(pos.x * 16 + 8, pos.y * 16 + 8);
      setFillColor(sf::Color(starColors[rng.generate(0, 8)]));
      setRadius(rng.generate(10.f, 40.f) / 8.f);
    }
  }

private:
  static constexpr uint32_t starColors[8] = {
    0xffffffff, 0xffd9ffff, 0xffa3ffff, 0xffffc8c8,
    0xffffcb9d, 0xff9f9fff, 0xff415eff, 0xff28199d
  };
};

