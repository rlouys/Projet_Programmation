
/*** LIBS ***/

#include "game_graphics.h"
#include "menus_graphics.h"
#include "timers_and_effects.h"
#include "hero.h"
#include "game.h"

#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>




/*** CONSTANTES ***/

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 1000

#define EMERALD 0.03, 0.49, 0.13
#define WHITE 1, 1, 1
#define BLACK 0, 0, 0
#define GREY 0.5, 0.5, 0.5
#define DARK_GREY 0.1, 0.1, 0.1


/*** VARIABLES ***/

float df = 5;
float *deplacement_fenetre = &df;
bool frame = true;
bool startgame;
bool try;
int counterAlpha = 0;
char* letter = " ";
// options_keys var
int difficulty = 1;
char* difficulty_str;
bool screen;
char* screen_str;
bool gameplay_keys;
char* gameplay_keys_str;
bool cheatMode;
char* cheatmode_str;

char username[20];
char* usernameScore;

bool optionSwitch = false;


int optionSwitchKey;

/*** FUNCTIONS ***/

// initialise les fonctions au clavier lorsque dans un menu

void keyboardFunc(unsigned char Key, int x, int y) {

    switch (Key) {
   
    case 'c':
        startgame = !startgame;
		glutDisplayFunc(DisplayGame);
		glutPostRedisplay();
		break;

	case 'n':

		glutDisplayFunc(UsernameDisplay);
		glutPostRedisplay();
		break;

	case 'x':
        if(try==false){
		glutDisplayFunc(DisplayEnding);
		glutPostRedisplay();
        }

       // wait();
        //exit(0);

        if(try==true) wait();
        
    	break;
    
    case 'r':
            startgame = false;
            hero->health = 42;
            hero->killed = 0;

            
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

void Alphabet(unsigned char Key, int x, int y)
{

    switch (Key) {
    
        case 'a':
            username[counterAlpha] = 'A';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;



        case 'b':
            username[counterAlpha] = 'B';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'c':
            username[counterAlpha] = 'C';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'd':
            username[counterAlpha] = 'D';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'e':
            username[counterAlpha] = 'E';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'f':
            username[counterAlpha] = 'F';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'g':
            username[counterAlpha] = 'G';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'h':
            username[counterAlpha] = 'H';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'i':
            username[counterAlpha] = 'I';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'j':
            username[counterAlpha] = 'J';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'k':
            username[counterAlpha] = 'K';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'l':
            username[counterAlpha] = 'L';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'm':
            username[counterAlpha] = 'M';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'n':
            username[counterAlpha] = 'N';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;


        case 'o':
            username[counterAlpha] = 'O';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'p':
            username[counterAlpha] = 'P';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'q':
            username[counterAlpha] = 'Q';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;


        case 'r':
            username[counterAlpha] = 'R';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 's':
            username[counterAlpha] = 'S';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 't':
            username[counterAlpha] = 'T';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;


        case 'u':
            username[counterAlpha] = 'U';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'v':
            username[counterAlpha] = 'V';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'w':
            username[counterAlpha] = 'W';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'x':
            username[counterAlpha] = 'X';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'y':
            username[counterAlpha] = 'Y';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 'z':
            username[counterAlpha] = 'Z';
            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            counterAlpha++;
            break;

        case 0x08: 

            if(counterAlpha>0)
            {            letter = "_";

            glTranslatef(-10,0,0);
            username[counterAlpha-1] = '\0';
            counterAlpha--;
            }

            glutDisplayFunc(UsernameDisplay);
            glutPostRedisplay();
            break;
        case 13:

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
// ----------------------------------------------------------------- //

void keyboardFuncOpt(unsigned char Key, int x, int y) {

    switch (Key) {
   

    if(!optionSwitch)
    {
        case 'd':
            difficulty += 1;
            if((difficulty) == 5)
            {
                difficulty = 1;
            } 
            glutDisplayFunc(DisplayOptions);
            glutPostRedisplay();
            break;

        case 'k':
            gameplay_keys = !gameplay_keys;
            glutDisplayFunc(DisplayOptions);
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
            //screen disposition = !screen disposition {code en attente}
            glutDisplayFunc(DisplayOptions);
            glutPostRedisplay();

            break;
    }
    case 'r':

        if(optionSwitch == false)
        {
            glutDisplayFunc(WelcomeDisplay);
            glutKeyboardFunc(keyboardFunc);
        }
        else
        {
            glutDisplayFunc(DisplayGame);

            glutKeyboardFunc(keyboardFunc);
        }

        optionSwitchKey = 1;

		glutPostRedisplay();
		break;

    	
    
    };
   
}

// ----------------------------------------------------------------- //

// clavier lié au menu pause en jeu

void keyboardFuncPausedInGame(unsigned char Key, int x, int y) {

    switch (Key) {
   
    case 'g':
        optionSwitch = !optionSwitch;
        
        if(optionSwitchKey == 1){
            optionSwitch = !optionSwitch;
            optionSwitchKey = 0;
        }


		glutDisplayFunc(DisplayGameplay);
        glutKeyboardFunc(keyboardFuncOpt);
		glutPostRedisplay();
		break;

	case 'o':
        
        optionSwitch = !optionSwitch;

        if(optionSwitchKey == 1){
            optionSwitch = !optionSwitch;
            optionSwitchKey = 0;
        }

		glutDisplayFunc(DisplayOptions);
		glutPostRedisplay();
		break;

	case 'd':
       
		optionSwitch = !optionSwitch;
        
        if(optionSwitchKey == 1){
            optionSwitch = !optionSwitch;
            optionSwitchKey = 0;
        }


		glutDisplayFunc(DisplayCredits);
        glutKeyboardFunc(keyboardFuncOpt);
		glutPostRedisplay();
		break;

    case 'r':

        
        if(optionSwitch == true)
        {
            glutDisplayFunc(WelcomeDisplay);
            glutKeyboardFunc(keyboardFunc);
        }
        else
        {
            glutDisplayFunc(GameOptionsDisplay);

            glutDisplayFunc(DisplayGame);

            glutKeyboardFunc(keyboardFunc);
        }

        

		glutPostRedisplay();

    	break;
    
    case 27:
			startgame = !startgame;
			glutDisplayFunc(DisplayGame);
			glutPostRedisplay();
			break;

    case 'x':
			glutDisplayFunc(DisplayEnding);
			glutPostRedisplay();
			break;        
    	
    case 'c':
    		startgame = !startgame;
			glutDisplayFunc(DisplayGame);
			glutPostRedisplay();
			break;  
    };
   
}


// ----------------------------------------------------------------- //

// Dessine un cadre autour d'un texte

void frameDraw(int red, int green, int blue, int x, int y, int length, int title)
{
    
    int i, j;
    int x_left = x-10;
    int x_right = x+200;
    int y_up = y + 15;
    int y_down = y - 15;  

    if (title == 0){

        for (i = 0; i < 30; i++){ 
            glRasterPos3f(x_left, y_down+i, 1); // DRAW LEFT LINE FRAME
            char msg1[]="|";
            for(int i = 0; i <strlen(msg1);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg1[i]);

            glRasterPos3f(x_right, y_down+i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
            
        }

        for(j = 0; j <= length; j++)
        {
            glRasterPos3f(x_left+j, y_down, 1); // DRAW DOWN LINE FRAME
            char msg3[]="-";
            for(int i = 0; i <strlen(msg3);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

            glRasterPos3f(x_left+j, y_up, 1); // DRAW UP LINE FRAME
            char msg4[]="-";
            for(int i = 0; i <strlen(msg4);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);
        }
    }

        if(title == 1)
        {

            y_down -= 20;
            y_up += 25;

            for(j = 0; j <= length; j++){
                glRasterPos3f((x_left+j)-length, y_down, 1); // DRAW RIGHT LINE FRAME
                char msg4[]="-";
                for(int i = 0; i <strlen(msg4);i++){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);}
            }

            for(j = 0; j <= length; j++){
                glRasterPos3f((x_left+j)-length, y_up, 1); // DRAW RIGHT LINE FRAME
                char msg5[]="-";
                for(int i = 0; i <strlen(msg5);i++){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);}  
            }    
        
            for(j = 0; j <= length+210; j++)
            {
                glRasterPos3f(x_left+j, y_down, 1); // DRAW RIGHT LINE FRAME
                char msg3[]="-";
                for(int i = 0; i <strlen(msg3);i++)
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

                glRasterPos3f(x_left+j, y_up, 1); // DRAW LEFT LINE FRAME
                char msg4[]="-";
                for(int i = 0; i <strlen(msg4);i++)
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);                     
            }
        }
}

// -------------------------------------------------------------- //

// Crée l'écran de DÉMARRAGE

void WelcomeDisplay()
{	

	int x = (SCREEN_WIDTH/2)-80;
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(EMERALD);

    frameDraw(EMERALD, x+30, 850, 630, 1);

    glColor3f(WHITE);

    glRasterPos3f(x-130, 850, 1);
    char msg1[]="SUSTAINABLE MOBILITY : SUBSISTANCE";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);


    glColor3f(WHITE);

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

    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 580, 210, 0);
    glColor3f(WHITE);

    glRasterPos3f(50, 580, 0);
    char msg7[]=">>>> SORTIE >>>>('x')";
    for(int i = 0; i <strlen(msg7);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

    glColor3f(WHITE);
    
    glRasterPos3f(x-20, 50, 0);
    char msg8[]="Press 'c' to enter the game";
    for(int i = 0; i <strlen(msg8);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg8[i]);

    glutSwapBuffers();

    
}

// ------------------------------------------------------------------ //

void GameOptionsDisplay()
{
    glColor3f(EMERALD);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(200,400,0);
    drawSquare(EMERALD, 20);

    glTranslatef(0,400,0);

    for(int i = 0; i < 29; i++)
    {
    drawSquare(DARK_GREY, 6);
    glTranslatef(10,0,0);
    }


    frameDraw(EMERALD, 210, 850, 630, 1);
	writeSomething(EMERALD, 243, 850, "P A U S E D  ~  O P T I O N S");

    writeSomethingHelvetica(DARK_GREY, 243, 760, "('c')   CONTINUE >>>>");
    writeSomethingHelvetica(DARK_GREY, 243, 700, "('g')   GAMEPLAY >>>>");
    writeSomethingHelvetica(DARK_GREY, 243, 640, "('o')   OPTIONS >>>>");
    writeSomethingHelvetica(DARK_GREY, 243, 580, "('d')   CREDITS >>>>");
    writeSomethingHelvetica(DARK_GREY, 243, 440, "('x')   QUIT AND SAVE >>>>");


    glutKeyboardFunc(keyboardFuncPausedInGame);

    glutSwapBuffers(); 
}


// ------------------------------------------------------------------ //

void UsernameDisplay()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(EMERALD);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    int i;
    int j;

    for (i = 0; i < 48; i++){ 
            glRasterPos3f(175, 750+i, 1); // DRAW LEFT LINE FRAME
            char msg1[]="|";
            for(int i = 0; i <strlen(msg1);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg1[i]);

            glRasterPos3f(650, 750+i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
            
        }

        for(j = 0; j <= 475; j++)
        {
            glRasterPos3f(175+j, 800, 1); // DRAW DOWN LINE FRAME
            char msg3[]="-";
            for(int i = 0; i <strlen(msg3);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

            glRasterPos3f(175+j, 750, 1); // DRAW UP LINE FRAME
            char msg4[]="-";
            for(int i = 0; i <strlen(msg4);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);
        }


    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 580, 210, 0);
    glColor3f(WHITE);

    glRasterPos3f(50, 580, 0);
    char msg0[]="<<<<<<<<<<<<<<<<<<<<<< ('ESC')";
    for(int i = 0; i <strlen(msg0);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg0[i]);


    frameDraw(EMERALD, 210, 850, 630, 1);
	//writeSomething(EMERALD, 310, 770, "H  A  R  U  H  I  K  O");    
	writeSomething(EMERALD, 180, 850, "E N T R E Z    V O T R E     U S E R N A M E :"); 


    writeSomethingArray(WHITE, 330, 770, username);
        
    glRasterPos3f(550, 730, 0);
    char msg1[]= "PRESS ENTER";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg1[i]);
    
    
    glutKeyboardFunc(Alphabet);






    glutSwapBuffers();

}

// ------------------------------------------------------------------ //

// Crée le menu de FIN en cas d'ÉCHEC (you failed...)

void EndGameDisplay()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(EMERALD);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    int a = hero->current_xp;
	char str[10];

	sprintf(str, "%d", a);

    int b = hero->killed;
    
    char strn[10];
    sprintf(strn, "%d", b);

	writeSomething(EMERALD, 200, 930, "++++++++++++++++++++++++");    
    writeSomething(EMERALD, 200, 915, "+                                                    +");
	writeSomething(WHITE, 200, 900, "               YOU FAILED               ");
    writeSomething(EMERALD, 200, 900, "+                                                    +");
    writeSomething(EMERALD, 200, 885, "+                                                    +");
    writeSomething(EMERALD, 200, 870, "++++++++++++++++++++++++");
	writeSomething(WHITE, 200, 800, "Your score :");
	writeSomething(EMERALD, 450, 800, str);
    writeSomething(WHITE, 200, 750, "Ennemy killed :");
	writeSomething(EMERALD, 450, 750, strn);
    writeSomething(WHITE, 100, 700, "   (beta)    Objet bonus utilises :            ");
    writeSomething(WHITE, 100, 650, "   (beta)    Obstacles degats :                ");
    writeSomething(WHITE, 100, 600, "   (beta)    Obstacle emprisonnes :            ");
    writeSomething(EMERALD, 450, 700, "0");
    writeSomething(EMERALD, 450, 650, "0");
    writeSomething(EMERALD, 450,  600, "0");

    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 430, 210, 0);
    glColor3f(WHITE);
    
    glRasterPos3f(50, 430, 1);
    char msg[]="<<<<<<<<<<<<<<<<<<<<<< ('r')";
    for(int i = 0; i <strlen(msg);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg[i]);

    glutKeyboardFunc(keyboardFunc);

    glutSwapBuffers();
}

