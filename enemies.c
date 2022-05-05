/*** LIBS ***/

//#include <GL/glut.h>
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

						/*******************
						 * INITIALISATIONS *
						 *******************/

//Initialise une liste d'ennemis vide

EnemyList initialListEnemies()
{
	//allocation mémoire pour la liste chainée des ennemis
	EnemyList e = malloc(sizeof(ListEnemy));

	//si non crée après coup, alors on exit
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

// Initialise une liste d'obstacles vide

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

// Créer et initialise les stats un ennemi

enemy createEnemy(int *maxY)
{
	// allocation de l'ennemi
	enemy new = malloc(sizeof(enemies));

	//l'ennemi apparaitra sur les cases entre la 11eme et 37eme case du plateau
	float x = (rand() % ((37+1)-11) + 11);

	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 

	//initialisation des stats de l'ennemi
	new->vie = 3;
	new->pos.x = x;
	new->pos.y = 50.0;
	new->next = NULL;
	new->previous = NULL;
	new->active = true;
	new->slowness = 0;

	return new;
}


// --------------------------------------------------------------------- // 

// Créer et initialise les stats d'un obstacle

obstacles createObstacle(int *maxY)
{
	// allocation de l'obstacle
	obstacles new = malloc(sizeof(obstacle));

	// l'ennemi apparaitra sur les cases entre la 11eme et 37eme case du plateau
	float x = (rand() % ((37+1)-11) + 11);

	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 

	// initialisation des stats de l'obstacle
	new->pos.x = x;
	new->pos.y = 55;
	new->next = NULL;
	new->previous = NULL;
	new->jailed = false;
	new->active = true;

	return new;
}


						/***************
						 * ALLOCATIONS *
						 ***************/

// Place un ennemi dans la liste chainée des ennemis

void insertionEnemies(EnemyList e, enemy car)
{
	enemy newEnemy = malloc(sizeof(enemies));
	
	if (newEnemy == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newEnemy = car;

	// si la liste est vide, alors l'ennemi est le premier ET le dernier de la liste
	if (e->first == NULL || e->last == NULL)
	{
		e->last= newEnemy;
		e->first = newEnemy;
	}
	
	else
	{
		// placement dans la liste
		newEnemy->next = e->first;
		e->first->previous = newEnemy;
		e->first = newEnemy;
	}
	e->quantite += 1;
	//}
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

	// si la liste est vide, alors l'obstacle est le premier ET le dernier de la liste

	if (o->first == NULL || o->last == NULL)
	{
		o->last= newObstacle;
		o->first = newObstacle;
	}
	else
	{
		// placement dans la liste
		newObstacle->next = o->first;
		o->first->previous = newObstacle;
		o->first = newObstacle;
	}
	o->quantite += 1;
	//}
}


						/****************
						 * SUPPRESSIONS *
						 ****************/

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
			// si ennemi->active == false, on initialise un enemy "poubelle"
			// On place l'ennemi dans la "poubelle" puis on le remplace dans la
			// liste par l'ennemi suivant (newEnemy = newEnemy->next)
			// avant de free(); la classe poubelle
			if (newEnemy->active == test)
			{
				enemy deleted = malloc(sizeof(enemies));
				deleted = newEnemy;
				newEnemy = newEnemy->next;

				// si un seul element, alors on vide la liste en remplaçant
				// first et last par NULL.
				if (e->first == deleted && e->last == deleted)
				{
					e->first = NULL;
					e->last = NULL;
				}

				// si c'est le dernier element de la liste && liste plurale.
				else if (e->first != deleted && e->last == deleted)
				{
					e->last = deleted->previous;
					e->last->next = NULL;
				}

				// si c'est le premier élément dans la liste && liste plurale
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

				// si le jeu est actif et que le héro à de la vie, 
				// alors augmente le score du héro car ennemi supprimé
				if(startgame==true && hero->health != 0 && endmap == false)
				{
					hero->current_xp += 50;
				}	
				
				//endmap = false;		

			}
			else
			{
				newEnemy = newEnemy->next;
			}
		}
	}
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
					o->first = NULL;
					o->last = NULL;
				}

				// si c'est le dernier element de la liste && liste plurale.
				else if (o->first != deleted && o->last == deleted)
				{
					o->last = deleted->previous;
					o->last->next = NULL;
				}

				// si c'est le premier element de la liste && liste plurale.
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


				// si le jeu est actif et que le héro à de la vie, 
				// alors augmente le score du héro car obstacle supprimé

				if(startgame==true && hero->health != 0 && endmap == false)
				{
					hero->current_xp += 50;
				}	
				//endmap = false;		

			}
			else
			{
				newObstacle = newObstacle->next;
			}
		}
	}
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

		// initialisation d'un élément "poubelle"
		enemy deleted = malloc(sizeof(enemies));

		//supprime tous les ennemis toujours dans la liste à la fin de la partie
		//(tant que non NULL) en les passant en active = false 
		//(pour être supprimé via le timer UpdateDeleteEnnemis)
		// en cas où, place l'ennemi dans une liste qui va être free();
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

		// initialisation d'un élément "poubelle"
		obstacles deleted = malloc(sizeof(obstacle));

		//supprime tous les obstacles toujours dans la liste à la fin de la partie
		//(tant que non NULL) en les passant en active = false 
		//(pour être supprimé via le timer UpdateDeleteObstacles)
		// en cas où, place l'ennemi dans une liste qui va être free();

		while(newObstacle != NULL)
		{
			newObstacle->active = false;
			deleted = newObstacle;
			newObstacle = newObstacle->next;
			free(deleted);

		}

}