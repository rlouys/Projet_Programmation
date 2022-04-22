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

// timer qui gère le défilement de la map
void scrolling(int value);

// timer qui gère les collisions tir et ennemis (en test : allie et ennemis gérés en +)
void updateCollisions(int valeur);

// timer qui gère les collisions alliés et ennemis (en test : allie et ennemis gérés en +)
void updateCollisionsHE(int valeur);

// timer qui gère les changements de statut de l'ennemi
void updateEnemies(int valeur);

// timer qui gère l'insertion de nouveaux ennemis
void updateNewEnemies(int valeur);

// timer qui gère le défilement des tirs
void updateTirs(int valeur);

// timer qui gère les suppressions d'ennemis
void updateDeleteEnemies(int valeur);

// timer qui gère les suppressions d'ennemis
void updateDeleteTirs(int valeur);

// timer qui gère les changements de status de l'obstacle
void updateObstacle(int valeur);

// timer qui gère l'insertion de nouveaux obstacles
void updateNewObstacles(int valeur);

// timer qui gère les suppressions d'obstacles
void updateDeleteObstacles(int valeur);



#endif