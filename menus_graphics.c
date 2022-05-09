
/*** LIBS ***/

#include "game_graphics.h"
#include "menus_graphics.h"
#include "timers_and_effects.h"
#include "hero.h"
#include "game.h"

//#include <GL/glut.h>

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
#define RED 1, 0, 0
#define BLUE 0, 0, 1
#define YELLOW 1, 1, 0
#define SAND 0.94, 0.87, 0.70



/*** VARIABLES ***/

int c = 0; // void mouse
int counterAlpha = 0; // compteur pour affichage du pseudo
// en fonction d'où on se trouvait avant de rentrer dans les options
float difficulty = 0; // niveau de difficulté

// pour l'affichage des options dynamiques
char* letter = " ";
char* difficulty_str;
char* screen_str;
char* gameplay_keys_str;
char* cheatmode_str;
char *username = " ";
char* usernameScore;
char username_array[20];
int username_lock = 0;
int newGame;
int newGame_lock = 0;

bool cheatMode = false;
bool gameplay_keys = false;
bool screen;
bool frame = true;
bool startgame;
int startgame_option_bug;
bool try;
bool SHOOT;
bool cheatMode_pressed;






/*** FUNCTIONS ***/


                /**********************
                 * KEYBOARD FUNCTIONS *
                 **********************/



// initialise les fonctions au clavier lorsque dans un menu

