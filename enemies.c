/*** LIBS ***/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "game_graphics.h"
#include "enemies.h"

/*** FUNCTIONS ***/
// --------------------------------------------------------------------- // 

listeEn initialListEnemies()
{
	listeEn e = malloc(sizeof(listeEnemies));
	if (e == NULL)
	{
		exit(EXIT_FAILURE);
	}
	e->starList = NULL;
	e->endList = NULL;
	e->quantite = 0;
	return e;
}

// --------------------------------------------------------------------- // 

enemy createEnemy(int *maxY)
{
	enemy new = malloc(sizeof(enemies));
	int y = (rand() % (*maxY + 10) + 1);
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->vie = 1;
	new->pos.x = 5;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	return new;
}

// --------------------------------------------------------------------- // 

void insertionEnemies(listeEn e, enemy base)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new = base;
	if (e->starList == NULL || e->endList == NULL)
	{
		e->endList= new;
		e->starList = new;
	}
	else
	{
		new->nextptr = e->starList;
		e->starList->prevptr = new;
		e->starList = new;
	}
	e->quantite += 1;
}

// --------------------------------------------------------------------- // 

void suppressionEnemies(listeEn e, bool test)
{
	test = false;
	if (e->starList != NULL)
	{
		enemy base = malloc(sizeof(enemies));
		if (base == NULL)
		{
			exit(EXIT_FAILURE);
		}
		base = e->starList;
		while (base != NULL)
		{
			if (base->active == test)
			{
				enemy deleate = malloc(sizeof(enemies));
				deleate = base;
				base = base->nextptr;
				if (e->starList == deleate && e->endList == deleate)
				{
					e->starList = NULL;
					e->endList = NULL;
				}
				else if (e->starList != deleate && e->endList == deleate)
				{
					e->endList = deleate->prevptr;
					e->endList->nextptr = NULL;
				}
				else if (e->starList == deleate && e->endList != deleate)
				{
					e->starList  = deleate->nextptr;
					e->starList->prevptr = NULL;
				}
				else
				{
					deleate->nextptr->prevptr = deleate->prevptr;
					deleate->prevptr->nextptr = deleate->nextptr;
				}
				free(deleate);
				e->quantite--;
			}
			else
			{
				base = base->nextptr;
			}
		}
	}
}

// --------------------------------------------------------------------- // 
