#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game_graphics.h"
#include "menus_graphics.h"
#include "characters.h"

#define MAP "map-test.txt" 

// --------------------------------------------------------------------------------------------_//
int value;

// load variables //

int xPos;
int yPos;
int mX;
int mY;
int tick;
int direction;
//int camera = 1000/mY;
//int value = -24.39;//24.39;

// --------------------------------------------------------------------------------------------_//

bool loadMap(int mX, int mY)		//fonction qui ouvre le fichier txt et charge la carte dans le tableau
{
	

    map = malloc(sizeof(char *) * mX);	
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
	
	*(map + i) = malloc(sizeof(char *) * mX);	
	for(i = 0; i < mX; i++)
		{
		*(map + i) = malloc(sizeof(char *) * mX);	
			for(j = 0; j < mY; j++)
			{		
				c = fgetc(f);
				*(*(map + i) + j) = c;
			}
			fgetc(f);
		}

	    fclose(f);
		
	    printf("\n");

		for(i = 0; i < mX; i++)
		{
			for(j = 0; j < mY; j++)
			{
				printf("%c", map[i][j]);
			}
			printf("\n");
		}
				
		
 return true;
 }		

// --------------------------------------------------------------------------------------------_//

// DRAW A SQUARE (SIZEOF = Map_pixel_size/nb_objects)
// les couleurs doivent être entrées en paramètre

void drawSquare(float red, float green, float blue, int j, int i, int type)
{
	//glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(red,green,blue);

	int map_size = 1000;

	if(type==0)
	{
	glVertex2d(i*(map_size/mY),j*(map_size/mX));
	glVertex2d((i+2)*(map_size/mY),j*(map_size/mX));
	glVertex2d((i+2)*(map_size/mY),(j+1)*(map_size/mX));
	glVertex2d(i*(map_size/mY), (j+1)*(map_size/mX));
	}
	else if(type==1)
	{
	glVertex2d(i*(map_size/mY),j*(map_size/mX));
	glVertex2d((i+0.5)*(map_size/mY),j*(map_size/mX));
	glVertex2d((i+0.5)*(map_size/mY),(j+1)*(map_size/mX));
	glVertex2d(i*(map_size/mY), (j+1)*(map_size/mX));
	}
	else if(type ==2)
	{
	glVertex2d((i+0.5)*(map_size/mY),j*(map_size/mX));
	glVertex2d((i+1)*(map_size/mY),j*(map_size/mX));
	glVertex2d((i+1)*(map_size/mY),(j+1)*(map_size/mX));
	glVertex2d((i+0.5)*(map_size/mY), (j+1)*(map_size/mX));
	}

	//glPopMatrix();


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

/*void update()
{
	value *= 1.2;
	glutPostRedisplay();
	glutTimerFunc(100,update,0);
}*/

// --------------------------------------------------------------------------------------------_//

void drawMap(int mX, int mY)			
{	
	glClear(GL_COLOR_BUFFER_BIT);
	//glPushMatrix();
	//glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	glTranslatef(0,-value,0);

	for (int j = 0; j < mX; ++j)
	{
		for (int i = 0; i < mY+1; i++)
		{
			if(*(*(map + j) + i) == '#') // Murs bruns
			{	

				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/

				drawSquare(0.30, 0.23, 0.12, j, i, 0);	
						//	glTranslatef(0,1000/mY,0);

			}

			if(*(*(map + j) + i) == '1') // Sable bordures
			{
				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/

				drawSquare(0.94, 0.87, 0.70, j, i, 0);
			}
		
			if (*(*(map + j) + i) == '|') // lignes centrales
			{

				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/
			
				drawSquare(0.5, 0.5, 0.5, j, i, 1);
				drawSquare(1.0, 1.0, 1.0, j, i, 2);
			
			}

			if (*(*(map + j) + i) == 'l') // piste cyclable
			{

				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/

				drawSquare(0.5, 0.5, 0.5, j, i, 1);
				drawSquare(1.0, 1.0, 0.7, j, i, 2);

			}

			if(*(*(map + j) + i) == 'e') // Ennemis
			{

				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/

				drawSquare(1.0, 0.0, 0.0, j, i, 0);

			}

			if(*(*(map + j) + i) == ' ') // Fond de plateau
			{

				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/

				drawSquare(0.5, 0.5, 0.5, j, i, 0);

			}	

			if(*(*(map + j) + i) == 'z') // A adapter, sert à combler un vide de dessin non désiré
			{
				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/

				drawSquare(1, 1, 1, j, i, 0);

			}
			
			if(*(*(map + j) + i) == 'b') // Hero
			{
				/*glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();*/

				drawSquare(1.0, 1.0, 1.0, j, i, 0);
		
			}
		}
	}
	//glPopMatrix();

}




