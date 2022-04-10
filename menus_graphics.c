
/*** LIBS ***/

#include "game_graphics.h"
#include "menus_graphics.h"
#include "timers_and_effects.h"
#include "characters.h"


#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

// ------------------------------------------------------------------ //
/*** VARIABLES ***/
// ------------------------------------------------------------------ //

int mX;
int mY;
char* cheatMode;
bool cheatModeT;
float df = 5;
float *deplacement_fenetre = &df;
bool try;

// ------------------------------------------------------------------ //
/*** FUNCTIONS ***/
// ------------------------------------------------------------------ //

void WelcomeDisplay()
{	

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.03, 0.49, 0.13);

    glRasterPos3f(50, 800, 1);
    char msg1[]="SUSTAINABLE MOBILITY : SUBSISTANCE";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);


    glRasterPos3f(50, 780, 1);
    char msg2[]="----------------------------------------------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);

    glColor3f(1, 0, 0);

    glRasterPos3f(50, 740, 0);
    char msg3[]="CONTINUER ('c')";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    glRasterPos3f(50, 700, 0);
    char msg4[]="Nouvelle partie ('n')";
    for(int i = 0; i <strlen(msg4);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);

    glRasterPos3f(50, 660, 0);
    char msg5[]="GAMEPLAY ('g')";
    for(int i = 0; i <strlen(msg5);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);

    glRasterPos3f(50, 620, 0);
    char msg6[]="OPTIONS ('o')";
    for(int i = 0; i <strlen(msg6);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);

    glRasterPos3f(50, 580, 0);
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
void EndGameDisplay()
{	
   // int tick;
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.03, 0.49, 0.13);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  //  glTranslatef(0,0,0);

   /* glRasterPos3f(-500, -250, 0);
    char msg1[]="----------- YOU FAILED -----------";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);*/

    int a = p->current_xp;
	char str[10];
	sprintf(str, "%d", a);

    int b = p->killed;
    
    char strn[10];
    sprintf(strn, "%d", b);

	writeSomething(1,1,1,200, 930, "++++++++++++++++++++++++");    
    writeSomething(1,1,1,200, 915, "+                                                    +");
	writeSomething(1,1,1,200, 900, "+              YOU FAILED              +");
    writeSomething(1,1,1,200, 885, "+                                                    +");
    writeSomething(1,1,1,200, 870, "++++++++++++++++++++++++");
	writeSomething(1,1,1,200, 800, "Your score :");
	writeSomething(1,1,1,450, 800, str);
    writeSomething(1,1,1,200, 750, "Ennemy killed :");
	writeSomething(1,1,1,450, 750, strn);

    drawSquare(1,1,1);


    glutSwapBuffers();
}
// ------------------------------------------------------------------ //



void DisplayOptions()
{	


	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.03, 0.49, 0.13);


    glRasterPos3f(50, 800, 1);
    char msg1[]="OPTIONS";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(50, 780, 1);
    char msg2[]="------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    glColor3f(1, 0, 0);

    glRasterPos3f(50, 750, 0);
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
    glColor3f(0.03, 0.49, 0.13);


    glRasterPos3f(50, 800, 1);
    char msg1[]="GAMEPLAY";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(50, 780, 1);
    char msg2[]="---------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    glColor3f(1, 0, 0);

    glRasterPos3f(50, 750, 0);
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

    glColor3f(0.03, 0.49, 0.13);

    glRasterPos3f(50, 800, 1);
    char msg1[]="SEE YOU LATER !";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(50, 780, 1);
    char msg2[]="-----------------";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    glColor3f(1, 0, 0);

    glRasterPos3f(50, 750, 0);
    char msg3[]="CREDITS (...)";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    
    glutSwapBuffers();
    wait();
}

// ------------------------------------------------------------------ //

void myMenu(int id){
	switch(id){

		case 2:
            glutDisplayFunc(DisplayOptions);
			break;
		case 3:
            glutDisplayFunc(DisplayGameplay);
			break;
		case 4:
			printf("Pause\n");	
			break;
		case 5:
			printf("_!_Cheat_mode_!_");	
            
		case 6:
            glutDisplayFunc(DisplayEnding);
	}
}

// ------------------------------------------------------------------ //


