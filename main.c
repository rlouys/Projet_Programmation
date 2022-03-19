#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "characters.h"
#include "game_graphics.h"
#include "menus_graphics.h"

#define WIDTH 1000
#define HEIGHT 1000

GLsizei winWidth = 1000, winHeight = 1000;

int xPos = 300;
int yPos = 300;

int mX = 40;
int mY = 41;

int tick = 0;
bool wrapAround = false;
int direction = 0;

/* Set range for world coordinates. */

const int REFRESH_MS = 5;

GLfloat xwcMin = 0.0, xwcMax = 1000.0;
GLfloat ywcMin = 0.0, ywcMax = 1000.0;




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

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

// ------------------------------------------------------------------ //

void handleResize(int width,int heigth)
{
    glViewport(0.0, 0.0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, heigth);
    glMatrixMode(GL_MODELVIEW);

}

// ------------------------------------------------------------------ //

void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(REFRESH_MS, timer, 0); // next timer call milliseconds later
}



void Display()
{	
	glClearColor(0.1f,0.1f,0.1f,0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawMap(mX, mY);


    glPushMatrix();
    glTranslatef(xPos, yPos, 0);
    HeroCharacter(direction); // génère le perso
    updatePos(direction); // permet le déplacement
    glPopMatrix();


    glFlush();
    tick++;

}

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
    glColor3f(0,0,0);
    glPointSize(1000);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,WIDTH,0,HEIGHT);
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

	glutInitWindowSize(1000,1000); // mY*3*Square_size
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Sustainable Mobility : Subsistance");


 
	initRendering();
   // handleResize(WIDTH, HEIGHT);

	glutDisplayFunc(Display);
    handleResize(WIDTH, HEIGHT);

   // glutReshapeFunc(winReshapeFcn);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(arrowFunc);


// MENU

	glutCreateMenu (myMenu);
	glutAddMenuEntry ("|             MENU               |", 0);
	glutAddMenuEntry ("''''''''''''''''''''''''''''''''''''''''''''''''''", 1);

	glutAddMenuEntry ("| Options", 2);
	glutAddMenuEntry ("| Gameplay", 3);
	glutAddMenuEntry ("| Pause", 4);
	glutAddMenuEntry ("| Cheat mode : disabled", 5);
	glutAddMenuEntry ("| Quit", 6);

	glutAttachMenu (GLUT_RIGHT_BUTTON);

// 
    init();
    glutTimerFunc(0, timer, 0);


	glutMainLoop();

	return 0;

}