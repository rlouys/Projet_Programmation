#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

/*** LIBS ***/

#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

/***  STRUCTURES   ***/

struct positionP
{
	float x;
	float y;
};

// Définition du héro //

struct Hero
	{
		int evolution;
		int health;
		int attack;
		struct positionP pos;
		int current_xp;
		bool weapon_type; // false: normal weapon | true:  bubble weapon
		int killed;
	};

typedef struct Hero* Hero;

Hero hero;

// --------------------------------------------- // 

/***  VARIABLES  ***/

int xPos;
int yPos;
int mX;
int mY;

/*** FUNCTIONS ***/


// Initialise le héro et ses statistiques
Hero createHero(int *mX, int *mY); 

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.
void moveUp(Hero hero); 
void moveDown(Hero hero); 
void moveRight(Hero hero); 
void moveLeft(Hero hero); 


// change l'arme tenue par le héro (arme à feu et canon à bulles);
void switchWeapon(Hero hero);

// -------------------- // 


#endif

	