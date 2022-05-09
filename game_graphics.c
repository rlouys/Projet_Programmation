/*** LIBS ***/


//#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/*** FILES ***/

#include "game_graphics.h"
#include "menus_graphics.h"
#include "hero.h"
#include "enemies.h"
#include "game.h"
#include "timers_and_effects.h"

/***  CONSTANTES  ***/

#define MAP "map-test.txt" 
#define HEART_SIZE 0.695 //(0.1 = little || 1 = big)
#define NB_COEURS 5

//COLORS//
#define EMERALD 0.03, 0.49, 0.13
#define WHITE 1, 1, 1
#define BLACK 0, 0, 0
#define GREY 0.5, 0.5, 0.5
#define BROWN 0.30, 0.23, 0.12
#define SAND 0.94, 0.87, 0.70
#define RED 1.0, 0, 0
#define YELLOW 1, 1, 0
#define BLUE 0.0, 0.0, 1.0
#define CYAN 0, 1, 1
#define YELLOWGREEN 0.604, 0.804, 0.196
#define ORANGE 1, 0.647, 0
#define BRICK 0.698039216, 0.133333333, 0.133333333
#define GREEN 0, 1, 0
/***  VARIABLES  ***/

int mX = 80; // nombre de cases en largeur de la map
int mY = 49; // nombre de cases en longueur de la map
int level = 1; // niveau de la partie en cours

float r, g, bl; // permet de changer la couleur des ennemis en fonction de la difficulté et du niveau en cours
float *value; // valeur de défilement de la map
float difficulty;

bool cheatMode;
bool GOLD;

char *username; // username du héro
char username_array[20];


/*** FUNCTIONS ***/ 


                    /***************
                     * MEM_LOADERS *
                     ***************/

// charge la map en mémoire

bool loadMap(int *mX, int *mY)		
{
    map = malloc(sizeof(char *) * (*mX));

    FILE *f = NULL;

    f = fopen(MAP, "r");

    if(f == NULL)
    {
        printf("file empty");
        return false;
    }

    char c;

    int i = 0;
    int j = 0;
	
	for(i = 0; i < (*mX); i++)
		{

			*(map + i) = malloc(sizeof(char *) * (*mX));	
			for(j = 0; j < (*mY); j++)
			{		
				c = fgetc(f);
				*(*(map + i) + j) = c;
			}
			fgetc(f);
		}

	    fclose(f);
		
		for(i = 0; i < (*mX); i++)
		{
			for(j = 0; j < (*mY); j++)
			{
				printf("%c", *(*(map + i) + j));			
			}
			printf("\n");

		}
				
		
 return true;

 }		


                    /***************
                     * MAP DRAWING *
                     ***************/

// dessine la map et tout les éléments statiques (score, murs)

void drawMap(int *mX, int *mY, Hero hero)			
{	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();

	glTranslatef(0,-(*value),0); // scrolling
	// dessine les divers éléments du dessin de la map
	for (int j = 0; j < (*mX); ++j)
	{
		for (int i = 0; i < (*mY); i++)
		{
			if(*(*(map + j) + i) == '#') // Murs bruns gauche
			{	
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0); // scrolling

				drawSquare(BROWN, 1);	
				drawLineBorder(GREY,0);
				drawLineBorder(BLACK,3);
			}

			if(*(*(map + j) + i) == '@') // Murs bruns droits
			{	

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0); // scrolling

				drawSquare(BROWN, 1);	
				drawLineBorder(GREY,1);
				drawLineBorder(BLACK,2);

			}

			if(*(*(map + j) + i) == '1') // Sable bordures
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);

				drawSquare(SAND, 1);
			}
		
			if (*(*(map + j) + i) == '|') // lignes centrales
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0); // scrolling

				drawLine(WHITE);
			}

			if (*(*(map + j) + i) == 'l') // piste cyclable
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0); // scrolling

				drawLine(WHITE);
			}

			if(*(*(map + j) + i) == ' ' || *(*(map + j) + i) == 'X') // Fond de plateau
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawSquare(BLACK, 1);
			}	
		}
	}
	//dessine le nombre de points de vie du Héro
	drawHealth(hero);

	//dessine le nom du héro en haut à gauche de l'écran de jeu
	drawUsername();

	//dessine le score du Héro
	drawScore(hero);

	//dessine le numéro du niveau en cours
	drawLevel();

	//dessine le nombre de points d'attaque du héro
	drawAttack();

	//dessine le nombre d'ennemis tués
	drawKills();

	//dessine le type d'arme tenu en main
	drawWeapon();

	if(cheatMode == true)
	{
		writeSomething(RED, 12, 80, "CHEAT MODE");
		writeSomething(RED, 27, 50, "ENABLED");
	}
	else	
	{
	// dessin switch weapon
	writeSomething(BLACK, 135, 65, "'w'");
	writeSomething(BLACK, 20, 80, "SWITCH");
	writeSomething(BLACK, 17, 50, "WEAPON");
	}

}

