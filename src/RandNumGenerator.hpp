#include <stdint.h>

struct RandNumGenerator {
  uint32_t seed = 0;

  uint32_t generate() {
    seed += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)seed * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;

    return m2;
  }

  int generate(int min, int max) {
    return (generate() % (max - min)) + min;
  }

  float generate(float min, float max) {
    return (generate() / (float)(0x7fffffff) * (max - min)) + min;
  }
};

