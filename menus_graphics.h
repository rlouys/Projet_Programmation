#ifndef __MENUS_GRAPHICS_H__
#define __MENUS_GRAPHICS_H__

/*** LIBS ***/

//#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



/*** VARIABLES ***/

int mX;
int mY;

/*** FUNCTIONS ***/

                    /******************
                     * SHAPE DRAWINGS *
                     ******************/

// Dessine un cadre autour d'un texte
void frameDraw(int red, int green, int blue, int x, int y, int length, int title); 

// dessin du tableau highscore du menu de démarrage
void drawHighScore();


                        /**********
                         * ÉCRANS *
                         **********/


// Crée l'écran de DÉMARRAGE
void WelcomeDisplay(); 

// Crée l'écran des options durant la partie
void GameOptionsDisplay();

// Crée l'écran de demande de Username
void UsernameDisplay();

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

// Crée et affiche l'écran de crédits
void DisplayCredits();

                        /*********************
                         * FONCTION D ECRANS *
                         *********************/

// initialise les options dynamiques à l'écran avant la première touche pressée
void options_keys(int option_number);


                        /*******************
                         * MENU CLIC DROIT *
                         *******************/

// Crée le menu clic droit
void init_rightClick_Menu(); 

// Initialise le menu clic droit
void myMenu(int id); 







#endif
