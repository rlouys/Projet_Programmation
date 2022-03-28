/*** LIBS ***/

#include "timers_and_effects.h"
#include "game_graphics.h"
#include "game.h"
#include "enemies.h"
#include "tirs.h"
#include "characters.h"

/*** VARIABLES ***/

int mX;
int mY;
float *value;

/*** FUNCTIONS ***/

// ---------------------------------------------------------------------------------- //

void timer(int valeur) {
    
    glutPostRedisplay();      // Post re-paint request to activate display()
	*value = *value *2;
	if((*value)>=400){
            *value = 20;
        }
	//printf("Valeur : %lf\n", *value);
    glutTimerFunc(1000/FPS, timer, 0); // next timer call milliseconds later

}

// ---------------------------------------------------------------------------------- //

void updateCollisions(int valeur)
{
	enemy baseE = e->starList;
	tirsP baseP = t->starList;
	if (e->starList != NULL && t->starList != NULL)
	{
		checkCollision(baseE, baseP);
		if (t->starList->nextptr != NULL)
			{
				baseP = baseP->nextptr;	
				checkCollision(baseE, baseP);
				while (baseP->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollision(baseE, baseP);
				}
			}
		if (e->starList->nextptr != NULL)
		{
			baseE = baseE->nextptr;
			baseP = t->starList;
			checkCollision(baseE, baseP);
			if (t->starList->nextptr != NULL)
			{
				baseP = baseP->nextptr;
				checkCollision (baseE, baseP);
				while (baseP->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollision(baseE, baseP);
				}
			}
			while (baseE->nextptr != NULL)
			{
				baseE = baseE->nextptr;
				baseP = t->starList;
				checkCollision(baseE, baseP);
				if (t->starList->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollision (baseE, baseP);
					while (baseP->nextptr != NULL)
					{
						baseP = baseP->nextptr;
						checkCollision(baseE, baseP);
					}
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateCollisions, 0);
}

// ---------------------------------------------------------------------------------- //

void updateEnemies(int valeur)
{
	q = e->starList;
	if (e->starList != NULL)
	{
		q->pos.x += 1;
		if (q->pos.x > 28)
		{
			q->pos.x = 2;
			q->active = false;
		}
		while (q->nextptr != NULL)
		{
			q = q->nextptr;
			q->pos.x +=1;
			if (q->pos.x > 28)
			{
				q->pos.x = 2;
				q->active = false;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(200, updateEnemies, 1);
}

// ---------------------------------------------------------------------------------- //

void updateNewEnemies(int valeur)
{
	enemy new = createEnemy((&mX));
	insertionEnemies(e, new);
	glutPostRedisplay();
	glutTimerFunc(1000, updateNewEnemies, 3);
}

// ---------------------------------------------------------------------------------- //

void updateTirs(int valeur)
{
	r = t->starList;
	if (t->starList != NULL)
	{
		r->pos.x -= 1;
		if (r->pos.x < 24)
		{
			r->pos.x = 88;
			r->active = false;
		}
		while (r->nextptr != NULL)
		{
			r = r->nextptr;
			r->pos.x -= 1;
			if (r->pos.x < 24)
			{
				r->pos.x = 88;
				r->active = false;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateTirs, 2);
}


void updateDeleteEnemies(int valeur)
{
	if (e->starList != NULL || e->endList != NULL)
	{
		suppressionEnemies(e, test);
	}
	glutPostRedisplay();
	glutTimerFunc(200, updateDeleteEnemies, 4);
}

void updateDeleteTirs(int valeur)
{
	if (t->starList != NULL || t->endList != NULL)
	{
		suppressionTirs(t, test);
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateDeleteTirs, 5);
}




