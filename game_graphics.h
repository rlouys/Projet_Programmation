#ifndef _GAME_GRAPHICS_H_
#define _GAME_GRAPHICS_H_

/*** LIBS ***/

#include <stdbool.h>

/*** FILES ***/

#include "enemies.h"
#include "hero.h"
#include "tirs.h"
#include "timers_and_effects.h" 
#include "game.h"

/***  CONSTANTES  ***/

#define Hero_size 20.0
#define Square_size 20.0
#define Shoot_size 10.0

/***  VARIABLES  ***/

char **map;
int mX;
int mY;

/*** FUNCTIONS ***/ 

// charge la map
bool loadMap(int *mX, int *mY); 

// affiche la vitalité du joueur en temps réel
void drawHealth(Hero hero); 

// affiche le score du joueur en temps réel
void drawScore(Hero hero);  

// affiche le username du joueur en temps réel
void drawUsername();  

// dessine un coeur aux couleurs voulues
void drawHeart(float red, float green, float blue);

// dessine une ligne aux couleurs voulues
void drawLine(float red, float green, float blue); 

// dessine une bordure à un carré, aux couleurs voulues et à la disposition voulue || border 0 == gauche | border 1 == droite
void drawLineBorder(float red, float green, float blue, int border); 

// dessine un carré aux couleurs voulues
void drawSquare(float red, float green, float blue, int size); 

// dessine le héro (design du hero)
void drawHero(float red, float green, float blue); 

// dessine un cercle aux couleurs voulues
void drawCircle(float red, float green, float blue, int posx, int posy, float rayon); 

// écrit un texte aux couleurs et positions voulues
void writeSomething(float red, float green, float blue, int x, int y, char *txt); 

// écrit un texte aux couleurs et positions voulues en helvetica taille 18
void writeSomethingHelvetica(float red, float green, float blue, int x, int y, char *txt);

// écrit un texte aux couleurs et positions voulues (avec un tableau)
void writeSomethingArray(float red, float green, float blue, int x, int y, char txt[]);

// dessine la map et tout les éléments statiques (score, murs)
void drawMap(int *mX, int *mY, Hero hero); 

// place le héro sur la carte (en le plaçant au bon endroit)
void drawPlayer(Hero hero); 

// dessine un ennemi et le place sur la carte
void drawEnemy(enemy e); 

//dessine les obstacles
void drawObstacles(obstacles o);

// dessine les tirs envoyés du joueur
void drawTirs(tir_Struct p); 

// dessine des ennemis à la chaine (utilise drawEnemy à la chaine)
void drawAllEnnemis(EnemyList e); 

// dessine les tirs à la chaine (utilise drawTirs à la chaîne)
void drawAllObstacles(ObstacleList t);

// dessine les tirs à la chaine (utilise drawTirs à la chaîne)
void drawAllTirs(listetir_Struct t);

// affiche le jeu à l'écran
void DisplayGame();












#endif

















