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

bool startgame; // état du jeu en cours (pause ou en cours)
bool endmap; // état de l'ennemi (fin de map ou pas)
bool PURPLE = false;
bool GOLD = false;
bool RED = false;

int level;

float difficulty;
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

enemy setEnemyLevel(enemy car)
{

	
	if(RED == true)
	{
		car->color = 0;
		RED = false;
		car->vie = 3;

	}
	else if(PURPLE == true)
	{
		car->color = 1;
		PURPLE = false;
		car->vie = 15;


	}
	else if(GOLD == true)
	{
		car->color = 2;
		GOLD = false;
		car->vie = 50;

	}

		return car;
	
}

// --------------------------------------------------------------------- // 

// Créer et initialise les stats un ennemi

enemy createEnemy(int *maxY)
{
	setLevel();

	/*if(hero->current_xp >= 400 && hero->current_xp <= 500)
	{
		level++;
	}*/
	// allocation de l'ennemi
	enemy new = malloc(sizeof(struct enemies));

	//l'ennemi apparaitra sur les cases entre la 11eme et 37eme case du plateau
	float x = (rand() % ((37+1)-11) + 11);

	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 

	setEnemyLevel(new);
	//initialisation des stats de l'ennemi
	//new->vie = 3;
	new->pos.x = x;
	new->pos.y = 55.0;
	new->next = NULL;
	new->previous = NULL;
	new->active = true;
	new->slowness = 0;
	//new->color = 3;
	new->changed = false;

	return new;
}


// --------------------------------------------------------------------- // 

// Créer et initialise les stats d'un obstacle

obstacles createObstacle(int *maxY)
{
	setLevel();

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


					if(newEnemy->color == 2)
					{
						hero->current_xp += 500+((difficulty-1)*10);
					}
					else if(newEnemy->color == 1)
					{
						hero->current_xp += 250+((difficulty-1)*10);
					}
					else if(newEnemy->color == 0)
					{
						hero->current_xp += 150+((difficulty)*10);
					}

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
					/*if(newEnemy->color == 2)
					{
						hero->current_xp += 500;//+((difficulty-1)*10);

					}
					else if(newEnemy->color == 1)
					{
						hero->current_xp += 150;

					}
					else if(newEnemy->color == 0)
					{
						hero->current_xp += 50;

					}*/

				}else if(endmap == true)
				{
					endmap = false;
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
				}else if(endmap == true)
				{
					endmap = false;
				}		

			}
			else
			{
				newObstacle = newObstacle->next;
			}
		}
	}
}

