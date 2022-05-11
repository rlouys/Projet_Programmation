#ifndef _GAME_GRAPHICS_H_
#define _GAME_GRAPHICS_H_

/*** LIBS ***/

#include <stdbool.h>
#include <stdio.h>

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

/*** FUNCTIONS ***/ 


                    /***************
                     * MEM_LOADERS *
                     ***************/

// charge la map en mémoire
bool loadMap(int *mX, int *mY); 



                    /***************
                     * MAP DRAWING *
                     ***************/

// dessine la map et tout les éléments statiques (score, murs)
void drawMap(int *mX, int *mY, Hero hero); 

void initRendering();

void handleResize(int width, int heigth);

                    /******************
                     * SHAPES DRAWINGS *
                     ******************/

// dessine un carré aux couleurs voulues
void drawSquare(float red, float green, float blue, float size); 

// dessine un cercle aux couleurs voulues
void drawCircle(float red, float green, float blue, int posx, int posy, float rayon); 

// dessine une ligne aux couleurs voulues
void drawLine(float red, float green, float blue); 

// dessine une bordure à un carré, aux couleurs voulues et à la disposition voulue || border 0 == gauche | border 1 == droite
void drawLineBorder(float red, float green, float blue, int border); 

// dessine un coeur aux couleurs voulues
void drawHeart(float red, float green, float blue);

                    /*****************
                     * DATAS DRAWINGS *
                     *****************/
// dessine le niveau en cours
void drawLevel();

// affiche la vitalité du joueur en temps réel
void drawHealth(Hero hero); 

// affiche l'état des bonus du joueur en temps réel
void drawAttack();

// affiche les stats du jeu en cours (enemy killed....)
void drawKills();

// affiche le username du joueur en temps réel
void drawUsername();  

// affiche le score du joueur en temps réel
void drawScore(Hero hero);  

void drawWeapon();

                    /***********************
                     * CHARACTERS DRAWINGS *
                     ***********************/
// dessine une voiture
void drawCar(enemy e);

// dessine un vélo
void drawBike();

// dessine un mur de briques (les obstacles)
void drawBrickWall();

// place le héro sur la carte (en le plaçant au bon endroit)
void drawPlayer(Hero hero); 

// dessine un ennemi et le place sur la carte
void drawEnemy(enemy e); 

// dessine des ennemis à la chaine (utilise drawEnemy à la chaine)
void drawAllEnnemis(EnemyList e); 

                    /**************************
                     * MOBILE OBJECTS DRAWINGS *
                     **************************/
                    
//dessine les obstacles
void drawObstacles(obstacles o, float red, float green, float blue);

// dessine les tirs à la chaine (utilise drawTirs à la chaîne)
void drawAllObstacles(ObstacleList t);

//dessine les objets bonus
void drawBonus(bonus_objet BONUS);

// dessine des bonus à la chaine (utilise drawBonus à la chaine)
void drawAllBonus(BonusList b);


// TIRS

// dessine les tirs envoyés du joueur
void drawTirsHero(tir_Struct p); 

// dessine les tirs alliés à la chaine (utilise drawTirs à la chaîne)
void drawAllTirsHero(listetir_Struct t);

// dessine les tirs envoyés du joueur
void drawTirsEnemy(tir_Struct p); 

// dessine les tirs ennemis à la chaine (utilise drawTirs à la chaîne)
void drawAllTirsEnemy(listetir_StructEnemy t);




                    /***********************
                     * FREE TEXTS DRAWINGS *
                     ***********************/

// écrit un texte aux couleurs et positions voulues
void writeSomething(float red, float green, float blue, int x, int y, char *txt); 

// ecrit un texte en 9by15
void writeSomething9by15(float red, float green, float blue,  int x, int y, char *caractere, int taille, int ij);

// écrit un texte aux couleurs et positions voulues en helvetica taille 18
void writeSomethingHelvetica(float red, float green, float blue, int x, int y, char *txt);

// écrit un texte aux couleurs et positions voulues en helvetica taille 18
void writeSomethingArrayHelvetica(float red, float green, float blue, int x, int y, char txt[]);

// écrit un texte aux couleurs et positions voulues (avec un tableau)
void writeSomethingArray(float red, float green, float blue, int x, int y, char txt[]);




#endif

















