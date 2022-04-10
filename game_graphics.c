/*** LIBS ***/


#include <GL/glut.h>
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
#define FOND 0.0
#define HEART_SIZE 0.8 //(0.1 = little || 1 = big)

/***  VARIABLES  ***/


float *value;
int mX;
int mY;


/*** FUNCTIONS ***/ 
// --------------------------------------------------------------------------------------------_//

// charge la map

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
		
	    printf("\n");

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

// --------------------------------------------------------------------------------------------_//

// affiche la vitalité du joueur en temps réel

void drawHealth(Hero hero){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int i;

	int x = 700;
	int y = 980;

	glTranslatef(x,y,0);

//vie = 3
	for(i = 1; i <= hero->health; i++)
	{	
		
		drawHeart(1,0,0);
		glTranslatef(Square_size*2,0,0);

	}

}

// --------------------------------------------------------------------------------------------_//

// affiche le score du joueur en temps réel

void drawScore(Hero hero)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	
	int a = hero->current_xp;

	char str[10];

	sprintf(str, "%d", a);


	writeSomething(0,0,0,700, 780, "SCORE");
	writeSomething(0,0,0,690, 760, "-------");
	writeSomething(0,0,0,700, 738, str);

}

// --------------------------------------------------------------------------------------------_//

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

// --------------------------------------------------------------------------------------------_//

// dessine une ligne aux couleurs voulues


void drawLine(float red, float green, float blue)
{
	
	float line = Square_size/3;

	glBegin(GL_QUADS);
	glColor3f(red,green,blue);

	
	glVertex3f(line, 0.0f, 0.0f);
	glVertex3f(line*2, 0.0f, 0.0f);
	glVertex3f(line*2,Square_size, 0.0f);
	glVertex3f(line,Square_size, 0.0f);

	red = FOND;
	green = FOND;
	blue = FOND;

	glColor3f(red,green,blue);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(line, 0.0f, 0.0f);
	glVertex3f(line,Square_size, 0.0f);
	glVertex3f(0,Square_size, 0.0f);

	glColor3f(red,green,blue);

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

// --------------------------------------------------------------------------------------------_//

// DRAW A SQUARE (SIZEOF = Map_pixel_size/nb_objects)
// les couleurs doivent être entrées en paramètre
// dessine un carré aux couleurs voulues

void drawSquare(float red, float green, float blue)
{
	glBegin(GL_QUADS);
	glColor3f(red,green,blue);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(Square_size, 0.0f, 0.0f);
		glVertex3f(Square_size,Square_size, 0.0f);
		glVertex3f(0.0f,Square_size, 0.0f);
		
	
	glEnd();

}
// --------------------------------------------------------------------------------------------_//

// dessine le héro (design du hero)

void drawHero(float red, float green, float blue)
{

	glBegin(GL_QUADS);
	glColor3f(red,green,blue);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(Hero_size, 0.0f, 0.0f);
		glVertex3f(Hero_size,Hero_size, 0.0f);
		glVertex3f(0,Hero_size, 0.0f);
		
	
	glEnd();

}


// --------------------------------------------------------------------------------------------_//

// dessine un cercle aux couleurs voulues

void drawCircle(float red, float green, float blue, int posx, int posy, float rayon)
{

	glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posx, posy);
    int detail = 50;
    for (int i = 0; i <= detail; i++) {
        double deg = (i * (360 * 1) / detail) + 0;
        double x = rayon * cos(deg * 3.14 / 180);
        double y = rayon * sin(deg * 3.14 / 180);
        glVertex2f(x, y);
    }



}
// --------------------------------------------------------------------------------------------_//

// écrit un texte aux couleurs et positions voulues

void writeSomething(float red, float green, float blue, int x, int y, char *txt){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(red, green, blue);
	glRasterPos3f(x, y, 0);
    char *msg1= txt;

    for(int i = 0; i <strlen(msg1);i++)
	{
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
	}



}

// --------------------------------------------------------------------------------------------_//

// dessine la map et tout les éléments statiques (score, murs)