// ------------------------------------------------------------------ //

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

// ------------------------------------------------------------------ //

void handleResize(int width,int heigth)
{
    glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0, width, 0, heigth);
}


                    /******************
                     * SHAPES DRAWINGS *
                     ******************/


// DRAW A SQUARE (SIZEOF = Map_pixel_size/nb_objects)
// les couleurs doivent être entrées en paramètre
// dessine un carré aux couleurs voulues

void drawSquare(float red, float green, float blue, float size)
{
	glBegin(GL_QUADS);

	glColor3f(red, green, blue);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f((Square_size*size), 0.0f, 0.0f);
		glVertex3f((Square_size*size),(Square_size*size), 0.0f);
		glVertex3f(0.0f,(Square_size*size), 0.0f);
		
	glEnd();
}

// --------------------------------------------------------------------------------------------_//

// dessine un cercle aux couleurs voulues

void drawCircle(float red, float green, float blue, int posx, int posy, float radius)
{
	int N = 180;
	float Dtheta = 2 * 3.1415926 / N;
	float angle = 0.0;

	glColor3f(red, green, blue);
	glVertex2f(posx, posy);

    glBegin(GL_LINE_LOOP);

	for (int i=0; i <= N; i++)
	{
		angle = i*Dtheta;
		glVertex2f(cos(angle)*radius,sin(angle)*radius);
	}
    
	glEnd();
}

// --------------------------------------------------------------------------------------------_//

// dessine une ligne aux couleurs voulues

void drawLine(float red, float green, float blue)
{
	float line = Square_size/3;

	glBegin(GL_QUADS);


	// dessin de la ligne dans la couleur souhaitée
	glColor3f(red,green,blue);

	glVertex3f(line, 0.0f, 0.0f);
	glVertex3f(line*2, 0.0f, 0.0f);
	glVertex3f(line*2,Square_size, 0.0f);
	glVertex3f(line,Square_size, 0.0f);


	// rempli les 2/3 restant dans la couleur du fond de map
	glColor3f(BLACK);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(line, 0.0f, 0.0f);
	glVertex3f(line,Square_size, 0.0f);
	glVertex3f(0,Square_size, 0.0f);

	glColor3f(BLACK);

	glVertex3f(line*2, 0.0f,0.0f);
	glVertex3f(line*3, 0.0f,0.0f);
	glVertex3f(line*3,Square_size,0.0f);
	glVertex3f(line*2,Square_size,0.0f);

	glEnd();
}

// ------------------------------------------------------------------------ // 

// dessine une bordure à un carré, aux couleurs voulues et à la disposition voulue || border 0 == gauche | border 1 == droite

void drawLineBorder(float red, float green, float blue, int border) //border 0 == gauche | border 1 == droite
{
	float line = Square_size/3;

	glBegin(GL_QUADS);
	glColor3f(red,green,blue);

	// border => permet de choisir quelle bordure va être dessinée
	if(border == 0) // gauche
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(line, 0.0f, 0.0f);
		glVertex3f(line,Square_size, 0.0f);
		glVertex3f(0.0f,Square_size, 0.0f);
	}

	else if(border == 1)// droite
	{
		glVertex3f(line*2, 0.0f, 0.0f);
		glVertex3f(line*3, 0.0f, 0.0f);
		glVertex3f(line*3,Square_size, 0.0f);
		glVertex3f(line*2,Square_size, 0.0f);
	}

	else if(border == 2)//grillage droite
	{
		glVertex2d(line*2, line);
		glVertex2d(line*3, line);
		glVertex2d(line*3, line*1.5);
		glVertex2d(line*2, line*1.5);
	}

	else if(border == 3)//grillage gauche
	{
		glVertex2d(0, line);
		glVertex2d(0, line*1.5);
		glVertex2d(line, line*1.5);
		glVertex2d(line, line);
	}
	
	glEnd();
}


