#ifndef __GAME_H__
#define __GAME_H__

/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>







// déplace le héro en fonction de la touche flechée pressée
void move();


                            /*************
                             * FUNCTIONS *
                             *************/

// Function to copy an array to a string
char *copyToString(char array[]);

                                /********
                                 * GAME *
                                 ********/



// fonction qui va vérifier si il y a une partie enregistrée ou non
// si pas de partie enregistrée, impossible de "continuer" et affichage du message en rouge
// si partie enregistrée, newgame possible ET continuer
int checkNewGame(int newGame);

// affiche le jeu à l'écran
void DisplayGame();

// dessine le jeu et lance la partie, fait apparaitre les ennemis et les tirs
void game(int *mX, int *mY, Hero hero, EnemyList e, listetir_Struct t, listetir_StructEnemy te,  ObstacleList o, BonusList b);


                                /*********
                                 * SAVES *
                                 *********/
                                
// inverse deux entiers dans un tableau
void swapIntegers(int* un, int* deux);

// inverse deux strings dans un tableau
void swapUsername(top Top, int k);

// Sauvegarde le score de la partie en cours et l'enregistre dans un fichier txt (scores.txt)
void saveScore(Hero hero);

// Sauvegarde le contexte de la partie au moment de quitter
void saveContext();




#endif