#include <GL/glut.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game_graphics.h"
//#include "menus_graphics.h"

// load map //


bool loadMap(int mX, int mY)		//fonction qui ouvre le fichier txt et charge la carte dans le tableau
{
	

    map = malloc(sizeof(char *) * mX);	
    FILE *f = NULL;
    f = fopen("map2.txt", "r");
    if(f == NULL)
    {
        printf("file empty");
        return false;
    }
    char c;
    int i= 0;
    int j = 0;
	
	*(map + i) = malloc(sizeof(char *) * mY);	
	for(i = 0; i < mX; i++)
		{
		*(map + i) = malloc(sizeof(char *) * mY);	
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


// draw map //

void drawWall(int mX, int mY)			// fonction qui affiche les murs et les plateformes
{	


	for (int j = 0; j < mX; ++j)
	{
		for (int i = 0; i < mY; ++i)
		{
			if(*(*(map + j) + i) == '#')
			{	



				glColor3f(1.0f,1.0f,1.0f);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				//glTranslatef(j*Square_size,i*Square_size,0.0f);

				glBegin(GL_QUADS);
				//glColor3f(1.0,1.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size/2,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
				glBegin(GL_POLYGON);         //draw road
				glColor3f(0.5,0.5,0.5);
				glVertex3f(0,15, 0.0f);
				glVertex3f(50, 15, 0.0f);
				glVertex3f(mX*Square_size, 15, 0.0f);
				glVertex3f(0, mY*Square_size, 0.0f);
				glEnd();
			
			}

			if(*(*(map + j) + i) == '@')
			{	



				glColor3f(1.0f,1.0f,1.0f);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				//glTranslatef(j*Square_size,i*Square_size,0.0f);

				glBegin(GL_QUADS);
				//glColor3f(1.0,1.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size/2,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
				glBegin(GL_POLYGON);         //draw road
				glColor3f(0.5,0.5,0.5);
				glVertex3f(0,15, 0.0f);
				glVertex3f(50, 15, 0.0f);
				glVertex3f(mX*Square_size, 15, 0.0f);
				glVertex3f(0, mY*Square_size, 0.0f);
				glEnd();
			
			}
		
			if (*(*(map + j) + i) == '|')
			{
				glColor3f(1.0f,1.0f,0.0f);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				//glTranslatef(j*Square_size, i*Square_size,0.0f);
				glBegin(GL_QUADS);

				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size/4, 0.0f, 0.0f);
				glVertex3f(Square_size/4,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();


			}
			if(*(*(map + j) + i) == 'e')
			{
				glColor3f(0.0f,0.0f,0.0f);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				//glTranslatef(j*Square_size,i*Square_size,0.0f);

				glBegin(GL_QUADS);
				//glColor3f(1.0,1.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
				
				glBegin(GL_POLYGON);         //draw road
				glColor3f(0.5,0.5,0.5);
				glVertex3f(0,15, 0.0f);
				glVertex3f(50, 15, 0.0f);
				glVertex3f(mX*Square_size, 15, 0.0f);
				glVertex3f(0, mY*Square_size, 0.0f);
				glEnd();
			}
			if(*(*(map + j) + i) == 'z')
			{
				glColor3f(0.0f,0.0f,0.0f);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				//glTranslatef(j*Square_size,i*Square_size,0.0f);

				glBegin(GL_QUADS);
				glColor3f(0.5,0.5,0.5);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
				
			}
			if(*(*(map + j) + i) == 'b')
			{
				glColor3f(1.0f,1.0f,1.0f);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				//glTranslatef(j*Square_size,i*Square_size,0.0f);

				glBegin(GL_QUADS);
				//glColor3f(1.0,1.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
				
				glBegin(GL_POLYGON);         //draw road
				glColor3f(0.5,0.5,0.5);
				glVertex3f(0,15, 0.0f);
				glVertex3f(50, 15, 0.0f);
				glVertex3f(mX*Square_size, 15, 0.0f);
				glVertex3f(0, mY*Square_size, 0.0f);
				glEnd();
			}

		}
	}

	

}