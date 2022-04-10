#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

/*** LIBS ***/

#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

/***  STRUCTURES   ***/

struct positionP
{
	int x;
	int y;
};

	// Définition du héro //

struct Hero
	{
		int evolution;
		int health;
		int attack;
		struct positionP pos;
		float current_xp;
		int weapon_type;
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

	Hero createHero(int *mX, int *mY); // Initialize the hero and initialize its stats
	void moveUp(Hero hero); // Verify if the hero can move UP or not
	void moveDown(Hero hero); // Verify if the hero can move DOWN or not
	void moveRight(Hero hero); // Verify if the hero can move RIGHT or not
	void moveLeft(Hero hero); // Verify if the hero can move LEFT or not

// -------------------- // 


#endif

	