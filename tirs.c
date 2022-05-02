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


					/******************
					 * INITIALISATION *
					 ******************/

// initialise une liste qui contient les tirs et leur "stats"

listetir_Struct  initialListeTirsHero()
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

// initialise une liste qui contient les tirs
listetir_StructEnemy  initialListeTirsEnemy()
{
	listetir_StructEnemy te = malloc(sizeof(listeTirs));
	if (te == NULL)
	{
		exit(EXIT_FAILURE);
	}
	te->first = NULL;
	te->last = NULL;
	te->quantite = 0;
	return te;
}
// ---------------------------------------------------------------------------------- //

// dessine le tir sur la map

tir_Struct createTirsHero(Hero hero)
{
	
	// le tir est positionné sur la position du héro
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

// dessine le tir sur la map

tir_Struct createTirsEnemy(enemy en)
{
	
	// le tir est positionné sur la position de l'ennemi en cours
	float x = (en->pos.x)*2;
	float y = ((en->pos.y)*2) + 1; 

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


					/***************
					 * ALLOCATIONS *
					 ***************/


// insère le tir allié dans la liste

void insertionTirsHero(listetir_Struct t, tir_Struct base)
{
	tir_Struct newTir = malloc(sizeof(tirs));
	if (newTir == NULL)
	{
		exit(EXIT_FAILURE);
	}
	newTir = base;

	//insère des tirs dans une liste en fonction de l'état de la liste
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

// dessine le tir ennemi dans la liste

void insertionTirsEnemy(listetir_StructEnemy te, tir_Struct base)
{
	tir_Struct newTir = malloc(sizeof(tirs));
	if (newTir == NULL)
	{
		exit(EXIT_FAILURE);
	}
	newTir = base;
	if (te->first == NULL || te->last == NULL)
	{
		te->last = newTir;
		te->first = newTir;
	}
	else
	{
		newTir->next = te->first;
		te->first->previous = newTir;
		te->first = newTir;
	}
	te->quantite += 1;
}

					/****************
					 * SUPPRESSIONS *
					 ****************/

//supprime le tir allié s'il y a une collision (booléen renvoyé depuis timers_and_effects.h suite à un test)

void suppressionTirsHero(listetir_Struct t, bool test)
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

// supprime le tir ennemi s'il y a une collision (booléen renvoyé depuis timers_and_effects.h suite à un test)

void suppressionTirsEnemy(listetir_StructEnemy te, bool test)
{
	test = false;
	if (te->first != NULL)
	{
		tir_Struct shoot = malloc(sizeof(tirs));
		shoot = te->first;
		while (shoot != NULL)
		{
			if (shoot->active == test)
			{
				tir_Struct delete = malloc(sizeof(tirs));
				delete = shoot;
				shoot = shoot->next;
				if (te->first == delete && te->last == delete)
				{
					te->last = NULL;
					te->first = NULL;
				}
				else if (te->first != delete && te->last == delete)
				{
					te->last = delete->previous;
					te->last->next = NULL;
				}
				else if (te->first == delete && te->last != delete)
				{
					te->first = delete->next;
					te->first->previous = NULL;
				}
				else
				{
					delete->next->previous = delete->previous;
					delete->previous->next = delete->next;
				}
				free(delete);
				te->quantite--;
			}
			else
			{
				shoot = shoot->next;
			}
		}
	}
}

// supprime tous les tirs en fin de niveau

void suppressionTirsEndGame(listetir_Struct t)
{
	tir_Struct newTir = malloc(sizeof(tirs));

		if(newTir == NULL)
		{
			exit(EXIT_FAILURE);	
		}

		newTir = t->first;

		while(newTir != NULL)
		{
			// désactivation des tirs pour suppression
			// mise dans une structure "poubelle" pour free();
			newTir->active = false;
			tir_Struct deleted = malloc(sizeof(tirs));
			deleted = newTir;
			newTir = newTir->next;
			free(deleted);

		}

}

// ---------------------------------------------------------------------------------- //

						/***********
						 * ACTIONS *
						 ***********/

// permet au héro de tirer (createTirs + insertionTirs) 
//lié à la barre d'espace

void tirer(Hero hero, listetir_Struct t)
{
	tir_Struct newTir = createTirsHero(hero);
	insertionTirsHero(t, newTir);
}
// ----------------------------Hero hero------------------------------------------------------ //

// permet à l'ennemi  de tirer (createTirs + insertionTirs) 
//lié à la barre d'espace
void tirer_enemy(enemy en, listetir_StructEnemy te)
{
	tir_Struct newTir = createTirsEnemy(en);
	insertionTirsEnemy(te, newTir);
}