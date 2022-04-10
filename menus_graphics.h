#ifndef __MENUS_GRAPHICS_H__
#define __MENUS_GRAPHICS_H__

/*** LIBS ***/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*** VARIABLES ***/

int mX;
int mY;

/*** FUNCTIONS ***/

void WelcomeDisplay(); // Create the WELCOME display (start menu)
void EndGameDisplay(); // Create the FAILURE endgame display (...you failed...)
void WinDisplay();
void DisplayOptions(); // Create the OPTIONS display while inside the WelcomeDisplay (o)
void DisplayGameplay(); // Create the GAMEPLAY display while inside the WelcomeDisplay (g)
void DisplayEnding(); // Create the ENDING display while inside the WelcomeDisplay when you want to exit the game (x)
void myMenu(int id); // Create the RIGHT_BUTTON_CLICK menu
void wait(); // Used to wait until a certain time (Endgame display - Wait... - Exit L222)
void frameDraw(int red, int green, int blue, int x, int y, int length, int title);
void keyboardFunc(unsigned char Key, int x, int y);



#endif
