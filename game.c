/*** LIBS ***/

#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game_graphics.h"
#include "tirs.h"
#include "enemies.h"
#include "hero.h"
#include "enemies.h"
#include "game.h"

/***  VARIABLES ***/ 

float *value;
float *deplacement_fenetre;

bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool SHOOT = false;
bool CHECKCOLLISION = false;

/*** FUNCTIONS ***/

// ------------------------------------------------------------ // 

// definition de la fonction Keyboard permettant de quitter/tirer

void Keyboard(unsigned char key, int x, int y)  
{
	switch(key)
	{
		case 27:
			//glutDisplayFunc(WelcomeDisplay);
			exit(0);
	
		case 32:
			SHOOT = true;
			break;		
	}	
}

// ------------------------------------------------------------ // 

// definition de la fonction arrowFunction permettant de se déplacer via les flèches directionnelles

void arrowFunction(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        UP = true;
        break;
    case GLUT_KEY_DOWN:
        DOWN = true;
        break;
    case GLUT_KEY_LEFT:
        LEFT = true;
        break;
    case GLUT_KEY_RIGHT:
        RIGHT = true;
        break;
    }
}

// ------------------------------------------------------------ // 

// dessine le jeu et lance la partie, fait apparaitre les ennemis et les tirs

void game(int *maxX, int *maxY, Hero hero, EnemyList e, listetir_Struct t)
{		

	glPushMatrix();
	drawMap(&mX, &mY, hero);			//afficher la carte
    glPopMatrix();
	drawPlayer(hero);
	if (e->first != NULL || e->last != NULL)
	{
		drawAllEnnemis(e);
	}		


	if (t->first != NULL || t->last != NULL)
	{
		drawAllTirs(t);
	}

	
	
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	glutSpecialFunc(arrowFunction);

	if (LEFT == true)
	{
		
		moveLeft(hero);		//va se déplacer vers la gauche si on appuie sur q+
		LEFT = false;
		
	}
	if (RIGHT == true)
	{
		
		moveRight(hero);		//va se déplacer vers la droite si on apppuie sur d
		RIGHT = false;
	}
	if (UP == true)
	{
		moveUp(hero);
		UP = false;
	}
	
	if (DOWN == true)
	{
		
        moveDown(hero);
		DOWN = false;
	}
	if (SHOOT == true)
	{
		tirer(hero, t);
		SHOOT=false;
	}

	glutPostRedisplay();
}

// ------------------------------------------------------------ // 

// vérifie s'il y a une collision entre l'ennemi et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsEnnemis (enemy e, tir_Struct w)
{	
	bool Collide = false;
	int key = 1;

	if ((w->pos.x/2) == e->pos.x && e->pos.y == ((w->pos.y-2)/2)-1 && key != 0)
		{
			Collide = true;
			key = 0;
			
		}
	
	if (Collide)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		
		e->vie = (e->vie) - hero->attack;


		if(e->vie == 0)
		{
		e->active = false;
		hero->killed += 1;

		}

		w->active = false;
		CHECKCOLLISION = false;
	}
	
} 


// ------------------------------------------------------------ // 
/*
void checkCollisionHeroEnnemis (enemy e)
{	
	bool Collide = false;
	int key = 1;

	if (hero->pos.x == e->pos.x && e->pos.y == hero->pos.y && key != 0)
		{
			Collide = true;
			key = 0;
			
		}
	
	if (Collide)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		
		e->vie = 0;
		printf( "vie ennemi : %i", e->vie);
		hero->health -= 1;
		printf("vie hero : %i", hero->health);


		if(e->vie == 0)
		{
		e->active = false;
		hero->killed += 1;

		}

		CHECKCOLLISION = false;
	}
	
} 
*/