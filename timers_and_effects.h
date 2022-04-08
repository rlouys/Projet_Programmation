#ifndef __TIMERS_AND_EFFECTS_H__
#define __TIMERS_AND_EFFECTS_H__

/*** LIBS ***/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdbool.h>

/*** VARIABLES ***/

#define FPS 30
bool test;


/*** FUNCTIONS ***/

void timer(int value);
void updateCollisions(int valeur);
void updateEnemies(int valeur);
void updateNewEnemies(int valeur);
void updateTirs(int valeur);
void updateDeleteEnemies(int valeur);
void updateDeleteTirs(int valeur);
//void MenuTimer(int valeur);


#endif