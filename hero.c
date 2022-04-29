/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*** FILES ***/

#include "hero.h"
#include "menus_graphics.h"
#include "game_graphics.h"

/*** VARIABLES ***/

bool startgame;
bool endmap;

/*** FUNCTIONS ***/

// ------------------------------------------------------------------ //

// Initialise le héro et ses statistiques

Hero createHero(int *maxX, int *maxY)
{
	Hero hero;

	int x = 0, y = 0;

	for (int i = 0; i < *maxX; ++i)
	{
		for (int j = 0; j < *maxY; ++j)
		{
			if(*(*(map + i) + j) == 'X')
			{
				x = j;
				y = i;
			}
		}
	}

	// Stats initialisation
	hero = malloc(sizeof(Hero)+50);
	hero->health = 40;
	hero->pos.x = x;
	hero->pos.y = y;
	hero->current_xp = 100;
	hero->attack = 1;
	hero->killed = 0;
	hero->weapon_type = false;
	hero->obstacles_taken = 0;
	hero->color_type = false;

	return hero;
}


// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveUp(Hero hero)		
{
	int y = 0;

	y = hero->pos.y+1;
     	
	if (hero->pos.y < 11)
	{
		hero->pos.y = y;
	}
}

// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveDown(Hero hero)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;
	
	x = hero->pos.x;
	y = hero->pos.y-1;

     	if (*(*(map + y) + x)!='#' )
	{
		hero->pos.y = y;
	}
}

// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveRight(Hero hero)
{
	int  x = 0, y = 0;
		
	x = hero->pos.x+1;
	y = hero->pos.y;

	if (*(*(map + y) + x)!='@')
	{
		hero->pos.x = x;
	}     
	
}

// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveLeft(Hero hero)
{
	int  x = 0, y = 0;

	x = hero->pos.x-1;
	y = hero->pos.y;

	if (*(*(map + y) + x) !='#')
	{
		hero->pos.x = x;
	}
}

// ------------------------------------------------------------------ //

void switchWeapon(Hero hero)
{
	hero->weapon_type = !(hero->weapon_type);
}

// ------------------------------------------------------------------ //

//Initialise une liste d'objets bonus vide

BonusList initialListeBonus()
{
	BonusList b = malloc(sizeof(ListeBonus));
	if (b == NULL)
	{
		exit(EXIT_FAILURE);
	}
	b->first = NULL;
	b->last = NULL;
	b->quantite = 0;

	return b;
}

// ------------------------------------------------------------------ //

// Créer et initialise les stats un ennemi

bonus_objet createBonus(int *maxY)
{
	
	bonus_objet new = malloc(sizeof(objet_bonus));
	int x = (rand() % (30-6+1) + 6);
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	//new->type = rand()%4;


	new->pos.x = x;
	new->pos.y = 65;
	new->next = NULL;
	new->previous = NULL;
	new->active = true;

	return new;
}

// --------------------------------------------------------------------- // 

// Créer un objet bonus et le place dans la liste chainée

void insertionBonus(BonusList b, bonus_objet bonus)
{
	bonus_objet newBonus = malloc(sizeof(objet_bonus));
	
	if (newBonus == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newBonus = bonus;

	if (b->first == NULL || b->last == NULL)
	{
		b->last= newBonus;
		b->first = newBonus;
	}
	else
	{
		newBonus->next = b->first;
		b->first->previous = newBonus;
		b->first = newBonus;
	}
	e->quantite += 1;
	//}
}

// --------------------------------------------------------------------- // 
//Supprime tous les objets bonus en fin de niveau

void suppressionBonusEndGame(BonusList b)
{
	
		bonus_objet newBonus = malloc(sizeof(objet_bonus));

		if(newBonus == NULL)
		{
			exit(EXIT_FAILURE);	
		}

		newBonus = b->first;

		bonus_objet deleted = malloc(sizeof(objet_bonus));

		while(newBonus != NULL)
		{
			newBonus->active = false;
			deleted = newBonus;
			newBonus = newBonus->next;
			free(deleted);

		}

}

// --------------------------------------------------------------------- // 

//Supprime un bonus et l'enleve de la liste
void suppressionBonus(BonusList b, bool test)
{

	if (b->first != NULL)
	{
		bonus_objet newBonus = malloc(sizeof(objet_bonus));
		if (newBonus == NULL)
		{
			//exit(EXIT_FAILURE);
		}
		newBonus = b->first;
		while (newBonus != NULL)
		{
			if (newBonus->active == test)
			{
				bonus_objet deleted = malloc(sizeof(objet_bonus));
				deleted = newBonus;
				newBonus = newBonus->next;
				if (b->first == deleted && b->last == deleted)
				{
				//	enemy undeleted = malloc(sizeof(enemies));
					b->first = NULL;
					b->last = NULL;
				}
				else if (b->first != deleted && b->last == deleted)
				{
					b->last = deleted->previous;
					b->last->next = NULL;
				}
				else if (b->first == deleted && b->first != deleted)
				{
					b->first  = deleted->next;
					b->first->previous = NULL;
					
				}
				else
				{
					deleted->next->previous = deleted->previous;
					deleted->previous->next = deleted->next;
				}
				free(deleted);

				b->quantite--;

				if(startgame==true && hero->health != 0 && endmap == false)
				{
					hero->current_xp += 50;
				}	
				endmap = false;		

			}
			else
			{
				newBonus = newBonus->next;
			}
		}
	}
}

// --------------------------------------------------------------------- // 
