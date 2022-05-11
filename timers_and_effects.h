#ifndef __TIMERS_AND_EFFECTS_H__
#define __TIMERS_AND_EFFECTS_H__

/*** LIBS ***/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "enemies.h" 
#include "tirs.h"
#include "hero.h"

/*** VARIABLES ***/

#define FPS 30
bool test;


/*** FUNCTIONS ***/


// vérifie s'il y a une collision entre l'ennemi et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsEnnemis (enemy e, tir_Struct p);

// vérifie s'il y a une collision entre l'ennemi et l'allié, le cas échéant, enlève de la vie aux deux persos
void checkCollisionAlliesEnemy (enemy en);

// vérifie s'il y a une collision entre l'obstacle et le tir allié, le cas échéant
void checkCollisionTirsObstacles (obstacles o, tir_Struct w);

// vérifie s'il y a une collision entre l'obstacle et l'allié, le cas échéant, enlève de la vie au perso
void checkCollisionAlliesObstacles (obstacles fence);

// vérifie s'il y a une collision entre l'objet bonus et le tir allié, le cas échéant
void checkCollisionTirsBonus (bonus_objet b, tir_Struct w);

// vérifie s'il y a une collision entre l'objet bonus et l'allié, et confère le(s) bonus
void checkCollisionAlliesBonus (bonus_objet bns);

// fait pause temporairement
void wait1();

// change la couleur de l'ennemi
void setGold();
void setPurple();
void setPurpleOrGold();

// donne un niveau à l'ennemi, pour gérer les évolutions
enemy setEnemyLevel(enemy car);


// augmente la difficulté en fonction du niveau de difficulté et du level en cours
void setLevel();

/*** TIMERS ***/

                            /*******
                             * MAP *
                             *******/

// timer qui gère le défilement de la map
void scrolling(int value); // t0


                /**************************
                 * COLLISIONS TIRS ALLIÉS *
                 **************************/

// timer qui gère les collisions tir et ennemis (en test : allie et ennemis gérés en +)
void updateCollisions(int valeur); // t1



                /**********************
                 * MOUVEMENTS ENNEMIS *
                 **********************/

// timer qui gère les changements de statut de l'ennemi
void updateEnemies(int valeur); // t2

// timer qui gère l'insertion de nouveaux ennemis
void updateNewEnemies(int valeur); // t3

// timer qui gère les suppressions d'ennemis
void updateDeleteEnemies(int valeur); // t5


                /************************
                 * MOUVEMENTS OBSTACLES *
                 ************************/

// timer qui gère le déplacement des obstacles, et check les collisions
// après déplacement
void updateObstacle(int valeur); // t7

// ajoute un nouvel obstacle si la partie est en cours
void updateNewObstacles(int valeur); // t8

// s'il y a un obstacle dans la liste, le supprime
// si la partie est en cours
void updateDeleteObstacles(int valeur); // t9



                /********************
                 * MOUVEMENTS BONUS *
                 ********************/

// timer qui gère les changements de statut de l'objet bonus
void updateBonus(int valeur);  // t10

// timer qui gère l'insertion de nouveaux objets bonus
void updateNewBonus(int valeur); // t11

// timer qui gère les suppressions d'objets bonus
void updateDeleteBonus(int valeur); // t12


                    /********
                     * TIRS *
                     ********/

// timer qui gère le défilement des tirs alliés si la partie est en cours
void updateTirsHero(int valeur); // t4

// timer qui gère le défilement des tirs alliés 
void updateTirsEnemy(int valeur); // t13

// timer qui gère les suppressions des tirs alliés et ennemis
void updateDeleteTirs(int valeur); // t6


#endif