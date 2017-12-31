/*
 * Super Marduino
 * A platform game with Arduino Uno.
 * 
 * Requirements:
 * Nokia 5510 tft and three buttons.
 * Additional libraries: Adafruit GFX and Adafruit_PCD8544.
 * 
 * Created by Tobias Beise Ulrich
 * http://tobiasbu.github.io/website 
 * 
 * GitHub:
 * https://github.com/tobiasbu/marduino
 * 
 * 2014-2016.
 * 
 * -------------------------------------
 * LAST UPDATE: 15/06/2016
 * Header information update.
 * 
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
//#include "Adafruit_ILI9341.h"
#include <Adafruit_ST7735.h>

#define TFT_DC 8
#define TFT_CS 10
#define TFT_RST 9

// Color definitions
#define  ST7735_BLACK           0x0000
#define ST7735_WHITE           0xFFFF

#include "marduinotypes.h"
#include "tilemap.h"
#include "mariobitmap.h"
#include "levels.h"
#include "tilesetbitmap.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
TileMap gameTilemap;

#define DELAY 75 // delay for fixed update interval 
#define P_STILL 0
#define P_MOVE 1
#define P_JUMP 2
#define P_DEAD 3

#define GAME_INTRO 100
#define GAME_TITLE 101
#define GAME_CREDITS 102
#define GAME_LEVEL 103
#define GAME_PLAY 104
#define GAME_GAMEOVER 105

#define PIN_BUTTON_LEFT 5
#define PIN_BUTTON_SELECT 6
#define PIN_BUTTON_RIGHT 7

#define PIN_SPEAKER 12


unsigned int gamestate = GAME_INTRO; // game state
long TIMER_PREV = 0; // timer 
unsigned long TIMER_CURRENT = 0;
//mario img
int const pimagew = 16;
int const pimageh = 16;
//marduino settings
int player_state = P_STILL; //player state 
int player_direction = 1;
int last_direction = 1;
int life = 3;
long playertimer = 0;
long playertimer_prev = 0;
//posicao do mario
Vector2f player_position(0,tft.height()-pimageh-8);
Vector2f player_position2(0,tft.height()-pimageh-8);
Vector2f last_safe_position(0,tft.height()-pimageh-8);

int lastPosY = 0;

int lastFrameX = 0;
int lastFrameY = 0;
//horizontal speed vars
float hspd = 0;
float hspd_speed = 3.0;
//jump vars and gravity control
float grav = 0.6;
float jumpspd = 4.0;
float vspd = 0;
boolean onAir = false;
boolean check_pulo = false;
//animation vars
int frame = 0;
int frameMax = 4;
float frameSpd = 1;
float frameCounter = 0;
boolean animInit = false;
//collision box offset
float pboxoffsetx = 3; 

// camera control
Vector2f camera = {0,0};
Vector2f last_camera = {0,0};
int camera_player_side = 0;


float sign(float x) {

  if (x > 0)
    return 1;
  else if (x < 0)
    return -1;
  
  return 0;
  
};



boolean buttonPressing[] = {false,false,false}; // button is pressing
boolean buttonRelease[] = {false,false,false}; // button is released
boolean buttonPressed[] = {false,false,false}; // button has pressed one time 
boolean buttonPressedCheck[] = {false,false,false};
boolean buttonReleaseCheck[] = {false,false,false};

void inputManager() {

  //input manager in loop || gerenciador de inputs em loop
  
  int p[3];
  p[0] = digitalRead(PIN_BUTTON_LEFT);//LÃª o pino 5
  p[1] = digitalRead(PIN_BUTTON_SELECT);//LÃª o pino 6
  p[2] = digitalRead(PIN_BUTTON_RIGHT);//LÃª o pino 7
  
  for (int i = 0; i < 3; i++) {
  
      if (buttonPressed[i]) { // pressed ok
        buttonPressed[i] = false;
        buttonPressedCheck[i] = true;
      }
      
      if (buttonRelease[i]) { // release ok
        buttonRelease[i] = false;
        buttonReleaseCheck[i] = true;
      }
    
    if (p[i] == LOW) { // arduino check
    
      buttonPressing[i] = true; // pressing button
      
      buttonRelease[i] = false; //turn release off
      buttonReleaseCheck[i] = false;     
    
      if (!buttonPressedCheck[i]) 
        buttonPressed[i] = true;
        
    } else {
      //turn off all
      buttonPressing[i] = false;
      buttonPressed[i] = false;
      buttonPressedCheck[i] = false;
      
      if (!buttonReleaseCheck[i]) //released button!
        buttonRelease[i] = true;
    }
   
  }
 
}


boolean intersectionRect(float * rect1, float * rect2) {
  
  if (rect1[0] < rect2[0] + rect2[2] && rect1[0] + rect1[2] > rect2[0]) {
     if (rect1[1] < rect2[1] + rect2[3] && rect1[3] + rect1[1] > rect2[1]) {
      return true;
    }
  }
  return false;

}

void playerCollisionChecker(float hs, float vs) {

  float playerRect[4] = {player_position.x+pboxoffsetx+hs+camera.x, player_position.y+vs,10,16};
  
  for (int i = 0; i < CollisionMap0Size*4; i += 4) {
  
    float rectTest[] = {pgm_read_word_near(&CollisionMap0[i]), pgm_read_word_near(&CollisionMap0[i+1]), pgm_read_word_near(&CollisionMap0[i+2]), pgm_read_word_near(&CollisionMap0[i+3])};
    
        if (intersectionRect(playerRect,rectTest)) {
          if (hs != 0) {
          
              hspd = (int)hspd;
              player_position.x = (int)player_position.x;
              boolean corrector = false;
    
              while (!corrector) {      
                   
                  playerRect[0] = player_position.x+pboxoffsetx+camera.x+sign(hspd);
                  
                  if (!intersectionRect(playerRect,rectTest))  
                    player_position.x += sign(hspd);
                  else 
                    corrector = true;
              }
              
               hspd = 0;
              
              break;
          }
          
          if (vs != 0) {
             
              vspd = (int)vspd;
              player_position.y = (int)player_position.y;
              boolean correctorY = false;
    
              while (!correctorY) {      
                   
                  playerRect[1] = player_position.y+camera.y+sign(vspd);
                  
                  if (!intersectionRect(playerRect,rectTest))  
                    player_position.y += sign(vspd);
                  else 
                    correctorY = true;
              }
              
               vspd = 0;
               check_pulo = false;
              break;
          }
        }
             
  
  }

}

boolean verifyCollision(float * rect) {

    for (int i = 0; i < CollisionMap0Size*4; i += 4) {
  
      float rectTest[4] = {pgm_read_word_near(&CollisionMap0[i]), pgm_read_word_near(&CollisionMap0[i+1]), pgm_read_word_near(&CollisionMap0[i+2]), pgm_read_word_near(&CollisionMap0[i+3])};
    
        if (intersectionRect(rect,rectTest)) {
               return true;
        }
        
    }
    
    return false;
}

void playerLogic(boolean move_esq, boolean move_dir, boolean jump) {

  lastFrameX = player_position.x;
  lastFrameY = player_position.y;
  //HORIZONTAL MOVEMENT
//clearSection(player_position.x, player_position.y,pimagew,pimageh);
  if (player_state != P_DEAD) {
  
      hspd = 0;
      boolean moving = false;
     
      if (move_esq == true && move_dir == false) {
          player_direction = 1;
          moving = true;
      } else if (move_dir == true && move_esq == false) {
          player_direction = -1;
          moving = true;
      }
      
      if (moving)
          hspd = hspd_speed * (float)player_direction;
    
      playerCollisionChecker(hspd,0);
      
      player_position2.x += hspd;
      
       if (camera_player_side == -1) {
          if (player_position.x > (tft.width()/2)-10)
            camera_player_side = 0;
          else
            player_position.x += hspd;
    
          // screen limit <
          if (player_position.x < 0) {
            player_position.x = 0;
            hspd = 0;
          }  
    
       } else if (camera_player_side == 1) {
          if (player_position.x < (tft.width()/2)-10)
            camera_player_side = 0;
          else
            player_position.x += hspd;
            
          // screen limit >
          if (player_position.x > tft.width()) {
            gamestate = GAME_TITLE;
            /*player_position.x = tft.width()-pimagew;
            hspd = 0;*/
          }
        }
        
        if (camera_player_side == 0) {
          last_camera.x = camera.x;
          //verify for limit side >
          if (camera.x >= 0 && camera.x <= gameTilemap.getMapWidth()*8-tft.width()) {
            camera.x += hspd;
          } if (camera.x > gameTilemap.getMapWidth()*8-tft.width()) {
            camera_player_side = 1;
            camera.x = gameTilemap.getMapWidth()*8-tft.width();
            player_position.x += hspd;
          } if (camera.x < 0) {
            camera_player_side = -1;
            player_position.x += hspd; 
            camera.x = 0;  
          }
        } 
  
      //VERTICAL MOVEMENT
    
      //gravidade (esta no ar)
     float playerRect[4] = { camera.x+player_position.x+pboxoffsetx,camera.y+player_position.y+1, 10, 16 };
      
      if (!verifyCollision(playerRect)) {
        vspd += grav;
        check_pulo = true;
        onAir = true;
      } else {
        onAir = false;
      }
    
      // checa colisao com chao
      if (vspd != 0) {
          playerCollisionChecker(0,vspd);
      }
      
      if (jump == true && check_pulo == false) {
        vspd -= jumpspd;
        check_pulo = true;  
        tone(PIN_SPEAKER,400,100);
      }
      lastPosY = player_position.y;
      player_position.y += vspd;
      player_position2.y += vspd;
      
      if (vspd == 0 && !onAir) {
          last_direction = player_direction;
          last_camera.x = camera.x;
          last_camera.y = player_position2.y;
          last_safe_position.x = player_position.x;
          last_safe_position.y = player_position.y;
      }
      
      //fall

      if (player_position.y+camera.y > gameTilemap.getMapHeight()*gameTilemap.getTileHeight()) {
          if (player_state != P_DEAD)
              player_state = P_DEAD;
      }
    
    if (player_state != P_DEAD) {
       if (hspd == 0 && vspd == 0) {
        if (player_state != P_STILL) {
          player_state = P_STILL;
          animInit = true;
        }
      } else  if (hspd != 0 && vspd == 0) {
         if (player_state != P_MOVE) {
          player_state = P_MOVE;
          animInit = true;
        }
      } 
      
      if (vspd != 0) {
        if (player_state != P_JUMP) {
          player_state = P_JUMP;
          animInit = true;
         }   
      }
    
      
     }
  } else {
  
   playertimer++; // every DELAY | 1 = 75 millis
    
    if (playertimer > 1000/75) { // 1 sec
    
          playertimer = 0;
          life--;
          
          if (life > 0) {  
            player_position.x = (int)((last_safe_position.x/8)*8);/*+(8*-last_direction);*/
            player_position.y = (int)((last_safe_position.y/8)*8);
            player_position2.x = player_position.x;
            camera.x = (int)((last_camera.x/8)*8);/*+(8*last_direction);*//*-(tft.width()/2)-8;*/
            camera.y = 0;
            player_state = P_STILL;
            vspd = 0;
            hspd = 0;
            check_pulo = false;
        } else {
            gamestate = GAME_GAMEOVER;
        }
   }
  }
  
}