void drawMap(int *mX, int *mY, Hero hero)			
{	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();

	glTranslatef(0,-(Square_size),0);

	for (int j = 0; j < (*mX); ++j)
	{
		for (int i = 0; i < (*mY); i++)
		{
		
			if(*(*(map + j) + i) == '#') // Murs bruns
			{	

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawSquare(0.30, 0.23, 0.12);	
				drawLineBorder(0.5,0.5,0.5,0);
				drawLineBorder(0.0,0.0,0.0,3);

				

			}

			if(*(*(map + j) + i) == '@') // Murs bruns
			{	

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawSquare(0.30, 0.23, 0.12);	
				drawLineBorder(0.5,0.5,0.5,1);
				drawLineBorder(0.0,0.0,0.0,2);

			}

			if(*(*(map + j) + i) == '1') // Sable bordures
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);

				drawSquare(0.94, 0.87, 0.70);
			}
		
			if (*(*(map + j) + i) == '|') // lignes centrales
			{

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				//drawLine(1, 1, 0);
				drawLine(1, 1, 1);

			}

			if (*(*(map + j) + i) == 'l') // piste cyclable
			{

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawLine(1, 1, 1);


			}

			if(*(*(map + j) + i) == 'e') // Ennemis
			{

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);

				drawSquare(1.0, 0.0, 0.0);

			}

			if(*(*(map + j) + i) == ' ' || *(*(map + j) + i) == 'X') // Fond de plateau
			{

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawSquare(FOND, FOND, FOND);

			}

			if(*(*(map + j) + i) == 'z') // A adapter, sert à combler un vide de dessin non désiré
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);

				drawSquare(1, 1, 1);

			}
			
			if(*(*(map + j) + i) == 'b') // Hero
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glTranslatef(i*Square_size,j*Square_size,0.0f);

				drawSquare(1.0, 1.0, 1.0);
		
			}
		}
	}
	drawHealth(hero);
	writeSomething(0,0,0,690,1010,"HEALTH");
	writeSomething(0,0,0,680,995,"---------");
	
	drawScore(hero);


}

// ------------------------------------------------------------------ //

// place le héro sur la carte (en le plaçant au bon endroit)


void drawPlayer(Hero hero)
{
	int i, j;

	
	
	i = hero->pos.x;
	j = hero->pos.y;
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(i*Square_size,j*Square_size,0.0f);
	glColor3f(0.0f,1.0f,0.0f);

	//drawSquare(1.0, 0.0, 1.0);	
	drawHero(0.03, 0.49, 0.13);
}

// ------------------------------------------------------------------ //

// dessine un ennemi et le place sur la carte

void drawEnemy(enemy e)	
{
	int i, j;
	i = e->pos.x;
	j = e->pos.y;
	glColor3f(1.0f,0.0F,0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(i*Square_size,j*Square_size,0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(Square_size,0.0f,0.0f);
	glVertex3f(Square_size,Square_size,0.0f);
	glVertex3f(0.0f,Square_size,0.0f);
	glEnd();
}

// ------------------------------------------------------------------ //

// dessine les tirs envoyés du joueur

void drawTirs(tir_Struct t)
{
	int i, j;

	j = t->pos.x;
	i = t->pos.y;

	//glColor3f(0.141f, 0.901, 0.0f);
	glColor3f(1,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j*Shoot_size,i*Shoot_size,0.0f);
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

// dessine des ennemis à la chaine (utilise drawEnemy à la chaine)

void drawAllEnnemis(EnemyList e)
{	
	enemy first = malloc(sizeof(enemies));
	enemy next = malloc(sizeof(enemies));
	first = e->first;
	next = e->first->next;
	if (e->first != NULL || e->last != NULL) // test existence
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

// ------------------------------------------------------------- //

// dessine les tirs à la chaine (utilise drawTirs à la chaîne)

void drawAllTirs(listetir_Struct t)
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
		drawTirs(first);
		if (t->first->next != NULL)
		{
			drawTirs(next);
			while (next->next != NULL)
			{
				next = next->next;
				drawTirs(next);
			}
		}
	}
}

// ------------------------------------------------------------- //

void DisplayGame()
{	
    
	glClearColor(0.1f,0.1f,0.1f,0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game(&mX, &mY, hero,e,t);

    glFlush();

}






