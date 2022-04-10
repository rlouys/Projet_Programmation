/*** LIBS ***/

#include <GL/glut.h>
#include "game_graphics.h"
#include "hero.h"
#include "tirs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/*** FUNCTIONS ***/

// ---------------------------------------------------------------------------------- //

listetirsP  initialListeTirs()
{
	listetirsP t = malloc(sizeof(listeTirs));
	if (t == NULL)
	{
		exit(EXIT_FAILURE);
	}
	t->first = NULL;
	t->last = NULL;
	t->quantite = 0;
	return t;
}

// ---------------------------------------------------------------------------------- //

tirsP createTirs(Hero hero)
{
	

	int x = (hero->pos.x)*2;
	int y = ((hero->pos.y)*2) + 2; 
	tirsP new = malloc(sizeof(tirs));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	return new;
}

// ---------------------------------------------------------------------------------- //

void insertionTirs(listetirsP t, tirsP base)
{
	tirsP new = malloc(sizeof(tirs));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new = base;
	if (t->first == NULL || t->last == NULL)
	{
		t->last = new;
		t->first = new;
	}
	else
	{
		new->nextptr = t->first;
		t->first->prevptr = new;
		t->first = new;
	}
	t->quantite += 1;
}

// ---------------------------------------------------------------------------------- //

void suppressionTirs(listetirsP t, bool test)
{
	test = false;
	if (t->first != NULL)
	{
		tirsP base = malloc(sizeof(tirs));
		base = t->first;
		while (base != NULL)
		{
			if (base->active == test)
			{
				tirsP delete = malloc(sizeof(tirs));
				delete = base;
				base = base->nextptr;
				if (t->first == delete && t->last == delete)
				{
					t->last = NULL;
					t->first = NULL;
				}
				else if (t->first != delete && t->last == delete)
				{
					t->last = delete->prevptr;
					t->last->nextptr = NULL;
				}
				else if (t->first == delete && t->last != delete)
				{
					t->first = delete->nextptr;
					t->first->prevptr = NULL;
				}
				else
				{
					delete->nextptr->prevptr = delete->prevptr;
					delete->prevptr->nextptr = delete->nextptr;
				}
				free(delete);
				t->quantite--;
			}
			else
			{
				base = base->nextptr;
			}
		}
	}
}

// ---------------------------------------------------------------------------------- //

void tirer(Hero hero, listetirsP t)
{
	tirsP new = createTirs(hero);
	insertionTirs(t, new);
}
// ---------------------------------------------------------------------------------- //