void playerDraw() {
  
  //get size of playerbox & player position, then fill that box with bg color.
  //BMP * frameAtual;
  const unsigned char * frameAtual;
  const unsigned char * idxActual;
  bool flipH = false;
  //animation setup
  if (animInit) {
  
    frame = 0;
    frameCounter = 0;   
    
    if (player_state == P_STILL || player_state == P_JUMP) {
      frameSpd = 0.;
      frameMax = 1; 
    } else if (player_state == P_MOVE) {
      frameSpd = 0.8;
      frameMax = 4;
    }
  
     animInit = false;
  }
  
  //controlador de tempo de frames
  if (frameMax > 1) {
    frameCounter += frameSpd*DELAY;
    
    if (frameCounter > DELAY) {
      frame++;
      frameCounter = 0;
      if (frame > frameMax-1) {
        frame = 0;
      }
    }
  }
  
  //frames manager 
  idxActual = mario0col;
  if (player_state == P_STILL) {
   if (player_direction == 1) 
    flipH = false;
   else
   flipH = true;
  } else if (player_state == P_JUMP) {
    if (player_direction == 1) {
      idxActual = marioJcol;
    }
    else{
      idxActual = marioJcol;
      flipH = true;
    }
  } else if (player_state == P_MOVE) {
    
    if (player_direction == 1) {
      switch (frame) {
        case 0: idxActual = mario1col; break;
        case 1: idxActual = mario0col;break;
        case 2: idxActual = mario2col;break;
        case 3: idxActual = mario0col;break;
      }
    } else {
      flipH = true;
      switch (frame) {
        case 0: idxActual = mario1col; break;
        case 1: idxActual = mario0col; break;
        case 2: idxActual = mario2col; break;
        case 3: idxActual = mario0col; break;
      }
    }
  
  }
  //int yDif = abs(lastPosY - player_position.y);
  
  //
  int yDif = abs(lastFrameY - player_position.y);
  int xDif = abs(lastFrameX - player_position.x);
  int xStart = 0;
  int yStart = 0;
  if(lastFrameX < player_position.x)
  {
    xStart = lastFrameX;
  }
  else
  {
    xStart = player_position.x;
  }
  if(lastFrameY < player_position.y)
  {
    yStart = lastFrameY;
  }
  else
  {
    yStart = player_position.y;
  }
  
  if(lastFrameY != player_position.y && lastFrameX != player_position.y)
  {
    //tft.fillRect(xStart,yStart,xDif+pimagew+1,yDif+pimageh+1,ST7735_WHITE);
  }
  
  
  //tft.drawFastBitmap(player_position.x, player_position.y, frameAtual, pimagew,pimageh,1, ST7735_WHITE);
  tft.drawFastColorBitmap(player_position.x, player_position.y, pimagew,pimageh,idxActual,marioPal,flipH,false);
  // debug collision box
  //tft.fillRect(player_position.x+pboxoffsetx, player_position.y, 10, 16, ST7735_BLACK);

}

