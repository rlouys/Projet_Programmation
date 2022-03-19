#include "game_graphics.h"
#include "menus_graphics.h"
#include "characters.h"


#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ------------------------------------------------------------------ //

GLfloat xwcMin, xwcMax;
GLfloat ywcMin, ywcMax;

int xPos;
int yPos;

int mX;
int mY;

int tick;

int direction;

void WelcomeDisplay()
{	

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawWall(mX, mY);

    glColor3f(1, 0, 0);

    glRasterPos3f(50, 500, 1);
    char msg1[]="SUSTAINABLE MOBILITY : SUBSISTANCE";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(50, 480, 1);
    char msg2[]="----------------------------------------------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);

    glRasterPos3f(50, 400, 0);
    char msg3[]="CONTINUER ('c')";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    glRasterPos3f(50, 375, 0);
    char msg4[]="Nouvelle partie ('n')";
    for(int i = 0; i <strlen(msg4);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);

    glRasterPos3f(50, 300, 0);
    char msg5[]="GAMEPLAY ('g')";
    for(int i = 0; i <strlen(msg5);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);

    glRasterPos3f(50, 275, 0);
    char msg6[]="OPTIONS ('o')";
    for(int i = 0; i <strlen(msg6);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);

    glRasterPos3f(50, 250, 0);
    char msg7[]="Sortie('x')";
    for(int i = 0; i <strlen(msg7);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

    glRasterPos3f(50, 50, 0);
    char msg8[]="Press 'c' to enter the game";
    for(int i = 0; i <strlen(msg8);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg8[i]);

    glutSwapBuffers();
}

// ------------------------------------------------------------------ //

void DisplayOptions()
{	


	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawWall(mX, mY);

    glColor3f(1, 0, 0);

    glRasterPos3f(50, 500, 1);
    char msg1[]="OPTIONS";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(50, 480, 1);
    char msg2[]="------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);

    glRasterPos3f(50, 400, 0);
    char msg3[]="LOREM IPSUM (...)";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    
    glutSwapBuffers();
}

// ------------------------------------------------------------------ //

void DisplayGameplay()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawWall(mX, mY);

    glColor3f(1, 0, 0);

    glRasterPos3f(50, 500, 1);
    char msg1[]="GAMEPLAY";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(50, 480, 1);
    char msg2[]="---------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);

    glRasterPos3f(50, 400, 0);
    char msg3[]="LOREM IPSUM (...)";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    
    glutSwapBuffers();
}

// ------------------------------------------------------------------ //

void DisplayEnding()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //	drawWall(mX, mY);

    glColor3f(1, 0, 0);

    glRasterPos3f(50, 500, 1);
    char msg1[]="CYA";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(50, 480, 1);
    char msg2[]="-----------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);

    glRasterPos3f(50, 400, 0);
    char msg3[]="CREDITS (...)";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    
    glutSwapBuffers();
}

// ------------------------------------------------------------------ //

void myMenu(int id){
	switch(id){

		case 2:
			printf("Options\n");
			break;
		case 3:
			printf("Gameplay\n");
			break;
		case 4:
			printf("Pause\n");	
			break;
		case 5:
			printf("_!_Cheat_mode_!_");	
		case 6:
			printf("Cya!");	
	}
}

// ------------------------------------------------------------------ //


