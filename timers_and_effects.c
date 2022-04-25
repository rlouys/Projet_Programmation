/*** LIBS ***/

#include "timers_and_effects.h"
#include "game_graphics.h"
#include "game.h"
#include "enemies.h"
#include "tirs.h"
#include "hero.h"
#include "menus_graphics.h"

/*** CONSTANTES ***/

#define ENNEMI_SPEED 1 // 10 = ultraspeed/hardcore | 1000 = slow
#define ENNEMI_PER_HUNDRED_SECOND 150
#define RANGE_MAX 120
#define ATTACK_SPEED 1 // 1 is superfast, 1000 is slow
#define OBSTACLE_SPEED 600 // 10 = ultraspeed/hardcore | 1000 = slow
#define OBSTACLES_PER_TEN_SECOND 1

#define MAX_SCORE 10000

/*** VARIABLES ***/

int mX;
int mY;
float *value;
float *deplacement_fenetre;
int counter = 0;
bool startgame;

/*** FUNCTIONS ***/

// ---------------------------------------------------------------------------------- //

// timer qui gère le défilement de la map

void scrolling(int valeur) {
	

	if(startgame==true){ 

		*value = *value *1.75;

			if((*value)>=500){
					*value = 20;
			}
	
   }

       glutPostRedisplay();      
       glutTimerFunc(1000/FPS, scrolling, 0); 

  // printf("startgame :::: \n");
}

// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //

// timer qui gère les collisions tir et ennemis (en test : allie et ennemis gérés en +)

void updateCollisions(int valeur)
{
	if(startgame==true){ 
	enemy En = e->first;
	tir_Struct Sht = t->first;

	//checkCollisionHeroEnnemis(En); // en test

	if (e->first != NULL && t->first != NULL)
	{
		checkCollisionTirsEnnemis(En, Sht);

		if (t->first->next != NULL)
			{
				Sht = Sht->next;	
				checkCollisionTirsEnnemis(En, Sht);

				
				while (Sht->next != NULL)
				{
					Sht = Sht->next;
					checkCollisionTirsEnnemis(En, Sht);

				}
			}
		if (e->first->next != NULL)
		{
			En = En->next;
			Sht = t->first;
			checkCollisionTirsEnnemis(En, Sht);

			if (t->first->next != NULL)
			{
				Sht = Sht->next;
				checkCollisionTirsEnnemis (En, Sht);

				while (Sht->next != NULL)
				{
					Sht = Sht->next;
					checkCollisionTirsEnnemis(En, Sht);

				}
			}
			while (En->next != NULL)
			{
				En = En->next;
				Sht = t->first;
				checkCollisionTirsEnnemis(En, Sht);

				if (t->first->next != NULL)
				{
					Sht = Sht->next;
					checkCollisionTirsEnnemis (En, Sht);

					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsEnnemis(En, Sht);

					}
				}
			}
		}
	}
	}
	glutPostRedisplay();
	glutTimerFunc(10, updateCollisions, 0);
}

// --------------------------------------------------- // 

// timer qui gère les changements de statut de l'ennemi