// ------------------------------------------------------------------ //

// Crée le menu de FIN en cas de VICTOIRE (you win!)

void WinDisplay()
{	
   // int tick;
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(EMERALD);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    int a = hero->current_xp;
	char str[10];

	sprintf(str, "%d", a);

    int b = hero->killed;
    
    char strn[10];
    sprintf(strn, "%d", b);

	writeSomething(EMERALD, 200, 930, "++++++++++++++++++++++++");    
    writeSomething(EMERALD, 200, 915, "+                                                    +");
	writeSomething(WHITE, 200, 900, "                   YOU WIN              ");
    writeSomething(EMERALD, 200, 900, "+                                                    +");
    writeSomething(EMERALD, 200, 885, "+                                                    +");
    writeSomething(EMERALD, 200, 870, "++++++++++++++++++++++++");
	writeSomething(WHITE, 200, 800, "Your score :");
	writeSomething(EMERALD, 450, 800, str);
    writeSomething(WHITE, 200, 750, "Ennemy killed :");
	writeSomething(EMERALD, 450, 750, strn);
    writeSomething(WHITE, 100, 700, "   (beta)    Objet bonus utilises :            ");
    writeSomething(WHITE, 100, 650, "   (beta)    Obstacles degats :                ");
    writeSomething(WHITE, 100, 600, "   (beta)    Obstacle emprisonnes :            ");
    writeSomething(EMERALD, 450, 700, "0");
    writeSomething(EMERALD, 450, 650, "0");
    writeSomething(EMERALD, 450,  600, "0");

    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 430, 210, 0);
    glColor3f(WHITE);
    
    glRasterPos3f(50, 430, 1);
    char msg[]="<<<<<<<<<<<<<<<<<<<<<< ('r')";
    for(int i = 0; i <strlen(msg);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg[i]);

    glutKeyboardFunc(keyboardFunc);


    glutSwapBuffers();
}
// ------------------------------------------------------------------ //

