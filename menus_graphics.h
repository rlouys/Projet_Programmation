#ifndef __MENUS_GRAPHICS_H__
#define __MENUS_GRAPHICS_H__

/*** LIBS ***/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*** VARIABLES ***/

int mX;
int mY;

/*** FUNCTIONS ***/

// initialise les fonctions au clavier lorsque dans un menu
void keyboardFunc(unsigned char Key, int x, int y); 

// Dessine un cadre autour d'un texte
void frameDraw(int red, int green, int blue, int x, int y, int length, int title); 

// Crée l'écran de DÉMARRAGE
void WelcomeDisplay(); 

// Crée le menu de FIN en cas d'ÉCHEC (you failed...)
void EndGameDisplay(); 

// Crée le menu de FIN en cas de VICTOIRE (you win!)
void WinDisplay(); 

// Crée et affiche l'écran des OPTIONS
void DisplayOptions(); 

// Crée et affiche l'écran lié au GAMEPLAY
void DisplayGameplay(); 

// Crée et affiche l'écran de fin de programme
void DisplayEnding(); 

// Crée le menu clic droit
void init_rightClick_Menu(); 

// Initialise le menu clic droit
void myMenu(int id); 

// Utilisé pour attendre un certain temps (delay) depuis le main.c
void wait(); 




#endif
