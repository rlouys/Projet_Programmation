#ifndef _TIRS_H_
#define _TIRS_H_

/*** LIBS ***/ 
#include <stdbool.h>

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

typedef struct tirs *tir_Struct; 
typedef struct listeTirs *listetir_Struct;



/*** VARIABLES ***/ 

tir_Struct shoot;
listetir_Struct t;

/*** FUNCTIONS ***/


// initialise une liste qui contient les tirs et leur "stats"
listetir_Struct  initialListeTirs();

// positionne le tir sur la map devant le héro
tir_Struct createTirs(Hero hero);


//dessine le tir sur la map et incrémente la liste
void insertionTirs(listetir_Struct t, tir_Struct base);

//supprime le tir s'il y a une collision (booléen renvoyé depuis timers_and_effects.h suite à un test)
void suppressionTirs(listetir_Struct t, bool test);

// permet au héro de tirer (createTirs + insertionTirs)
void tirer(Hero hero, listetir_Struct t);




#endif