// initialise les options dynamiques à l'écran avant la première touche pressée
void options_keys(int option_number)
{   
    
        switch (option_number) {

            case 1:
        
                if(screen == true)
                { 
                    screen_str = "ECRAN     :  V R T C   ('s')";
                }
                else
                {
                    screen_str = "ECRAN     :  H R Z T   ('s')"; 
                }
                
                break;

            case 2:
                if(difficulty == 1)
                { 
                    difficulty_str = "DIFFICULTE:  FACILE    ('d')";
                    //level++;
                }
                else if (difficulty == 2)
                {
                    difficulty_str = "DIFFICULTE:  NORMAL    ('d')"; 
                    //level++;
                }
                else if (difficulty == 3)
                {
                    difficulty_str = "DIFFICULTE:  DIFFICILE ('d')"; 
                }
                else if (difficulty == 4)
                {
                    difficulty_str = "DIFFICULTE:  EXTREME   ('d')"; 
                }

                break;

            case 3:

                if(cheatMode == true)
                { 
                    cheatmode_str = "CHEAT MODE:  ENABLED   ('z')";
                }
                else
                {
                    cheatmode_str = "CHEAT MODE:  DISABLED  ('z')"; 
                }
                break;

            case 4:
                
                if(gameplay_keys == true)
                { 
                    gameplay_keys_str = "TOUCHES   :  Z Q S D   ('k')";
                }
                else
                {
                    gameplay_keys_str = "TOUCHES   :  A R R O W ('k')"; 
                }

                break;

                
            
            };
   
}







        


    


