/*** LIBS ***/

#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game_graphics.h"
#include "tirs.h"
#include "enemies.h"
#include "characters.h"

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

void game(int *maxX, int *maxY, player p, listeEn e, listetirsP t)
{
	//drawScore(p);
		

	glPushMatrix();
	drawMap(&mX, &mY, p);			//afficher la carte
    glPopMatrix();
	drawPlayer(p);
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
		
		moveLeft(p);		//va se déplacer vers la gauche si on appuie sur q+
		printf("p->pos.x : %i\n", p->pos.x);
		printf("p->pos.y : %i\n", p->pos.y);
		LEFT = false;
		
	}
	if (RIGHT == true)
	{
		
		moveRight(p);		//va se déplacer vers la droite si on apppuie sur d
		printf("p->pos.x : %i\n", p->pos.x);
		printf("p->pos.y : %i\n", p->pos.y);
		RIGHT = false;
	}
	if (UP == true)
	{
		moveUp(p);
		printf("p->pos.x : %i\n", p->pos.x);
		printf("p->pos.y : %i\n", p->pos.y);
		UP = false;
	}
	
	if (DOWN == true)
	{
		
        moveDown(p);
		printf("p->pos.x : %i\n", p->pos.x);
		printf("p->pos.y : %i\n", p->pos.y);
		DOWN = false;
	}
	if (SHOOT == true)
	{
		tirer(p, t);
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
		int wposx = w->pos.x/2;
		int eposx = e->pos.x;
		int eposy = e->pos.y;
		int wposy = (w->pos.y-2)/2;
		printf("e->pos.x = %i                      ", eposx);
		printf("e->pos.y = %i\n", eposy);
		printf("t->pos.x = %i                      ", wposx);
		printf("t->pos.y = %i\n", wposy);

			Collide = true;
			key = 0;
			
		}
	
	if (Collide)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		
		e->vie = (e->vie) - p->attack;
		printf("\n\n\nvie restante : %i\n\n\n", e->vie);


		if(e->vie == 0)
		{
		e->active = false;
		}

		w->active = false;
		CHECKCOLLISION = false;
	}
	
} 


// ------------------------------------------------------------ // 
/*void checkCollision (enemy e, tirsP p)
{	bool ColX = false;
	bool ColY = false;
	if (p->pos.x + Shoot_size <= e->pos.x && e->pos.x + Square_size <= p->pos.x)
	{
		printf("test\n");
		ColX = true;
		
	}
	if (p->pos.y + Shoot_size <= e->pos.y && e->pos.y + Square_size <= p->pos.y)
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
		p->active = false;
		CHECKCOLLISION = false;
	}
	
} */