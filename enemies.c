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
bool endmap;

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
	int x = (rand() % (30-6+1) + 6);
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->vie = 1;
	new->pos.x = x;
	new->pos.y = 65;
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

//Supprime tous les ennemis en fin de niveau
void suppressionEnemiesEndGame(EnemyList e)
{
	
		enemy newEnemy = malloc(sizeof(enemies));

		if(newEnemy == NULL)
		{
			exit(EXIT_FAILURE);	
		}

		newEnemy = e->first;

		enemy deleted = malloc(sizeof(enemies));

		while(newEnemy != NULL)
		{
			newEnemy->active = false;
			deleted = newEnemy;
			newEnemy = newEnemy->next;
			free(deleted);

		}

}
// --------------------------------------------------------------------- // 
//Supprime tous les obstacles en fin de niveau

void suppressionObstaclesEndGame(ObstacleList o)
{
	
		obstacles newObstacle = malloc(sizeof(obstacle));

		if(newObstacle == NULL)
		{
			exit(EXIT_FAILURE);	
		}

		newObstacle = o->first;

		obstacles deleted = malloc(sizeof(obstacle));

		while(newObstacle != NULL)
		{
			newObstacle->active = false;
			deleted = newObstacle;
			newObstacle = newObstacle->next;
			free(deleted);

		}

}
// --------------------------------------------------------------------- // 

//Supprime un ennemi et l'enleve de la liste

void suppressionEnemies(EnemyList e, bool test)
{

	if (e->first != NULL)
	{
		enemy newEnemy = malloc(sizeof(enemies));
		if (newEnemy == NULL)
		{
			//exit(EXIT_FAILURE);
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
				free(deleted);

				e->quantite--;

				if(startgame==true && hero->health != 0 && endmap == false)
				{
					hero->current_xp += 50;
				}	
				endmap = false;		

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
	int x = (rand() % (30-6+1) +6);
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->pos.x = x;
	new->pos.y = 55;

	new->next = NULL;
	new->previous = NULL;
	new->jailed = false;
	new->active = true;

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

//Supprime un obstacle et l'enleve de la liste

void suppressionObstacles(ObstacleList o, bool test)
{

	if (o->first != NULL)
	{
		obstacles newObstacle = malloc(sizeof(obstacle));
		if (newObstacle == NULL)
		{
			//exit(EXIT_FAILURE);
		}
		newObstacle = o->first;
		while (newObstacle != NULL)
		{
			if (newObstacle->active == test)
			{
				obstacles deleted = malloc(sizeof(obstacle));
				deleted = newObstacle;
				newObstacle = newObstacle->next;
				if (o->first == deleted && o->last == deleted)
				{
				//	enemy undeleted = malloc(sizeof(enemies));
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

				if(startgame==true && hero->health != 0 && endmap == false)
				{
					hero->current_xp += 10;
				}	
				endmap = false;		

			}
			else
			{
				newObstacle = newObstacle->next;
			}
		}
	}
}

// --------------------------------------------------------------------- // 