// ------------------------------------------------------------------------ // 

// dessine un coeur aux couleurs voulues

void drawHeart(float red, float green, float blue)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(red, green, blue);

	for(float a = 0; a < 2*(3.15); a+=0.01)
	{
		float x = HEART_SIZE*(16 * pow(sin(a), 3));
		float y = HEART_SIZE*(-1*(13 * cos(a) - 5 * cos(2*a) - 2*cos(3*a) - cos(4*a)));
		glVertex2f(x,-y);
	}

	glEnd();
}







                    /*****************
                     * DATAS DRAWINGS *
                     *****************/


// dessine le niveau en cours
void drawLevel()
{
	int a = level;
	char str[10];
	sprintf(str, "%d", a);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    writeSomethingArray(BLACK, 885, 55, str);
	writeSomething(BLACK,850, 95, "LEVEL");

	glColor3f(BLACK);

	frameDraw(BLACK, 825, 100, 130, 0);

	for (int i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(945,115-i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
	}
}

// --------------------------------------------------------------------------------------------_//

// affiche la vitalité du joueur en temps réel

void drawHealth(Hero hero)
{

	int i;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(825,890,0);

	for(i = 1; i <= hero->health-difficulty; i++)
	{	
		
		drawHeart(1,0,0);
		glTranslatef((Square_size*1.5),0,0);

		// tous les 5 coeurs, on passe à la ligne suivante
		if(i % 5 == 0)
		{
			glTranslatef(-( (Square_size*1.5) * NB_COEURS) , -(Square_size*2), 0);
		}

	}

	writeSomething(BLACK,835,970,"HEALTH");

	glColor3f(BLACK);

	frameDraw(BLACK, 825, 975, 130, 0);

	for (i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(945,990-i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);       
	}

	frameDraw(BLACK,825, 930, 130, 0);

	for (i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(945,945-i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);   
	}

	glTranslatef(845,935,0);

	// points de vie format 'numérique'
	drawHeart(BLACK);

	// transforme le nombre de point de vie du héro en format texte
	int a = hero->health;
	char str[10];
	sprintf(str, "%d", a);
	writeSomething(BLACK, 873, 925, str);

	glTranslatef(925,935,0);

	drawHeart(BLACK);

}

// --------------------------------------------------------------------------------------------_//

// affiche l'état des bonus du joueur en temps réel

void drawAttack()
{
	int i;

	// transforme le nombre de point d'attaque du héro en format texte
	int a = hero->attack;
	char str[10];
	sprintf(str, "%d", a);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    writeSomethingArray(BLACK, 885, 155, str);
	writeSomething(BLACK, 870, 155, "x");
	writeSomething(BLACK, 825, 195, "DAMAGES");

	glColor3f(BLACK);

	frameDraw(BLACK, 825, 200, 130, 0);

	for (i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(945,215-i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]); 
	}
}



// --------------------------------------------------------------------------------------------_//

// affiche les stats du jeu en cours (enemy killed....)

void drawKills()
{

	int i;

	// transforme le nombre d'ennemis tués en format texte
	int a = hero->killed;
	char str[10];
	sprintf(str, "%d", a);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    writeSomethingArray(BLACK, 30, 730, str);
	writeSomething(BLACK, 45, 770, "KILLS");

	glColor3f(BLACK);
	frameDraw(BLACK, 35, 775, 130, 0);

	for (i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(152,790-i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);       
	}
}


// --------------------------------------------------------------------------------------------_//

// affiche le score du joueur en temps réel

