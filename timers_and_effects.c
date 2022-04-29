/*** LIBS ***/

#include "timers_and_effects.h"
#include "game_graphics.h"
#include "game.h"
#include "enemies.h"
#include "tirs.h"
#include "hero.h"
#include "menus_graphics.h"

/*** CONSTANTES ***/

#define ENNEMI_SPEED 30000 // 10 = ultraspeed/hardcore | 1000 = slow
#define ENNEMI_PER_HUNDRED_SECOND 1
#define RANGE_MAX 120
#define ATTACK_SPEED 1 // 1 is superfast, 1000 is slow
#define OBSTACLE_SPEED 20 // 10 = ultraspeed/hardcore | 1000 = slow
#define OBSTACLES_PER_HUNDRED_SECOND 100
#define BONUS_SPEED 20
#define BONUS_PER_HUNDRED_SECOND 100


#define MAX_SCORE 200

/*** VARIABLES ***/

int mX;
int mY;
float *value;
float *deplacement_fenetre;
int counter = 0;
bool startgame;
bool endmap;
int level;

/*** FUNCTIONS ***/

// ---------------------------------------------------------------------------------- //

// timer qui gère le défilement de la map

void scrolling(int valeur) {
	

	if(startgame==true){ 

		*value = *value *1.75;

			if((*value)>=500){
					*value = 20;
			}
	
   }

       glutPostRedisplay();      
       glutTimerFunc(1000/FPS, scrolling, 0); 

  // printf("startgame :::: \n");
}

// ---------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------- //

// timer qui gère les collisions tir et ennemis || obstacles(en test : allie et ennemis gérés en +)

void updateCollisions(int valeur)
{
	if(startgame==true){ 
		// ----------------- //
		enemy En = e->first;
		tir_Struct Sht = t->first;
		obstacles fence = o->first;
		bonus_objet bonus = b->first;

		if (e->first != NULL && t->first != NULL)
		{
			checkCollisionTirsEnnemis(En, Sht);

			if (t->first->next != NULL)
				{
					Sht = Sht->next;	
					checkCollisionTirsEnnemis(En, Sht);

					
					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsEnnemis(En, Sht);

					}
				}
			if (e->first->next != NULL)
			{
				En = En->next;
				Sht = t->first;
				checkCollisionTirsEnnemis(En, Sht);

				if (t->first->next != NULL)
				{
					Sht = Sht->next;
					checkCollisionTirsEnnemis (En, Sht);

					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsEnnemis(En, Sht);

					}
				}
				while (En->next != NULL)
				{
					En = En->next;
					Sht = t->first;
					checkCollisionTirsEnnemis(En, Sht);

					if (t->first->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsEnnemis (En, Sht);

						while (Sht->next != NULL)
						{
							Sht = Sht->next;
							checkCollisionTirsEnnemis(En, Sht);

						}
					}
				}
			}
		}

	// --------------- //

	Sht = t->first;
	
		if (o->first != NULL && t->first != NULL)
		{
			checkCollisionTirsObstacles(fence, Sht);

			if (t->first->next != NULL)
				{
					Sht = Sht->next;	
					checkCollisionTirsObstacles(fence, Sht);

					
					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsObstacles(fence, Sht);

					}
				}
			if (o->first->next != NULL)
			{
				fence = fence->next;
				Sht = t->first;
				checkCollisionTirsObstacles(fence, Sht);

				if (t->first->next != NULL)
				{
					Sht = Sht->next;
					checkCollisionTirsObstacles(fence, Sht);

					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsObstacles(fence, Sht);

					}
				}
				while (fence->next != NULL)
				{
					fence = fence->next;
					Sht = t->first;
					checkCollisionTirsObstacles(fence, Sht);

					if (t->first->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsObstacles(fence, Sht);

						while (Sht->next != NULL)
						{
							Sht = Sht->next;
							checkCollisionTirsObstacles(fence, Sht);

						}
					}
				}
			}
		}

	// ------------- // 

	Sht = t->first;
	
		if (b->first != NULL && t->first != NULL)
		{
			checkCollisionTirsBonus(bonus, Sht);

			if (t->first->next != NULL)
				{
					Sht = Sht->next;	
					checkCollisionTirsBonus(bonus, Sht);

					
					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsBonus(bonus, Sht);

					}
				}
			if (b->first->next != NULL)
			{
				bonus = bonus->next;
				Sht = t->first;
				checkCollisionTirsBonus(bonus, Sht);

				if (t->first->next != NULL)
				{
					Sht = Sht->next;
					checkCollisionTirsBonus(bonus, Sht);

					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsBonus(bonus, Sht);

					}
				}
				while (bonus->next != NULL)
				{
					bonus = bonus->next;
					Sht = t->first;
					checkCollisionTirsBonus(bonus, Sht);

					if (t->first->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsBonus(bonus, Sht);

						while (Sht->next != NULL)
						{
							Sht = Sht->next;
							checkCollisionTirsBonus(bonus, Sht);

						}
					}
				}
			}
		}






	}
	glutPostRedisplay();
	glutTimerFunc(10, updateCollisions, 1);
}	// --------------- //


