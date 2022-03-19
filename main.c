#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "characters.h"
#include "game_graphics.h"
#include "menus_graphics.h"

GLsizei winWidth = 600, winHeight = 600;

/* Set range for world coordinates. */

const int REFRESH_MS = 5;

GLfloat xwcMin, xwcMax;
GLfloat ywcMin, ywcMax;

int xPos;
int yPos;

int mX;
int mY;

int tick;

int direction;
bool wrapAround;

//char **map;



// ------------------------------------------------------------------ //


void arrowFunc(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        direction = 3;
        break;
    case GLUT_KEY_DOWN:
        direction = 1;
        break;
    case GLUT_KEY_LEFT:
        direction = 2;
        break;
    case GLUT_KEY_RIGHT:
        direction = 0;
        break;
    }
}

// ------------------------------------------------------------------ //



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
	gluOrtho2D(0, width, heigth, 0);
}

// ------------------------------------------------------------------ //

void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(REFRESH_MS, timer, 0); // next timer call milliseconds later
}

// ------------------------------------------------------------------ //

/*void Display()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawWall(mX, mY);

    glPushMatrix();
    glTranslatef(xPos, yPos, 0);

    HeroCharacter(direction); // génère le perso
    updatePos(direction); // permet le déplacement

    glPopMatrix();
    glFlush();
    tick++;

}*/

// ------------------------------------------------------------------ //


/*void WelcomeDisplay()
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
}*/

// ------------------------------------------------------------------ //

/*void DisplayOptions()
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
}*/

// ------------------------------------------------------------------ //

/*void DisplayGameplay()
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
}*/

// ------------------------------------------------------------------ //


// ------------------------------------------------------------------ //

/*void DisplayEnding()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawWall(mX, mY);

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
}*/

// ------------------------------------------------------------------ //

/*void myMenu(int id){
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
}*/

// ------------------------------------------------------------------ //

// ------------------------------------------------------------------ //

void keyboardFunc(unsigned char Key, int x, int y) {


    switch (Key) {
    case 'w':
        wrapAround = !wrapAround;
        printf("Wraparound set to %s\n", ((wrapAround) ? "true" : "false"));
        glutPostRedisplay();
        break;
    case 'c':
		glutDisplayFunc(Display);
		glutPostRedisplay();
		break;

	case 'n':
		glutDisplayFunc(Display);
		glutPostRedisplay();
		break;

	case 'x':
		glutDisplayFunc(DisplayEnding);
		glutPostRedisplay();
		break;

	case 'g':
		glutDisplayFunc(DisplayGameplay);
		glutPostRedisplay();
		break;

	case 'o':
		glutDisplayFunc(DisplayOptions);		
		glutPostRedisplay();
		break;	    

	case 'm':
		glutDisplayFunc(WelcomeDisplay);
		glutPostRedisplay();	
		break;	
    };
   
}

// ------------------------------------------------------------------ //

void init(void) {
    /* Set color of display window to white. */
    glClearColor(1, 1, 1, 1.0);
}

// ------------------------------------------------------------------ //

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

// ------------------------------------------------------------------ //

void parseArgs(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0) {
            printf("Wraparound enabled");
            wrapAround = true;
        } else {
           printf("Unrecognized option: %s", argv[i]);
        }
    }
}

// ------------------------------------------------------------------ //


int main(int argc, char *argv[])
{

	// TESTS // 
/*
	List Hero = new_character();
	print_character(Hero);

	
	Hero = create_Hero(Hero);
	print_character(Hero);

	printf("Cleaning the Hero....\n\n");
	Hero = clear_list (Hero);
	print_character(Hero); 

*/

// ------------------------------------------------------------------ //
	// GLUT //

    parseArgs(argc, argv);

	loadMap(mX, mY);     //Charge la carte
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(mX*Square_size, mY*Square_size); // mY*3*Square_size
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Sustainable Mobility : Subsistance");



	initRendering();

	glutDisplayFunc(WelcomeDisplay);
    glutReshapeFunc(winReshapeFcn);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(arrowFunc);

	glutCreateMenu (myMenu);
	glutAddMenuEntry ("|             MENU               |", 0);
	glutAddMenuEntry ("''''''''''''''''''''''''''''''''''''''''''''''''''", 1);

	glutAddMenuEntry ("| Options", 2);
	glutAddMenuEntry ("| Gameplay", 3);
	glutAddMenuEntry ("| Pause", 4);
	glutAddMenuEntry ("| Cheat mode : disabled", 5);
	glutAddMenuEntry ("| Quit", 6);

	glutAttachMenu (GLUT_RIGHT_BUTTON);

    init();
    glutTimerFunc(0, timer, 0);


	glutMainLoop();

	return 0;

}