int counterGUI = 0;

void drawGui() {

  String stringint = String(life,DEC);
  String string = String("x" + stringint);
  //String stringint = String(counterGUI,DEC);
  //String string = String("time:" + stringint);
  //counterGUI++;
  
  tft.setTextSize(1);
  tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
  tft.setCursor(0,0);
  tft.print(string);

}

void sceneIntro() {
  
  clearScreen(); //clean screen 
  String text = "Regi and Tobi";
  tft.setTextSize(1);
  tft.setTextColor(ST7735_BLACK);
  tft.setCursor((tft.width()-getTextSize(text))/2,tft.height()/2-12);
  tft.print(text);
  text = "presents";
  tft.setCursor((tft.width()-getTextSize(text))/2,tft.height()/2-4);
  tft.print(text);
  //tft.tft(); display.display()?
  inputManager();
  TIMER_CURRENT = millis();
    
   if (TIMER_CURRENT - TIMER_PREV > 2500) { 
      
        TIMER_PREV = TIMER_CURRENT;
        clearScreen();
        gamestate = GAME_TITLE;
   }
}

void sceneTitle() {

    // loop title screen
    float sizex = 14*6;

   int select = 0; 
   int selectMax = 3;
   unsigned int triggerSelect = 0;
   unsigned int counter = 0;
   unsigned int counterMax = 0;

   
  while (gamestate == GAME_TITLE) {

   TIMER_CURRENT = millis();
    
   if (TIMER_CURRENT - TIMER_PREV > DELAY) { 
      
        TIMER_PREV = TIMER_CURRENT;
        
        inputManager();
        
        if (triggerSelect == 0) {
            if (buttonPressed[2]) {
              select++;
              clearScreen();
              if (select >= selectMax) 
                select = 0;
                
            } else if (buttonPressed[0]) {
                  select--;
                  clearScreen();
              if (select < 0)
                select = selectMax-1;    
            }
           
           
           if (buttonPressed[1]) {
            triggerSelect = 1;
            counterMax = 1;
          }
         } 
        
        
       String str = "test";
      
        switch (select) {
          case 0: {str = "< START GAME >"; break;};
          //case 1: {str = "< CREDITS >"; break;};
          //case 2: {str = "< EXIT GAME >"; break;};  
        }
        
        //clearScreen();
        int gameLogoSizeX = 84;
        int gameLogoSizeY = 24;

        //marioLogo - Multiple monochrome layers drawn in color : 89% (25666) | 774bytes
        //marioLogo - 256-color indexed color w/ monochrome mask: 96% (27562) | 2670bytes
        //marioLogo - Monochrome: 88%(25300) | 408 bytes
        //no logo - 24892(86%) 
        
       tft.drawXBitmap((tft.width()-gameLogoSizeX)/2, 0, toplogo, toplogo_width, toplogo_height,ST7735_BLUE);
       tft.drawXBitmap((tft.width()-gameLogoSizeX)/2, toplogo_height, botlogo, botlogo_width, botlogo_height,ST7735_RED);
      // tft.drawXBitmap((tft.width()-gameLogoSizeX)/2, toplogo_height, shadow, shadow_width, shadow_height,ST7735_BLACK);
       //
      //_tft->drawFastColorBitmap(x, y,_tileWidth,_tileHeight,*tilePtr,tilePal);
      //tft.drawCBMPsection(16,64,16,16,mario0col,marioPal,16,16,0,false,true);
       //tft.drawFastColorBitmap(16,16,8,8,tilePtr,tilePal);
     //long time = millis();
      tft.drawCBMPsection(16,64,16,16,mario0col,marioPal,16,16,0,false,true);
      //time = millis() - time;
      //tft.setCursor(64,64);
      //tft.fillRect(64,64,8,8,ST7735_WHITE);
      //tft.println(time,DEC);
      
       
       String output;
       uint8_t test;
       /* for(uint16_t i = 0; i< 8; i++)
        {
          test = pgm_read_byte(&tilePtr[i]);
          output += test;
        }*/
         tft.setCursor((tft.width()-getTextSize(output))/2,tft.height()/2-12);
        tft.println(output);
        tft.setTextSize(1);
        
        if (triggerSelect == 1)
          tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
        else
          tft.setTextColor(ST7735_BLACK);
        
        tft.setCursor((tft.width()-getTextSize(str))/2,24+8);
        tft.print(str);
        //playerDraw();
        //tft.tft(); display.display()?
       
      
      
       if (triggerSelect != 0) {
        if (counter > counterMax) {
            counter = 0;
            triggerSelect++;
        } else {
            counter++;
        }
      }
      }
            
        if (triggerSelect == 3) {
          
          if (select == 0) {
            gamestate = GAME_LEVEL;
          } else {
            triggerSelect = 0;
          }   
        }
      
       
   }
   
  }


