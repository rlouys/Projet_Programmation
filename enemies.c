/*** LIBS ***/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/*** FILES ***/

#include "game_graphics.h"
#include "enemies.h"
#include "menus_graphics.h"

/*** VARIABLES ***/

bool startgame; 

/*** FUNCTIONS ***/

//Initialise une liste d'ennemis vide

EnemyList initialListEnemies()
{
	EnemyList e = malloc(sizeof(ListEnemy));
	if (e == NULL)
	{
		exit(EXIT_FAILURE);
	}
	e->first = NULL;
	e->last = NULL;
	e->quantite = 0;
	return e;
}

// --------------------------------------------------------------------- // 

// Créer et initialise les stats un ennemi

enemy createEnemy(int *maxY)
{
	
	enemy new = malloc(sizeof(enemies));
	int x = (rand() % (30-5+1) +5);
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->vie = 1;
	new->pos.x = x;
	new->pos.y = 51;
	new->next = NULL;
	new->previous = NULL;
	new->active = true;
	return new;
}

// --------------------------------------------------------------------- // 

// Créer un ennemi et le place dans la liste chainée

void insertionEnemies(EnemyList e, enemy car)
{
	enemy newEnemy = malloc(sizeof(enemies));
	
	if (newEnemy == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newEnemy = car;

	if (e->first == NULL || e->last == NULL)
	{
		e->last= newEnemy;
		e->first = newEnemy;
	}
	else
	{
		newEnemy->next = e->first;
		e->first->previous = newEnemy;
		e->first = newEnemy;
	}
	e->quantite += 1;
	//}
}

// --------------------------------------------------------------------- // 

//Clean la map des ennemis

/*void deleteAllEnemies(EnemyList e)
{

	
	//int i;

	//for(i = 0; i <= e->quantite; i++)
	//{

		if(e->first != NULL){

			suppressionEnemies(e, true);
		}

	//}

}*/


// --------------------------------------------------------------------- // 

//Supprime un ennemi et l'enleve de la liste

void suppressionEnemies(EnemyList e, bool test)
{

	if (e->first != NULL)
	{
		enemy newEnemy = malloc(sizeof(enemies));
		if (newEnemy == NULL)
		{
		//	exit(EXIT_FAILURE);
		}
		newEnemy = e->first;
		while (newEnemy != NULL)
		{
			if (newEnemy->active == test)
			{
				enemy deleted = malloc(sizeof(enemies));
				deleted = newEnemy;
				newEnemy = newEnemy->next;
				if (e->first == deleted && e->last == deleted)
				{
				//	enemy undeleted = malloc(sizeof(enemies));
					e->first = NULL;
					e->last = NULL;
				}
				else if (e->first != deleted && e->last == deleted)
				{
					e->last = deleted->previous;
					e->last->next = NULL;
				}
				else if (e->first == deleted && e->first != deleted)
				{
					e->first  = deleted->next;
					e->first->previous = NULL;
					
				}
				else
				{
					deleted->next->previous = deleted->previous;
					deleted->previous->next = deleted->next;
				}
				//free(deleted);

				e->quantite--;

				if(startgame==true && hero->health != 0 && hero->current_xp != 200)
				{
					hero->current_xp += 50;
				}			

			}
			else
			{
				newEnemy = newEnemy->next;
			}
		}
	}
}

// --------------------------------------------------------------------- // 

//Initialise une liste d'obstacles vide

ObstacleList initialListObstacles()
{
	ObstacleList o = malloc(sizeof(ObstacleList));
	if (o == NULL)
	{
		exit(EXIT_FAILURE);
	}
	o->first = NULL;
	o->last = NULL;
	o->quantite = 0;

	return o;
}

// --------------------------------------------------------------------- // 

// Créer et initialise les stats d'un obstacle

obstacles createObstacle(int *maxY)
{
	
	obstacles new = malloc(sizeof(obstacle));
	int x = (rand() % (30-5+1) +5);
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->pos.x = x;
	new->pos.y = 55;

	new->next = NULL;
	new->previous = NULL;
	new->jailed = false;

	return new;
}

// --------------------------------------------------------------------- // 

// Créer un obstacle et le place dans la liste chainée

void insertionObstacles(ObstacleList o, obstacles fence)
{
	obstacles newObstacle = malloc(sizeof(obstacle));
	
	if (newObstacle == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newObstacle = fence;

	if (o->first == NULL || o->last == NULL)
	{
		o->last= newObstacle;
		o->first = newObstacle;
	}
	else
	{
		newObstacle->next = o->first;
		o->first->previous = newObstacle;
		o->first = newObstacle;
	}
	o->quantite += 1;
	//}
}

// --------------------------------------------------------------------- // 
/*
Supprime un obstacle et l'enleve de la liste

void suppressionObstacles(ObstacleList o, bool test)
{

	test = false;
	if (o->first != NULL)
	{
		obstacles newObstacle = malloc(sizeof(obstacle));
		if (newObstacle == NULL)
		{
			exit(EXIT_FAILURE);
		}
		newObstacle = o->first;
		while (newObstacle != NULL)
		{
			if (newObstacle->jailed == test)
			{
				obstacles deleted = malloc(sizeof(obstacle));
				deleted = newObstacle;
				newObstacle = newObstacle->next;
				if (o->first == deleted && o->last == deleted)
				{
					o->first = NULL;
					o->last = NULL;
				}
				else if (o->first != deleted && o->last == deleted)
				{
					o->last = deleted->previous;
					o->last->next = NULL;
				}
				else if (o->first == deleted && o->first != deleted)
				{
					o->first  = deleted->next;
					o->first->previous = NULL;
					
				}
				else
				{
					deleted->next->previous = deleted->previous;
					deleted->previous->next = deleted->next;
				}
				free(deleted);
				o->quantite--;

				if(startgame==true && hero->health != 0 && hero->current_xp != 200)
				{
					hero->current_xp += 10;
				}

				if(hero->current_xp == 200)
				{
						glutDisplayFunc(WinDisplay);
				}

			}
			else
			{
				newObstacle->next = newObstacle->next;
			}
		}
	}
}

// --------------------------------------------------------------------- // 
*/