// ------------------------------------------------------------------ //

// Crée et affiche l'écran des OPTIONS

void DisplayOptions()
{	

    int x = (SCREEN_WIDTH/2)-80;
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(EMERALD);

    frameDraw(EMERALD, x+30, 850, 630, 1);

    glColor3f(WHITE);

    glRasterPos3f(x-30, 850, 1);
    char msg1[]="O    P    T    I    O    N    S";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    //options_keys(0);

// ~~~~~~~~~~~~~~~~~~~~~~~~~ // 

    glColor3f(WHITE);
    frameDraw(WHITE, x, 750, 210, 0);

    glRasterPos3f(x, 750, 1);

    options_keys(2);

    char* msg3 = difficulty_str;
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);


    frameDraw(WHITE, x, 700, 210, 0);

    options_keys(4);
    glRasterPos3f(x, 700, 1);
    char* msg4 = gameplay_keys_str;
    for(int i = 0; i <strlen(msg4);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);


    frameDraw(WHITE, x, 650, 210, 0);


    options_keys(1);
    glRasterPos3f(x, 650, 1);
    char* msg5 = screen_str;
    for(int i = 0; i <strlen(msg5);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);
    frameDraw(WHITE, x, 600, 210, 0);



    options_keys(3);
    glRasterPos3f(x, 600, 1);
    char* msg6 = cheatmode_str;
    for(int i = 0; i <strlen(msg6);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);

    glColor3f(EMERALD);
    frameDraw(EMERALD, x, 500, 210, 0);
    glColor3f(WHITE);
    

    glRasterPos3f(x, 500, 1);
    char msg7[]="<<<<<<<<<<<<<<<<<<<<<< ('r')";
    for(int i = 0; i <strlen(msg7);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

    glutKeyboardFunc(keyboardFuncOpt);


    glutSwapBuffers();
}