void keyboardFunc(unsigned char Key, int x, int y) {

    switch (Key) {
   
    case 'c':

    	newGame = checkNewGame(newGame);

        if(newGame == 0)
        {
            saveContext();
            //saveScore(hero);

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

        startgame_option_bug = 0;
        startgame = !startgame;
		glutDisplayFunc(UsernameDisplay);
		glutPostRedisplay();
		break;
    

	case 'x':

        if(try==false)
        {
            glutDisplayFunc(DisplayEnding);
            glutPostRedisplay();
        }

        if(try==true) wait();
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

        // BACKSPACE == SUPPRIME LA LETTRE
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
		    username = copyToString(username_array);
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

	case 'l':
       
        

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
            newGame = 0;
            saveContext();
            saveScore(hero);
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


                    /******************
                     * SHAPE DRAWINGS *
                     ******************/

// Dessine un cadre autour d'un texte choisi

void frameDraw(int red, int green, int blue, int x, int y, int length, int title)
{
    
    int i, j;
    int x_left = x-10;
    int x_right = x+200;
    int y_up = y + 15;
    int y_down = y - 15;  

    // si c'est un titre, alors le cadre s'étire à toute la fenêtre
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
// --------------------------------------------------------------- //

void drawHighScore()
{
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();

    glColor3f(EMERALD);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(300,500,0);
    drawSquare(EMERALD, 15);

    glTranslatef(150, 0, 0);
    drawSquare(EMERALD, 15);

    glTranslatef(150, 0, 0);
    drawSquare(EMERALD, 15);

    glTranslatef(-300,290,0);

    for(int i = 0; i < 60; i++)
    {
        drawSquare(SAND, 0.5);
        glTranslatef(10,0,0);
    }

    glTranslatef(-600,-300,0);


    for(int i = 0; i < 60; i++)
    {
        drawSquare(SAND, 0.5);
        glTranslatef(10,0,0);
    }

    glTranslatef(-600,230,0);

    for(int i = 0; i < 60; i++)
    {
        drawSquare(SAND, 0.5);
        glTranslatef(10,0,0);
    }

    glTranslatef(-300,-270,0);

    writeSomething(WHITE, 350,750, "-         H    I    G    H    S    C    O    R    E    S         -");
    
    //int top_1,top_2,top_3,top_4;
    int score_1, score_2, score_3, score_4;
    char username_1[20], username_2[20], username_3[20], username_4[20];
    int killed_1, killed_2, killed_3, killed_4;

    FILE *f = fopen("scores.txt", "r");
    
    fscanf(f, "%s %d %d %s %d %d %s %d %d %s %d %d",  username_1, &score_1, &killed_1, username_2, &score_2, &killed_2, username_3, &score_3, &killed_3, username_4, &killed_4, &score_4);
    writeSomethingHelvetica(WHITE, 330,630, "1");
    writeSomethingHelvetica(WHITE, 330,580, "2");
    writeSomethingHelvetica(WHITE, 330,550, "3");
    writeSomethingHelvetica(WHITE, 330,520, "4");
    writeSomethingHelvetica(WHITE, 320,680, "TOP");
    writeSomethingHelvetica(WHITE, 400,680, "USERNAME");
    writeSomethingHelvetica(WHITE, 575,680, "SCORE");
    writeSomethingHelvetica(WHITE, 700,680, "ENNEMI_KILLED");
    
	char score_un[10];
	sprintf(score_un, "%d", score_1);

	char killed_un[10];
	sprintf(killed_un, "%d", killed_1);

    if(score_1 == 0) writeSomethingHelvetica(WHITE, 575,630, "0");
    else writeSomethingHelvetica(WHITE, 575,630, score_un);

    if(killed_1 == 0) writeSomethingHelvetica(WHITE, 750,630, "-----");
    else writeSomethingHelvetica(WHITE, 750,630, score_un);

    writeSomethingHelvetica(WHITE, 385,630, username_1);

//            ~                       ~

	char score_deux[10];
	sprintf(score_deux, "%d", score_2);

	char killed_deux[10];
	sprintf(killed_deux, "%d", killed_2);

    if(score_2 == 0) writeSomethingHelvetica(WHITE, 575,580, "---");
    else writeSomethingHelvetica(WHITE, 575,580, score_deux);

    if(killed_2 == 0) writeSomethingHelvetica(WHITE, 750,580, "---");
    else writeSomethingHelvetica(WHITE, 750,580, killed_deux);

    writeSomethingHelvetica(WHITE, 385,580, username_2);

//            ~                       ~

	char score_trois[10];
	sprintf(score_trois, "%d", score_3);

	char killed_trois[10];
	sprintf(killed_trois, "%d", killed_3);

    if(score_3 == 0) writeSomethingHelvetica(WHITE, 575,550, "---");
    else writeSomethingHelvetica(WHITE, 575,550, score_trois);

    if(killed_3 == 0) writeSomethingHelvetica(WHITE, 750,550, "---");
    else writeSomethingHelvetica(WHITE, 750,550, killed_trois);

    writeSomethingHelvetica(WHITE, 385,550, username_3);

//            ~                       ~
	
    char score_quatre[10];
	sprintf(score_quatre, "%d", score_4);

	char killed_quatre[10];
	sprintf(killed_quatre, "%d", killed_4);

    if(score_4 == 0) writeSomethingHelvetica(WHITE, 575,520, "---");
    else writeSomethingHelvetica(WHITE, 575,520, score_quatre);

    if(killed_4 == 0) writeSomethingHelvetica(WHITE, 750,520, "---");
    else writeSomethingHelvetica(WHITE, 750,520, killed_quatre);

    writeSomethingHelvetica(WHITE, 385,520, username_4);
    
    fclose(f);
    // dessin du cadre couleur sable du top 1

    //compareTops(); // fonction tri qui replace tout au bon endroit
    



    // dessin du cadre autour du top 1
    glColor3f(SAND);
    for (int i = 0; i < 30; i++){ 
        glRasterPos3f(838, 615+i, 1); // DRAW LEFT LINE FRAME
        char msg1[]="|";
        for(int i = 0; i <strlen(msg1);i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg1[i]);

        glRasterPos3f(305, 615+i, 1); // DRAW RIGHT LINE FRAME
        char msg2[]="|";
        for(int i = 0; i <strlen(msg2);i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    }

    for(int j = 0; j <= 525; j++)
    {
        glRasterPos3f(310+j, 610, 1); // DRAW DOWN LINE FRAME
        char msg3[]="-";
        for(int i = 0; i <strlen(msg3);i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

        glRasterPos3f(310+j, 650, 1); // DRAW UP LINE FRAME
        char msg4[]="-";
        for(int i = 0; i <strlen(msg4);i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);
    }
}
                        /**********
                         * ÉCRANS *
                         **********/


// Crée l'écran de DÉMARRAGE

void WelcomeDisplay()
{	

	int x = (SCREEN_WIDTH/2)-80;

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(EMERALD);

    frameDraw(EMERALD, x+30, 850, 630, 1);

    // couleur
    glColor3f(WHITE);

    glRasterPos3f(x-150, 850, 1);
    char msg1[]="S U S T A I N A B L E   M O B I L I T Y  :  S U B S I S T A N C E";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glRasterPos3f(x+575, 850, 1);
    char msg50[]=" ~ ";
    for(int i = 0; i <strlen(msg50);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg50[i]);

    glRasterPos3f(x-250, 850, 1);
    char msg51[]=" ~ ";
    for(int i = 0; i <strlen(msg51);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg51[i]);

    glColor3f(WHITE);

    glRasterPos3f(50, 740, 0);
    char msg3[]="CONTINUER ('c')";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    glRasterPos3f(50, 700, 0);
    char msg4[]="Nouvelle partie ('n')";
    for(int i = 0; i <strlen(msg4);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);

    glRasterPos3f(50, 640, 0);
    char msg5[]="GAMEPLAY ('g')";
    for(int i = 0; i <strlen(msg5);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);

    glRasterPos3f(50, 600, 0);
    char msg6[]="OPTIONS ('o')";
    for(int i = 0; i <strlen(msg6);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);

    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 560, 210, 0);
    glColor3f(WHITE);

    glRasterPos3f(50, 560, 0);
    char msg7[]=">>>> SORTIE >>>>('x')";
    for(int i = 0; i <strlen(msg7);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

    glColor3f(WHITE);
    
    glRasterPos3f(x-20, 50, 0);
    char msg8[]="Press 'c' to enter the game";
    for(int i = 0; i <strlen(msg8);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg8[i]);


    glColor3f(RED);

    if(newGame == 1 && newGame_lock == 1)
    {
        glRasterPos3f(50, 500, 0);
        char msg3[]="AUCUNE PARTIE EN COURS";
        for(int i = 0; i <strlen(msg3);i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    }

    drawHighScore();
    glutSwapBuffers();

    
}

// ------------------------------------------------------------------ //

void GameOptionsDisplay()
{   
    //couleur
    glColor3f(EMERALD);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(200,400,0);
    drawSquare(EMERALD, 20);

    glTranslatef(0,400,0);

    // dessine le fond du menu option in game
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
    writeSomethingHelvetica(DARK_GREY, 243, 470, "('m')  TO MENU AND SAVE >>>>");
    
    writeSomethingHelvetica(DARK_GREY, 243, 440, "('x')   QUIT AND SAVE >>>>");


    glutKeyboardFunc(keyboardFuncPausedInGame);

    glutSwapBuffers(); 
}


// ------------------------------------------------------------------ //

// fenetre demandant le pseudo du joueur lors d'une nouvelle partie

void UsernameDisplay()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    newGame = 1;
    newGame_lock = 1;




    // couleurs
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

            glRasterPos3f(715, 750+i, 1); // DRAW RIGHT LINE FRAME
            char msg2[]="|";
            for(int i = 0; i <strlen(msg2);i++)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
            
        }

        for(j = 0; j <= 540; j++)
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


    frameDraw(EMERALD, 250, 850, 630, 1);
	//writeSomething(EMERALD, 310, 770, "H  A  R  U  H  I  K  O");    
	writeSomething(EMERALD, 210, 850, "  E N T R E Z    V O T R E     U S E R N A M E :"); 

    
    // affiche le username, qui est alimenté par la fonction Keyboard(Alphabet)
    writeSomethingArray(WHITE, 330, 770, username_array);
        
    glRasterPos3f(615, 730, 0);
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

    // couleurs
    glColor3f(EMERALD);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


    // transformation des variables numériques en format texte pour affichage
    // j'aurai pu réutiliser "a" à chaque fois, mais ce serait moins propre.
    
    int a = hero->current_xp;
	char str[10];
	sprintf(str, "%d", a);

    a = hero->killed;
    char strn[10];
    sprintf(strn, "%d", a);

    a = hero->obstacles_taken;
    char strng[10];
    sprintf(strng, "%d", a);

	writeSomething(EMERALD, 200, 930, "++++++++++++++++++++++++");    
    writeSomething(EMERALD, 200, 915, "+                                                    +");
	writeSomething(WHITE, 200, 900, "               YOU FAILED               ");
    writeSomething(EMERALD, 200, 900, "+                                                    +");
    writeSomething(EMERALD, 200, 885, "+                                                    +");
    writeSomething(EMERALD, 200, 870, "++++++++++++++++++++++++");
    writeSomething(WHITE, 200,800, "PLAYER NAME : ");
    writeSomethingArray(EMERALD, 450, 800, username);
	writeSomething(WHITE, 200, 750, "Your score :");
	writeSomething(EMERALD, 450, 750, str);
    writeSomething(WHITE, 200, 700, "Ennemy killed :");
	writeSomething(EMERALD, 450, 700, strn);
    writeSomething(WHITE, 100, 650, "   (beta)    Objet bonus utilises :            ");
    writeSomething(WHITE, 100, 600, "   (beta)    Obstacles pris :                ");
    writeSomething(WHITE, 100, 550, "   (beta)    Obstacle emprisonnes :            ");
    writeSomething(EMERALD, 450, 650, "0");
    writeSomething(EMERALD, 450, 600, strng);
    writeSomething(EMERALD, 450,  550, "0");

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

    // couleurs
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

// Crée et affiche l'écran des OPTIONS

void DisplayOptions()
{	


    int x = (SCREEN_WIDTH/2)-80;

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // initialise les variables affichées dans les options 
    options_keys(1);
    options_keys(2);
    options_keys(3);
    options_keys(4);

    // couleurs
    glColor3f(EMERALD);

    frameDraw(EMERALD, x+30, 850, 630, 1);

    glColor3f(WHITE);

    glRasterPos3f(x-30, 850, 1);
    char msg1[]="  O    P    T    I    O    N    S";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

    glColor3f(WHITE);


    // affiche la difficulté en cours
    frameDraw(WHITE, x, 750, 210, 0);
    glRasterPos3f(x, 750, 1);
    char* msg3 = difficulty_str;
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    // affiche les touches de jeu actives
    frameDraw(WHITE, x, 700, 210, 0);
    glRasterPos3f(x, 700, 1);
    char* msg4 = gameplay_keys_str;
    for(int i = 0; i <strlen(msg4);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);

    // affiche l'inclinaison de la map
    frameDraw(WHITE, x, 650, 210, 0);
    glRasterPos3f(x, 650, 1);
    char* msg5 = screen_str;
    for(int i = 0; i <strlen(msg5);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);

    // affiche si le cheat mode est actif ou non
    frameDraw(WHITE, x, 600, 210, 0);
    glRasterPos3f(x, 600, 1);
    char* msg6 = cheatmode_str;
    for(int i = 0; i <strlen(msg6);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);

    // affiche le bouton pour quitter
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

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(EMERALD);

    int x = (SCREEN_WIDTH/2)-80;

    frameDraw(EMERALD, x+30, 850, 630, 1);

    glColor3f(WHITE);

    glRasterPos3f(x+10, 850, 1);
    char msg1[]="G   A   M   E   P   L   A   Y";
    for(int i = 0; i <strlen(msg1);i++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);


    glColor3f(WHITE);

    glRasterPos3f(80, 750, 0);
    char msg3[]="Il suffit de deplacer le personnage avec les touches choisies. ";
    for(int i = 0; i <strlen(msg3);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

    glRasterPos3f(80, 730, 0);
    char msg4[]="Ensuite, vous pouvez tirer avec la barre d'espace. ";
    for(int i = 0; i <strlen(msg4);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);

    glRasterPos3f(80, 710, 0);
    char msg8[]="Le but du jeu est d'eliminer le maximum d'ennemis avant que votre vie ne tombe a 0.";
    for(int i = 0; i <strlen(msg8);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg8[i]);


    glRasterPos3f(80, 670, 0);
    char msg5[]="Le personnage possede : ";
    for(int i = 0; i <strlen(msg5);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);

    glRasterPos3f(80, 660, 0);
    char msg21[]="---------------------";
    for(int i = 0; i <strlen(msg21);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg21[i]);

    glRasterPos3f(80, 640, 0);
    char msg6[]="- Un nombre de points de vie (3 au debut),";
    for(int i = 0; i <strlen(msg6);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);

    glRasterPos3f(80, 620, 0);
    char msg7[]="- Un nombre de points d'attaques (1 au debut),";
    for(int i = 0; i <strlen(msg7);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

    glRasterPos3f(80, 600, 0);
    char msg20[]="- Un type d'arme (un fusil ou un canon à bulles).";
    for(int i = 0; i <strlen(msg20);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg20[i]);
    
    glRasterPos3f(80, 560, 0);
    char msg9[]="Les ennemis :";
    for(int i = 0; i <strlen(msg9);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg9[i]);    

    glRasterPos3f(80, 550, 0);
    char msg22[]="-------------";
    for(int i = 0; i <strlen(msg22);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg22[i]); 

    glRasterPos3f(80, 530, 0);
    char msg23[]="- Possède un nombre points de vie (3 au debut).";
    for(int i = 0; i <strlen(msg23);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg23[i]); 

    glRasterPos3f(72, 510, 0);
    char msg10[]=" - Un ennemi elimine rapporte 50 points";
    for(int i = 0; i <strlen(msg10);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg10[i]);

    glRasterPos3f(72, 490, 0);
    char msg11[]=" - Une collision avec un ennemi enleve 1 point de vie, et retire 100 points.";
    for(int i = 0; i <strlen(msg11);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg11[i]);
    
    glRasterPos3f(72, 470, 0);
    char msg12[]=" - Un ennemi arrivant en bas de la map enleve 1 point de vie, et retire 100 points.";
    for(int i = 0; i <strlen(msg12);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg12[i]);

    glRasterPos3f(72, 450, 0);
    char msg30[]=" - Un ennemi peut être ralenti avec le canon à bulles.";
    for(int i = 0; i <strlen(msg30);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg30[i]);

    glTranslatef(0,-20,0);

    glRasterPos3f(72, 430, 0);
    char msg24[]="Les bonus :";
    for(int i = 0; i <strlen(msg24);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg24[i]);

    glRasterPos3f(72, 420, 0);
    char msg25[]="---------";
    for(int i = 0; i <strlen(msg25);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg25[i]);    


    glRasterPos3f(72, 400, 0);
    char msg13[]=" - Un bonus attrape via une bulle ou une collision rajoute 1 point d'attaque et de vie au hero";
    for(int i = 0; i <strlen(msg13);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg13[i]);

    glTranslatef(-2,-25,0);

    glRasterPos3f(72, 400, 0);
    char msg55[]=" - Une collision avec un bonus donne une attaque ultime pour les 5 prochains kills.";
    for(int i = 0; i <strlen(msg55);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg55[i]);

    glRasterPos3f(72, 380, 0);
    char msg14[]=" - Un bonus detruit n'apporte aucun effet";
    for(int i = 0; i <strlen(msg14);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg14[i]);

    glRasterPos3f(72, 340, 0);
    char msg26[]="Les obstacles : ";
    for(int i = 0; i <strlen(msg26);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg26[i]);

    glRasterPos3f(72, 330, 0);
    char msg27[]="-------------";
    for(int i = 0; i <strlen(msg27);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg27[i]);

    glRasterPos3f(72, 310, 0);
    char msg15[]=" - Une collision avec un obstacle fait perdre 1 de vie et 100 de score";
    for(int i = 0; i <strlen(msg15);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg15[i]);

    glRasterPos3f(72, 290, 0);
    char msg16[]=" - Un obstacle peut etre arrete avec le canon a bulle, puis detruit avec le fusil";
    for(int i = 0; i <strlen(msg16);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg16[i]);

    // dessin d'un cadre pour le bouton "retour en arrière"
    glColor3f(EMERALD);
    frameDraw(EMERALD, 80, 100, 210, 0);
    glColor3f(WHITE);
    
    glRasterPos3f(80, 100, 1);
    char msg17[]="<<<<<<<<<<<<<<<<<<<<<< ('r')";
    for(int i = 0; i <strlen(msg17);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg17[i]);

    glRasterPos3f(80, 220, 1);
    char msg40[]="! Un cheat mode peut etre active via le clic droit ou via le menu des options !";
    for(int i = 0; i <strlen(msg40);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg40[i]);


    glRasterPos3f(80, 165, 1);
    char msg41[]="E   N   J   O   Y !";
    for(int i = 0; i <strlen(msg41);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg41[i]);

    // dessin des "objets de jeu"  
    glTranslatef(30,630,1);
    drawSquare(BLUE, 1);

    glTranslatef(2,-127,0);
    drawSquare(RED, 1);

    glTranslatef(10,-108,0);
    drawCircle(BLUE, 0, 0, 6);
    drawCircle(BLUE, 0, 0, 7);
    drawCircle(BLUE, 0, 0, 10);

    glTranslatef(-22,-100,0);
    drawSquare(YELLOW, 1);
    glTranslatef(14,0,0);
    drawSquare(YELLOW, 1);
    glTranslatef(14,0,0);
    drawSquare(YELLOW, 1);

    // systeme D pour remettre le curseur à la bonne place pour redessin des autres fenetres
    glTranslatef(-46, -250, -1);
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

    glRasterPos3f(350, 850, 1);
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

                        /*********************
                         * FONCTION D ECRANS *
                         *********************/


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

                if(difficulty == 0)
                { 
                    difficulty_str = "DIFFICULTE:  FACILE    ('d')";
                }

                else if (difficulty == 1)
                {
                    difficulty_str = "DIFFICULTE:  NORMAL    ('d')"; 
                }

                else if (difficulty == 2)
                {
                    difficulty_str = "DIFFICULTE:  DIFFICILE ('d')"; 
                }

                else if (difficulty == 3)
                {
                    difficulty_str = "DIFFICULTE: IMPOSSIBRU ('d')"; 
                }

                break;

            case 3:

                if(cheatMode == false)
                { 
                    cheatmode_str = "CHEAT MODE:  DISABLED  ('z')";
                }

                else
                {
                    cheatmode_str = "CHEAT MODE:   ENABLED  ('z')"; 
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

// -------------------------------------------------------------------- //


                        /*******************
                         * MENU CLIC DROIT *
                         *******************/

// Crée le menu clic droit

void init_rightClick_Menu(){
    glutCreateMenu (myMenu);

	glutAddMenuEntry ("|             MENU               |", 0);
	glutAddMenuEntry ("''''''''''''''''''''''''''''''''''''''''''''''''''",0);
	glutAddMenuEntry ("| Pause", 1);
	glutAddMenuEntry ("| Cheatmode : disabled", 2);
	glutAddMenuEntry ("| Quit", 3);

	glutAttachMenu (GLUT_RIGHT_BUTTON);
}





// ------------------------------------------------------------------ //

// Initialise le menu clic droit

void myMenu(int id){
	switch(id){

		
		case 1:

			printf("Pause\n");	
            startgame = !startgame;
			break;
		case 2:

			printf("_!_Cheat_mode_!_");
            cheatMode = !cheatMode;	
            cheatMode_pressed = true;
            break;
		case 3:
        
            glutDisplayFunc(DisplayEnding);
	}
}


