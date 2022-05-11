#ifndef _ENEMIES_H_
#define _ENEMIES_H_

/*** LIBS ***/

#include <stdbool.h>

/*** STRUCTURES    ***/

//initialisation de la structure qui gère les positions des ennemis et obstacles
struct positions
{
	float x;
	float y;
};


//initialisation de la structure des ennemis
struct enemies

{
	int vie;
	int color;// red, purple ou gold

	bool active; // booléen qui sert à savoir si l'ennemi est toujours en vie ou non
	bool slowness; // bool de ralentissement si touché par une bulle
	bool changed;

	struct positions pos;
	struct enemies *previous;
	struct enemies *next;
};
typedef struct enemies enemies;


//initialisation de la liste chaînée des ennemis
struct ListEnemy
{
	
	int quantite;

	struct enemies *first;
	struct enemies *last;
	
};

typedef struct ListEnemy ListEnemy;
typedef struct enemies *enemy; 
typedef struct ListEnemy *EnemyList;


//initialisation de la structure des obstacles
struct obstacle
{
	bool jailed;
	bool active;
	
	struct positions pos;
	struct obstacle *previous;
	struct obstacle *next;
};
typedef struct obstacle obstacle;
typedef struct obstacle *obstacles;


//initialisation de la liste chaînée des obstacles
struct ListObstacles
{
	int quantite;
	
	struct obstacle *first;
	struct obstacle *last;
};

typedef struct ListObstacles ListObstacles;
typedef struct ListObstacles *ObstacleList;


/*** VARIABLES ***/

enemy car; // variable ennemi
EnemyList e; // variable pour la liste d'ennemis

obstacles fence; // variable obstacle
ObstacleList o; // variable pour la liste des obstacles


/*** FUNCTIONS ***/


					/******************
					 * INITIALISATION *
					 ******************/


// Initialise une liste d'ennemis vide
EnemyList initialListEnemies(); 

// Initialise une liste d'obstacles vide
ObstacleList initialListObstacles(); 

// Créer et initialise les stats un ennemi
enemy createEnemy(int *maxY); 

// Créer et initialise les stats d'un obstacle
obstacles createObstacle(int *maxY); 


					/***************
					 * ALLOCATIONS *
					 ***************/

// Créer un ennemi et le place dans la liste chainée
void insertionEnemies(EnemyList e, enemy car); 

// Créer un obstacle et le place dans la liste chainée
void insertionObstacles(ObstacleList o, obstacles fence); 



					/****************
					 * SUPPRESSIONS *
					 ****************/

//Supprime un ennemi et l'enleve de la liste
void suppressionEnemies(EnemyList e, bool test); 

//Supprime un obstacle et l'enleve de la liste
void suppressionObstacles(ObstacleList o, bool test); 


#endif
