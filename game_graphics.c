/*** LIBS ***/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game_graphics.h"
#include "menus_graphics.h"
#include "characters.h"
#include "enemies.h"
#include "game.h"
#include "timers_and_effects.h"
// --------------------------------------------------------------------------------------------_//
#define MAP "map-test.txt" 
#define FOND 0.5
// --------------------------------------------------------------------------------------------_//


/***  VARIABLES  ***/

float *value;
int mX;
int mY;


/*** FUNCTIONS ***/ 
// --------------------------------------------------------------------------------------------_//

bool loadMap(int *mX, int *mY)		//fonction qui ouvre le fichier txt et charge la carte dans le tableau
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

// --------------------------------------------------------------------------------------------_//

// DRAW A SQUARE (SIZEOF = Map_pixel_size/nb_objects)
// les couleurs doivent être entrées en paramètre

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

void drawSky()
{
        glBegin(GL_POLYGON); 
            glColor3f(1.0,0.0,0.0);
	
            glVertex3f(Square_size, mY*Square_size, 0);
            glVertex3f(Square_size, Square_size, 0);
            glVertex3f(mX*Square_size, Square_size, 0);
            glVertex3f(mX*Square_size, mY*Square_size, 0);
        glEnd();
}

// --------------------------------------------------------------------------------------------_//

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

void drawMap(int *mX, int *mY)			
{	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();

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

			}

			if(*(*(map + j) + i) == '1') // Sable bordures
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawSquare(0.94, 0.87, 0.70);
			}
		
			if (*(*(map + j) + i) == '|') // lignes centrales
			{

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawLine(1, 1, 0);
			
			}

			if (*(*(map + j) + i) == 'l') // piste cyclable
			{

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawLine(1, 0.843, 0);

			}

			if(*(*(map + j) + i) == 'e') // Ennemis
			{

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

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
				glTranslatef(0,-(*value),0);

				drawSquare(1, 1, 1);

			}
			
			if(*(*(map + j) + i) == 'b') // Hero
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glTranslatef(0,-(*value),0);

				drawSquare(1.0, 1.0, 1.0);
		
			}
		}
	}
}

// ------------------------------------------------------------------ //

void drawPlayer(player p)
{
	int i, j;

	
	i = p->pos.x;
	j = p->pos.y;
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(i*Square_size,j*Square_size,0.0f);
	glColor3f(0.0f,1.0f,0.0f);

	drawSquare(1.0, 0.0, 1.0);	
}

// ------------------------------------------------------------------ //

void drawEnemy(enemy e)	
{
	int i, j;
	i = e->pos.x;
	j = e->pos.y;
	glColor3f(1.0f,0.0F,0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j*Square_size,i*Square_size,0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(Square_size,0.0f,0.0f);
	glVertex3f(Square_size,Square_size,0.0f);
	glVertex3f(0.0f,Square_size,0.0f);
	glEnd();
}

// ------------------------------------------------------------------ //

void drawTirs(tirsP p)
{
	int i, j;
	i = p->pos.x;
	j = p->pos.y;
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j*Shoot_size,i*Shoot_size,0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(Shoot_size,0.0f,0.0f);
	glVertex3f(Shoot_size,Shoot_size,0.0f);
	glVertex3f(0.0f,Shoot_size,0.0f);
	glEnd();
}

// ------------------------------------------------------------- //

void drawAllEnnemis(listeEn e)
{	
	enemy first = malloc(sizeof(enemies));
	enemy next = malloc(sizeof(enemies));
	first = e->starList;
	next = e->starList->nextptr;
	if (e->starList != NULL || e->endList != NULL)
	{
		drawEnemy(first);
		if (e->starList->nextptr != NULL)
		{
			drawEnemy(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawEnemy(next);
			}
		}
	}
}

// ------------------------------------------------------------- //

void drawAllTirs(listetirsP t)
{
	tirsP first = malloc(sizeof(tirs));
	tirsP next = malloc(sizeof(tirs));
	first = t->starList;
	if (t->starList != NULL && t->starList->nextptr != NULL)
	{
	next = t->starList->nextptr;
	}
	if (t->starList != NULL || t->endList != NULL)
	{
		drawTirs(first);
		if (t->starList->nextptr != NULL)
		{
			drawTirs(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawTirs(next);
			}
		}
	}
}





