/*** LIBS ***/

//#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menus_graphics.h"
#include "game_graphics.h"
#include "tirs.h"
#include "enemies.h"
#include "hero.h"
#include "enemies.h"
#include "game.h"
#include "timers_and_effects.h"
#include "keyboard.h"

#define BLACK 0, 0, 0

/***  VARIABLES ***/ 

int startgame_option_bug = 1;

float *value; //scrolling
float *deplacement_fenetre;

char *username;
char username_array[20];

int newGame; // test si le jeu est nouveau ou pas (s'il y a une sauvegarde)
int newGame_lock;
int NewGame_statslock;
int level;
int difficulty;

bool startgame;
bool gameplay_keys;
bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool SHOOT = false;
bool SHOOT_ENEMY = false;
bool LEFTK = false;
bool RIGHTK = false;
bool DOWNK = false;
bool UPK = false;
bool cheatMode;
bool NewGame;


/*** FUNCTIONS ***/



// ------------------------------------- // 

// déplace le héro en fonction de la touche flechée pressée

void move(){

	enemy en = e->first;

	if(startgame == true && gameplay_keys == false)
	{
		// déplacements du héro via les touches flechées
		if (LEFT == true)
		{
			moveLeft(hero);		
			LEFT = false;

		}

		if (RIGHT == true)
		{
			moveRight(hero);		
			RIGHT = false;
		}

		if (UP == true)
		{
			moveUp(hero);
			UP = false;
		}
		
		if (DOWN == true)
		{
			moveDown(hero);
			DOWN = false;
		}

		

	}
	// pour les déplacements via les touches ZQSD
	if(startgame == true && gameplay_keys == true)
	{

	if (LEFTK == true)
		{
			moveLeft(hero);		
			LEFTK = false;

		}

		if (RIGHTK == true)
		{
			moveRight(hero);		
			RIGHTK = false;
		}

		if (UPK == true)
		{
			moveUp(hero);
			UPK = false;
		}
		
		if (DOWNK == true)
		{
			moveDown(hero);
			DOWNK = false;
		}

	}
	// envoie le tir allié
		if (SHOOT == true)
		{
			tirer(hero, t);
			SHOOT=false;
		}

		// envoie le(s) tir(s) ennemi(s)
		if (SHOOT_ENEMY == true)
		{
			tirer_enemy(en, te);
			SHOOT_ENEMY = false;
		}
}

// ------------------------------------------------------------------ //
// Function to copy the string
char* copyToString(char array[])
{
    char* string;
    string = (char*)malloc(20);
 
    strcpy(string, array);
    return (char*)string;
}

// ------------------------------------------------------------- //

// fonction qui va vérifier si il y a une partie enregistrée ou non
// si pas de partie enregistrée, impossible de "continuer" et affichage du message en rouge
// si partie enregistrée, newgame possible ET continuer
int checkNewGame(int newGame)
{
	FILE *f = fopen("hero_save.txt", "r+");
	
	int jeu;
	char name[20];

	fscanf(f,"%s %d", name, &jeu);

	if(jeu == 0)
	{
		newGame = 0;
	}
	else if(jeu == 1)
	{
		newGame = 1;
	}

	
	if(newGame == 0)
	{
		username = copyToString(name);
	}

	fclose(f);

	return newGame;
	
}


// ------------------------------------------------------------- //
//Fonctionne bien sauf premiere fois

