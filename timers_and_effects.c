/*** LIBS ***/

#include "timers_and_effects.h"
#include "game_graphics.h"
#include "game.h"
#include "enemies.h"
#include "tirs.h"
#include "hero.h"
#include "menus_graphics.h"

/*** CONSTANTES ***/

#define ENNEMI_SPEED 50 // 10 = ultraspeed/hardcore | 1000 = slow
#define ENNEMI_PER_HUNDRED_SECOND 20
#define RANGE_MAX 120
#define ATTACK_SPEED 1 // 1 is superfast, 1000 is slow
#define OBSTACLE_SPEED 10 // 10 = ultraspeed/hardcore | 1000 = slow
#define OBSTACLES_PER_HUNDRED_SECOND 10
#define BONUS_SPEED 100
#define BONUS_PER_TEN_SECOND 1

#define MAX_SCORE 200

/*** VARIABLES ***/

int mX;
int mY;
int level;
int counter = 0;

float vl = 20.0;
float *value = &vl;
float *deplacement_fenetre;

bool startgame;
bool endmap;
bool SHOOT_ENEMY; // from game.c
bool CHECKCOLLISION = false;



/*** FUNCTIONS ***/

// ------------------------------------------------------------ // 

// vérifie s'il y a une collision entre l'ennemi et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsEnnemis (enemy e, tir_Struct w)
{	
	bool Collide = false;
	int key = 1;

	// condition de collision
	if ((w->pos.x/2) == e->pos.x && e->pos.y <= ((w->pos.y-2)/2)+1.5 && key != 0)
		{
			Collide = true;
			key = 0; // pour n'enlever qu'une fois de la vie
			
		}
	
	if (Collide)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		// si collision, l'ennemi perd de la vie à hauteur du nombre
		// de points d'attaque du héro
		e->vie = (e->vie) - hero->attack;

		// si l'ennemi n'a plus de vie, il passe à désactivé, pour suppression
		// le compteur d'ennemis tué est incrémenté
		if(e->vie <= 0)
		{
			e->active = false;
			hero->killed += 1;
		}

		// tir désactivé pour suppression
		w->active = false;

		// réinitialisation du booléen de collision
		CHECKCOLLISION = false;
	}
	
} 

// ------------------------------------- //

void checkCollisionAlliesEnemy (enemy en)
{	
	bool CollideO = false;
	int key = 1;

	// condition de collision
	if( (en->pos.x == hero->pos.x) && (((en->pos.y) <= hero->pos.y +0.1) && ((en->pos.y) > hero->pos.y -1))   && key != 0   )

	{
			CollideO = true;
			key = 0; // pour n'enlever qu'une fois de la vie
	} 

	if (CollideO)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		// si collision entre allié et ennemi
		// le héro perd de la vie, l'ennemi aussi
		// le héro perd son bonus
		hero->health -= 1;
		en->vie -=1;
		hero->color_type = false;
		
		// si le héro n'a plus de vie, la partie est finie, on affiche le display de fin
		if(hero->health == 0){
			glutDisplayFunc(EndGameDisplay);
		}

		// si l'ennemi n'a plus de vie, il est désactivé pour suppression
		if(en->vie <= 0){
			en->active = false;
		}
		// réinitialisation du booléen de collision
		CHECKCOLLISION = false;
	}
	
} 


// ------------------------------------------------------------ // 

// vérifie s'il y a une collision entre l'obstacle et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsObstacles (obstacles o, tir_Struct w)
{	
	bool CollideO = false;
	int key = 1;
	// Si le tir arrive à la position de l'obstacle en x ou en x+1 ou en x-1, alors suppression ennemi
	if (    
	((((w->pos.x/2) == o->pos.x) && (o->pos.y <= (((w->pos.y-2)/2)+1.5))) /**/ 
	||  ((((w->pos.x/2)) == (o->pos.x+1)) && (o->pos.y <=  (((w->pos.y-2)/2)+1.5)))
	
	||  ((((w->pos.x/2)) == (o->pos.x-1)) && (o->pos.y <=  (((w->pos.y-2)/2)+1.5))))
	&& key != 0)

	{
			CollideO = true;
			key = 0;
	}

	if (CollideO)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		// si un tir touche un obstacle, il est supprimé
		w->active = false;
		CHECKCOLLISION = false;
	}
	
}


// ------------------------------------- //

