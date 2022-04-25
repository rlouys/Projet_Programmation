/*** LIBS ***/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/*** FILES ***/

#include "game_graphics.h"
#include "hero.h"
#include "tirs.h"

/*** FUNCTIONS ***/

// initialise une liste qui contient les tirs et leur "stats"

listetir_Struct  initialListeTirs()
{
	listetir_Struct t = malloc(sizeof(listeTirs));
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

// dessine le tir sur la map

tir_Struct createTirs(Hero hero)
{
	

	float x = (hero->pos.x)*2;
	float y = ((hero->pos.y)*2) + 2; 
	tir_Struct newTir = malloc(sizeof(tirs));
	if (newTir == NULL)
	{
		exit(EXIT_FAILURE);
	}
	newTir->pos.x = x;
	newTir->pos.y = y;
	newTir->next = NULL;
	newTir->previous = NULL;
	newTir->active = true;
	return newTir;
}

// ---------------------------------------------------------------------------------- //

//dessine le tir sur la map

void insertionTirs(listetir_Struct t, tir_Struct base)
{
	tir_Struct newTir = malloc(sizeof(tirs));
	if (newTir == NULL)
	{
		exit(EXIT_FAILURE);
	}
	newTir = base;
	if (t->first == NULL || t->last == NULL)
	{
		t->last = newTir;
		t->first = newTir;
	}
	else
	{
		newTir->next = t->first;
		t->first->previous = newTir;
		t->first = newTir;
	}
	t->quantite += 1;
}

// ---------------------------------------------------------------------------------- //

//supprime le tir s'il y a une collision (booléen renvoyé depuis timers_and_effects.h suite à un test)

void suppressionTirs(listetir_Struct t, bool test)
{
	test = false;
	if (t->first != NULL)
	{
		tir_Struct shoot = malloc(sizeof(tirs));
		shoot = t->first;
		while (shoot != NULL)
		{
			if (shoot->active == test)
			{
				tir_Struct delete = malloc(sizeof(tirs));
				delete = shoot;
				shoot = shoot->next;
				if (t->first == delete && t->last == delete)
				{
					t->last = NULL;
					t->first = NULL;
				}
				else if (t->first != delete && t->last == delete)
				{
					t->last = delete->previous;
					t->last->next = NULL;
				}
				else if (t->first == delete && t->last != delete)
				{
					t->first = delete->next;
					t->first->previous = NULL;
				}
				else
				{
					delete->next->previous = delete->previous;
					delete->previous->next = delete->next;
				}
				free(delete);
				t->quantite--;
			}
			else
			{
				shoot = shoot->next;
			}
		}
	}
}

// ---------------------------------------------------------------------------------- //

// permet au héro de tirer (createTirs + insertionTirs)

void tirer(Hero hero, listetir_Struct t)
{
	tir_Struct newTir = createTirs(hero);
	insertionTirs(t, newTir);
}
// ---------------------------------------------------------------------------------- //
