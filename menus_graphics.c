
/*** LIBS ***/

#include "game_graphics.h"
#include "menus_graphics.h"
#include "timers_and_effects.h"
#include "hero.h"
#include "game.h"
#include "keyboard.h"

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
#define BRICK 0.698039216, 0.133333333, 0.133333333


/*** VARIABLES ***/
int c;
int counterAlpha; // compteur pour affichage du pseudo
// en fonction d'où on se trouvait avant de rentrer dans les options
int difficulty = 0; // niveau de difficulté
int username_lock = 0;
int newGame;
int newGame_lock = 0;
int NewGame_statslock = 0; // variable pour corriger un bug 
int startgame_option_bug;
int level; // niveau en cours

// pour l'affichage des options dynamiques
char* difficulty_str;
char* screen_str;
char* gameplay_keys_str;
char* cheatmode_str;
char *username;
char* usernameScore;
char username_array[20];

char* letter;

bool cheatMode = false;
bool gameplay_keys = false;
bool screen;
bool frame = true;
bool startgame;
bool try;
bool SHOOT;
bool cheatMode_pressed;






/*** FUNCTIONS ***/


                


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

void drawHighScore(top Top)
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
    

    FILE *f = fopen("scores.txt", "r");
    
    fscanf(f, "%s %d %d %s %d %d %s %d %d %s %d %d %s %d %d", Top->username[0], &Top->score[0], &Top->killed[0], Top->username[1], &Top->score[1], &Top->killed[1], Top->username[2], &Top->score[2], &Top->killed[2], Top->username[3], &Top->score[3], &Top->killed[3], Top->username[4], &Top->score[4], &Top->killed[4]);
    writeSomethingHelvetica(WHITE, 330,630, "1");
    writeSomethingHelvetica(WHITE, 330,580, "2");
    writeSomethingHelvetica(WHITE, 330,550, "3");
    writeSomethingHelvetica(WHITE, 330,520, "4");
    writeSomethingHelvetica(WHITE, 320,680, "TOP");
    writeSomethingHelvetica(WHITE, 400,680, "USERNAME");
    writeSomethingHelvetica(WHITE, 575,680, "SCORE");
    writeSomethingHelvetica(WHITE, 700,680, "ENNEMI_KILLED");
    

	char score_un[10];
	sprintf(score_un, "%d", Top->score[4]);
	char killed_un[10];
	sprintf(killed_un, "%d", Top->killed[4]);

    if(Top->score[4] == 0) writeSomethingHelvetica(WHITE, 575,630, "-----");
    else writeSomethingHelvetica(WHITE, 575,630, score_un);

    if(Top->killed[4] == 0) writeSomethingHelvetica(WHITE, 750,630, "-----");
    else writeSomethingHelvetica(WHITE, 750,630, killed_un);

    writeSomethingArrayHelvetica(WHITE, 385,630, Top->username[4]);

//            ~                       ~

	char score_deux[10];
	sprintf(score_deux, "%d", Top->score[3]);

	char killed_deux[10];
	sprintf(killed_deux, "%d", Top->killed[3]);

    if(Top->score[3] == 0) writeSomethingHelvetica(WHITE, 575,580, "---");
    else writeSomethingHelvetica(WHITE, 575,580, score_deux);

    if(Top->killed[3] == 0) writeSomethingHelvetica(WHITE, 750,580, "---");
    else writeSomethingHelvetica(WHITE, 750,580, killed_deux);

    writeSomethingArrayHelvetica(WHITE, 385,580, Top->username[3]);

//            ~                       ~

	char score_trois[10];
	sprintf(score_trois, "%d", Top->score[2]);

	char killed_trois[10];
	sprintf(killed_trois, "%d", Top->killed[2]);

    if(Top->score[2] == 0) writeSomethingHelvetica(WHITE, 575,550, "---");
    else writeSomethingHelvetica(WHITE, 575,550, score_trois);

    if(Top->killed[2] == 0) writeSomethingHelvetica(WHITE, 750,550, "---");
    else writeSomethingHelvetica(WHITE, 750,550, killed_trois);

    writeSomethingArrayHelvetica(WHITE, 385,550, Top->username[2]);

