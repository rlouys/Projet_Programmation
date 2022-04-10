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


bool startgame; 

/*** FUNCTIONS ***/

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
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	return new;
}

// --------------------------------------------------------------------- // 

void insertionEnemies(EnemyList e, enemy base)
{
	//if(e->quantite <= 10){
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new = base;
	if (e->first == NULL || e->last == NULL)
	{
		e->last= new;
		e->first = new;
	}
	else
	{
		new->nextptr = e->first;
		e->first->prevptr = new;
		e->first = new;
	}
	e->quantite += 1;
	//}
}

// --------------------------------------------------------------------- // 

void suppressionEnemies(EnemyList e, bool test)
{

	test = false;
	if (e->first != NULL)
	{
		enemy base = malloc(sizeof(enemies));
		if (base == NULL)
		{
			exit(EXIT_FAILURE);
		}
		base = e->first;
		while (base != NULL)
		{
			if (base->active == test)
			{
				enemy deleted = malloc(sizeof(enemies));
				deleted = base;
				base = base->nextptr;
				if (e->first == deleted && e->last == deleted)
				{
					e->first = NULL;
					e->last = NULL;
				}
				else if (e->first != deleted && e->last == deleted)
				{
					e->last = deleted->prevptr;
					e->last->nextptr = NULL;
				}
				else if (e->first == deleted && e->first != deleted)
				{
					e->first  = deleted->nextptr;
					e->first->prevptr = NULL;
					
				}
				else
				{
					deleted->nextptr->prevptr = deleted->prevptr;
					deleted->prevptr->nextptr = deleted->nextptr;
				}
				free(deleted);
				e->quantite--;

				if(startgame==true && hero->health != 0 && hero->current_xp != 200)
				{
					hero->current_xp += 50;
				}

				//printf("Score : %f\n", hero->current_xp);

				
				if(hero->current_xp == 200)
				{
						
						glutDisplayFunc(WinDisplay);
				}

			}
			else
			{
				base = base->nextptr;
			}
		}
	}
}

// --------------------------------------------------------------------- // 
