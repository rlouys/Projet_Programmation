#ifndef _TIRS_H_
#define _TIRS_H_

/*** LIBS ***/ 

#include <stdbool.h>
#include "characters.h"
#include "game_graphics.h"

/*** STRUCTURES ***/ 

struct positionT
{
	int x;
	int y;
};
typedef struct tirs tirs;
struct tirs
{
	struct positionT pos;
	bool active;
	struct tirs *prevptr;
	struct tirs *nextptr;
};

typedef struct listeTirs listeTirs;
struct listeTirs
{
	
	int quantite;
	struct tirs *starList;
	struct tirs *endList;
	
};

/*** FUNCTIONS ***/

typedef struct tirs *tirsP; 
typedef struct listeTirs *listetirsP;
tirsP createTirs(player p);
listetirsP  initialListeTirs();
void insertionTirs(listetirsP t, tirsP base);
void suppressionTirs(listetirsP t, bool test);
void tirer(player p, listetirsP t);
tirsP r;
listetirsP t;

#endif