void checkCollisionAlliesObstacles (obstacles fence)
{	
	bool CollideO = false;
	int key = 1;

	// condition de collision allié et obstacle
	if( 
	/**/ (((fence->pos.x == hero->pos.x) &&  (fence->pos.y <= (hero->pos.y +0.1)) && (fence->pos.y > (hero->pos.y -0.1)))
	/**/ ||
	/**/  (((fence->pos.x+1) == hero->pos.x) && (fence->pos.y <= (hero->pos.y +0.1)) && (fence->pos.y > (hero->pos.y -0.1)))
	/**/ || 
	/**/ (((fence->pos.x-1) == hero->pos.x) && (fence->pos.y <= (hero->pos.y +0.1)) && (fence->pos.y > (hero->pos.y -0.1)))
	)

	/**/  && key != 0   )

	{

			CollideO = true;

			key = 0;
		
	

			if (CollideO)
			{
				CHECKCOLLISION = true;
			}
			
			if (CHECKCOLLISION)
			{	
				if(key == 0)
				{
					// si collision, alors le hero perd de la vie
					// le héro perd de l'xp
					// le héro perd un bonus d'attaque
					hero->health -= 1; // ENLEVE 5 !! A CORRIGER !! 
					hero->current_xp -= 100;
					fence->pos.y -= 0.1;
					key = 1;
					hero->color_type = false;


					// le héro perd 1 bonus d'attaque
					if(hero->attack > 1)
					{
						hero->attack -= 1;
					}
				}
				// compteur d'obstacles pris augmente
				hero->obstacles_taken += 1;


				// si le héro n'a plus de vie, on affiche la fin de jeu
				if(hero->health == 0){
					glutDisplayFunc(EndGameDisplay);
				}

				// réinitialisation du booléen de collision
				CHECKCOLLISION = false;
			}
	}
} 

// ------------------------------------- //

// vérifie s'il y a une collision entre l'ennemi et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsBonus (bonus_objet b, tir_Struct w)
{	
	bool Collide = false;
	int key = 1;

	// condition de collision entre les tirs et les objets bonus
	if (    (((w->pos.x/2) >= b->pos.x-1) && ((w->pos.x/2) < b->pos.x+1))                 && b->pos.y <= ((w->pos.y-2)/2)+1.5 && key != 0)
		{
			Collide = true;
			key = 0;
			
		}

	if (Collide)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		// le bonus est désactivé pour suppression
		b->active = false;

		// le tir est désactivé pour suppression
		w->active = false;
		CHECKCOLLISION = false;
	}
	
} 
// ------------------------------------- //

void checkCollisionAlliesBonus (bonus_objet bns)
{	
	bool CollideO = false;
	int key = 1;
	

	// condition de collision Allies et Objts bonus
	if( ( (bns->pos.x < hero->pos.x+1) && (bns->pos.x >= hero->pos.x-1)) && (((bns->pos.y) <= hero->pos.y +1) && ((bns->pos.y) > hero->pos.y -1))   && key != 0   )

	{ 
			CollideO = true;
			key = 0;
	} 

	if (CollideO)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	

		// si collision
		// le hero gagne des points d'attaque 
		// le hero récupère de la santé
		hero->color_type = true;
		hero->attack += 1;
		if(hero->health <= 45)
		{
			hero->health += 5;
		}
		else
		{
			hero->health = 50;
		}
		drawHealth(hero);
		

		// l'objet est désactivé pour suppression
		bns->active = false;
		
		// réinitialisation du booléen de collision
		CHECKCOLLISION = false;
	}
	
} 

// ---------------------------------------------------------------------------------- //

void wait()
{
    int timerwait;

    for(timerwait = 0; timerwait < 200000; timerwait++)
    {
            printf("wait : %i\n", timerwait);
    }
}


/*** TIMERS ***/


                            /*******
                             * MAP *
                             *******/


// timer qui gère le défilement de la map

void scrolling(int valeur) {
	

	if(startgame==true)
	{ 

		*value = *value *1.75;

			if((*value)>=500){
					*value = 20;
			}
			// la valeur est celle du défilement de la map, elle défile
			// jusqu'à un certain point (500) puis revient à sa position
			// de départ
   }
       glutPostRedisplay();      
       glutTimerFunc(1000/FPS, scrolling, 0); 

}


                /**************************
                 * COLLISIONS TIRS ALLIÉS *
                 **************************/


// timer qui gère les collisions tir et ennemis || obstacles(en test : allie et ennemis gérés en +)

