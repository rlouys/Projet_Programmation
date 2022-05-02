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

//bool test = false;
//bool startgame = false;


int main(int argc, char *argv[])
{

    // VARIABLES // 

    mX = 80;
    mY = 49;
    srand(time(NULL));

    // map & jeu
	loadMap(&mX, &mY);     //Charge la carte
	
     hero = createHero(&mX, &mY);
     e = initialListEnemies();
     t = initialListeTirsHero();
     te = initialListeTirsEnemy();
     o = initialListObstacles();
     b = initialListeBonus();

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
    glutMouseFunc(mouse);    	


// MENU CLIC DROIT

    init_rightClick_Menu();
  

// TIMERS

    glutTimerFunc(50, scrolling, 0);

    glutTimerFunc(100, updateCollisions, 1);

    glutTimerFunc(200, updateEnemies, 2);
    glutTimerFunc(50, updateNewEnemies, 4);
    glutTimerFunc(10, updateDeleteEnemies, 5);

    glutTimerFunc(50, updateObstacle, 7);
	glutTimerFunc(10, updateNewObstacles, 8);
	glutTimerFunc(10, updateDeleteObstacles, 9);

	glutTimerFunc(10, updateBonus, 10);
    glutTimerFunc(10, updateNewBonus, 11);
    glutTimerFunc(10, updateDeleteBonus, 12);

    glutTimerFunc(1, updateTirsHero, 3);
    glutTimerFunc(1, updateTirsEnemy, 13);
    glutTimerFunc(10, updateDeleteTirs, 6);


    glEnable(GL_DEPTH_TEST);
	glutMainLoop();
        
	return 0;

}