void sceneChange(String text, unsigned int nextState)
{
  int sizex = getTextSize(text);
  
  while (gamestate == GAME_GAMEOVER) {
    
         clearScreen();
   
          tft.fillRect(0, 0, tft.width(), tft.height(), ST7735_BLACK);
          tft.setTextSize(1);
          tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
          tft.setCursor((tft.width()-sizex)/2,(tft.height()/2)-3);
          tft.print("GAME OVER");
                     
          
    
         //tft.tft();display.display
         
    TIMER_CURRENT = millis();
    
      if (TIMER_CURRENT - TIMER_PREV > 3000) { 
      
        TIMER_PREV = TIMER_CURRENT;
        gamestate = GAME_TITLE;
        clearScreen();
      }
        
  }
}

void resetGame() {

  player_state = P_STILL; 
  life = 3;
  player_direction = 1;
  player_position.x = 0;
  player_position.y = 16/*tft.height()-pimageh-8*/;
  vspd = 0;
  hspd = 0;


  camera.x = 0;
  camera.y = 0;
  last_camera.x = 0;
  last_camera.y = 0;
  camera_player_side = -1;
  check_pulo = false;

}

void sceneGame() {

  resetGame();
  
  
  while (gamestate == GAME_PLAY) {
  
    TIMER_CURRENT = millis();
    
      if(TIMER_CURRENT - TIMER_PREV > DELAY) { // game loop
      
        TIMER_PREV = TIMER_CURRENT;
      
        inputManager(); // 5 = 0
        
        //if (buttonPressing[2] && buttonPressing[1] && buttonPressing[0]) 
        //    gamestate = GAME_TITLE;
        
        
        playerLogic(buttonPressing[2],buttonPressing[0],buttonPressed[1]);
      
        //clearScreen(); 
        //if(camera.x != last_camera.x)
        //{
        //clearTileMap();
        //}

        //long time = millis();
        gameTilemap.drawMap(camera.x,camera.y);
        //time = millis() - time;
       //// tft.setCursor(64,64);
        //tft.fillRect(64,64,8,8,ST7735_WHITE);
        //tft.println(time,DEC);
        //tft.setCursor(64,72);
        //tft.fillRect(64,72,8,8,ST7735_WHITE);
       // tft.println(freeRam(),DEC);
        
        playerDraw();
        drawGui();
        
        //tft.tft(); display.display
    }

  }
  
}

