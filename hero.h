#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

/*** LIBS ***/

#include <stdbool.h>
#include <math.h>
//#include <GL/glut.h>

/***  STRUCTURES   ***/

struct positionP
{
	float x;
	float y;
};

// Définition du héro //

struct Hero
	{
		char chars;
		int evolution; // beta - unused
		int health; // vie
		int attack; // pts d'attaque
		int current_xp; // score
		int killed;
		int red_killed; // nombre d'ennemis or tués
		int purple_killed; // nombre d'ennemis or tués
		int gold_killed; // nombre d'ennemis or tués
		int ulti_active;
		int ulti_killed;
		int obstacles_taken; // nombre d'obstacles 'pris'


		int weapon_type; // false: normal weapon | true:  bubble weapon
		int bonus_active; // active si bonus actif
		struct positionP pos;

	};

typedef struct Hero* Hero;

Hero hero;

// structure qui permet de prendre les scores, les triers et les afficher dans l'ordre
struct Score
{
	int killed[5];
	int score[5];
	char username[5][20];
};

typedef struct Score *top;

top Top;
// ----------------------------------------- //

// définition des objets bonus 

struct objet_bonus
	{
		int side;

		bool active;
		
		struct positionP pos;
		struct objet_bonus *previous;
		struct objet_bonus *next;
	};

typedef struct objet_bonus objet_bonus;

// définition de la liste d'objets bonus

struct ListeBonus
	{
		int quantite;
		struct objet_bonus *first;
		struct objet_bonus *last;
		int qtyToUlti;

	};

typedef struct ListeBonus ListeBonus;
typedef struct objet_bonus *bonus_objet;
typedef struct ListeBonus *BonusList;

// --------------------------------------------- // 

/***  VARIABLES  ***/

int mX;
int mY;

bonus_objet bonus;
BonusList b;

/*** FUNCTIONS ***/
						/********
						 * HERO *
						 ********/

// Initialise le héro et ses statistiques
Hero createHero(int *mX, int *mY); 


						/*************
						 * HERO FUNC *
						 *************/

// Vérifient si le héro peut se déplacer dans un sens ou dans un autre.
void moveUp(Hero hero); 
void moveDown(Hero hero); 
void moveRight(Hero hero); 
void moveLeft(Hero hero); 

// change l'arme tenue par le héro (arme à feu et canon à bulles);
void switchWeapon(Hero hero);

						/***************
						 * OBJET BONUS *
						 ***************/

//Initialise une liste d'objets bonus vide
BonusList initialListeBonus();

// Créer et initialise les stats un ennemi
bonus_objet createBonus(int *maxY);

// Créer un objet bonus et le place dans la liste chainée
void insertionBonus(BonusList b, bonus_objet BONUS);

//Supprime un bonus et l'enleve de la liste
void suppressionBonus(BonusList b, bool test);




// -------------------- // 


#endif

	