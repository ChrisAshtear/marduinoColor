
//#include <avr/pgmspace.h>

#ifndef MARDUINOTYPES_H
#define MARDUINOTYPES_H

//#define BMP const unsigned char PROGMEM
//#define TILEMAPSET const unsigned int PROGMEM

typedef const unsigned char PROGMEM BMP;
typedef const uint16_t PROGMEM COLMAP;
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
  int16_t x;
  int16_t y;
  uint8_t imgSz;
  const unsigned char * curFrame;
  const unsigned char * frames[5];
  const uint16_t * pal;
  uint8_t state;
  int8_t curDirection;
  int8_t lastDirection;
  boolean onAir = false;
  boolean check_pulo = false;
  float hspd = 0;
  float vspd = 0;
  uint16_t maxRLEsz;

  ObjectData(int xx, int yy, int imgSize, uint16_t maxRLE, const uint16_t objPal, const unsigned char* frameIdle,const unsigned char* frameRun0, const unsigned char* frameRun1, const unsigned char* frameJump, const unsigned char* frameDeath)
  {

    x= xx;
    y= yy;
    imgSz = imgSize;
    pal = objPal;
    frames[0] = frameIdle;
    frames[1] = frameRun0;
    frames[2] = frameRun1;
    frames[3] = frameJump;
    frames[4] = frameDeath;
    curFrame = frameIdle;
    curDirection = 1;
    lastDirection = 0;
    state = 0;
    maxRLEsz = maxRLE;
  };
};

#endif
