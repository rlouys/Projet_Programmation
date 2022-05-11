/*** LIBS ***/

//#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menus_graphics.h"
#include "game_graphics.h"
#include "tirs.h"
#include "enemies.h"
#include "hero.h"
#include "enemies.h"
#include "game.h"
#include "timers_and_effects.h"

#define BLACK 0, 0, 0

bool startgame;
bool SHOOT;
bool SHOOT_ENEMY;
bool UPK;
bool DOWNK;
bool LEFTK;
bool RIGHTK;
bool UP;
bool DOWN;
bool LEFT;
bool RIGHT;
bool try;
bool gameplay_keys;
bool screen;
bool cheatMode;
bool cheatMode_pressed;

int c = 0; // void mouse
int difficulty;
int newGame;
int newGame_lock;
int startgame_option_bug;
int NewGame_statslock;
int counterAlpha = 0;

char username_array[20];

char* letter = " ";
char *username = " ";



// definition de la fonction Keyboard permettant de quitter/tirer

void Keyboard(unsigned char key, int x, int y)  
{
	switch(key)
	{
		// ESC KEY
		case 27:
			startgame = !startgame;
			glutDisplayFunc(GameOptionsDisplay);
			glutPostRedisplay();
			break;

		// SPACE KEY
		case 32:
		SHOOT = true;
		break;	

		// BACKSPACE KEY
		case 0x08:
			// si le tir existe, alors il est tiré
			if(te->first == NULL || te->last == NULL)
			{
				SHOOT_ENEMY = true;
			}	
			if(te->first != NULL || te->last == NULL)
			{
				SHOOT_ENEMY = true;
			}
			break;

		// mouvement du héro
		case 'w':
		switchWeapon(hero);	
		break;
		
		//touches flechées
		case 'z':
		UPK = true;
		break;

		case 'q':
		LEFTK = true;
		break;	
		
		case 's':
		DOWNK = true;
		break;

		case 'd':
		RIGHTK = true;
		break;

		}	
}

// ------------------------------------------------------------ // 

// definition de la fonction arrowFunction permettant de se déplacer via les flèches directionnelles

void arrowFunction(int key, int x, int y)
{
    switch (key) 
	{
		// déplacement du héro avec les touches 
		case GLUT_KEY_UP:
			UP = true;
			break;

		case GLUT_KEY_DOWN:
			DOWN = true;
			break;

		case GLUT_KEY_LEFT:
			LEFT = true;
			break;

		case GLUT_KEY_RIGHT:
			RIGHT = true;
			break;
    }
}


// ------------------------------------------------------------ // 


// initialise les fonctions au clavier lorsque dans un menu

