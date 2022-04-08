/*** LIBS ***/

#include "timers_and_effects.h"
#include "game_graphics.h"
#include "game.h"
#include "enemies.h"
#include "tirs.h"
#include "characters.h"
#include "menus_graphics.h"

/*** VARIABLES ***/

int mX;
int mY;
float *value;
float *deplacement_fenetre;
int counter = 0;
bool startgame;

#define ENNEMI_SPEED 100 // 10 = ultraspeed/hardcore | 1000 = slow
#define ENNEMI_PER_TEN_SECOND 5
#define RANGE_MAX 120
#define ATTACK_SPEED 10 // 1 is superfast, 1000 is slow
/*** FUNCTIONS ***/

// ---------------------------------------------------------------------------------- //

void timer(int valeur) {
	
	if(startgame==true){ 

		*value = *value *1.75;

			if((*value)>=500){
					*value = 20;
			}
	
   }
       glutPostRedisplay();      
       glutTimerFunc(1000/FPS, timer, 0); 

  // printf("startgame :::: \n");
}

// ---------------------------------------------------------------------------------- //
/* void MenuTimer(int valeur) {
    
    glutPostRedisplay();      // Post re-paint request to activate display()
	
	*deplacement_fenetre += 1;
	int somme = 0;
	somme += *deplacement_fenetre;
	printf("somme : %i\n", somme);
	if((*deplacement_fenetre)==-20){
		*deplacement_fenetre = 5;
	}

	if((somme)>=21)
	{
			*deplacement_fenetre = -21;
			somme = 0;

	}
	//printf("Valeur : %lf\n", *value);
    glutTimerFunc(10, MenuTimer, 6); // next timer call milliseconds later

}*/

// ---------------------------------------------------------------------------------- //

void updateCollisions(int valeur)
{
	if(startgame==true){ 

	enemy baseE = e->first;
	tirsP baseP = t->first;
	
	if (e->first != NULL && t->first != NULL)
	{
		checkCollisionTirsEnnemis(baseE, baseP);
		if (t->first->nextptr != NULL)
			{
				baseP = baseP->nextptr;	
				checkCollisionTirsEnnemis(baseE, baseP);
				while (baseP->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollisionTirsEnnemis(baseE, baseP);
				}
			}
		if (e->first->nextptr != NULL)
		{
			baseE = baseE->nextptr;
			baseP = t->first;
			checkCollisionTirsEnnemis(baseE, baseP);
			if (t->first->nextptr != NULL)
			{
				baseP = baseP->nextptr;
				checkCollisionTirsEnnemis (baseE, baseP);
				while (baseP->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollisionTirsEnnemis(baseE, baseP);
				}
			}
			while (baseE->nextptr != NULL)
			{
				baseE = baseE->nextptr;
				baseP = t->first;
				checkCollisionTirsEnnemis(baseE, baseP);
				if (t->first->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollisionTirsEnnemis (baseE, baseP);
					while (baseP->nextptr != NULL)
					{
						baseP = baseP->nextptr;
						checkCollisionTirsEnnemis(baseE, baseP);
					}
				}
			}
		}
	}
	}
	glutPostRedisplay();
	glutTimerFunc(10, updateCollisions, 0);
}

// ---------------------------------------------------------------------------------- //

void updateEnemies(int valeur)
{
	if(startgame==true){ 

	q = e->first;
	if (e->first != NULL)
	{
		q->pos.y -= 1;
		if (q->pos.y == 0)
		{
			q->pos.y = 40;
			p->current_xp -= 50;
			//q->active = false;
			printf("score : %i\n", p->current_xp);
			e->quantite--;

		}
		while (q->nextptr != NULL)
		{
			q = q->nextptr;
			q->pos.y -=1;
			if (q->pos.y == 0)
			{
				q->pos.y = 40;
				p->current_xp -= 50;
				printf("score : %i\n", p->current_xp);
				e->quantite--;

				//q->active = false;
			}
		}
	}
	}
	glutPostRedisplay();
	glutTimerFunc(ENNEMI_SPEED, updateEnemies, 1);
}

// ---------------------------------------------------------------------------------- //

void updateNewEnemies(int valeur)
{
	if(startgame==true){ 

	enemy new = createEnemy((&mX));
	insertionEnemies(e, new);
	/*counter += 1;
	printf("counter : %i", counter);
	if(counter == 10)
	{
		glutDisplayFunc(WelcomeDisplay);
	}*/
	}
	glutPostRedisplay();
	glutTimerFunc(10000/ENNEMI_PER_TEN_SECOND, updateNewEnemies, 3);
	
}

// ---------------------------------------------------------------------------------- //

void updateTirs(int valeur)
{
	if(startgame==true){ 

	r = t->first;
	if (t->first != NULL)
	{
		r->pos.y += 1;
		if (r->pos.y >= RANGE_MAX)
		{
			r->pos.y = 24;
			r->active = false;
		}
		while (r->nextptr != NULL)
		{
			r = r->nextptr;
			r->pos.y += 1;
			if (r->pos.y >= RANGE_MAX)
			{
				r->pos.y = 24;
				r->active = false;
			}
		}
	}
	}
	glutPostRedisplay();
	glutTimerFunc(ATTACK_SPEED, updateTirs, 2);
}

// ---------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------- //


void updateDeleteEnemies(int valeur)
{
	if(startgame==true){ 

	if (e->first != NULL || e->last != NULL)
	{
		suppressionEnemies(e, test);
	}
	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteEnemies, 4);
}

void updateDeleteTirs(int valeur)
{
	if(startgame==true){ 

	if (t->first != NULL || t->last != NULL)
	{
		suppressionTirs(t, test);
	}
	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteTirs, 5);
}




