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

#define BLACK 0, 0, 0

/***  VARIABLES ***/ 

int startgame_option_bug = 1;

float *value;
float *deplacement_fenetre;

char *username;
char username_array[20];

int newGame;
int newGame_lock;

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



/*** FUNCTIONS ***/

// definition de la fonction Keyboard permettant de quitter/tirer

void Keyboard(unsigned char key, int x, int y)  
{
	switch(key)
	{
		// ESC KEY
		case 27:
			startgame = !startgame;
			glutDisplayFunc(GameOptionsDisplay);
			glutPostRedisplay();
			break;

		// SPACE KEY
		case 32:
		SHOOT = true;
		break;	

		// BACKSPACE KEY
		case 0x08:
			// si le tir existe, alors il est tiré
			if(te->first == NULL || te->last == NULL)
			{
				SHOOT_ENEMY = true;
			}	
			if(te->first != NULL || te->last == NULL)
			{
				SHOOT_ENEMY = true;
			}
			break;

		// mouvement du héro
		case 'w':
		switchWeapon(hero);	
		break;
		
		//touches flechées
		case 'z':
		UPK = true;
		break;

		case 'q':
		LEFTK = true;
		break;	
		
		case 's':
		DOWNK = true;
		break;

		case 'd':
		RIGHTK = true;
		break;

		}	
}

// ------------------------------------------------------------ // 

// definition de la fonction arrowFunction permettant de se déplacer via les flèches directionnelles

void arrowFunction(int key, int x, int y)
{
    switch (key) 
	{
		// déplacement du héro avec les touches 
		case GLUT_KEY_UP:
			UP = true;
			break;

		case GLUT_KEY_DOWN:
			DOWN = true;
			break;

		case GLUT_KEY_LEFT:
			LEFT = true;
			break;

		case GLUT_KEY_RIGHT:
			RIGHT = true;
			break;
    }
}

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
	char trash[20];

	fscanf(f,"%s %i", trash, &jeu);

	if(jeu == 0)
	{
		newGame = 0;
	}
	else if(jeu == 1)
	{
		newGame = 1;
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

// Sauvegarde le score de la partie en cours

void saveScore(Hero hero)		
{
    FILE *f = fopen("scores.txt","r");
	
	FILE *files = fopen("scores.txt","r+");

    int score_1 = 0, score_2 = 0, score_3 = 0, score_4 = 0;
    char username_1[20] = {'0'}, username_2[20] = {'0'}, username_3[20] = {'0'}, username_4[20] = {'0'};
    
	int killed_1 = 0, killed_2 = 0, killed_3 = 0, killed_4 = 0;

	fscanf(f, "%s %d %d %s %d %d %s %d %d %s %d %d",  username_1, &score_1, &killed_1, username_2, &score_2, &killed_2, username_3, &score_3, &killed_3, username_4, &killed_4, &score_4);

	printf("%s ::: \n", username_1);

	//strcpy(user_test,username);
		printf("%s ::: \n", username_1);
		printf("%s ::: \n", username_1);
		printf("%s username2 \n", username_2);
				printf("%s username3 \n", username_3);
		printf("%s username4 \n", username_4);

		printf("%s username_array :\n", username_array);

	if(strcmp(username_1, "------------") != 0)
	{
		if(strcmp(username_2, "------------") != 0)
		{
			if(strcmp(username_3, "------------") != 0)
			{
				if(strcmp(username_4, "------------") != 0)
				{
					/*score_4 = hero->current_xp;
					if(hero->killed > 0) killed_4 = hero->killed;
					else killed_4 = 0;*/
					fprintf(files, "%s %d %d %s %d %d %s %d %d %s %d %d        ", username_1, score_1, killed_1, username_2, score_2, killed_2, username_3, score_3, killed_3, username_array, score_4, killed_4);
					printf("%i hero killed", hero->killed);
					//compareTops();
					// ICI COMPARER LES CHIFFRES ET LE METTRE A LA BONNE PLACE
				}
				else
				{
					score_4 = hero->current_xp;
					if(hero->killed > 0) killed_4 = hero->killed;
					else killed_4 = 0;
					fprintf(files, "%s %d %d %s %d %d %s %d %d %s %d %d          ", username_1, score_1, killed_1, username_2, score_2, killed_2, username_3, score_3, killed_3, username_array, killed_4, score_4);
					printf("%i hero killed", hero->killed);
				}
			}
			else
			{
				score_3 = hero->current_xp;
				if(hero->killed > 0) killed_3 = hero->killed;
				else killed_3 = 0;
				fprintf(files, "%s %d %d %s %d %d %s %d %d %s %d %d          ", username_1, score_1, killed_1, username_2, score_2, killed_2, username_array, score_3, killed_3, username_4, killed_4, score_4);

			}
		}
		else
		{
			score_2 = hero->current_xp;
			if(hero->killed > 0) killed_2 = hero->killed;
			else killed_2 = 0;
			fprintf(files, "%s %d %d %s %d %d %s %d %d %s %d %d         ", username_1, score_1, killed_1, username_array, score_2, killed_2, username_3, score_3, killed_3, username_4, killed_4, score_4);

		}

	}

	else
	{
		printf("%i hero killed", hero->killed);
		score_1 = hero->current_xp;
		if(hero->killed > 0) killed_1 = 15;
		else killed_1 = 0;
		fprintf(files, "%s %d %d %s %d %d %s %d %d %s %d %d", username_array, score_1, killed_1, username_2, score_2, killed_2, "------------", score_3, killed_3, "------------", killed_4, score_4);
	}

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

	
	/*// obstacles
	int jailed;
	if(fence->jailed == true)
		jailed = 1;
	else
		jailed = 0;
	

	fprintf(f, "%f ", fence->pos.x);
	fprintf(f, "%f ", fence->pos.y);
	fprintf(f, "%i ", jailed);*/



	fclose(f);




}