// --------------------------------------------------- // 

// timer qui gère les changements de statut de l'ennemi

void updateEnemies(int valeur)
{
	if(startgame==true && hero->health != 0 && hero->current_xp != MAX_SCORE)
	{ 

		car = e->first;
		if (e->first != NULL)
		{
			car->pos.y -= 0.20;
			checkCollisionAlliesEnemy(car);

			if (car->pos.y <= 0)
			{
				hero->current_xp -= 10;
				e->quantite--;
				hero->health -= 1;
				hero->killed +=1;
				car->active = false;
				endmap = true;
				drawHealth(hero);


				if(hero->health == 0)
					{
						startgame = false;
						saveScore(hero);

						glutDisplayFunc(EndGameDisplay);
						
					}

			}
			while (car->next != NULL)
			{
				car = car->next;
				car->pos.y -= 0.20;
				checkCollisionAlliesEnemy(car);

				if (car->pos.y <= 0)
				{
					//car->pos.y = 40;
					hero->current_xp -= 10;
					e->quantite--;
					car->active = false;
					endmap = true;
					hero->health -= 1;
					drawHealth(hero);

					if(hero->health == 0)
					{
						saveScore(hero);
						startgame = false;
						glutDisplayFunc(EndGameDisplay);

					}
				}
			}
		}

		}else if (hero->current_xp == 10000){

			startgame = false;
			
			suppressionEnemiesEndGame(e);
			suppressionObstaclesEndGame(o);
			suppressionTirsEndGame(t);
			level++;
			saveScore(hero);

			hero->current_xp = 0;
			//wait();

			//startgame = true;
			glutDisplayFunc(DisplayGame);

		}
	glutPostRedisplay();
	glutTimerFunc(ENNEMI_SPEED, updateEnemies, 2);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère l'insertion de nouveaux ennemis

void updateNewEnemies(int valeur)
{
	if(startgame==true){ 

	enemy new = createEnemy((&mX));
	insertionEnemies(e, new);
	
	}
	
	glutPostRedisplay();
	glutTimerFunc(100000/ENNEMI_PER_HUNDRED_SECOND, updateNewEnemies, 3);
	
}

// ---------------------------------------------------------------------------------- //

// timer qui gère le défilement des tirs

void updateTirs(int valeur)
{
	if(startgame==true){ 

	shoot = t->first;
	if (t->first != NULL)
	{
		shoot->pos.y += 1;
		if (shoot->pos.y >= RANGE_MAX)
		{
			shoot->active = false;
		}
		while (shoot->next != NULL)
		{
			shoot = shoot->next;
			shoot->pos.y += 1;
			if (shoot->pos.y >= RANGE_MAX)
			{
				shoot->active = false;
			}
		}
	}
	}
	glutPostRedisplay();
	glutTimerFunc(1, updateTirs, 4);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère les suppressions d'ennemis

void updateDeleteEnemies(int valeur)
{
	if(startgame==true){ 

		if (e->first != NULL || e->last != NULL)
		{
			suppressionEnemies(e, false);
		}

		

	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteEnemies, 5);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère les suppressions d'ennemis

void updateDeleteTirs(int valeur)
{
	if(startgame==true){ 

	if (t->first != NULL || t->last != NULL)
	{
		suppressionTirs(t, test);
	}
	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteTirs, 6);
}

// ---------------------------------------------------------------------------------- //

void updateObstacle(int valeur)
{

	int key = 1;

	if(startgame==true && hero->health != 0){ 

		fence = o->first;
		if (o->first != NULL)
		{
			fence->pos.y -= 0.2;
			
				checkCollisionAlliesObstacles(fence);
			
			//key = 0;
			if (fence->pos.y <= 0 && key != 0)
			{
				hero->current_xp -= 10;
				o->quantite--;
				fence->active = false;
				endmap = true;
				drawHealth(hero);


				if(hero->health == 0){
						glutDisplayFunc(EndGameDisplay);

					}

			}
			while (fence->next != NULL)
			{
				fence = fence->next;
				fence->pos.y -=0.2;

				
					checkCollisionAlliesObstacles(fence);
				
				if (fence->pos.y <= 0 && key != 0)
				{
					
					hero->current_xp -= 10;
					o->quantite--;
					fence->active = false;
					endmap = true;
					drawHealth(hero);

					if(hero->health == 0)
					{
						saveScore(hero);
						startgame = false;
						glutDisplayFunc(EndGameDisplay);
					}

				}
			}
		}
		} else if (hero->current_xp == 10000){

			startgame = false;
			
			suppressionEnemiesEndGame(e);
			suppressionObstaclesEndGame(o);
			suppressionTirsEndGame(t);
			level++;
			saveScore(hero);

			hero->current_xp = 0;
			glutDisplayFunc(DisplayGame);

		}
		glutPostRedisplay();
		glutTimerFunc(OBSTACLE_SPEED, updateObstacle, 7);


}

// ---------------------------------------------------------------------------------- //

void updateNewObstacles(int valeur)
{
	if(startgame==true){ 

		obstacles new = createObstacle((&mX));
		insertionObstacles(o, new);
		
		
	}
	
	glutPostRedisplay();
	glutTimerFunc(100000/OBSTACLES_PER_HUNDRED_SECOND, updateNewObstacles, 8);


}
// ---------------------------------------------------------------------------------- //

void updateDeleteObstacles(int valeur)
{
	if(startgame==true){ 

		if (o->first != NULL || o->last != NULL)
		{
			suppressionObstacles(o, test);
		}

	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteObstacles, 9);


}
// ---------------------------------------------------------------------------------- //

void updateBonus(int valeur)
{
	if(startgame==true && hero->health != 0 && hero->current_xp != MAX_SCORE)
	{ 

		bonus = b->first;
		if (b->first != NULL)
		{
			bonus->pos.y -= 0.20;
			checkCollisionAlliesBonus(bonus);

			if (bonus->pos.y <= 0)
			{
				b->quantite--;
				hero->health -= 1;
				//hero->bonus_picked++;
				hero->current_xp += 30;
				bonus->active = false;
				endmap = true;
				drawHealth(hero);
			}

			while (bonus->next != NULL)
			{
				bonus = bonus->next;
				bonus->pos.y -= 0.20;
				checkCollisionAlliesBonus(bonus);

				if (bonus->pos.y <= 0)
				{
					//car->pos.y = 40;
					b->quantite--;
					bonus->active = false;
					endmap = true;
					hero->health -= 1;
					hero->current_xp += 30;
					//hero->bonus_picked++;
					drawHealth(hero);

					
				}
			}
		}

		}else if (hero->current_xp == 10000){

			startgame = false;
			
			suppressionEnemiesEndGame(e);
			suppressionObstaclesEndGame(o);
			suppressionTirsEndGame(t);
			level++;
			saveScore(hero);

			hero->current_xp = 0;
			//wait();

			//startgame = true;
			glutDisplayFunc(DisplayGame);

		}
	glutPostRedisplay();
	glutTimerFunc(BONUS_SPEED, updateBonus, 10);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère l'insertion de nouveaux ennemis

void updateNewBonus(int valeur)
{
	if(startgame==true){ 

	bonus_objet new = createBonus((&mX));
	insertionBonus(b, new);
	
	}
	
	glutPostRedisplay();
	glutTimerFunc(100000/BONUS_PER_HUNDRED_SECOND, updateNewBonus, 11);
	
}


// ---------------------------------------------------------------------------------- //

// timer qui gère les suppressions d'ennemis

void updateDeleteBonus(int valeur)
{
	if(startgame==true){ 

		if (b->first != NULL || b->last != NULL)
		{
			suppressionBonus(b, false);
		}

		

	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteBonus, 11);
}