void updateEnemies(int valeur)
{
	if(startgame==true && hero->health != 0 && hero->current_xp != MAX_SCORE)
	{ 

		car = e->first;
		if (e->first != NULL)
		{
			car->pos.y -= 0.15;
			checkCollisionAlliesEnemy(car);

			if (car->pos.y <= 0)
			{
				hero->current_xp -= 50;
				e->quantite--;
				hero->health -= 1;
				hero->killed +=1;
				car->active = false;
				drawHealth(hero);


				if(hero->health == 0)
					{
						startgame = false;
						saveScore(hero);

						glutDisplayFunc(EndGameDisplay);
						
					}

			}
			while (car->next != NULL)
			{
				car = car->next;
				car->pos.y -= 0.15;
				checkCollisionAlliesEnemy(car);

				if (car->pos.y <= 0)
				{
					//car->pos.y = 40;
					hero->current_xp -= 50;
					e->quantite--;
					car->active = false;
					hero->health -= 1;
					drawHealth(hero);

					if(hero->health == 0)
					{
						saveScore(hero);
						startgame = false;
						glutDisplayFunc(EndGameDisplay);

					}
				}
			}
		}

		}else if (hero->current_xp == MAX_SCORE){

			startgame = false;
			//suppressionEnemies(e, true);
			saveScore(hero);

			hero->current_xp = 0;

			//glutDisplayFunc(WinDisplay);

		}
	glutPostRedisplay();
	glutTimerFunc(ENNEMI_SPEED, updateEnemies, 1);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère l'insertion de nouveaux ennemis

void updateNewEnemies(int valeur)
{
	if(startgame==true){ 

	enemy new = createEnemy((&mX));
	insertionEnemies(e, new);
	
	}
	
	glutPostRedisplay();
	glutTimerFunc(100000/ENNEMI_PER_HUNDRED_SECOND, updateNewEnemies, 3);
	
}

// ---------------------------------------------------------------------------------- //

// timer qui gère le défilement des tirs

void updateTirs(int valeur)
{
	if(startgame==true){ 

	shoot = t->first;
	if (t->first != NULL)
	{
		shoot->pos.y += 0.5;
		if (shoot->pos.y >= RANGE_MAX)
		{
			shoot->active = false;
		}
		while (shoot->next != NULL)
		{
			shoot = shoot->next;
			shoot->pos.y += 0.5;
			if (shoot->pos.y >= RANGE_MAX)
			{
				shoot->active = false;
			}
		}
	}
	}
	glutPostRedisplay();
	glutTimerFunc(1, updateTirs, 2);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère les suppressions d'ennemis

void updateDeleteEnemies(int valeur)
{
	if(startgame==true){ 

		if (e->first != NULL || e->last != NULL)
		{
			suppressionEnemies(e, false);
		}

		

	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteEnemies, 4);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère les suppressions d'ennemis

void updateDeleteTirs(int valeur)
{
	if(startgame==true){ 

	if (t->first != NULL || t->last != NULL)
	{
		suppressionTirs(t, test);
	}
	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteTirs, 5);
}

// ---------------------------------------------------------------------------------- //

void updateObstacle(int valeur)
{
	if(startgame==true && hero->health != 0 && hero->current_xp != 200){ 

	fence = o->first;
	if (o->first != NULL)
	{
		fence->pos.y -= 1;

		if (fence->pos.y == 0)
		{
			fence->pos.y = 40;
			hero->current_xp -= 10;
			o->quantite--;
			

			if(hero->health == 0){
					glutDisplayFunc(EndGameDisplay);

				}

		}
		while (fence->next != NULL)
		{
			fence = fence->next;
			fence->pos.y -=1;

			if (fence->pos.y == 0)
			{
				fence->pos.y = 40;
				//hero->current_xp -= 50;
				o->quantite--;
				//hero->health -= 1;

				//drawHealth(hero);

				/*if(hero->health == 0){
					glutDisplayFunc(EndGameDisplay);

				}*/
			}
		}
	}
	}
	glutPostRedisplay();
	glutTimerFunc(OBSTACLE_SPEED, updateObstacle, 6);


}

// ---------------------------------------------------------------------------------- //

void updateNewObstacles(int valeur)
{
	if(startgame==true){ 

		obstacles new = createObstacle((&mX));
		insertionObstacles(o, new);
		
		
	}
	
	glutPostRedisplay();
	glutTimerFunc(10000/OBSTACLES_PER_TEN_SECOND, updateNewObstacles, 7);


}
// ---------------------------------------------------------------------------------- //

/*void updateDeleteObstacles(int valeur)
{
	if(startgame==true){ 

		if (o->first != NULL || o->last != NULL)
		{
			suppressionObstacles(o, test);
		}

	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteObstacles, 8);


}*/
// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //


