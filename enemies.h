#ifndef _ENEMIES_H_
#define _ENEMIES_H_

/*** LIBS ***/

#include <stdbool.h>

/*** STRUCTURES    ***/

struct positionE
{
	float x;
	float y;
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



struct obstacle
{
	struct positionE pos;
	bool jailed;
	bool active;
	struct obstacle *previous;
	struct obstacle *next;
};
typedef struct obstacle obstacle;

struct ListObstacles
{
	int quantite;
	struct obstacle *first;
	struct obstacle *last;
};
typedef struct ListObstacles ListObstacles;

typedef struct obstacle *obstacles;
typedef struct ListObstacles *ObstacleList;


/*** VARIABLES ***/

enemy car;
EnemyList e;

obstacles fence;
ObstacleList o;







/*** FUNCTIONS ***/

// Initialise une liste d'ennemis vide
EnemyList initialListEnemies(); 

// Créer et initialise les stats un ennemi
enemy createEnemy(int *maxY); 

// Créer un ennemi et le place dans la liste chainée
void insertionEnemies(EnemyList e, enemy car); 

//Supprime un ennemi et l'enleve de la liste
void deleteAllEnemies(EnemyList e); 

//Supprime tous les ennemis en fin de niveau
void suppressionObstaclesEndGame(ObstacleList o);

//Supprime tous les ennemis en fin de niveau
void suppressionEnemiesEndGame(EnemyList e);

//Supprime un ennemi et l'enleve de la liste
void suppressionEnemies(EnemyList e, bool test); 

// Initialise une liste d'obstacles vide
ObstacleList initialListObstacles(); 

// Créer et initialise les stats d'un obstacle
obstacles createObstacle(int *maxY); 

// Créer un obstacle et le place dans la liste chainée
void insertionObstacles(ObstacleList o, obstacles fence); 

//Supprime un obstacle et l'enleve de la liste
void suppressionObstacles(ObstacleList o, bool test); 



#endif
