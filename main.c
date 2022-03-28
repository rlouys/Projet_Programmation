/*** LIBS ***/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "characters.h"
#include "game_graphics.h"
#include "menus_graphics.h"
#include "timers_and_effects.h"
#include "enemies.h"
#include "tirs.h"
#include "game.h"

/*** VARIABLES ***/

bool test = false;
int tick = 0;
int direction = 0;
float vl = 20.0;
float *value = &vl;
int c = 0;


/*** FUNCTIONS ***/
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
    glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(width, 0,0, heigth);

}

// ------------------------------------------------------------------ //

int updatePosition(int value){
    
    value = value*1.25;
    if(value>=500){
            value = 10;
        }
    return value;

}

// ------------------------------------------------------------------ //

void Display()
{	
    
	glClearColor(0.1f,0.1f,0.1f,0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game(&mX, &mY, p,e,t);

    glFlush();

}

// ------------------------------------------------------------------ //

void keyboardFunc(unsigned char Key, int x, int y) {


    switch (Key) {
    /*case 'w':
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

/*void parseArgs(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0) {
            printf("Wraparound enabled");
            wrapAround = true;
        } else {
           printf("Unrecognized option: %s", argv[i]);
        }
    }
}*/

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
    mX = 80;
    mY = 41;
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
    srand(time(NULL));
   // parseArgs(argc, argv);

	loadMap(&mX, &mY);     //Charge la carte
	

     p = createPlayer(&mX, &mY);
     e = initialListEnemies();
     t = initialListeTirs();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize((mY)*Square_size, mX*Square_size);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Sustainable Mobility : Subsistance");


 
	initRendering();
	glutDisplayFunc(WelcomeDisplay);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(arrowFunc);
    glutMouseFunc(mouse);    	

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

 
    glutTimerFunc(50, timer, 0);
    glutTimerFunc(50, updateCollisions, 0);
    glutTimerFunc(200, updateEnemies, 1);
    glutTimerFunc(50, updateTirs, 2);
    glutTimerFunc(50, updateNewEnemies, 3);
    glutTimerFunc(50, updateDeleteEnemies, 4);
    glutTimerFunc(50, updateDeleteTirs, 5);


    glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;

}