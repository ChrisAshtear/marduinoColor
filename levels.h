
#include "marduinotypes.h"

#ifndef LEVELS_H
#define LEVELS_H

const int CollisionMap0Size = 15;
const int CollisionMap1Size = 23;//23

COLMAP CollisionMap0[] = {
 0, 40, 120, 8,
120, 32, 48, 8,
184, 32, 24, 8,
232, 24, 24, 8,
280, 24, 16, 8,
312, 16, 24, 8,
352, 24, 16, 8,
384, 40, 128, 8,
528, 32, 16, 8,
560, 24, 48, 8,
560,32, 8, 16,
600, 32, 8, 16,
624, 32, 24, 8,
680, 40, 120, 8,
472, 32, 16, 8 };

TILEMAPSET CollisionMap1[] = {
  0,48,80,40,
  112,64,128,24,
  136,48,16,16,
  256,80,64,8,
  336,80,88,8,
  472,56,40,8,
  656,48,24,8,
  552,72,16,16,
  592,64,16,24,
  624,56,16,32,
  736,80,64,8,
  456,80,72,8,
  184,56,16,8,
  224,48,16,16,
  256,32,8,8,
  280,40,8,8,
  304,24,8,8,
  336,24,32,8,
  352,48,48,8,
  392,8,8,40,
  688,32,24,8,
  736,32,24,8,
  776,32,24,8
};

ENEMY EnemyMap1[] = {
  168,40,
  216,40,
  296,64,
  392,56,
  496,32,
  784,8
};

/*TILEMAPSET TileMap0[] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,162,1,163,1,
1,1,1,1,1,1,1,145,146,1,1,1,1,1,1,145,146,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,162,163,162,163,162,163,1,1,1,1,162,163,1,1,1,1,1,1,1,1,1,1,1,1,162,1,1,1,163,
1,1,1,1,1,1,1,161,1,1,1,145,146,1,1,161,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,11,11,11,1,1,1,1,1,1,145,146,1,1,1,162,163,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,162,1,1,163,162,1,1,163,162,163,162,1,1,163,1,1,162,163,1,1,162,163,1,1,162,1,1,1,1,1,
1,1,1,1,1,1,1,161,1,145,146,161,1,1,1,161,1,1,162,163,1,1,1,1,1,1,1,1,1,2,3,4,1,1,1,11,11,1,1,1,1,1,1,1,11,11,1,1,161,1,1,1,162,1,1,163,162,163,1,1,1,1,145,146,1,1,1,1,1,162,11,11,11,11,11,11,1,1,163,162,1,1,1,1,163,162,1,1,163,162,1,1,163,162,1,1,1,102,103,1,
1,1,1,1,1,1,1,161,1,161,1,161,1,1,1,76,77,77,77,77,78,1,1,2,3,4,1,1,1,1,14,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,161,1,1,162,1,1,1,1,163,1,163,55,56,1,161,1,1,1,11,11,162,1,11,1,162,1,1,11,1,1,2,3,4,1,1,1,1,163,1,1,162,1,1,1,1,163,162,163,1,118,119,1,
77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,87,87,87,87,87,80,1,1,1,14,1,1,1,1,1,14,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,76,77,77,77,77,77,77,77,77,77,78,71,72,76,77,78,1,1,1,162,1,1,11,162,1,1,1,11,1,162,1,14,1,1,1,1,1,76,77,77,77,77,77,77,77,77,77,77,77,77,77,77

};*/

#define level1Height 64
#define level0Height 40

TILEMAPSET TileMap0[] = {
13,13,13,13,13,13,13,16,17,13,13,13,13,13,13,16,17,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,27,21,13,13,16,17,13,13,27,21,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,9,9,13,13,13,13,13,13,16,17,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,27,21,16,17,27,21,13,13,27,21,13,28,29,13,13,13,13,13,13,13,13,13,0,1,2,13,13,13,9,9,13,13,13,13,13,13,13,9,9,13,13,27,21,13,13,13,19,20,13,13,13,13,13,13,13,16,17,13,13,13,13,13,13,9,9,9,9,9,9,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,11,12,13,
13,13,13,13,13,13,13,27,21,27,21,27,21,13,13,7,8,8,8,8,18,13,13,0,1,2,13,13,13,13,6,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,27,21,13,13,13,30,31,32,13,13,13,14,15,13,27,21,13,13,9,9,13,13,9,13,13,13,13,9,13,13,0,1,2,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,22,23,13,
7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,24,24,24,24,24,24,13,13,13,6,13,13,13,13,13,6,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,7,8,8,8,8,8,8,8,8,8,18,25,26,8,8,18,13,13,13,13,13,13,9,13,13,13,13,9,13,13,13,6,13,13,13,13,13,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};


TILEMAPSET TileMap1[] = {
13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,16,17,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,27,21,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,13,13,13,9,9,10,9,13,13,13,9,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,27,21,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,16,17,13,13,16,17,13,13,13,13,13,9,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,13,13,13,13,13,13,13,16,17,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,9,9,13,13,13,9,9,9,13,13,9,9,9,
13,13,28,29,27,21,14,15,13,13,13,13,13,13,13,13,13,13,13,13,13,27,21,13,13,27,21,13,13,13,13,13,13,13,13,9,13,13,13,13,13,13,13,13,13,13,13,13,13,9,13,13,13,13,13,13,13,27,21,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
7,8,8,8,8,18,25,26,7,18,13,13,13,13,13,13,13,14,15,13,13,27,21,13,13,27,21,13,14,15,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,9,9,9,9,9,13,13,13,13,13,13,13,27,21,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,9,9,13,13,13,13,13,13,13,16,17,13,13,13,13,13,13,
24,24,24,24,24,24,25,26,24,24,13,13,13,13,13,13,13,25,26,28,29,27,21,14,15,27,21,13,25,26,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,27,21,9,10,9,9,9,13,13,13,13,13,13,13,13,13,13,13,13,13,13,14,15,13,13,13,13,13,13,13,13,13,13,13,13,27,21,13,13,13,13,13,13,
24,24,24,24,24,24,25,26,24,24,13,13,13,13,7,8,8,25,26,7,8,8,18,25,26,7,8,18,25,26,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,27,21,13,13,19,20,13,13,13,13,13,13,13,13,13,13,13,14,15,13,13,25,26,13,13,13,13,13,13,13,13,13,13,13,13,27,21,13,13,13,11,12,13,
24,24,24,24,24,24,25,26,24,24,13,13,13,13,24,24,24,25,26,24,24,24,24,25,26,24,24,24,25,26,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,27,21,13,13,30,31,32,13,13,13,13,13,14,15,13,13,13,25,26,13,13,25,26,13,13,13,13,13,13,13,13,13,13,13,13,27,21,28,29,13,22,23,13,
24,24,24,24,24,24,25,26,24,24,13,13,13,13,24,24,24,25,26,24,24,24,24,25,26,24,24,24,25,26,13,13,9,9,9,9,9,9,9,9,13,13,3,4,4,4,4,4,4,4,4,4,5,13,13,13,13,7,8,8,8,8,8,8,8,18,13,13,13,25,26,13,13,13,25,26,13,13,25,26,13,13,13,13,13,13,13,13,13,13,13,13,7,8,8,8,8,8,8,18
};


#endif