void keyboardFunc(unsigned char Key, int x, int y) {

    switch (Key) {
   
    case 'c':

    	newGame = checkNewGame(newGame);

        if(newGame == 0)
        {
            saveContext();
            startgame_option_bug = 0;
            startgame = !startgame;
            glutDisplayFunc(DisplayGame);
            glutPostRedisplay();
            break;
        }
        else if(newGame == 1)
        {
            newGame_lock = 1;
            break;
        }




	case 'n': 
        NewGame_statslock = 1;
        startgame_option_bug = 0;
		glutDisplayFunc(UsernameDisplay);
		glutPostRedisplay();
		break;
    

	case 'x':

        if(try==false)
        {
            glutDisplayFunc(DisplayEnding);
            glutPostRedisplay();
        }

        if(try==true) wait1();
    	break;
    
    case 'r':
            startgame = false;
            glutDisplayFunc(WelcomeDisplay);
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

// ----------------------------------------------------------------- //

// clavier virtuel permettant d'afficher ce que l'on écrit
// dans la demande de pseudo 'n'

void Alphabet(unsigned char Key, int x, int y)
{

// sert à limiter le nombre de caractères entrés max.
if(counterAlpha <= 9)
{
    switch (Key) {
        
        case 'a':

            username_array[counterAlpha] = 'A';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;


        case 'b':

            username_array[counterAlpha] = 'B';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'c':

            username_array[counterAlpha] = 'C';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'd':

            username_array[counterAlpha] = 'D';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'e':

            username_array[counterAlpha] = 'E';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'f':

            username_array[counterAlpha] = 'F';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'g':

            username_array[counterAlpha] = 'G';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'h':

            username_array[counterAlpha] = 'H';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'i':

            username_array[counterAlpha] = 'I';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'j':

            username_array[counterAlpha] = 'J';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'k':

            username_array[counterAlpha] = 'K';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'l':

            username_array[counterAlpha] = 'L';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'm':

            username_array[counterAlpha] = 'M';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'n':

            username_array[counterAlpha] = 'N';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;


        case 'o':

            username_array[counterAlpha] = 'O';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'p':

            username_array[counterAlpha] = 'P';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'q':

            username_array[counterAlpha] = 'Q';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;


        case 'r':

            username_array[counterAlpha] = 'R';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 's':

            username_array[counterAlpha] = 'S';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 't':

            username_array[counterAlpha] = 'T';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;


        case 'u':

            username_array[counterAlpha] = 'U';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'v':

            username_array[counterAlpha] = 'V';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'w':

            username_array[counterAlpha] = 'W';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'x':

            username_array[counterAlpha] = 'X';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'y':

            username_array[counterAlpha] = 'Y';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'z':

            username_array[counterAlpha] = 'Z';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case '-':

            username_array[counterAlpha] = '_';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        // BACKSPACE == SUPPRIME LA LETTRE
        case 0x08: 

            if(counterAlpha>0)
            {            
                letter = "_";
                glTranslatef(-10,0,0);
                username_array[counterAlpha-1] = '\0';
                counterAlpha--;
            }

            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            break;

        case 13:

		    username = copyToString(username_array);

            //bug, impossible d'initialiser le héro si nouvelle partie alors que partie sauvegardée...
		    hero->health = 5;
            hero->attack = 3;
            hero->killed = 0;
            hero->red_killed = 0;
            hero->purple_killed = 0;
            hero->gold_killed = 0;
            hero->current_xp = 0;
            hero->pos.x = 10;
            hero->pos.y = 2;
            hero->weapon_type = 0;
            hero->obstacles_taken = 0;
            hero->bonus_active = 0;
            hero->ulti_killed = 0;
            hero->ulti_active = 0;

           // saveContext();

            startgame = !startgame;
            glutDisplayFunc(DisplayGame);
            glutPostRedisplay();
            break;

        case 27 :

            glutDisplayFunc(WelcomeDisplay);
            glutKeyboardFunc(keyboardFunc);
            glutPostRedisplay();
            break;
        };

}
else
{

    switch (Key) {

        // BACKSPACE == SUPPRIME LA LETTRE
        case 0x08: 

            if(counterAlpha>0)
            {            letter = "_";

                glTranslatef(-10,0,0);
                username_array[counterAlpha-1] = '\0';
                counterAlpha--;
            }

            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            break;

        case 13:

		    username = copyToString(username_array);

            //bug, impossible d'initialiser le héro si nouvelle partie alors que partie sauvegardée...
		    hero->health = 5;
            hero->attack = 3;
            hero->killed = 0;
            hero->red_killed = 0;
            hero->purple_killed = 0;
            hero->gold_killed = 0;
            hero->current_xp = 0;
            hero->pos.x = 10;
            hero->pos.y = 2;
            hero->weapon_type = 0;
            hero->obstacles_taken = 0;
            hero->bonus_active = 0;
            hero->ulti_killed = 0;
            hero->ulti_active = 0;

           // saveContext();

            startgame = !startgame;
            glutDisplayFunc(DisplayGame);
            glutPostRedisplay();
            break;

        case 27 :

            glutDisplayFunc(WelcomeDisplay);
            glutKeyboardFunc(keyboardFunc);
            glutPostRedisplay();
            break;
        };

}    

}
// ----------------------------------------------------------------- //

// actions clavier du menu des options

void keyboardFuncOpt(unsigned char Key, int x, int y) {

    switch (Key) {
       
        case 'd':
            difficulty += 1;
            if((difficulty) == 4)
            {
                difficulty = 0;
            } 
            glutDisplayFunc(DisplayOptions);
            glutPostRedisplay();
            break;

        case 'k':
            gameplay_keys = !gameplay_keys;
            //glutDisplayFunc(DisplayOptions);
            glutPostRedisplay();
            break;

        case 's':
            screen = !screen;
            //screen disposition = !screen disposition {code en attente}
            glutDisplayFunc(DisplayOptions);
            glutPostRedisplay();
            break;

        case 'z':

            cheatMode = !cheatMode;
            cheatMode_pressed = true;
            //screen disposition = !screen disposition {code en attente}
            glutDisplayFunc(DisplayOptions);
            glutPostRedisplay();

            break;
    
    case 'r':

        // si on fait un retour en arriere
        // on vérifie si on était en jeu ou hors jeu
        // relance ou non le jeu
        // réaffiche le menu de démarrage ou non
        if(startgame == true)
        {
            glutDisplayFunc(WelcomeDisplay);
            glutKeyboardFunc(keyboardFunc);
        }
        else if (startgame == false && startgame_option_bug == 0)
        {
            glutDisplayFunc(DisplayGame);
            glutKeyboardFunc(keyboardFunc);
        }

        else if (startgame == false && startgame_option_bug == 1)
        {
            glutDisplayFunc(WelcomeDisplay);
            glutKeyboardFunc(keyboardFunc);
        }


		glutPostRedisplay();
		break;

    	
    
    };
   
}



// ----------------------------------------------------------------- //

// clavier lié au menu pause en jeu

void keyboardFuncPausedInGame(unsigned char Key, int x, int y) {

    switch (Key) {
   
    case 'g':

		glutDisplayFunc(DisplayGameplay);
        glutKeyboardFunc(keyboardFuncOpt);
		glutPostRedisplay();
		break;

	case 'o':
    

		glutDisplayFunc(DisplayOptions);
		glutPostRedisplay();
		break;

	case 'd':
       
		glutDisplayFunc(DisplayCredits);
        glutKeyboardFunc(keyboardFuncOpt);
		glutPostRedisplay();
		break;

	case 32:
			SHOOT = true;
			break;	

    case 27:

			startgame = !startgame; 
			glutDisplayFunc(DisplayGame);
			glutPostRedisplay();
			break;

    case 'x':
            newGame = 0;
            saveContext();
            saveScore(hero);
			glutDisplayFunc(DisplayEnding);
			glutPostRedisplay();
			break;        
    	
    case 'c':
    		startgame = true;
			glutDisplayFunc(DisplayGame);
			glutPostRedisplay();
			break;  
    
    case 'm':
            //newGame = 0;
            saveScore(hero);
            newGame = 0;

            saveContext();
            // ouvrir un fichier, enregistrer tout ce qu'il faut, et aller rechercher dans ce fichier par après !!
            glutDisplayFunc(WelcomeDisplay);
            glutKeyboardFunc(keyboardFunc);
            glutPostRedisplay();
            break;
    };

  
   
}



                        /***************
                         * MENU SOURIS *
                         ***************/


// action à la souris || Clic gauche : indique la position d'où on se trouve || Clic droit(comment) : ferme la fenêtre (exit(0)). 

void mouse(int bouton,int etat,int x,int y) { // action à la souris || Clic gauche : indique la position d'où on se trouve || Clic droit : ferme la fenêtre (exit(0)). 
  if ( etat == GLUT_DOWN )
  {
    switch ( bouton ) {
        // donne la position du clic
      case GLUT_LEFT_BUTTON  : c = (c+1)%7; 
                               printf("%4d %4d\n",x,y); 
                               glutPostRedisplay();
                               break ;
      /*case GLUT_RIGHT_BUTTON : exit(0);
                               break; */
    }
  }
}