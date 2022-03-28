#ifndef _GAME_GRAPHICS_H_
#define _GAME_GRAPHICS_H_

/*** LIBS ***/

#include <stdbool.h>

#include "enemies.h"
#include "characters.h"
#include "tirs.h"
#include "timers_and_effects.h" 
#include "game.h"


#define Square_size 20.0
#define Shoot_size 10.0

/***  VARIABLES  ***/

char **map;
int mX;
int mY;

/*** FUNCTIONS ***/ 

bool loadMap(int *mX, int *mY);
void drawMap(int *mX, int *mY);
void drawSquare(float red, float green, float blue);
void drawCircle(float red, float green, float blue, int posx, int posy, float rayon);
void drawPlayer(player p);
void drawEnemy(enemy e);	
void drawTirs(tirsP p);
void drawAllEnnemis(listeEn e);
void drawSky();
void drawLine(float red, float green, float blue);



#endif

















