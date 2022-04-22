#ifndef __GAME_H__
#define __GAME_H__

/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>


/*** FUNCTIONS ***/

// definition de la fonction Keyboard permettant de quitter/tirer
void Keyboard(unsigned char key, int x, int y);

// definition de la fonction arrowFunction permettant de se déplacer via les flèches directionnelles
void arrowFunction(int key, int x, int y);

// dessine le jeu et lance la partie, fait apparaitre les ennemis et les tirs
void game(int *mX, int *mY, Hero hero, EnemyList e, listetir_Struct t, ObstacleList o);

// vérifie s'il y a une collision entre l'ennemi et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsEnnemis (enemy e, tir_Struct p);

// vérifie s'il y a une collision entre l'ennemi et l' allié, le cas échéant, enleve de la vie au héro, supprime l'ennemi et augmente le score
void checkCollisionHeroEnnemis (enemy e);

// vérifie s'il y a une collision entre l'obstacle et le tir allié, le cas échéant
void checkCollisionTirsObstacles (tir_Struct w, obstacles o);

// vérifie s'il y a une collision entre l'ennemi et l'allié, le cas échéant, enlève de la vie aux deux persos
void checkCollisionAlliesEnemy (enemy en);


#endif