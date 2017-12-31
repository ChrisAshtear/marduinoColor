
//#include <avr/pgmspace.h>

#ifndef MARDUINOTYPES_H
#define MARDUINOTYPES_H

//#define BMP const unsigned char PROGMEM
//#define TILEMAPSET const unsigned int PROGMEM

typedef const unsigned char PROGMEM BMP;
typedef const unsigned int PROGMEM TILEMAPSET;
typedef const uint8_t PROGMEM COLORIDX;
typedef const uint16_t PROGMEM PAL;
typedef const uint16_t PROGMEM ENEMY;

struct Vector2f {
float x;
float y;

Vector2f(float xx, float yy) {
  x = xx;
  y = yy;
};

};

#endif
