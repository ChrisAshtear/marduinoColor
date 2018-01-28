

#include "tilemap.h"
#include "tilesetbitmap.h"
#include "levels.h"

#define MAP_HEIGHT 40
//96 is in pixels, 12 in tiles
//MONOCHROME BG layer?

  TileMap::TileMap() {
        _tileMapWidth = 1;
        _tileMapHeight = 1;
        _tileWidth = 8;
        _tileHeight = 8;
        _tileMapID = NULL;
  }

	void TileMap::getTileIndexByPos(int coordx, int coordy, int * pickedTile) {
		pickedTile[0] = coordx / _tileWidth;
		pickedTile[1] = coordy / _tileHeight;
	}

	void TileMap::getPosByTileIndex(int tilex, int tiley, int * result) {
		result[0] = tilex*_tileWidth;
		result[1] = tiley*_tileHeight;
	}

  unsigned int TileMap::getMapWidth() {
          return _tileMapWidth;
  }
  
  unsigned int TileMap::getMapHeight() {
          return _tileMapHeight; 
  }
  
  unsigned int TileMap::getTileWidth() {
          return _tileWidth;        
  }
  
  unsigned int TileMap::getTileHeight() {
          return _tileHeight;
  }

	void TileMap::settftPointer(Adafruit_ST7735 * disp) {
		_tft = disp;
	}

	void TileMap::setTileSize(unsigned int w, unsigned int h) {
		_tileWidth = w;
		_tileHeight = h;
	}

	void TileMap::setMapSize(unsigned int w, unsigned int h) {
		_tileMapWidth = w;
		_tileMapHeight = h;
	}

	void TileMap::setTileMap(TILEMAPSET * tilemaparray) {
		_tileMapID = tilemaparray;		
	}

	void TileMap::drawTile(const unsigned int id, int x, int y) {
    int16_t setWidth = TILESETW;
    int16_t setHeight = TILESETH;
      //_tft->drawCBMPsection(x,y,_tileWidth,_tileHeight,tileSet,tilePal,setWidth,setHeight,id,false,false,4);
      _tft->drawCBMPsectionRLE(x,y,_tileWidth,_tileHeight,tileSet,tsLoc,tilePal,setWidth,setHeight,id,false,false);
      //const unsigned char *tilePtr[_tileHeight * _tileHeight]= {tileSet+((_tileHeight * _tileHeight)*id)};
      //_tft->drawFastColorBitmap(x, y,_tileWidth,_tileHeight,*tilePtr,tilePal);
			//_tft->drawFastBitmap(x, y, tileToDraw, _tileWidth,_tileHeight,1,ST7735_WHITE);
      //_tft->drawSurface(x, y, tileToDraw, _tileWidth,_tileHeight,1,ST7735_WHITE);
      //_tft->drawBitmap(x, y, tileToDraw, _tileWidth,_tileHeight,1);
	}
	
	void TileMap::drawMap(int xcamera, int ycamera) {

    uint8_t yOffset = 32;
		//define tile x and y index iterator
		int it_start[2] = {0,0};
		int it_end[2] = {1,1};
    int mapHeight = _tft->height();
    if(_tft->height() > MAP_HEIGHT)
    {
      mapHeight = MAP_HEIGHT;
    }
		getTileIndexByPos(xcamera, ycamera, it_start);
		getTileIndexByPos(xcamera+_tft->width()+_tileWidth, ycamera+mapHeight, it_end);

    // reverse camera movement
     xcamera *= -1;
    //_tft->startDraw(0,0,_tft->width()-1,mapHeight-1);
		for (int yy = it_start[1]; yy < it_end[1]; yy++) {
		for (int xx = it_start[0]; xx < it_end[0]; xx++) {

                        
			unsigned int tileIndex = xx + (yy*_tileMapWidth);
      tileIndex = pgm_read_word_near(&_tileMapID[tileIndex]);
      
      if (tileIndex != -1)  
		    drawTile(tileIndex,xcamera+(xx*_tileWidth),yOffset+ycamera+(yy*_tileHeight));
                        //Serial.print(test);
                        //Serial.print("\n");    // prints a tab

		}
		}		
	  //_tft->endDraw();
	}

 /*void TileMap::createCollisionMap() {
  
   //_mapCollider = new Rect[_tileMapWidth*_tileMapHeight];

                for (int yy = 0; yy < _tileMapHeight; yy++) {
    for (int xx = 0; xx < _tileMapWidth; xx++) {
  
                        unsigned int tileIndex = xx + (yy * _tileMapWidth);
                        tileIndex = pgm_read_word_near(&_tileMapID[tileIndex]);
                        
                        if (tileIndex == 0 || tileIndex == 1 || tileIndex == 144 || tileIndex == 145 || tileIndex == 161 || tileIndex == 162 || tileIndex == 163) {
                        
                             _mapCollider[tileIndex].x = -1;
                             _mapCollider[tileIndex].y = -1;
                             _mapCollider[tileIndex].width = -1;
                             _mapCollider[tileIndex].height = -1;
                        
                        } else {
                 
                             _mapCollider[tileIndex].x = xx*_tileWidth;
                             _mapCollider[tileIndex].y = yy*_tileHeight;
                             _mapCollider[tileIndex].width = _tileWidth;
                             _mapCollider[tileIndex].height = _tileHeight;                        
                        
                        }
  
                }
                }

  };*/
