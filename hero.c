/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*** FILES ***/

#include "hero.h"
#include "menus_graphics.h"
#include "game_graphics.h"

/*** VARIABLES ***/

int n_lock = 0;
int n;
int nd;
int newGame_lock;

bool startgame;
bool endmap;
bool cheatMode;

float difficulty;

char *username;
char username_array[20];

int newGame;

/*** FUNCTIONS ***/

// ------------------------------------------------------------------ //

// Initialise le héro et ses statistiques

Hero createHero(int *maxX, int *maxY)
{
	int i;

	int xp, vie, attack, killed, obstacles, weapon, bonus, jeu;

	float posx, posy;

	char name[20];

	Hero hero = malloc(sizeof(struct Hero));

	// position à 0, et on commence à chercher dans le fichier map
	int x = 0, y = 0; 

	for ( i = 0; i < *maxX; ++i)
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
	newGame = checkNewGame(newGame);

	if(newGame == 0)
	{
		FILE *f = fopen("hero_save.txt", "r");
		
		// Stats initialisation	

		if(f == NULL)
		{
			printf("Impossible de charger le fichier\n");
			exit(1);
    	}

		fscanf(f, "%s %d %d %d %d %d %d %d %d %f %f", name, &jeu, &xp, &vie, &attack, &killed, &obstacles, &weapon, &bonus, &posx, &posy);

		if(newGame == 0)
		{
			fscanf(f, "%s", name);
			username = copyToString(name);
		}
		if(newGame == 1)
		{
			username = copyToString(username_array);
		}

		//getUsername();
		hero->current_xp = xp;
		hero->health = vie;
		hero->attack = attack;
		hero->killed = killed;

		hero->pos.x = posx;
		hero->pos.y = posy;
		hero->weapon_type = weapon;
		hero->obstacles_taken = obstacles;
		hero->bonus_active = bonus;

		hero->ulti_active = 0;


		fclose(f);
	}else if(newGame == 1)
	{
		hero->health = 5;
		hero->attack = 3;
		hero->killed = 0;
		hero->red_killed = 0;
		hero->purple_killed = 0;
		hero->gold_killed = 0;
		hero->current_xp = 0;
		hero->pos.x = x;
		hero->pos.y = y;
		hero->weapon_type = 0;
		hero->obstacles_taken = 0;
		hero->bonus_active = 0;
		hero->ulti_active = 0;

	}

	return hero;
}


// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveUp(Hero hero)		
{
	int y = 0;

    
	// pos Y max du héro == 10
	if(cheatMode == false)
	{
		y = hero->pos.y+1;

		// SI LES MURS DROITS NE BLOQUENT PAS LE HERO
		if (hero->pos.y <= 11)
		{
			hero->pos.y = y;
		}
	}
	else
	{
		y = hero->pos.y+3;

		// SI LES MURS DROITS NE BLOQUENT PAS LE HERO
		if (y < 12)
		{
			hero->pos.y = y;
		}
		else if (y >= 12)
		{
			hero->pos.y = 11;
		}
	}
}

// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveDown(Hero hero)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int y = 0;

    
	// pos Y max du héro == 10
	if(cheatMode == false)
	{
		y = hero->pos.y-1;

		// SI LES MURS DROITS NE BLOQUENT PAS LE HERO
		if (hero->pos.y >= 2)
		{
			hero->pos.y = y;
		}
	}
	else
	{
		y = hero->pos.y-3;

		// SI LES MURS DROITS NE BLOQUENT PAS LE HERO
		if (y >= 2)
		{
			hero->pos.y = y;
		}
		else if (y < 2)
		{
			hero->pos.y = 1;
		}
	}
}

// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveRight(Hero hero)
{
	int  x = 0, y = 0;
		
	if(cheatMode == false)
	{
		
		x = hero->pos.x+1;
		y = hero->pos.y;

		// SI LES MURS DROITS NE BLOQUENT PAS LE HERO
		if (*(*(map + y) + x) !='@')
		{
			hero->pos.x = x;
		}
	}
	else
	{
		x = hero->pos.x+3;
		y = hero->pos.y;

		// SI LES MURS DROITS NE BLOQUENT PAS LE HERO
		if ( *(*(map + y) + x) !='@' && *(*(map + y) + (x-1)) != '@' && *(*(map + y) + (x-2)) != '@' )
		{
			hero->pos.x = x;
		}
		else if (*(*(map + y) + x) == '@')
		{
			hero->pos.x = x-1;
		}
		else if( *(*(map + y) + (x-1)) == '@')
		{
			hero->pos.x = x-2;
		}
	}
}

// ------------------------------------------------------------------ //

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.

void moveLeft(Hero hero)
{
	int  x = 0, y = 0;

	if(cheatMode == false)
	{
		
		x = hero->pos.x-1;
		y = hero->pos.y;

		// SI LES MURS GAUCHES NE BLOQUENT PAS LE HERO
		if (*(*(map + y) + x) !='#')
		{
			hero->pos.x = x;
		}
	}
	else
	{
		x = hero->pos.x-3;
		y = hero->pos.y;

		// SI LES MURS GAUCHES NE BLOQUENT PAS LE HERO
		if ( *(*(map + y) + x) !='#' && *(*(map + y) + (x+1)) !='#' && *(*(map + y) + (x+2)) != '#' )
		{
			hero->pos.x = x;
		}
		else if (*(*(map + y) + x) =='#')
		{
			hero->pos.x = x+1;
		}
		else if( *(*(map + y) + (x+1)) == '#')
		{
			hero->pos.x = x+2;
		}
	}





}

// ------------------------------------------------------------------ //

// switch l'arme du héro de fusil à canon à bulles et inversement

void switchWeapon(Hero hero)
{
	// change l'arme tenue par le héro
	if(cheatMode == false)
	{
		if(hero->weapon_type == 1)
		{
			hero->weapon_type = 0;
		}
		else if(hero->weapon_type == 0)
		{
			hero->weapon_type = 1;
		}
	}
	
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

	if(cheatMode == false && hero->ulti_active == 0)
	{
		new->pos.x = x;
	}
	else if(cheatMode == true || hero->ulti_active == 1)
	{
		new->pos.x = 80;
	}
	new->pos.y = 90;
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

	b->quantite += 1;
	
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


		// désactivation e tous les bonus et mise du bonus dans une
		// structure "poubelle" pour free();
		while(newBonus != NULL)
		{
			newBonus->active = false;
			bonus_objet deleted = malloc(sizeof(objet_bonus));

			deleted = newBonus;
			newBonus = newBonus->next;
			
			free(deleted);

		}

}