// ------------------------------------------------------------------ //

// Crée et affiche l'écran lié au GAMEPLAY

void DisplayGameplay()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawWall(mX, mY);
    glColor3f(EMERALD);

    int x = (SCREEN_WIDTH/2)-80;

    frameDraw(EMERALD, x+30, 850, 630, 1);

    glColor3f(WHITE);

    glRasterPos3f(x-30, 850, 1);
    char msg1[]="G   A   M   E   P   L   A   Y";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);


    glColor3f(WHITE);

    glRasterPos3f(50, 750, 0);
    char msg3[]="Il suffit de deplacer le personnage avec les touches choisies. ";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    glRasterPos3f(50, 730, 0);
    char msg4[]="Ensuite, vous pouvez tirer avec la barre d'espace. ";
    for(int i = 0; i <strlen(msg4);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);

    glRasterPos3f(50, 690, 0);
    char msg5[]="Le personnage possede : ";
    for(int i = 0; i <strlen(msg5);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);

    glRasterPos3f(50, 670, 0);
    char msg6[]="- Un nombre de points de vie (3 au debut),";
    for(int i = 0; i <strlen(msg6);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);

    glRasterPos3f(50, 650, 0);
    char msg7[]="- Un nombre de points d'attaques (3 au debut),";
    for(int i = 0; i <strlen(msg7);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

    glRasterPos3f(50, 610, 0);
    char msg8[]="Le but du jeu est d'eliminer le maximum d'ennemis avant que votre vie ne tombe a 0.";
    for(int i = 0; i <strlen(msg8);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg8[i]);

    glRasterPos3f(50, 570, 0);
    char msg9[]="Chaque ennemi possède trois points de vie (au debut).";
    for(int i = 0; i <strlen(msg9);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg9[i]);    

    glRasterPos3f(50, 550, 0);
    char msg10[]="Un ennemi elimine rapporte 50 points";
    for(int i = 0; i <strlen(msg10);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg10[i]);

    glRasterPos3f(50, 530, 0);
    char msg11[]="Une collision avec un ennemi enleve 1 point de vie, et retire 50 points.";
    for(int i = 0; i <strlen(msg11);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg11[i]);
    
    glRasterPos3f(50, 510, 0);
    char msg12[]="Un ennemi arrivant en bas de la map enleve 1 point de vie, et retire 50 points.";
    for(int i = 0; i <strlen(msg12);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg12[i]);

    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 430, 210, 0);
    glColor3f(WHITE);
    
    glRasterPos3f(50, 430, 1);
    char msg13[]="<<<<<<<<<<<<<<<<<<<<<< ('r')";
    for(int i = 0; i <strlen(msg13);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg13[i]);

    glutSwapBuffers();
}