void drawUsername()
{
	int i;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


    writeSomethingArray(BLACK, 30, 930, username);

	writeSomething(BLACK, 45, 970, "PSEUDO");
	glColor3f(BLACK);
	frameDraw(BLACK, 35, 975, 130, 0);

	for (i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(152,990-i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
            
	}

}


// --------------------------------------------------------------------------------------------_//

// affiche le score du joueur en temps réel

void drawScore(Hero hero)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int i;

	int a = hero->current_xp;

	char str[10];

	sprintf(str, "%d", a);


	writeSomething(BLACK,45, 870, "SCORE");
	writeSomething(BLACK,30, 830, str);
	glColor3f(BLACK);
	frameDraw(BLACK, 35, 875, 130, 0);

	for (i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(152,890-i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
            
	}

}

// --------------------------------------------------------------------------------------------_//

// dessine l'arme tenue en main en temps réel
void drawWeapon()
{
	int i;

	// dessin du cadre et de l'inscription du type d'arme
	writeSomething(BLACK,40, 670, "WEAPON");
	glColor3f(BLACK);
	frameDraw(BLACK, 30, 675, 140, 0);

	// rafistolage
	for (i = 0 ; i < 30 ; i++)
	{
		glRasterPos3f(157,690-i, 1); // DRAW RIGHT LINE FRAME
		char msg2[]="|";
		for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
	}

	// affichage du type d'arme en main
	// Condition d'affichage, si gun => affiche gun, si bubble => affiche bubble S
	if(hero->weapon_type == false)
	{
		glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();

		if(hero->bonus_active == false)
		{
			writeSomething(BLACK, 60, 627, "G U N");

			// left squares
			glTranslatef(140, 635, 0);
			drawSquare(GREEN, 0.45);
			glTranslatef(10, 0, 1);
			drawSquare(GREEN, 0.45);
			glTranslatef(0, -10, 0);
			drawSquare(GREEN, 0.45);
			glTranslatef(-10, 0, 0);
			drawSquare(GREEN, 0.45);

			// right squares
			glTranslatef(-115, 10, 0);
			drawSquare(GREEN, 0.45);
			glTranslatef(10, 0, 0);
			drawSquare(GREEN, 0.45);
			glTranslatef(0, -10, 0);
			drawSquare(GREEN, 0.45);
			glTranslatef(-10, 0, 0);
			drawSquare(GREEN, 0.45);

		}

		else if(hero->bonus_active == true)
		{
			writeSomething(BLACK, 60, 627, "G U N");

			// left squares
			glTranslatef(140, 635, 0);
			drawSquare(RED, 0.45);
			glTranslatef(10, 0, 0);
			drawSquare(RED, 0.45);
			glTranslatef(0, -10, 0);
			drawSquare(RED, 0.45);
			glTranslatef(-10, 0, 0);
			drawSquare(RED, 0.45);

			// right squares
			glTranslatef(-115, 10, 0);
			drawSquare(RED, 0.45);
			glTranslatef(10, 0, 0);
			drawSquare(RED, 0.45);
			glTranslatef(0, -10, 0);
			drawSquare(RED, 0.45);
			glTranslatef(-10, 0, 0);
			drawSquare(RED, 0.45);
		}


	}
	else if(hero->weapon_type == true)
	{
		glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();

		writeSomething(BLACK, 47, 627, "BUBBLE");

		glTranslatef(160,635,0);
		drawCircle(BLUE, 50, 630, 6);
		drawCircle(BLUE, 50, 630, 7);
		drawCircle(BLUE, 50, 630, 10);

		glTranslatef(-130, 0,0);
		drawCircle(BLUE, 50, 630, 6);
		drawCircle(BLUE, 50, 630, 7);
		drawCircle(BLUE, 50, 630, 10);
	}
}





                    /***********************
                     * CHARACTERS DRAWINGS *
                     ***********************/



// place le héro sur la carte (en le plaçant au bon endroit)

void drawPlayer(Hero hero)
{
	float i, j;

	// i et j valent les positions x et y du héro
	i = hero->pos.x;
	j = hero->pos.y;
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// déplacement du héro à l'endroit de départ
	glTranslatef(i*Square_size,j*Square_size,0.0f);

	glColor3f(GREY);

	// dessin 
	glBegin(GL_QUADS);

	// velo structure

	glVertex3f(6, 0, 0);
	glVertex3f(((Square_size*2)/5)+2, 0, 0);
	glVertex3f(((Square_size*2)/5)+2, Square_size*2, 0);
	glVertex3f(6, Square_size*2, 0);

	// guidon

	glColor3f(BROWN);
	glVertex3f(-2, 25, 0);
	glVertex3f(((Square_size*2)/5)+10, 25, 0);
	glVertex3f(((Square_size*2)/5)+10, 28, 0);
	glVertex3f(-2, 28, 0);

	// baton droit
	glColor3f(BROWN);
	glVertex3f(((Square_size*2)/5)+10, 25, 0);
	glVertex3f(((Square_size*2)/5)+10, 32, 0);
	glVertex3f(((Square_size*2)/5)+7, 32, 0);
	glVertex3f(((Square_size*2)/5)+7, 25, 0);

	// baton gauche
	glColor3f(BROWN);
	glVertex3f(-2, 25, 0);
	glVertex3f(-2, 32, 0);
	glVertex3f(1, 32, 0);
	glVertex3f(1, 25, 0);

	// selle

	glColor3f(BROWN);
	glVertex3f(4, 10, 0);
	glVertex3f(((Square_size*2)/5)+4, 10, 0);
	glVertex3f(((Square_size*2)/5)+4, 18, 0);
	glVertex3f(4, 18, 0);





	glEnd();
}

// ------------------------------------------------------------------ //

// dessine un ennemi et le place sur la carte

void drawEnemy(enemy e)	
{
	float i, j;

	//i et j sont les coordonnées de départ de l'ennemi
	i = e->pos.x;
	j = e->pos.y;

	// couleur ennemi
	glColor3f(r,g,bl);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//déplacement de l'ennemi sur la case de départ
	glTranslatef(i*Square_size,j*Square_size,0.0f);

	// dessin
	glBegin(GL_QUADS);

	/*glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(Square_size,0.0f,0.0f);
	glVertex3f(Square_size,Square_size,0.0f);
	glVertex3f(0.0f,Square_size,0.0f);*/

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(Square_size, 0.0f, 0.0f);
	glVertex3f(Square_size, Square_size, 0.0f);
	glVertex3f(0.0f, Square_size, 0.0f);

	// capot
	glColor3f(BLACK);
	glVertex3f(0.0f, 8, 0.0f);
	glVertex3f(Square_size, 8, 0.0f);
	glVertex3f(Square_size, 7, 0.0f);
	glVertex3f(0, 7, 0.0f);




	//phares standards


	if(GOLD == false)
	{
		glColor3f(ORANGE);
	}
	else{
		glColor3f(CYAN);
	}


	//gauche
	glVertex3f(0, 0, 0.0f);
	glVertex3f(4, 0, 0.0f);
	glVertex3f(4, 4, 0.0f);
	glVertex3f(0, 4, 0.0f);

	//droite
	glVertex3f(20, 0, 0.0f);
	glVertex3f(20, 4, 0.0f);
	glVertex3f(16, 4, 0.0f);
	glVertex3f(16, 0, 0.0f);


	// pare-brise

	glColor3f(CYAN);

	glVertex3f(1, 8, 0.0f);
	glVertex3f(1, 19, 0.0f);
	glVertex3f(19, 19, 0.0f);
	glVertex3f(19, 8, 0.0f);

	//rétroviseurs

	glColor3f(GREY);
	//gauche
	glVertex3f(0, 6, 0);
	glVertex3f(-4, 6, 0);
	glVertex3f(-4, 10, 0);
	glVertex3f(0, 10, 0);


	//droite
	glVertex3f(20, 6, 0);
	glVertex3f(24, 6, 0);
	glVertex3f(24, 10, 0);
	glVertex3f(20, 10, 0);



	glEnd();
}


// ------------------------------------------------------------- //

// dessine des ennemis à la chaine (utilise drawEnemy à la chaine)

void drawAllEnnemis(EnemyList e)
{	
	// allocation de deux premiers ennemis
	enemy first = malloc(sizeof(enemies));
	enemy next = malloc(sizeof(enemies));

	first = e->first;
	next = e->first->next;

	if (e->first != NULL || e->last != NULL) // test existence de la liste
	{
		drawEnemy(first);
		if (e->first->next != NULL)
		{
			drawEnemy(next);
			while (next->next != NULL)
			{
				next = next->next;
				drawEnemy(next);
			}
		}
	}
}


                    /**************************
                     * MOBILE OBJECTS DRAWINGS *
                     **************************/

//dessine les obstacles

void drawObstacles(obstacles o, float red, float green, float blue)
{
	float i, j;

	//i et j sont les coordonnées de départ de l'obstacle
	i = o->pos.x;
	j = o->pos.y;

	// couleur obstacle
	glColor3f(red, green, blue);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// déplacement de l'obstacle à l'endroit de départ
	glTranslatef(i*Square_size,j*Square_size,0.0f);

	//dessin de l'obstacle
	glBegin(GL_QUADS);

	glVertex3f(-(Square_size),0.0f,0.0f);
	glVertex3f(Square_size*2,0.0f,0.0f);
	glVertex3f(Square_size*2,Square_size,0.0f);
	glVertex3f(-(Square_size),Square_size,0.0f);

	//lines

	// down line
	glColor3f(BLACK);
	glVertex3f(-(Square_size),7,0.0f);
	glVertex3f(Square_size*2,7,0.0f);
	glVertex3f(Square_size*2,6,0.0f);
	glVertex3f(-(Square_size),6,0.0f);


	// up line
	glVertex3f(-(Square_size),15,0.0f);
	glVertex3f(Square_size*2,15,0.0f);
	glVertex3f(Square_size*2,14,0.0f);
	glVertex3f(-(Square_size),14,0.0f);

	// vertical lines
	//up
	glVertex3f(-(Square_size)+21,15,0.0f);
	glVertex3f(-(Square_size)+21,20,0.0f);
	glVertex3f(-(Square_size)+19,20,0.0f);
	glVertex3f(-(Square_size)+19,15,0.0f);

	glVertex3f(-(Square_size)+41,15,0.0f);
	glVertex3f(-(Square_size)+41,20,0.0f);
	glVertex3f(-(Square_size)+39,20,0.0f);
	glVertex3f(-(Square_size)+39,15,0.0f);

	//down
	glVertex3f(-(Square_size)+21,7,0.0f);
	glVertex3f(-(Square_size)+21,0,0.0f);
	glVertex3f(-(Square_size)+19,0,0.0f);
	glVertex3f(-(Square_size)+19,7,0.0f);

	glVertex3f(-(Square_size)+41,7,0.0f);
	glVertex3f(-(Square_size)+41,0,0.0f);
	glVertex3f(-(Square_size)+39,0,0.0f);
	glVertex3f(-(Square_size)+39,7,0.0f);

	//middle
	glVertex3f(-(Square_size)+13,7,0.0f);
	glVertex3f(-(Square_size)+13,15,0.0f);
	glVertex3f(-(Square_size)+11,15,0.0f);
	glVertex3f(-(Square_size)+11,7,0.0f);

	glVertex3f(-(Square_size)+33,7,0.0f);
	glVertex3f(-(Square_size)+33,15,0.0f);
	glVertex3f(-(Square_size)+31,15,0.0f);
	glVertex3f(-(Square_size)+31,7,0.0f);

	glVertex3f(-(Square_size)+53,7,0.0f);
	glVertex3f(-(Square_size)+53,15,0.0f);
	glVertex3f(-(Square_size)+51,15,0.0f);
	glVertex3f(-(Square_size)+51,7,0.0f);

	glEnd();
}


// ------------------------------------------------------------- //

// dessine des obstacles à la chaine (utilise drawObstacles à la chaine)

void drawAllObstacles(ObstacleList o)
{	
	// allocation des deux premiers obstacles
	obstacles first = malloc(sizeof(obstacle));
	obstacles next = malloc(sizeof(obstacle));

	first = o->first;
	next = o->first->next;


	if (o->first != NULL || o->last != NULL) // test existence de la liste
	{
		// si emprisonné, deviens couleur glace
		if(first->jailed == false) 
		{
			drawObstacles(first, BRICK);
		}
		else
		{
			drawObstacles(first, CYAN);
		}
		
		if (o->first->next != NULL)
		{
			if(next->jailed == false)
			{
				drawObstacles(next, BRICK);
			}
			else
			{
				drawObstacles(next, CYAN);
			}
			while (next->next != NULL)
			{
				next = next->next;

				if(next->jailed == false)
				{
					drawObstacles(next, BRICK);
				}
				else
				{
					drawObstacles(next, CYAN);
				}
			}
		}
	}
}

// ------------------------------------------------------------------ //

//dessine les objets bonus

void drawBonus(bonus_objet bonus)
{
	if(cheatMode == false && hero->ulti_active == 0)
	{
	float i, j;

		// i et j sont les coordonnées de départ de l'objet bonus
		i = bonus->pos.x;
		j = bonus->pos.y;


	

	// attaque ultime
	
	bonus = b->first;



		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// déplacement du bonus à l'endroit de départ
		glTranslatef((i*Square_size)+10,(j*Square_size),0.0f);

		//dessin du bonus

	
		
	
		drawCircle(RED, i, j, 6);
		drawCircle(RED, i, j, 7);
		drawCircle(RED, i, j, 10);
		
	
	}
}


// ------------------------------------------------------------- //

// dessine des bonus à la chaine (utilise drawBonus à la chaine)

void drawAllBonus(BonusList b)
{	
	// allocation des deux premiers obstacles
	bonus_objet first = malloc(sizeof(objet_bonus));
	bonus_objet next = malloc(sizeof(objet_bonus));

	first = b->first;
	next = b->first->next;

	if (b->first != NULL || b->last != NULL) // test existence de la liste
	{
		drawBonus(first);
		if (b->first->next != NULL)
		{
			drawBonus(next);
			while (next->next != NULL)
			{
				next = next->next;
				drawBonus(next);
			}
		}
	}
}

// ------------------------------------------------------------------ //

// dessine les tirs envoyés du joueur

void drawTirsHero(tir_Struct t)
{
	int i, j;

	// attribue les valeurs de coordonnées du tir à i et j
	j = t->pos.x;
	i = t->pos.y;
	
	// si le héro est sous l'effet d'un bonus, la couleur du tir devient bleu
	// par défaut, elle est jaune
	if(hero->bonus_active == false) glColor3f(GREEN);
	else if(hero->bonus_active == true) glColor3f(RED);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// déplacement du tir à l'endroit de départ
	glTranslatef(j*Shoot_size,i*Shoot_size,0.0f);

	// dessin
	// si le héro tient son arme de base en main alors weapon_type == false
	if(t->type == false)
	{
		glBegin(GL_QUADS);

	if(cheatMode == false && hero->ulti_active == 0)
	{
		if(Hero_size > 20)
		{
			glVertex2d((Hero_size/5)*2, 0);
			glVertex2d((Hero_size/5)*3, 0);
			glVertex2d((Hero_size/5)*3, (Hero_size/2));
			glVertex2d((Hero_size/5)*2, (Hero_size/2));
		}
		else if(Hero_size <= 20)
		{
			glVertex2d((Hero_size/5)*1, 0);
			glVertex2d((Hero_size/5)*3, 0);
			glVertex2d((Hero_size/5)*3, (Hero_size/2));
			glVertex2d((Hero_size/5)*1, (Hero_size/2));
		}	
	}
	else if(cheatMode == true || hero->ulti_active == 1)
	{
		glVertex3f(-Square_size*2,0,0);
		glVertex3f(Square_size*3,0,0);
		glVertex3f(Square_size*3,Square_size,0);
		glVertex3f(-Square_size*2,Square_size,0);
	}

	// supprime l'ultime après 10 tués

	if(hero->ulti_active == 1)
	{
		if((e->qtyToUlti+1)%6 == 0)
		{
			hero->ulti_active = 0;
		}
	}
		
		glEnd();

		
	// si le héro tient son canon à bulles en main alors weapon_type == true
	}
	else if(t->type == true && cheatMode == false)
	{
		glTranslatef(7,0,0);
		drawCircle(BLUE, i, j, 3);
		drawCircle(BLUE, i, j, 5);
	}
}

// ------------------------------------------------------------- //

// dessine les tirs alliés à la chaine (utilise drawTirs à la chaîne)
// idem que drawAllEnnemies
void drawAllTirsHero(listetir_Struct t)
{
	tir_Struct first = malloc(sizeof(tirs));
	tir_Struct next = malloc(sizeof(tirs));

	first = t->first;
	if (t->first != NULL && t->first->next != NULL)
	{
		next = t->first->next;
	}
	if (t->first != NULL || t->last != NULL)
	{
		drawTirsHero(first);
		if (t->first->next != NULL)
		{
			drawTirsHero(next);
			while (next->next != NULL)
			{
				next = next->next;

				drawTirsHero(next);
			}
		}
	}
}

// -------------------------------------------------------- //


// dessine les tirs envoyés du joueur

void drawTirsEnemy(tir_Struct te)
{
	int i, j;

	// positions de tir
	j = te->pos.x;
	i = te->pos.y;
	
	// couleur
	glColor3f(RED);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// déplacement du tir ennemi à l'endroit de départ
	glTranslatef(j*Shoot_size,i*Shoot_size,0.0f);

	// dessin
	glBegin(GL_QUADS);

	if(Hero_size > 20)
	{
		glVertex2d((Hero_size/5)*2, 0);
		glVertex2d((Hero_size/5)*3, 0);
		glVertex2d((Hero_size/5)*3, (Hero_size/2));
		glVertex2d((Hero_size/5)*2, (Hero_size/2));
	}
	else
	{
		glVertex2d((Hero_size/5)*1, 0);
		glVertex2d((Hero_size/5)*4, 0);
		glVertex2d((Hero_size/5)*4, (Hero_size/2));
		glVertex2d((Hero_size/5)*1, (Hero_size/2));
	}

	glEnd();
}


// ------------------------------------------------------------- //

// dessine les tirs ennemis à la chaine (utilise drawTirs à la chaîne)
// idem que drawAllEnnemies

void drawAllTirsEnemy(listetir_StructEnemy te)
{
	tir_Struct first = malloc(sizeof(tirs));
	tir_Struct next = malloc(sizeof(tirs));
	first = te->first;
	if (te->first != NULL && te->first->next != NULL)
	{
	next = t->first->next;
	}
	if (te->first != NULL || te->last != NULL)
	{
		drawTirsEnemy(first);
		if (te->first->next != NULL)
		{
			drawTirsEnemy(next);
			while (next->next != NULL)
			{
				next = next->next;
				drawTirsEnemy(next);
			}
		}
	}
}







                    /***********************
                     * FREE TEXTS DRAWINGS *
                     ***********************/

// écrit un texte aux couleurs et positions voulues

void writeSomething(float red, float green, float blue, int x, int y, char *txt){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// couleur du texte
	glColor3f(red, green, blue);

	// déplacement du 'curseur' à l'endroit souhaité
	glRasterPos3f(x, y, 0);

    char *msg1= txt;
	
	// dessin en bitmap
    for(int i = 0; i <strlen(msg1);i++)
	{
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
	}
}

// --------------------------------------------------------------------------------------------_//

// écrit un texte aux couleurs et positions voulues en helvetica taille 18

void writeSomethingHelvetica(float red, float green, float blue, int x, int y, char *txt){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// couleurs du texte
	glColor3f(red, green, blue);

	// déplacement du 'curseur' à l'endroit souhaité
	glRasterPos3f(x, y, 0);

    char *msg1= txt;

	// dessin en bitmap
    for(int i = 0; i <strlen(msg1);i++)
	{
    	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg1[i]);
	}
}

// --------------------------------------------------------------------------------------------_//


// écrit un texte aux couleurs et positions voulues en TIMES 24 avec 
// un tableau statique en argument

void writeSomethingArray(float red, float green, float blue, int x, int y, char txt[])
{
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// couleur du texte
	glColor3f(red, green, blue);

	// déplacement du 'curseur' à l'endroit souhaité
	glRasterPos3f(x, y, 0);

	// dessin en bitmap
    for(int i = 0; txt[i] != '\0';i++)
	{
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, txt[i]);
	}
}








