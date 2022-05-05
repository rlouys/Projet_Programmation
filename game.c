/*** LIBS ***/

//#include <GL/glut.h>
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
int startgame_option_bug = 1;
bool gameplay_keys;


char username[20];

bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool SHOOT = false;
bool SHOOT_ENEMY = false;


/*** FUNCTIONS ***/


// ------------------------------------------------------------ // 

// definition de la fonction Keyboard permettant de quitter/tirer

void Keyboard(unsigned char key, int x, int y)  
{
	switch(key)
	{
		// ESC KEY
		case 27:
			startgame = !startgame;
			glutDisplayFunc(GameOptionsDisplay);
			glutPostRedisplay();
			break;

		// SPACE KEY
		case 32:
			SHOOT = true;
			break;	
		
		// BACKSPACE KEY
		case 0x08:
		
			if(te->first == NULL || te->last == NULL)
			{
				SHOOT_ENEMY = true;
			}	
			if(te->first != NULL || te->last == NULL)
			{
				SHOOT_ENEMY = true;
			}
			break;

		// changement d'arme
		case 'w':
				hero->weapon_type = !hero->weapon_type;	

		if(gameplay_keys == true)
		{

			case 'z':
			hero->pos.y += 1;
				break;

			case 'q':
			hero->pos.x -= 1;
				break;	
			
			case 's':
			hero->pos.y -= 1;
				break;

			case 'd':
			hero->pos.x += 1;
				break;
		}	


		
			
		}	
}

// ------------------------------------------------------------ // 

// definition de la fonction arrowFunction permettant de se déplacer via les flèches directionnelles

void arrowFunction(int key, int x, int y)
{
    switch (key) 
	{
		// déplacement du héro avec les touches 
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

// ------------------------------------- // 

// déplace le héro en fonction de la touche flechée pressée

void move(){

	if(startgame == true)
	{
		enemy en = e->first;

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

		// envoie le tir allié
		if (SHOOT == true)
		{
			tirer(hero, t);
			SHOOT=false;
		}

		// envoie le(s) tir(s) ennemi(s)
		if (SHOOT_ENEMY == true)
		{
			tirer_enemy(en, te);
			SHOOT_ENEMY = false;
		}

	}
}

// ------------------------------------------------------------- //
//Fonctionne bien sauf premiere fois

void DisplayGame()
{	
    
	glClearColor(0.1f,0.1f,0.1f,0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game(&mX, &mY, hero,e,t,te, o, b);

    glFlush();

	if(startgame == false)
	{
		glutDisplayFunc(GameOptionsDisplay);
	}


}
// ------------------------------------------------------------ // 

// dessine le jeu et lance la partie, fait apparaitre les ennemis et les tirs

void game(int *maxX, int *maxY, Hero hero, EnemyList e, listetir_Struct t, listetir_StructEnemy te, ObstacleList o, BonusList b)
{		
	
	glPushMatrix();
	drawMap(&mX, &mY, hero);			//afficher la carte
    glPopMatrix();

	drawPlayer(hero);

	// dessine tous les ennemis si la liste d'ennemi n'est pas vide
	if (e->first != NULL || e->last != NULL)
	{
		drawAllEnnemis(e);
	}

	// dessine tous les obstacles si la liste d'obstacles n'est pas vide
	if (o->first != NULL || o->last != NULL)
	{
		drawAllObstacles(o);
	}

	// dessine tous les tirs du Hero si la liste des tirs n'est pas vide
	if (t->first != NULL || t->last != NULL)
	{
		drawAllTirsHero(t);
	}

	// dessine tous les tirs ennemis si la liste des tirs n'est pas vide
	if(te->first != NULL || te->last != NULL)
	{
		drawAllTirsEnemy(te);
	}

	// dessine les objets bonus
	if(b->first != NULL || b->last != NULL)
	{
		drawAllBonus(b);
	}

	// fonctions clavier
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	if(gameplay_keys == false)
	{
		glutSpecialFunc(arrowFunction);
	}
	else
	{
		glutKeyboardFunc(Keyboard);
	}

	if(gameplay_keys == false)
	{
		move();
	}

	glutPostRedisplay();
}




// ------------------------------------------------------- //

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