void setup()   {

  Serial.begin(115200);

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, ST7735_BLACK tab
  tft.setRotation(2);
  //tft.begin();

  tft.fillScreen(ST7735_BLACK);
  
  //song - DOSENT WORK - DO NOT USE
  pinMode(PIN_SPEAKER, OUTPUT);//buzzer
  tone(PIN_SPEAKER,400,100);
  //pinMode(13, OUTPUT);//led indicator when singing a note
  
  // inputs
  //pinMode(PIN_BUTTON_LEFT, INPUT);//Define o pino 7 como entrada
  //digitalWrite(PIN_BUTTON_LEFT, HIGH);//Ativa o resistor de pull-up da porta 7
  //pinMode(PIN_BUTTON_SELECT, INPUT);//Define o pino 7 como entrada
  //digitalWrite(PIN_BUTTON_SELECT, HIGH);//Ativa o resistor de pull-up da porta 7
  //pinMode(PIN_BUTTON_RIGHT, INPUT);//Define o pino 7 como entrada
  digitalWrite(PIN_BUTTON_RIGHT, HIGH);//Ativa o resistor de pull-up da porta 7

  gameTilemap.setMapSize(100,6);
  gameTilemap.settftPointer(&tft);
  gameTilemap.setTileMap(TileMap0);

  
};

void printText(String text){
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_BLACK);  tft.setTextSize(1);
  tft.println(text);
}

//get text size(pixel size for setting cursor pos)
int getTextSize(String str){
    return getTextSize(str,-1);
}

int getTextSize(String str, int fontSize)
{
    if(fontSize == -1)
    {
      fontSize = 6;
    }
    return (str.length() * fontSize);
}

void clearScreen(){
  tft.fillScreen(ST7735_WHITE);
}

void clearSection(int16_t x, int16_t y, int16_t w, int16_t h)
{
  tft.fillRect(x,y,w,h,ST7735_WHITE);
}

void clearTileMap()
{
  tft.fillRect(0,0,tft.width(),48,ST7735_WHITE);
}

void loop() {
  
   switch (gamestate) { // "STATE MACHINE MANAGER"
  
    case GAME_INTRO: {sceneIntro(); break;}
    case GAME_TITLE: {sceneTitle(); break;}
    case GAME_LEVEL: {sceneChange("Level 1",GAME_PLAY); break;}
    case GAME_PLAY: {sceneGame(); break;}
    case GAME_GAMEOVER: {sceneChange("Game Over", GAME_TITLE); break;}
  } 

  
  
}