// ------------------------------------------------------------------ //

// Crée et affiche l'écran de fin de programme

void DisplayEnding()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(EMERALD);

    frameDraw(EMERALD, (SCREEN_WIDTH/2)-50, 850, 630, 1);

    glColor3f(WHITE);

    glRasterPos3f(300, 850, 1);
    char msg1[]="A   B  I  E  N  T  O  T ";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glColor3f(WHITE);

    frameDraw(WHITE, 50, 750, 210, 0);

    glRasterPos3f(50, 750, 0);
    char msg2[]="CREDITS";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    

    glColor3f(EMERALD);

    glRasterPos3f(50, 720, 0);
        char msg3[]="LOUYS RAPHAEL";
        for(int i = 0; i <strlen(msg3);i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    glutSwapBuffers();
    wait(); // used to wait until a certain time, before exitting
    exit(0);
}

// ------------------------------------------------------------------ //

// Crée et affiche l'écran de crédits

void DisplayCredits()
{	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(EMERALD);

    frameDraw(EMERALD, (SCREEN_WIDTH/2)-50, 850, 630, 1);

    glColor3f(WHITE);

    glRasterPos3f(300, 850, 1);
    char msg1[]="   C  R  E  D  I  T  S  ";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glColor3f(WHITE);

    frameDraw(WHITE, 50, 750, 210, 0);

    glRasterPos3f(50, 750, 0);
    char msg2[]="CREDITS";
    for(int i = 0; i <strlen(msg2);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    

    glColor3f(EMERALD);

    glRasterPos3f(50, 720, 0);
        char msg3[]="LOUYS RAPHAEL";
        for(int i = 0; i <strlen(msg3);i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    glutSwapBuffers();
    
}

// ---------------------------------------------------------------- //

// Crée le menu clic droit

void init_rightClick_Menu(){
    glutCreateMenu (myMenu);
	glutAddMenuEntry ("|             MENU               |", 0);
	glutAddMenuEntry ("''''''''''''''''''''''''''''''''''''''''''''''''''",0);

	glutAddMenuEntry ("| Options", 2);
	glutAddMenuEntry ("| Gameplay", 3);
	glutAddMenuEntry ("| Pause", 4);
	glutAddMenuEntry ("| Cheatmode : disabled", 5);
	glutAddMenuEntry ("| Quit", 6);

	glutAttachMenu (GLUT_RIGHT_BUTTON);
}





// ------------------------------------------------------------------ //

// Initialise le menu clic droit

void myMenu(int id){
	switch(id){

		case 2:
        	printf("Options\n");	

           // glutDisplayFunc(DisplayOptions);
			break;
		case 3:
        	printf("Gameplay\n");	
            //glutDisplayFunc(DisplayGameplay);
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


