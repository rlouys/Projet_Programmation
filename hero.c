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
int newGame;

/*** FUNCTIONS ***/



// Function to copy the string
char* copyToString(char array[])
{
    char* string;
    string = (char*)malloc(20);
 
    strcpy(string, array);
    return (char*)string;
}





char* getStringFromFile(FILE * f, char symbol)
{
	char lettre;
	int i = 0;
	char user[20];

	while(lettre != symbol)
	{
		lettre = fgetc(f);
	}
	
	while(lettre != ' ')
	{
		
		lettre = fgetc(f);
		user[i] = lettre;
		printf("user[i] : %c\n", user[i]);
		printf("%i\n", i);
		//printf("taille = %i\n", taille);
		i++;

	}

	user[i] = '\0';

	i = 0;

	username = copyToString(user);

	return username;
	//return "haruhiko";
}

// ------------------------------------------------------------------ //

char skipLine(char c, FILE * f, int skips, char symbol)
{
	//int i = 0;

	/*while(i != skips)
	{*/
		while(getc(f) != symbol)
			{
				getc(f);
			}
			//++;

	//}
		c = fgetc(f);


	return c;
}

// ------------------------------------------------------------------ //

int getIntegerFromFile(char c, FILE * f, char *class)
{

	if(strcmp(class, "xp") == 0){
		// pas de déplacement

	}else if(strcmp(class, "vie") == 0)
	{
		
		c = skipLine(c, f, 1, '#');
		//c = fgetc(f);


	}else if(strcmp(class, "atk") == 0){

		c = skipLine(c, f, 1, '(');
		//c = fgetc(f);

	}else if(strcmp(class, "killed") == 0){

		c = skipLine(c, f, 1, '@');
	//	c = fgetc(f);

	}else if(strcmp(class, "obst") == 0){
		
		c = skipLine(c, f, 1, '#');
		//c = fgetc(f);

	}
	char cd;
	int tmp;

	int key = 0;

	while(c != ' ')
	{
		tmp = charToInteger(c);
		cd = fgetc(f);

		if(cd != ' ')
		{
			if(key == 0)
			{
				nd = charToInteger(cd);
				n = concatenate(tmp,nd);
				key = 1;
			}
			else if(key == 1)
			{
				nd = charToInteger(cd);
				n = concatenate(n, tmp);
				n = concatenate(n, nd);
			}
		}
		else if(cd == ' ')
		{
			if(n_lock == 1)
			{
				n = concatenate(n, tmp);
				
			}
			else if(n_lock == 0)
			{
				n_lock = 1;
				n = tmp;
			}
		}

		c = fgetc(f); 
	}


	return n;
}


// ------------------------------------------------------------------ //

unsigned concatenate(unsigned x, unsigned y) {
    unsigned puissance = 10;

    while(y >= puissance)
        puissance *= 10;
	


    return (x * puissance) + y ;        
}

// ------------------------------------------------------------------ //

int charToInteger(char c)
{
	int numero = 0;
	numero = c - '0';

	return numero;
}

// ------------------------------------------------------------------ //

// Initialise le héro et ses statistiques

Hero createHero(int *maxX, int *maxY)
{
	//char* username = {'\0'};
	int i;

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

	//if(newGame_lock == 1)
	//{
		checkNewGame();

		//newGame = 1;
	//}

	if(newGame == 0)
	{
		FILE *f = fopen("contexte.txt", "r");
		
		// Stats initialisation

		// SCORE // 
		char c = fgetc(f); // 1
		n = getIntegerFromFile(c, f, "xp");
		hero->current_xp = n;
		n_lock = 0;

		// VIE //
		n = getIntegerFromFile(c, f, "vie");
		hero->health = n;
		// pour les chiffres < 10
		n_lock = 0;

		n = getIntegerFromFile(c, f, "atk");
		hero->attack = n;
		n_lock = 0;

		n = getIntegerFromFile(c, f, "killed");
		hero->killed = n;

		

		hero->pos.x = x;
		hero->pos.y = y;
		hero->weapon_type = false;
		hero->obstacles_taken = 0;
		hero->bonus_active = false;



		fclose(f);
	}else if(newGame == 1)
	{
		hero->health = 3;
		hero->attack = 1;
		hero->killed = 0;
		hero->current_xp = 0;
		hero->pos.x = x;
		hero->pos.y = y;
		hero->weapon_type = false;
		hero->obstacles_taken = 0;
		hero->bonus_active = false;
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
		hero->weapon_type = !(hero->weapon_type);
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

	if(cheatMode == false)
	{
		new->pos.x = x;
	}
	else if(cheatMode == true)
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