/*** LIBS ***/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


/*** FILES ***/

#include "hero.h"
#include "game_graphics.h"
#include "menus_graphics.h"
#include "timers_and_effects.h"
#include "enemies.h"
#include "tirs.h"
#include "game.h"

/*** CONSTANTES ***/ 

#define MAP_WIDTH mX*Square_size
#define MAP_HEIGTH mY*Square_size


/*** VARIABLES ***/

bool test = false;
//int tick = 0;
int direction = 0;
float vl = 20.0;
float *value = &vl;
int c = 0;
char* cheatMode = "| Cheat mode : disabled";
//bool cheatModeT = false;
bool startgame = false;
bool try = false;


/*** FUNCTIONS ***/
// ------------------------------------------------------------------ //

void wait()
{
    int timerwait;

    for(timerwait = 0; timerwait < 200000; timerwait++)
    {
            printf("wait : %i\n", timerwait);
    }
    exit(0);
}

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
    gluOrtho2D(0, width, 0, heigth);

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

// action à la souris || Clic gauche : indique la position d'où on se trouve || Clic droit(comment) : ferme la fenêtre (exit(0)). 

void mouse(int bouton,int etat,int x,int y) { // action à la souris || Clic gauche : indique la position d'où on se trouve || Clic droit : ferme la fenêtre (exit(0)). 
  if ( etat == GLUT_DOWN )
    switch ( bouton ) {
      case GLUT_LEFT_BUTTON  : c = (c+1)%7; 
                               printf("%4d %4d\n",x,y); 
                               glutPostRedisplay();
                               break ;
      /*case GLUT_RIGHT_BUTTON : exit(0);
                               break; */
                               }
}
// ------------------------------------------------------------------ //


int main(int argc, char *argv[])
{

    // VARIABLES // 

    mX = 80;
    mY = 41;
    srand(time(NULL));

    // map & jeu
	loadMap(&mX, &mY);     //Charge la carte
	
     hero = createHero(&mX, &mY);
     e = initialListEnemies();
     t = initialListeTirs();
     o = initialListObstacles();

     // GLUT initialisations

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(MAP_HEIGTH, MAP_WIDTH);
	glutInitWindowPosition(1000, 0);
	glutCreateWindow("Sustainable Mobility : Subsistance");
	initRendering();
	glutDisplayFunc(WelcomeDisplay);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(arrowFunc);
    glutMouseFunc(mouse);    	

// 26/4 - 13/43 
// 26/4 - 11/60 

// MENU CLIC DROIT

    init_rightClick_Menu();
  

// TIMERS
    glutTimerFunc(50, scrolling, 0);
    glutTimerFunc(100, updateCollisions, 0);
    glutTimerFunc(200, updateEnemies, 1);
    glutTimerFunc(1, updateTirs, 2);
    glutTimerFunc(50, updateNewEnemies, 3);
    glutTimerFunc(10, updateDeleteEnemies, 4);
    glutTimerFunc(10, updateDeleteTirs, 5);
    glutTimerFunc(50, updateObstacle, 6);
	glutTimerFunc(10, updateNewObstacles, 7);
	//glutTimerFunc(10, updateDeleteObstacles, 8);
	//glutTimerFunc(10, updateCollisionsHE, 10);

    glEnable(GL_DEPTH_TEST);
	glutMainLoop();
        
	return 0;

}