//            ~                       ~
	
    char score_quatre[10];
	sprintf(score_quatre, "%d", Top->score[1]);

	char killed_quatre[10];
	sprintf(killed_quatre, "%d", Top->killed[1]);

    if(Top->score[1] == 0) writeSomethingHelvetica(WHITE, 575,520, "---");
    else writeSomethingHelvetica(WHITE, 575,520, score_quatre);

    if(Top->killed[1] == 0) writeSomethingHelvetica(WHITE, 750,520, "---");
    else writeSomethingHelvetica(WHITE, 750,520, killed_quatre);

    writeSomethingArrayHelvetica(WHITE, 385,520, Top->username[1]);
    
    fclose(f);


    // dessin du cadre couleur sable du top 1
    glColor3f(SAND);

    writeSomething9by15(SAND,  838, 615, "|", 30, 0);
    writeSomething9by15(SAND,  305, 615, "|", 30, 0);
    writeSomething9by15(SAND,  310, 610, "-", 525, 1);
    writeSomething9by15(SAND,  310, 650, "-", 525, 1);

   
}
                        /**********
                         * ÉCRANS *
                         **********/


// Crée l'écran de DÉMARRAGE

void WelcomeDisplay()
{	
    top Top = malloc(sizeof(struct Score));


	int x = (SCREEN_WIDTH/2)-80;

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(EMERALD);

    frameDraw(EMERALD, x+30, 850, 630, 1);

    // textes
    writeSomethingArray(WHITE, (x-150), 850,"S U S T A I N A B L E   M O B I L I T Y  :  S U B S I S T A N C E"); 
    writeSomethingArray(WHITE, (x+575), 850, " ~ ");
    writeSomethingArray(WHITE, (x-250), 850, " ~ ");
    writeSomething9by15(WHITE, 50, 740, "CONTINUER ('c')", 0, 2);
    writeSomething9by15(WHITE, 50, 700, "Nouvelle partie ('n')", 0, 2);
    writeSomething9by15(WHITE, 50, 620, "GAMEPLAY ('g')", 0, 2);
    writeSomething9by15(WHITE, 50, 580, "OPTIONS ('o')", 0, 2);

    // cadre de la "sortie"
    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 500, 210, 0);
    glColor3f(WHITE);

    writeSomething9by15(WHITE, 50, 500, ">>>> SORTIE >>>>('x')", 0, 2);
    writeSomething9by15(WHITE, (x-20), 50, "Press 'c' to enter the game", 0, 2);
   
    if(newGame == 1 && newGame_lock == 1)
    {
        writeSomething9by15(RED, 50, 450, "AUCUNE PARTIE EN COURS", 0, 2);
    }


    drawHighScore(Top);

    glutKeyboardFunc(keyboardFunc);

    glutSwapBuffers();

    
}

// ------------------------------------------------------------------ //

