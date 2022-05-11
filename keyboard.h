#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

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

// initialise les fonctions au clavier lorsque dans un menu
void keyboardFunc(unsigned char Key, int x, int y); 

// sert à afficher une lettre que l'on écrit
void Alphabet(unsigned char Key, int x, int y);

// initialise les fonctions au clavier lorsque dans un menu
void keyboardFuncOpt(unsigned char Key, int x, int y); 

// clavier lié au menu pause en jeu
void keyboardFuncPausedInGame(unsigned char Key, int x, int y);


                        /***************
                         * MENU SOURIS *
                         ***************/

 // action à la souris 
 // Clic gauche : indique la position d'où on se trouve 
 // Clic droit : ferme la fenêtre (exit(0)). 
void mouse(int bouton,int etat,int x,int y);







#endif