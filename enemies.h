#ifndef _ENEMIES_H_
#define _ENEMIES_H_

/*** LIBS ***/

#include <stdbool.h>

/*** STRUCTURES    ***/

struct positionE
{
	int x;
	int y;
};
typedef struct enemies enemies;
struct enemies
{
	int vie;
	struct positionE pos;
	bool active;
	struct enemies *prevptr;
	struct enemies *nextptr;
};

typedef struct listeEnemies listeEnemies;
struct listeEnemies
{
	
	int quantite;
	struct enemies *first;
	struct enemies *last;
	
};


/*** FUNCTIONS ***/

typedef struct enemies *enemy; 
typedef struct listeEnemies *listeEn;
enemy createEnemy(int *maxY);
listeEn  initialListEnemies();
void insertionEnemies(listeEn e, enemy q);
void suppressionEnemies(listeEn e, bool test);
enemy q;
listeEn e;

#endif
