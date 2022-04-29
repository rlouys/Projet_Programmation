/*** LIBS ***/

#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menus_graphics.h"
#include "game_graphics.h"
#include "tirs.h"
#include "enemies.h"
#include "hero.h"
#include "enemies.h"
#include "game.h"

/***  VARIABLES ***/ 

float *value;
float *deplacement_fenetre;
bool startgame;

char username[20];

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
			startgame = !startgame;
			glutDisplayFunc(GameOptionsDisplay);
			glutPostRedisplay();
			break;
	
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

void game(int *maxX, int *maxY, Hero hero, EnemyList e, listetir_Struct t, ObstacleList o, BonusList b)
{		

	glPushMatrix();
	drawMap(&mX, &mY, hero);			//afficher la carte
    glPopMatrix();
	drawPlayer(hero);
	if (e->first != NULL || e->last != NULL)
	{
		drawAllEnnemis(e);
	}

	if (o->first != NULL || o->last != NULL)
	{
		drawAllObstacles(o);
	}

	if (t->first != NULL || t->last != NULL)
	{
		drawAllTirs(t);
	}
	if(b->first != NULL || b->last != NULL)
	{
		drawAllBonus(b);
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

	if ((w->pos.x/2) == e->pos.x && e->pos.y <= ((w->pos.y-2)/2)+1.5 && key != 0)
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

// vérifie s'il y a une collision entre l'obstacle et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsObstacles (obstacles o, tir_Struct w)
{	
	bool CollideO = false;
	int key = 1;
	printf("-------------------------\n\n");
	printf("w->pos.x : %f\n",w->pos.x);
	printf("w->pos.y : %f\n",w->pos.y);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("o->pos.x : %f\n",o->pos.x);
	printf("o->pos.y : %f\n",o->pos.y);
	printf("-------------------------\n\n"); // 30 /  60 || 31 / 61

	// Si le tir arrive à la position de l'obstacle en x ou en x+1, alors suppression ennemi
	if (    
	((((w->pos.x/2) == o->pos.x) && (o->pos.y <= (((w->pos.y-2)/2)+1.5))) /**/ 
	||  ((((w->pos.x/2)) == (o->pos.x+1)) && (o->pos.y <=  (((w->pos.y-2)/2)+1.5))))                                                                                     /**/
	&& key != 0)

	{
			CollideO = true;
			key = 0;
	}

	if (CollideO)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		w->active = false;
		CHECKCOLLISION = false;
	}
	
}

// ------------------------------------- //

void checkCollisionAlliesEnemy (enemy en)
{	
	bool CollideO = false;
	int key = 1;
	/*printf("-------------------------\n\n");
	printf("hero->pos.x : %f\n",hero->pos.x);
	printf("hero->pos.y : %f\n",hero->pos.y);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("en->pos.x : %f\n",en->pos.x);
	printf("en->pos.y : %f\n",en->pos.y);
	printf("-------------------------\n\n");*/

	
	if( (en->pos.x == hero->pos.x) && (((en->pos.y) <= hero->pos.y +0.1) && ((en->pos.y) > hero->pos.y -1))   && key != 0   )

	{

			CollideO = true;
			key = 0;
		
	} 

	if (CollideO)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		hero->health -= 1;
		en->vie -=1;
		hero->color_type = false;

		if(hero->health == 0){
			glutDisplayFunc(EndGameDisplay);
		}

		if(en->vie == 0){
			en->active = false;
		}

		CHECKCOLLISION = false;
	}
	
} 


// ------------------------------------- //

void checkCollisionAlliesObstacles (obstacles fence)
{	
	bool CollideO = false;
	int key = 1;
	/*printf("-------------------------\n\n");
	printf("hero->pos.x : %f\n",hero->pos.x);
	printf("hero->pos.y : %f\n",hero->pos.y);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("fence->pos.x : %f\n",fence->pos.x);
	printf("fence->pos.y : %f\n",fence->pos.y);
	printf("-------------------------\n\n");*/

	
	if( 
	/**/ ( ((fence->pos.x == hero->pos.x) &&  (fence->pos.y <= (hero->pos.y +0.1)) && (fence->pos.y > (hero->pos.y -0.1)) )
	/**/ ||
	/**/  ( ((fence->pos.x+1) == hero->pos.x) && (fence->pos.y <= (hero->pos.y +0.1)) && (fence->pos.y > (hero->pos.y -0.1)) ))
	/**/  && key != 0   )

	{

			CollideO = true;

			key = 0;
		
	

			if (CollideO)
			{
				CHECKCOLLISION = true;
			}
			
			if (CHECKCOLLISION)
			{	
				if(key == 0)
				{
				hero->health -= 1; // ENLEVE 5 !! A CORRIGER !! 
				fence->pos.y -= 0.1;
				key = 1;
				hero->color_type = false;
				}
				hero->obstacles_taken += 1;

				if(hero->health == 0){
					glutDisplayFunc(EndGameDisplay);
				}


				CHECKCOLLISION = false;
			}
	}
} 

// ------------------------------------- // 

// charge la map

void saveScore(Hero hero)		
{
    FILE *f = NULL;
	f = fopen("scores.txt","a");

	int score = hero->current_xp;
	
	fprintf(f, "%s       ", "HARUHIKO");
	fprintf(f,"%i \n", score);
	fclose(f);


}		
// ------------------------------------- //

void checkCollisionAlliesBonus (bonus_objet bns)
{	
	bool CollideO = false;
	int key = 1;
	printf("-------------------------\n\n");
	printf("hero->pos.x : %f\n",hero->pos.x);
	printf("hero->pos.y : %f\n",hero->pos.y);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("bonus->pos.x : %f\n",bns->pos.x);
	printf("bonus->pos.y : %f\n",bns->pos.y);
	printf("-------------------------\n\n");

	
	if( (bns->pos.x == hero->pos.x) && (((bns->pos.y) <= hero->pos.y +1) && ((bns->pos.y) > hero->pos.y -1))   && key != 0   )

	{

			CollideO = true;
			key = 0;
		
	} 

	if (CollideO)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		hero->health += 5;
		drawHealth(hero);

		if(hero->health == 0){
			glutDisplayFunc(EndGameDisplay);
		}

		bns->active = false;
		

		CHECKCOLLISION = false;
	}
	
} 


// ------------------------------------- //

// vérifie s'il y a une collision entre l'ennemi et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsBonus (bonus_objet b, tir_Struct w)
{	
	bool Collide = false;
	int key = 1;

	if ((w->pos.x/2) == b->pos.x && b->pos.y <= ((w->pos.y-2)/2)+1.5 && key != 0)
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
		

		hero->color_type = true;
		b->active = false;
		//hero->bonus_taken += 1;

		

		w->active = false;
		CHECKCOLLISION = false;
	}
	
} 