void GameOptionsDisplay()
{   
    //couleur
    glColor3f(EMERALD);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(290,400,0);
    drawSquare(EMERALD, 20);

    glTranslatef(0,400,0);

    // dessine le fond du menu option in game
    for(int i = 0; i < 29; i++)
    {
        drawSquare(DARK_GREY, 6);
        glTranslatef(10,0,0);
    }


    frameDraw(EMERALD, 300, 850, 630, 1);
	writeSomething(EMERALD, 333, 850, "P A U S E D  ~  O P T I O N S");

    writeSomethingHelvetica(DARK_GREY, 333, 760, "('c')   CONTINUE >>>>");
    writeSomethingHelvetica(DARK_GREY, 333, 700, "('g')   GAMEPLAY >>>>");
    writeSomethingHelvetica(DARK_GREY, 333, 640, "('o')   OPTIONS >>>>");
    writeSomethingHelvetica(DARK_GREY, 333, 580, "('d')   CREDITS >>>>");
    writeSomethingHelvetica(DARK_GREY, 333, 470, "('m')  TO MENU AND SAVE >>>>");
    
    writeSomethingHelvetica(DARK_GREY, 333, 440, "('x')   QUIT AND SAVE >>>>");


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
    NewGame_statslock = 1;



    // couleurs
    glColor3f(EMERALD);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    
    
    writeSomething9by15(WHITE,  175, 750, "|", 48, 0);
    writeSomething9by15(WHITE,  715, 750, "|", 48, 0);
    writeSomething9by15(WHITE,  175, 800, "-", 540, 1);
    writeSomething9by15(WHITE,  175, 750, "-", 540, 1);

    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 580, 210, 0);
    glColor3f(WHITE);

    writeSomething9by15(WHITE,  50, 580, "<<<<<<<<<<<<<<<<<<<<<< ('ESC')", 0, 2);

    frameDraw(EMERALD, 250, 850, 630, 1);
	writeSomething(EMERALD, 210, 850, "  E N T R E Z    V O T R E     U S E R N A M E :"); 

    
    // affiche le username, qui est alimenté par la fonction Keyboard(Alphabet)
    writeSomethingArray(WHITE, 330, 770, username_array);

    writeSomething9by15(WHITE,  615, 730, "PRESS ENTER", 0, 2);
    
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
    
    writeSomething9by15(SAND,  50, 430, "<<<<<<<<<<<<<<<<<<<<<< ('r')", 0, 2);

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
    
    writeSomething9by15(SAND,  50, 430, "<<<<<<<<<<<<<<<<<<<<<< ('r')", 0, 2);

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

    writeSomethingArray(WHITE, (x-30), 850, "  O    P    T    I    O    N    S");
    writeSomething9by15(WHITE,  x, 750, difficulty_str, 0, 2);
    writeSomething9by15(WHITE,  x, 700, gameplay_keys_str, 0, 2);
    writeSomething9by15(WHITE,  x, 650, screen_str, 0, 2);
    writeSomething9by15(WHITE,  x, 600, cheatmode_str, 0, 2);
    writeSomething9by15(WHITE,  x, 500, "<<<<<<<<<<<<<<<<<<<<<< ('r')", 0, 2);



    // affiche la difficulté en cours
    frameDraw(WHITE, x, 750, 210, 0);
    frameDraw(WHITE, x, 700, 210, 0);
    frameDraw(WHITE, x, 650, 210, 0);
    frameDraw(WHITE, x, 600, 210, 0);

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
    enemy en = malloc(sizeof(struct enemies));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(EMERALD);

    int x = (SCREEN_WIDTH/2)-80;

    frameDraw(EMERALD, x+30, 850, 630, 1);

    writeSomething(WHITE,  x+10, 850, "G     A     M     E     P     L     A     Y");
    writeSomething9by15(WHITE,  80, 790, "BIENVENUE DANS SUSTAINABILITY MOBILITY : SUBISTANCE !", 0, 2);

    writeSomething9by15(WHITE,  80, 750, "Le but du jeu est simple, reussir a detruire la mobilite forte !", 0, 2);

    writeSomething9by15(WHITE,  80, 725, "il vous faudra eliminer le maximum d'ennemis avant que votre vie ne tombe a 0.", 0, 2);
    writeSomething9by15(WHITE,  80, 660, "Le personnage possede un nombre de points de vie limites (15 max) ", 0, 2);
    writeSomething9by15(WHITE,  80, 630, "Il a aussi un nombre de points d attaque progressif (augmentable via les bonus)", 0, 2);
    writeSomething9by15(WHITE,  80, 600, "Vous aurez le choix entre deux types d'armes, le fusil (quoi qu'un peu excessif)", 0, 2);
    writeSomething9by15(WHITE,  80, 570, "Mais aussi un canon à bulles, permettant d'attraper les bonus, de figer un obstacle", 0, 2);
    writeSomething9by15(WHITE,  80, 540, "ou de ralentir un ennemi (vitesse / 2)", 0, 2);
   
    writeSomething9by15(WHITE,  250, 510, " ~ ", 0, 2);

    writeSomething9by15(WHITE,  80, 480, "Un ennemi elimine rapporte 100 points", 0, 2);
    writeSomething9by15(WHITE,  80, 450, "Une collision avec un ennemi enleve 1 point de vie, et retire 100 points.", 0, 2);
    writeSomething9by15(WHITE,  80, 420, "Un ennemi arrivant en bas de la map enleve 1 point de vie, et retire 100 points.", 0, 2);

    writeSomething9by15(WHITE,  250, 390, " ~ ", 0, 2);

    writeSomething9by15(WHITE,  80, 360, "Un bonus attrape via une bulle ou une collision rajoute 1 point d'attaque et de vie au hero", 0, 2);
    writeSomething9by15(WHITE,  80, 330, "Une collision avec un bonus donne une attaque ultime pour les 5 prochains kills.", 0, 2);
    writeSomething9by15(WHITE,  80, 300, "Un bonus detruit n'apporte aucun effet", 0, 2);

    writeSomething9by15(WHITE,  250, 270, " ~ ", 0, 2);

    writeSomething9by15(WHITE,  80, 240, "Une collision avec un obstacle fait perdre 1 de vie et 100 de score", 0, 2);

    glColor3f(EMERALD);
    frameDraw(EMERALD, 80, 75, 210, 0);
    glColor3f(WHITE);
    writeSomething9by15(WHITE,  80, 75, "<<<<<<<<<<<<<<<<<<<<<<  ('r')", 0, 2);
    writeSomething9by15(WHITE,  80, 185, "! Un cheat mode peut etre active via le clic droit ou via le menu des options !", 0, 2);
    writeSomething9by15(WHITE,  350, 120, "E   N   J   O   Y !", 0, 2);



    // dessin des "objets de jeu" dans le menu  
    glTranslatef(30,585,1);
    drawBike();

    glTranslatef(2,-137,0);
    //drawSquare(RED, 1);
    glColor3f(RED);
    drawCar(en);

    glTranslatef(10,-111,0);
    drawCircle(RED, 0, 0, 6);
    drawCircle(RED, 0, 0, 7);
    drawCircle(RED, 0, 0, 10);

    glTranslatef(-12,-103,0);
    glColor3f(BRICK);
    drawBrickWall();

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

    writeSomething(WHITE,  350, 850, "A   B  I  E  N  T  O  T ");

    glColor3f(EMERALD);
    frameDraw(WHITE, 50, 750, 210, 0);
    glColor3f(WHITE);

    writeSomething9by15(WHITE,  50, 750, "CREDITS", 0, 2);
    
    glColor3f(EMERALD);

    writeSomething9by15(WHITE,  50, 720, "Louys Raphaël", 0, 2);
    writeSomething9by15(WHITE,  50, 700, "Bac 1 - Informatique HD", 0, 2);
    writeSomething9by15(WHITE,  50, 680, "UNAMUR", 0, 2);

    glutSwapBuffers();
    wait1(); // used to wait until a certain time, before exitting
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

    writeSomething(WHITE,  320, 850, "   C   R   E   D   I   T  S   ");

    glColor3f(EMERALD);
    frameDraw(WHITE, 50, 750, 210, 0);
    glColor3f(WHITE);

    writeSomething9by15(WHITE,  50, 750, "CREDITS", 0, 2);
    
    glColor3f(EMERALD);
    
    writeSomething9by15(WHITE,  50, 720, "Louys Raphael", 0, 2);
    writeSomething9by15(WHITE,  50, 700, "Bac 1 - Informatique HD", 0, 2);
    writeSomething9by15(WHITE,  50, 680, "UNAMUR", 0, 2);

    glColor3f(EMERALD);
    frameDraw(EMERALD, 50, 550, 210, 0);
    glColor3f(WHITE);

    glRasterPos3f(50, 550, 1);
    char msg7[]="<<<<<<<<<<<<<<<<<<<<<< ('r')";
    for(int i = 0; i <strlen(msg7);i++)
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

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
                    screen_str = "ECRAN     :  H R Z T   ('s')";
                    writeSomething9by15(RED,70, 650, "WORKING ON IT, WON'T WORK", 0, 2);
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


