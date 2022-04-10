/*** LIBS ***/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "game_graphics.h"
#include "menus_graphics.h"
#include "characters.h"
#include "enemies.h"
#include "game.h"
#include "timers_and_effects.h"
// --------------------------------------------------------------------------------------------_//
#define MAP "map-test.txt" 
#define FOND 0.0
#define HEART_SIZE 0.8 //(0.1 = little || 1 = big)
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

void drawHealth(player p){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int i;

	int x = 700;
	int y = 980;

	glTranslatef(x,y,0);

//vie = 3
	for(i = 1; i <= p->vie; i++)
	{	
		
		drawHeart(1,0,0);
		glTranslatef(Square_size*2,0,0);

	}

}

// --------------------------------------------------------------------------------------------_//

void drawScore(player p)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	
	int a = p->current_xp;

	char str[10];

	sprintf(str, "%d", a);


	writeSomething(0,0,0,700, 780, "SCORE");
	writeSomething(0,0,0,690, 760, "-------");
	writeSomething(0,0,0,700, 738, str);

}


// --------------------------------------------------------------------------------------------_//

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

void drawMap(int *mX, int *mY, player p)			
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
	drawHealth(p);
	writeSomething(0,0,0,690,1010,"HEALTH");
	writeSomething(0,0,0,680,995,"---------");
	
	drawScore(p);


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

	//drawSquare(1.0, 0.0, 1.0);	
	drawHero(1.0,0.0,1.0);
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
	glTranslatef(i*Square_size,j*Square_size,0.0f);
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

	j = p->pos.x;
	i = p->pos.y;

	glColor3f(0.141f, 0.901, 0.0f);
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

void drawAllEnnemis(listeEn e)
{	
	enemy first = malloc(sizeof(enemies));
	enemy next = malloc(sizeof(enemies));
	first = e->first;
	next = e->first->nextptr;
	if (e->first != NULL || e->last != NULL) // test existence
	{
		drawEnemy(first);
		if (e->first->nextptr != NULL)
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
	first = t->first;
	if (t->first != NULL && t->first->nextptr != NULL)
	{
	next = t->first->nextptr;
	}
	if (t->first != NULL || t->last != NULL)
	{
		drawTirs(first);
		if (t->first->nextptr != NULL)
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






