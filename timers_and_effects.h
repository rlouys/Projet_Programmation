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
void scrolling(int value); // t0

// timer qui gère les collisions tir et ennemis (en test : allie et ennemis gérés en +)
void updateCollisions(int valeur); // t1

// timer qui gère les changements de statut de l'ennemi
void updateEnemies(int valeur); // t2

// timer qui gère l'insertion de nouveaux ennemis
void updateNewEnemies(int valeur); // t3

// timer qui gère le défilement des tirs
void updateTirs(int valeur); // t4

// timer qui gère les suppressions d'ennemis
void updateDeleteEnemies(int valeur); // t5

// timer qui gère les suppressions d'ennemis
void updateDeleteTirs(int valeur); // t6

// timer qui gère les changements de status de l'obstacle
void updateObstacle(int valeur); // t7

// timer qui gère l'insertion de nouveaux obstacles
void updateNewObstacles(int valeur); // t8

// timer qui gère les suppressions d'obstacles
void updateDeleteObstacles(int valeur); // t9

// timer qui gère les changements de statut de l'objet bonus
void updateBonus(int valeur);  // t10

// timer qui gère l'insertion de nouveaux objets bonus
void updateNewBonus(int valeur); // t11

// timer qui gère les suppressions d'objets bonus
void updateDeleteBonus(int valeur); // t12

#endif