void DisplayGame()
{	

	glClearColor(0.1f,0.1f,0.1f,0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game(&mX, &mY, hero,e,t,te, o, b);

    glFlush();

	// affiche le menu des options si on appuie sur ESC
	if(startgame == false)
	{
		glutDisplayFunc(GameOptionsDisplay);
	}

	glutPostRedisplay();
	glutSwapBuffers();
}
// ------------------------------------------------------------ // 

// dessine le jeu et lance la partie, fait apparaitre les ennemis et les tirs

void game(int *maxX, int *maxY, Hero hero, EnemyList e, listetir_Struct t, listetir_StructEnemy te, ObstacleList o, BonusList b)
{		
	
	glPushMatrix();
	drawMap(&mX, &mY, hero);			//afficher la carte
    glPopMatrix();

	drawPlayer(hero);

	// dessine tous les ennemis si la liste d'ennemi n'est pas vide
	if (e->first != NULL || e->last != NULL)
	{
		drawAllEnnemis(e);
	}

	// dessine tous les obstacles si la liste d'obstacles n'est pas vide
	if (o->first != NULL || o->last != NULL)
	{
		drawAllObstacles(o);
	}

	// dessine tous les tirs du Hero si la liste des tirs n'est pas vide
	if (t->first != NULL || t->last != NULL)
	{
		drawAllTirsHero(t);
	}

	// dessine tous les tirs ennemis si la liste des tirs n'est pas vide
	if(te->first != NULL || te->last != NULL)
	{
		drawAllTirsEnemy(te);
	}

	// dessine les objets bonus
	if((b->first != NULL || b->last != NULL) && cheatMode == false)
	{
		drawAllBonus(b);
	}

	// fonctions clavier
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	if(gameplay_keys == false)
	{
		glutSpecialFunc(arrowFunction);
	}
	// déplace le héros
	move();
	
	glutPostRedisplay();
}

// ------------------------------------------------------- //

//inverse deux entiers dans un tableau d'entiers
void swapIntegers(int* un, int* deux)
{
    int temp = *un;
    *un = *deux;
    *deux = temp;
}

// ------------------------------------------------------- //
//inverse deux strings dans un tableau de strings
void swapUsername(top Top, int k)
{


	char temp[20] = {'0'};
	
	strcpy(temp,Top->username[k]);
	strcpy(Top->username[k], Top->username[k+1]);
	strcpy(Top->username[k+1], temp);

}

// ------------------------------------------------------- //

// fait un bubblesort des tableaux du highscore
void bubbleSortScores(top Top, int taille)
{
	
	int i, k;

    for (i = 0; i < taille - 1; i++)

         for (k = 0; k < taille - i - 1; k++)

            if (Top->score[k] > Top->score[k + 1])
			{	
                swapIntegers(&Top->score[k], &Top->score[k + 1]);
				swapIntegers(&Top->killed[k], &Top->killed[k + 1]);
				swapUsername(Top, k);
			}

	

}
// ------------------------------------------------------ //

// Sauvegarde le score de la partie en cours

void saveScore(Hero hero)		
{
    FILE *f = fopen("scores.txt","r");
	
	FILE *files = fopen("scores.txt","r+");

	top Top = malloc(sizeof(struct Score));


	fscanf(f, "  %s   %d %d  %s           %d %d   %s   %d %d      %s                 %d %d   %s    %d %d",   Top->username[0], &Top->score[0], &Top->killed[0], Top->username[1], &Top->score[1], &Top->killed[1], Top->username[2], &Top->score[2], &Top->killed[2], Top->username[3], &Top->score[3], &Top->killed[3], Top->username[4], &Top->score[4], &Top->killed[4]);
	
	// si c'est un nouveau jeu, tu print le nom à gauche du fichier
	if(newGame == 1)
	{
		strcpy(Top->username[0], username_array);
		Top->killed[0] = hero->killed;
		Top->score[0] = hero->current_xp;
		
	}
	// si c'est pas un nouveau jeu, tu print le nom à droite du ficheir
	else if(newGame == 0)
	{
		strcpy(username_array, Top->username[4]);
		strcpy(Top->username[4], username_array);
		Top->killed[4] = hero->killed;
		Top->score[4] = hero->current_xp;

	}
	// trie les tableaux
	bubbleSortScores(Top, 5);

	// replace dans le fichier txt les tableaux triés
	fprintf(files, " %s %d %d %s %d %d %s %d %d %s %d %d %s %d %d", Top->username[0], Top->score[0], Top->killed[0], Top->username[1], Top->score[1], Top->killed[1], Top->username[2], Top->score[2], Top->killed[2], Top->username[3], Top->score[3], Top->killed[3], Top->username[4], Top->score[4], Top->killed[4] );

	// fermeture des fichiers
	// j'ai du ouvrir attacher 2 pointeurs au même fichier
	// car si je met en w+ (read write erase, ça ne fonctionne pas)
	// par contre si je "r" ET "w", ça fonctionne.
	fclose(files);
	fclose(f);
}	

// ------------------------------------------------------- //

// sauvegarde la partie en cours, pour reprise plus tard.

void saveContext()
{
	FILE *f = fopen("hero_save.txt", "w");

	// hero
	fprintf(f, "%s ", username);
	fprintf(f, "%i ", newGame);
	fprintf(f, "%d ", hero->current_xp);
	fprintf(f, "%i ", hero->health);
	fprintf(f, "%i ", hero->attack);
	fprintf(f, "%i ", hero->killed);
	fprintf(f, "%i ", hero->obstacles_taken);
	fprintf(f, "%i ", hero->weapon_type);
	fprintf(f, "%i ", hero->bonus_active);
	fprintf(f, "%f  ", hero->pos.x);
	fprintf(f, "%f ", hero->pos.y);
	fprintf(f, "%d ", level);
	fprintf(f, "%d        ", difficulty);

	fclose(f);




}


