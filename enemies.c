/*** LIBS ***/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "game_graphics.h"
#include "enemies.h"
#include "menus_graphics.h"

/*** FUNCTIONS ***/
// --------------------------------------------------------------------- // 

listeEn initialListEnemies()
{
	listeEn e = malloc(sizeof(listeEnemies));
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
	int y = (rand() % (34-7+1) +7);
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->vie = 3;
	new->pos.x = y;
	new->pos.y = 50;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	return new;
}

// --------------------------------------------------------------------- // 

void insertionEnemies(listeEn e, enemy base)
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

void suppressionEnemies(listeEn e, bool test)
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
				if(p->current_xp < 1000)
				{
				p->current_xp += 50;
				}
				printf("Score : %i\n", p->current_xp);
				if(p->current_xp == 500)
				{
						glutDisplayFunc(EndGameDisplay);
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
