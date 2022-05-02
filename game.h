#ifndef __GAME_H__
#define __GAME_H__

/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>





/*** FUNCTIONS ***/

                        /***********************
                         * KEY AND ARROW FUNCS *
                         ***********************/

// definition de la fonction Keyboard permettant de quitter/tirer
void Keyboard(unsigned char key, int x, int y);

// definition de la fonction arrowFunction permettant de se déplacer via les flèches directionnelles
void arrowFunction(int key, int x, int y);

// déplace le héro en fonction de la touche flechée pressée
void move();


                                /********
                                 * GAME *
                                 ********/

// affiche le jeu à l'écran
void DisplayGame();

// dessine le jeu et lance la partie, fait apparaitre les ennemis et les tirs
void game(int *mX, int *mY, Hero hero, EnemyList e, listetir_Struct t, listetir_StructEnemy te,  ObstacleList o, BonusList b);


                                /*********
                                 * SAVES *
                                 *********/

//sauvegarde le score de la dernière partie et l'enregistre dans un fichier txt
void saveScore(Hero hero);






#endif