#ifndef _TIRS_H_
#define _TIRS_H_

/*** LIBS ***/ 
#include <stdbool.h>
#include "hero.h"

/*** STRUCTURES ***/ 

struct positionT
{
	float x;
	float y;
};
typedef struct tirs tirs;

struct tirs
{
	struct positionT pos;
	bool active;
	struct tirs *previous;
	struct tirs *next;
};

typedef struct listeTirs listeTirs;
struct listeTirs
{
	
	int quantite;
	struct tirs *first;
	struct tirs *last;
	
};

typedef struct listeTirsEnemy listeTirsEnemy;
struct listeTirsEnemy
{
	int quantite;
	struct tirs *first;
	struct tirs *last;
};

typedef struct tirs *tir_Struct; 
typedef struct listeTirs *listetir_Struct;
typedef struct listeTirsEnemy *listetir_StructEnemy;



/*** VARIABLES ***/ 

tir_Struct shoot;
listetir_Struct t;
listetir_StructEnemy te;

/*** FUNCTIONS ***/

					/******************
					 * INITIALISATION *
					 ******************/

// initialise une liste qui contient les tirs et leur "stats"
listetir_Struct  initialListeTirsHero();

// initialise une liste qui contient les tirs et leur "stats"
listetir_StructEnemy  initialListeTirsEnemy();

// positionne le tir sur la map devant le héro
tir_Struct createTirsHero(Hero hero);

// positionne le tir sur la map devant l'ennemi
tir_Struct createTirsEnemy(enemy en);


					/***************
					 * ALLOCATIONS *
					 ***************/


//dessine le tir allié sur la map et incrémente la liste
void insertionTirsHero(listetir_Struct t, tir_Struct base);

//dessine le tir ennemi sur la map et incrémente la liste
void insertionTirsEnemy(listetir_StructEnemy te, tir_Struct base);


					/****************
					 * SUPPRESSIONS *
					 ****************/

//supprime le tir allié s'il y a une collision (booléen renvoyé depuis timers_and_effects.h suite à un test)
void suppressionTirsHero(listetir_Struct t, bool test);

//supprime le tir ennemi s'il y a une collision (booléen renvoyé depuis timers_and_effects.h suite à un test)
void suppressionTirsEnemy(listetir_StructEnemy te, bool test);

// supprime tous les tirs en fin de niveau
void suppressionTirsEndGame(listetir_Struct t);


						/***********
						 * ACTIONS *
						 ***********/

// permet au héro de tirer (createTirs + insertionTirs) 
//lié à la barre d'espace
void tirer(Hero hero, listetir_Struct t);

// permet à l'ennemi de tirer (createTirs + insertionTirs) 
//lié à la barre d'espace
void tirer_enemy(enemy en, listetir_StructEnemy te);



#endif