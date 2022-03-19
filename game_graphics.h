
 // LOAD MAP && DRAW MAP//


#ifndef _GAME_GRAPHICS_H_
#define _GAME_GRAPHICS_H_


#include <stdbool.h>


// BLOC SIZES DEFINITION // 

//#define MaxX 40
//#define MaxY 41
#define Square_size 24.39

char **map;

// FUNC // 

bool loadMap(int mX, int mY);
//void Display();
void drawMap(int mX, int mY);

#endif

















