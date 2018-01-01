
//#include <avr/pgmspace.h>

#ifndef MARDUINOTYPES_H
#define MARDUINOTYPES_H

//#define BMP const unsigned char PROGMEM
//#define TILEMAPSET const unsigned int PROGMEM

typedef const unsigned char PROGMEM BMP;
typedef const uint8_t PROGMEM TILEMAPSET;
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

struct ObjectData {
  uint8_t x;
  uint8_t y;
  const unsigned char * curFrame;
  const unsigned char * frames[];
  uint8_t objState;
  uint8_t curDirection;
  uint8_t lastDirection;

  ObjectData(int xx, int yy, const unsigned char frameIdle,const unsigned char frameRun0, const unsigned char frameRun1, const unsigned char frameJump, const unsigned char frameDeath)
  {
    x= xx;
    y= yy;
    frames[0] = frameIdle;
    frames[1] = frameRun0;
    frames[2] = frameRun1;
    frames[3] = frameJump;
    frames[4] = frameDeath;
    curFrame = frameIdle;
    curDirection = 0;
    lastDirection = 0;
    objState = 0;
  };
};

#endif