void updateCollisions(int valeur)
{
	if(startgame==true)
	{ 
		// ----------------- // TIRS ALLIES ET ENNEMIS
		enemy En = e->first;
		tir_Struct Sht = t->first;
		obstacles fence = o->first;
		bonus_objet bonus = b->first;

		// vérifie les listes d'ennemis, et à certaines conditions, vérifie s'il y a une collision
		// entre les tirs alliés et les ennemies
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

	// --------------- // TIR ALLIES ET OBSTACLES

	Sht = t->first;
	
		// vérifie les listes d'obstacles, et à certaines conditions, vérifie s'il y a une collision
		// entre les tirs alliés et les obstacles

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

	// ------------- // TIR ALLIE ET OBJET BONUS

	Sht = t->first;
	

		// vérifie les listes d'objets bonus, et à certaines conditions, vérifie s'il y a une collision
		// entre les tirs alliés et les objets bonus

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


                /**********************
                 * MOUVEMENTS ENNEMIS *
                 **********************/

// timer qui gère les changements de statut de l'ennemi

void updateEnemies(int valeur)
{
	if(startgame==true && hero->health != 0 && hero->current_xp != MAX_SCORE)
	{ 

		car = e->first;

		// si ennemi il y a, il se déplace de 0.20 vers le bas 

		if (e->first != NULL)
		{
			car->pos.y -= 0.20;

		// déplacement aléatoire vers la position du héro
		int a = rand() % 40;
					if(car->pos.y < 50 && a == 10)
					{

						if(car->pos.x > hero->pos.x)
						{
							car->pos.x -= 1;
						}

						else if(car->pos.x < hero->pos.x)
						{
							car->pos.x += 1;
						}
					}
			// après déplacement, vérifie s'il y a une collision
			checkCollisionAlliesEnemy(car);

			if (car->pos.y <= 0)
			{
				hero->current_xp -= 100;
				e->quantite--;
				hero->health -= 1;
				hero->killed +=1;
				car->active = false;
				endmap = true;
				hero->attack = 1;
				// le hero perd le bonus en cours	
				hero->color_type = false;
				hero->attack += 3;

				drawHealth(hero); // affiche la santé du héros en permanence


				if(hero->health == 0)
					{
						startgame = false;
						saveScore(hero); // sauvegarde le score de la partie en cours

						glutDisplayFunc(EndGameDisplay);		
					}
			}

			// pareil cas 1, mais avec l'ennemi suivant
			while (car->next != NULL)
			{
				car = car->next;
				car->pos.y -= 0.20;

				// déplacement aléatoire vers la position du héro
				if(car->pos.y < 50 && a == 10)
				{
					if(car->pos.x > hero->pos.x)
					{
						car->pos.x -= 1;
					}

					else if(car->pos.x < hero->pos.x)
					{
						car->pos.x += 1;
					}
				}

				// après déplacement, vérifie s'il y a une collision
				checkCollisionAlliesEnemy(car);

				if (car->pos.y <= 0)
				{
					hero->current_xp -= 100;
					e->quantite--;
					car->active = false;
					endmap = true;

					// le hero perd le bonus en cours	
					hero->attack -= 1;
					hero->color_type = false;

					drawHealth(hero); // affiche la santé du héros en permanence

					if(hero->health == 0)
					{
						saveScore(hero); // sauvegarde le score de la partie en cours
						startgame = false;
						glutDisplayFunc(EndGameDisplay);

					}
				}
			}
		}

		// si fin de partie car score max atteint, on arrête
		// tout, on supprime tous les objets sur la map
		// et on sauvegarde la partie avant de la quitter
		}else if (hero->current_xp == 10000){

			startgame = false;
			
			suppressionEnemiesEndGame(e);
			suppressionObstaclesEndGame(o);
			suppressionTirsEndGame(t);
			level++; // augmente le niveau
			saveScore(hero);
			hero->current_xp = 0;
			glutDisplayFunc(DisplayGame);

		}
	glutPostRedisplay();
	glutTimerFunc(ENNEMI_SPEED, updateEnemies, 2);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère l'insertion de nouveaux ennemis

void updateNewEnemies(int valeur)
{
	if(startgame==true)
	{ 
		enemy new = createEnemy((&mX));
		insertionEnemies(e, new);
	}
	
	glutPostRedisplay();
	glutTimerFunc(100000/ENNEMI_PER_HUNDRED_SECOND, updateNewEnemies, 3);
	
}


// ---------------------------------------------------------------------------------- //


// timer qui gère les suppressions d'ennemis

void updateDeleteEnemies(int valeur)
{
	if(startgame==true)
	{ 
		// s'il y a un ennemi dans la liste, le supprimes
		if (e->first != NULL || e->last != NULL)
		{
			suppressionEnemies(e, false);
		}

	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteEnemies, 5);
}


                /************************
                 * MOUVEMENTS OBSTACLES *
                 ************************/

// timer qui gère le déplacement des obstacles, et check les collisions
// après déplacement

void updateObstacle(int valeur)
{

	int key = 1;

	if(startgame==true && hero->health != 0){ 

		fence = o->first;
		if (o->first != NULL)
		{
			fence->pos.y -= 0.1;
			
				checkCollisionAlliesObstacles(fence);
			
			//key = 0;
			if (fence->pos.y <= 0 && key != 0)
			{
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
				fence->pos.y -=0.1;

				
					checkCollisionAlliesObstacles(fence);
				
				if (fence->pos.y <= 0 && key != 0)
				{
					
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
		// max score atteint, on arrête tout
		// on supprime les objets sur la map
		// on affiche le display de fin
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

// ajoute un nouvel obstacle si la partie est en cours

void updateNewObstacles(int valeur)
{
	if(startgame==true)
	{ 

		obstacles new = createObstacle((&mX));
		insertionObstacles(o, new);
		
	}
	
	glutPostRedisplay();
	glutTimerFunc(100000/OBSTACLES_PER_HUNDRED_SECOND, updateNewObstacles, 8);


}
// ---------------------------------------------------------------------------------- //

// s'il y a un obstacle dans la liste, le supprime
// si la partie est en cours

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

                /********************
                 * MOUVEMENTS BONUS *
                 ********************/

// timer qui gère les changements de statut de l'objet bonus

void updateBonus(int valeur)
{
	if(startgame==true && hero->health != 0 && hero->current_xp != MAX_SCORE)
	{ 

		bonus = b->first;
		if (b->first != NULL)
		{
			bonus->pos.y -= 0.5;

			
			if (bonus->pos.x > 38){
				bonus->side = 1;
			}
			
			else if(bonus->pos.x < 10){
				bonus->side = 0;
			}

			if(bonus->side == 1)
			{
				bonus->pos.x -= 0.15;
			}
			
			else if(bonus->side == 0){
				bonus->pos.x += 0.15;
			}

			checkCollisionAlliesBonus(bonus);

			if (bonus->pos.y <= 0)
			{
				b->quantite--;
				bonus->active = false;
				endmap = true;
				drawHealth(hero);
			}

			while (bonus->next != NULL)
			{
				bonus = bonus->next;
				bonus->pos.y -= 0.5;


				if (bonus->pos.x > 38){
				bonus->side = 1;
				}
				
				else if(bonus->pos.x < 10){
					bonus->side = 0;
				}

				if(bonus->side == 1)
				{
					bonus->pos.x -= 0.15;
				}

				else if(bonus->side == 0){
					bonus->pos.x += 0.15;
				}

				checkCollisionAlliesBonus(bonus);
			



				if (bonus->pos.y <= 0)
				{
					b->quantite--;
					bonus->active = false;
					endmap = true;
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
			glutDisplayFunc(DisplayGame);

		}
	glutPostRedisplay();
	glutTimerFunc(BONUS_SPEED, updateBonus, 10);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère l'insertion de nouveaux ennemis

void updateNewBonus(int valeur)
{
	if(startgame==true)
	{ 
		bonus_objet new = createBonus((&mX));
		insertionBonus(b, new);
	}
	
	glutPostRedisplay();
	glutTimerFunc(10000/BONUS_PER_TEN_SECOND, updateNewBonus, 11);
	
}


// ---------------------------------------------------------------------------------- //

// timer qui gère les suppressions d'ennemis

void updateDeleteBonus(int valeur)
{
	if(startgame==true)
	{ 
		if (b->first != NULL || b->last != NULL)
		{
			suppressionBonus(b, false);
		}

	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteBonus, 11);
}


                    /********
                     * TIRS *
                     ********/


// timer qui gère le défilement des tirs alliés si la partie est en cours

void updateTirsHero(int valeur)
{
	if(startgame==true)
	{ 
			// range max = s'arrête en bout de map, se voit supprimer

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
	glutTimerFunc(1, updateTirsHero, 4);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère le défilement des tirs ennemis

void updateTirsEnemy(int valeur)
{
	

	if(startgame==true){ 

		shoot = te->first;
		
		if (te->first != NULL)
		{

			/*int a = rand()% 10;
			if(a == 5)
			{
				SHOOT_ENEMY = true;
			}*/
			printf("shoot->pos.y : %lf\n", shoot->pos.y);
			if(SHOOT_ENEMY == true)
			{
				printf("--------- true !\n ------------- ");
			}
			else if(SHOOT_ENEMY == false)
			{
				printf("false !\n");
			}
			shoot->pos.y -= 1;
			if (shoot->pos.y <= 0)
			{
				shoot->active = false;
			}
			while (shoot->next != NULL)
			{
				shoot = shoot->next;
				shoot->pos.y -= 1;
				if (shoot->pos.y <= 0)
				{
					shoot->active = false;
				}
			}
		}
		
		

	}
	glutPostRedisplay();
	glutTimerFunc(1, updateTirsEnemy, 13);
}

// ---------------------------------------------------------------------------------- //

// timer qui gère les suppressions des tirs alliés et ennemis

void updateDeleteTirs(int valeur)
{
	if(startgame==true){ 

	if (t->first != NULL || t->last != NULL)
	{
		suppressionTirsHero(t, test);
	}
	if (te->first != NULL || te->last != NULL)
	{
		suppressionTirsEnemy(te, test);
	}
	}
	glutPostRedisplay();
	glutTimerFunc(10, updateDeleteTirs, 6);
}
