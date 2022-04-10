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


struct enemies

{
	int vie;
	struct positionE pos;
	bool active;
	struct enemies *prevptr;
	struct enemies *nextptr;
};
typedef struct enemies enemies;


struct ListEnemy
{
	
	int quantite;
	struct enemies *first;
	struct enemies *last;
	
};
typedef struct ListEnemy ListEnemy;


/*** FUNCTIONS ***/

typedef struct enemies *enemy; 
typedef struct ListEnemy *EnemyList;
enemy createEnemy(int *maxY);
EnemyList initialListEnemies();
void insertionEnemies(EnemyList e, enemy q);
void suppressionEnemies(EnemyList e, bool test);
enemy car;
EnemyList e;

#endif
