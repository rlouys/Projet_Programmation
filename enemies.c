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

// Initialise une liste d'ennemis vide

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
	new->vie = 3;
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

//Supprime un ennemi et l'enleve de la liste

void suppressionEnemies(EnemyList e, bool test)
{

	test = false;
	if (e->first != NULL)
	{
		enemy newEnemy = malloc(sizeof(enemies));
		if (newEnemy == NULL)
		{
			exit(EXIT_FAILURE);
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

				if(startgame==true && hero->health != 0 && hero->current_xp != 200)
				{
					hero->current_xp += 50;
				}

				if(hero->current_xp == 200)
				{
						glutDisplayFunc(WinDisplay);
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
