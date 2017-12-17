
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "marduinotypes.h"

#ifndef TILEMAP_H
#define TILEMAP_H

class TileMap {

private:

	TILEMAPSET * _tileMapID;
	unsigned int _tileWidth;
	unsigned int _tileHeight;
	unsigned int _tileMapWidth;
	unsigned int _tileMapHeight;
	Adafruit_ST7735 * _tft; //pointer to tft 

public:

	TileMap();
	void getTileIndexByPos(int, int, int *);
	void getPosByTileIndex(int, int, int *);
        unsigned int getMapWidth();
        unsigned int getMapHeight();
        unsigned int getTileWidth();
        unsigned int getTileHeight();
	void settftPointer(Adafruit_ST7735 *); //using Adafruit tft
	void setMapSize(unsigned int, unsigned int);
	void setTileSize(unsigned int, unsigned int);
	void setTileMap(TILEMAPSET *);
	void drawTile(const unsigned int, int, int);
	void drawMap(int, int);

};

#endif
