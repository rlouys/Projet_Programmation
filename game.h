#ifndef __GAME_H__
#define __GAME_H__

/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>


/*** FUNCTIONS ***/

void Keyboard(unsigned char key, int x, int y);
void game(int *mX, int *mY, player p, listeEn e, listetirsP t);
void checkCollisionTirsEnnemis (enemy e, tirsP p);
void drawAllTirs(listetirsP t);






#endif