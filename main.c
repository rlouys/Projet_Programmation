#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "characters.h"
#include "game_graphics.h"
#include "menus_graphics.h"


//GLsizei winWidth = 1000, winHeight = 1000;

int xPos = 182;
int yPos = 33;

int mX = 70;
int mY = 41;

int tick = 0;
bool wrapAround = false;
int direction = 0;

int value = 50;

int c = 0;
/* Set range for world coordinates. */

const int REFRESH_MS = 5;

GLfloat xwcMin = 182, xwcMax = 800.001;
GLfloat ywcMin = 33, ywcMax = 200.0;




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
        direction = 0;
        break;
    case GLUT_KEY_RIGHT:
        direction = 2;
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
    glViewport(0.0, 0.0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(1000, 0, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ------------------------------------------------------------------ //

void timer(int value) {
    
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(30, timer, 0); // next timer call milliseconds later

}

int updatePosition(int value){
    
    value = value*2;
    if(value>=200){
            value = 24.39;
        }

    return value;

}

void Display()
{	
	glClearColor(0.1f,0.1f,0.1f,0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    value = updatePosition(value);
    printf("Valeur : %d\n", value);
    glPushMatrix();
   // glLoadIdentity();
    drawMap(mX, mY);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(xPos, yPos, 0);
    HeroCharacter(direction); // génère le perso
    while(direction>=0 && direction<4)
    {
    updatePos(direction); // permet le déplacement
    direction = 4;
    }
    glPopMatrix();
   /* popEnnemis();
    updatePos(direction);*/
    glFlush();
    tick++;

}

// ------------------------------------------------------------------ //

void keyboardFunc(unsigned char Key, int x, int y) {


    switch (Key) {
   /* case 'w':
        wrapAround = !wrapAround;
        printf("Wraparound set to %s\n", ((wrapAround) ? "true" : "false"));
        glutPostRedisplay();
        break;*/
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

void mouse(int bouton,int etat,int x,int y) { // action à la souris || Clic gauche : indique la position d'où on se trouve || Clic droit : ferme la fenêtre (exit(0)). 
  if ( etat == GLUT_DOWN )
    switch ( bouton ) {
      case GLUT_LEFT_BUTTON  : c = (c+1)%7; 
                               printf("%4d %4d\n",x,y); 
                               glutPostRedisplay();
                               break ;
      case GLUT_RIGHT_BUTTON : exit(0);
                               break; 
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
    //handleResize(WIDTH, HEIGHT);

    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(arrowFunc);
    glutMouseFunc(mouse);    	

// MENU
/*
	glutCreateMenu (myMenu);
	glutAddMenuEntry ("|             MENU               |", 0);
	glutAddMenuEntry ("''''''''''''''''''''''''''''''''''''''''''''''''''", 1);

	glutAddMenuEntry ("| 
    Options", 2);
	glutAddMenuEntry ("| Gameplay", 3);
	glutAddMenuEntry ("| Pause", 4);
	glutAddMenuEntry ("| Cheat mode : disabled", 5);
	glutAddMenuEntry ("| Quit", 6);

	glutAttachMenu (GLUT_RIGHT_BUTTON);
*/
// 
    glutTimerFunc(10, timer, 0);
    //glutTimerFunc(25, &drawMap, 0);

	//glutTimerFunc(1000,update,0);

	glutMainLoop();

	return 0;

}