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
	struct enemies *previous;
	struct enemies *next;
};
typedef struct enemies enemies;


struct ListEnemy
{
	
	int quantite;
	struct enemies *first;
	struct enemies *last;
	
};
typedef struct ListEnemy ListEnemy;

typedef struct enemies *enemy; 
typedef struct ListEnemy *EnemyList;

/*** VARIABLES ***/

enemy car;
EnemyList e;


/*** FUNCTIONS ***/

// Initialise une liste d'ennemis vide
EnemyList initialListEnemies(); 

// Créer et initialise les stats un ennemi
enemy createEnemy(int *maxY); 

// Créer un ennemi et le place dans la liste chainée
void insertionEnemies(EnemyList e, enemy car); 

//Supprime un ennemi et l'enleve de la liste
void suppressionEnemies(EnemyList e, bool test); 

#endif
