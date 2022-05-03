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

	// position à 0, et on commence à chercher dans le fichier map
	int x = 0, y = 0; 

	for (int i = 0; i < *maxX; ++i)
	{
		for (int j = 0; j < *maxY; ++j)
		{
			if(*(*(map + i) + j) == 'X')
			{
				// quand 'X' trouvé sur la map, on note les coordonnées
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
	hero->bonus_active = false;

	return hero;
}


// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveUp(Hero hero)		
{
	int y = 0;

	y = hero->pos.y+1;
    
	// pos Y max du héro == 10
	if (hero->pos.y < 11)
	{
		hero->pos.y = y;
	}
}

// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveDown(Hero hero)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int y = hero->pos.y-1;

	// fixe la nouvelle position si pas déjà tout en bas
	if(hero->pos.y != 1)
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

	// SI LES MURS DROITS NE BLOQUENT PAS LE HERO
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

	// SI LES MURS GAUCHES NE BLOQUENT PAS LE HERO
	if (*(*(map + y) + x) !='#')
	{
		hero->pos.x = x;
	}
}

// ------------------------------------------------------------------ //

// switch l'arme du héro de fusil à canon à bulles et inversement

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

	// donne la position x de départ du bonus
	int x = (rand() % ((37+1)-11) + 11);

	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 

	new->pos.x = x;
	new->pos.y = 50;
	new->next = NULL;
	new->previous = NULL;
	new->active = true;

	// ceux qui popent du côté droit descendent vers la gauche
	if(x > 22) new->side = 1;
	// ceux qui popent du côté gauche descendent vers la droite
	else new->side = 0;

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

	// si liste vide, le bonus inséré est le premier ET le dernier
	if (b->first == NULL || b->last == NULL)
	{
		b->last= newBonus;
		b->first = newBonus;
	}

	// si liste non vide, on le rajoute à la fin de la liste
	else
	{
		newBonus->next = b->first;
		b->first->previous = newBonus;
		b->first = newBonus;
	}

	e->quantite += 1;
	
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
			exit(EXIT_FAILURE);
		}

		newBonus = b->first;

		// si bonus existe, on vérifie quand il passe inactive
		// à ce moment là on le compare avec un booléen test false
		// si false, alors on supprime l'ennemi en le mettant
		// dans une structure "poubelle"
		while (newBonus != NULL)
		{
			if (newBonus->active == test)
			{
				bonus_objet deleted = malloc(sizeof(objet_bonus));
				deleted = newBonus;
				newBonus = newBonus->next;

				// si liste avec un seul élement (newBonus)
				// alors on supprime toute la liste via first/last == NULL
				if (b->first == deleted && b->last == deleted)
				{
					b->first = NULL;
					b->last = NULL;
				}

				// si newBonus est le dernier element de la liste
				// on place la limite de la liste un cran en arrière
				// ce qui a pour effet de supprimer l'objet bonus
				else if (b->first != deleted && b->last == deleted)
				{
					b->last = deleted->previous;
					b->last->next = NULL;
				}

				// si newBonus est le premier element de la liste
				// on place le départ de la liste un cran en avant
				// ce qui a pour effet de supprimer l'objet bonus
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


				// si le jeu est en cours, que le héro n'est pas à cours de vie
				// que le bonus n'est pas arrivé à la fin de la map
				// alors le joueur récupère 50 d'expérience.
				if(startgame==true && hero->health != 0 && endmap == false)
				{
					hero->current_xp += 50;
				}	
			}

			else
			{
				newBonus = newBonus->next;
			}
		}
	}
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

		// désactivation e tous les bonus et mise du bonus dans une
		// structure "poubelle" pour free();
		while(newBonus != NULL)
		{
			newBonus->active = false;
			deleted = newBonus;
			newBonus = newBonus->next;
			free(deleted);

		}

}