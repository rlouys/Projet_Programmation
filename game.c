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

void Keyboard(unsigned char key, int x, int y)  // fonction allant gérer les input
{
	switch(key)
	{
		case 27:
			//glutDisplayFunc(WelcomeDisplay);
			exit(0);

		case 'z':
			UP = true;
			break;

		case'q':
			LEFT = true;
			break;

		case'd':
			RIGHT = true;
			break;

		case's':
			DOWN = true;
			break;
		
	        case 32:
			SHOOT = true;
			break;		
	}	
}

// ------------------------------------------------------------ // 

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

void game(int *maxX, int *maxY, Hero hero, EnemyList e, listetirsP t)
{
	//drawScore(hero);
		

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
	//	printf("hero->pos.x : %i\n", hero->pos.x);
	//	printf("hero->pos.y : %i\n", hero->pos.y);
		LEFT = false;
		
	}
	if (RIGHT == true)
	{
		
		moveRight(hero);		//va se déplacer vers la droite si on apppuie sur d
	//	printf("hero->pos.x : %i\n", hero->pos.x);
	//	printf("hero->pos.y : %i\n", hero->pos.y);
		RIGHT = false;
	}
	if (UP == true)
	{
		moveUp(hero);
	//	printf("hero->pos.x : %i\n", hero->pos.x);
	//	printf("hero->pos.y : %i\n", hero->pos.y);
		UP = false;
	}
	
	if (DOWN == true)
	{
		
        moveDown(hero);
	//	printf("hero->pos.x : %i\n", hero->pos.x);
	//	printf("hero->pos.y : %i\n", hero->pos.y);
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
void checkCollisionTirsEnnemis (enemy e, tirsP w)
{	bool Collide = false;
	int key = 1;
	//bool ColY = false;

	


	if ((w->pos.x/2) == e->pos.x && e->pos.y == ((w->pos.y-2)/2)-1 && key != 0)
		{
		/*int wposx = w->pos.x/2;
		int eposx = e->pos.x;
		int eposy = e->pos.y;
		int wposy = (w->pos.y-2)/2;*/

		/*printf("e->pos.x = %i                      ", eposx);
		printf("e->pos.y = %i\n", eposy);
		printf("t->pos.x = %i                      ", wposx);
		printf("t->pos.y = %i\n", wposy);*/

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
	//	printf("\n\n\nvie restante : %i\n\n\n", e->vie);


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
/*void checkCollision (enemy e, tirsP p)
{	bool ColX = false;
	bool ColY = false;
	if (hero->pos.x + Shoot_size <= e->pos.x && e->pos.x + Square_size <= hero->pos.x)
	{
		printf("test\n");
		ColX = true;
		
	}
	if (hero->pos.y + Shoot_size <= e->pos.y && e->pos.y + Square_size <= hero->pos.y)
	{
				printf("testY\n");

		ColY = true;
	}
	if (ColX || ColY)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		e->vie = (e->vie) -1;
		printf("vie restante : %i", e->vie);
		e->active = false;
		hero->active = false;
		CHECKCOLLISION = false;
	}
	
} */