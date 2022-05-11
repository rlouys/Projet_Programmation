/*** LIBS ***/

#include "timers_and_effects.h"
#include "game_graphics.h"
#include "game.h"
#include "enemies.h"
#include "tirs.h"
#include "hero.h"
#include "menus_graphics.h"



/*** CONSTANTES ***/

#define RANGE_MAX 90
#define ATTACK_SPEED 1 // 1 is superfast, 1000 is slow
#define MAX_SCORE 100000
#define BLACK 1, 1, 1

/*** VARIABLES ***/

int mX;
int mY;
int level;
int counter = 0;
int OBSTACLE_SPEED = 60;
int ENNEMI_SPEED = 60;
int OBSTACLES_PER_HUNDRED_SECOND = 20;
int ENNEMI_PER_HUNDRED_SECOND = 20;
int BONUS_SPEED = 60;
int BONUS_PER_HUNDRED_SECOND = 20;
int randomness = 0;
int saved_health;
int saved_attack;
int lock = 0;

float r = 1;
float g = 0;
float bl = 0;
float vl = 20.0;
float *value = &vl;
float *deplacement_fenetre;
float difficulty;
float car_speed = 0.0;

bool startgame;
bool endmap;
bool SHOOT_ENEMY; // from game.c
bool CHECKCOLLISION = false;
bool cheatMode;

bool cheatMode_pressed = false;
bool RED;
bool PURPLE;
bool GOLD;
bool BONUS;


/*** FUNCTIONS ***/

// ------------------------------------------------------------ // 

// vérifie s'il y a une collision entre l'ennemi et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsEnnemis (enemy en, tir_Struct w)
{	
	bool Collide = false;
	int key = 1;


	// condition de collision

	if(cheatMode == false && hero->ulti_active == 0)
	{
		if ((w->pos.x/2) == en->pos.x && en->pos.y <= ((w->pos.y-2)/2)+1.5 && key != 0)
			{
				Collide = true;
				key = 0; // pour n'enlever qu'une fois de la vie
			}
	}
	else if(cheatMode == true || hero->ulti_active == 1)
	{										//-> ENNEMI ==   x
		if (((w->pos.x/2) == en->pos.x+2 || // -> TIRS ==  xxxxx
		    (w->pos.x/2) == en->pos.x+1 ||
			(w->pos.x/2) == en->pos.x ||
			(w->pos.x/2) == en->pos.x-1 ||
			(w->pos.x/2) == en->pos.x-2) &&
			en->pos.y <= ((w->pos.y-2)/2)+1.5 && key != 0)
			{
				Collide = true;
				key = 0; // pour n'enlever qu'une fois de la vie
			}
	}
	
	if (Collide)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		// seulement si c'est le 'gun' et pas le bubble
		if(w->type == 0)
		{
			// si collision, l'ennemi perd de la vie à hauteur du nombre
			// de point d'attaque du héro
			en->vie = (en->vie) - hero->attack;

			// si l'ennemi n'a plus de vie, il passe à désactivé, pour suppression
			// le compteur d'ennemis tué est incrémenté
			if(en->vie <= 0)
			{
				en->active = false;
				hero->killed += 1;
				if(en->color == 2)
				{
					hero->gold_killed += 1;
				}
				else if(en->color == 1)
				{
					hero->purple_killed += 1;
				}
				else if(en->color == 0){
					hero->red_killed += 1;
				}
			}
		}
			// si bubble, alors ralenti
			if(w->type == 1)
			{
				en->slowness = 1;
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
	if( (en->pos.x == hero->pos.x) && (((en->pos.y) <= hero->pos.y +0.1) && ((en->pos.y) > hero->pos.y -1))   && key != 0)

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
		if(key == 0)
		{
			// si collision entre allié et ennemi
			// le héro perd de la vie, l'ennemi aussi
			// le héro perd son bonus
			hero->health -= 1;
			en->pos.y -= 0.5;
			en->vie -=1;
			hero->bonus_active = 0;

			// le héro perd 1 bonus d'attaque
			if(hero->attack > 5)
			{
				hero->attack -= 1;
			}

		
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
	
} 


// ------------------------------------------------------------ // 

// vérifie s'il y a une collision entre l'obstacle et le tir allié, le cas échéant, lui enlève de la vie ou le supprime, et augmente le score
void checkCollisionTirsObstacles (obstacles o, tir_Struct w)
{	
	bool CollideO = false;
	int key = 1;


	if(cheatMode == false && hero->ulti_active == 0)
	{
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
	}
	else if(cheatMode == true || hero->ulti_active == 1)
	{

		if (((
			(((w->pos.x/2) == o->pos.x+2) ||
			((w->pos.x/2) == o->pos.x+1) ||
			((w->pos.x/2) == o->pos.x) ||
			((w->pos.x/2) == o->pos.x-1) ||
			((w->pos.x/2) == o->pos.x-2)) 

		&& (o->pos.y <= (((w->pos.y-2)/2)+1.5))) /**/ 
		||  ((((w->pos.x/2)) == (o->pos.x+1)) && (o->pos.y <=  (((w->pos.y-2)/2)+1.5)))
		
		||  ((((w->pos.x/2)) == (o->pos.x-1)) && (o->pos.y <=  (((w->pos.y-2)/2)+1.5))))
		&& key != 0)

		{
				CollideO = true;
				key = 0;
		}


	}

	if (CollideO)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	

		
			// si un tir touche un obstacle, il est supprimé (le tir)
			w->active = false;
		
		if(cheatMode == false && hero->ulti_active == 0)
		{
			if (w->type == true)
			{
				o->jailed = true;
			}
			if(w->type == false && o->jailed == true)
			{
				o->active = false;
			}
		}
		else if(cheatMode == true || hero->ulti_active == 1)
		{
			
			o->active = false;
		}





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
					// pour collision unique fois
					key = 1;
					hero->bonus_active = 0;


					// le héro perd 1 bonus d'attaque
					if(hero->attack > 5)
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
void checkCollisionTirsBonus (bonus_objet bns, tir_Struct w)
{	
	bool Collide = false;
	int key = 1;

	// condition de collision entre les tirs et les objets bonus
	if (    (((w->pos.x/2) >= bns->pos.x-1) && ((w->pos.x/2) < bns->pos.x+1))                 && bns->pos.y <= ((w->pos.y-2)/2)+1.5 && key != 0)
		{
			Collide = true;
			key = 0;
			
		}

	if (Collide && key == 0)

	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{	
		if(key == 0)
		{
			if(w->type == true) // canon à bulles
			{
				hero->bonus_active = 1;
				// si collision
				// le hero gagne des point d'attaque 
				// le hero récupère de la santé
				if(BONUS == true)
				{
					hero->attack += 1;
					if(hero->health <= 14)
					{
						hero->health += 1;
					}
					else
					{
						hero->health = 15;
					}

					// gestion de l'ulti, si 9 tirs d'ulti sur un ennemi, alors repasse en attaque normale
					b->qtyToUlti += 1;

					if((b->qtyToUlti+1)%10 == 0)
					{
						hero->ulti_active = 1;
						b->qtyToUlti = 0;
					}
					if(hero->ulti_active == 1)
					{
						if((b->qtyToUlti+1)%10 == 0)
						{
							hero->ulti_active = 0;
						}
					}

					BONUS = false;
				}
				drawHealth(hero);
			}
			
			// le bonus est désactivé pour suppression
			bns->active = false;

			// le tir est désactivé pour suppression
			w->active = false;

			// tous les 10 bonus, le héro a une ulti pour 10 kills
			
			CHECKCOLLISION = false;
		}
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
		// le hero gagne des point d'attaque 
		// le hero récupère de la santé
		hero->attack += 1;
		if(hero->health <= 14)
		{
			hero->health += 1;
		}
		else
		{
			hero->health = 15;
		}
		drawHealth(hero);

		hero->ulti_killed += 1;
				// tous les 10 bonus, le héro a une ulti pour 10 kills
		if((b->qtyToUlti+1)%10 == 0)
		{
			hero->ulti_active = 1;
			hero->ulti_killed = 0;
		}

		if((hero->ulti_killed+1)%10 == 0)
		{
			hero->ulti_active = 0;
			hero->ulti_killed = 0;
		}


		

		// l'objet est désactivé pour suppression
		bns->active = 0;
		
		// réinitialisation du booléen de collision
		CHECKCOLLISION = false;
	}
	
} 

// ---------------------------------------------------------------------------------- //

void wait1()
{
    int timerwait;

    for(timerwait = 0; timerwait < 700000; timerwait++)
    {
            printf("wait : %i\n", timerwait);
    }
}
// ---------------------------------------------------------------------------------- //

void setRed()
{
	r = 1;
	g = 0;
	bl = 0;
	RED = true;


}

// ---------------------------------------------------------------------------------- //

// set rgb to gold
void setGold()
{
	r = 0.855;
	g = 0.647;
	bl = 0.125;
	GOLD = true;

}

// ---------------------------------------------------------------------------------- //


// set rgb to purple
void setPurple()
{
	r = 0.502;
	g = 0;
	bl = 0.502;
	PURPLE = true;


}

// ---------------------------------------------------------------------------------- //

// set rgb to purple or gold randomly
void setPurpleOrGold()
{
	int a = rand()%1;

	if(a == 0)
	{
		setGold();
	}
	else
	{
		setPurple();
	}
}

// ---------------------------------------------------------------------------------- //

void setLevel()
{
		/*** DIFFICULTY 1 ***/


		if(difficulty == 0 && level == 1)
		{
			ENNEMI_PER_HUNDRED_SECOND = 10;
			OBSTACLES_PER_HUNDRED_SECOND = 10;
			BONUS_PER_HUNDRED_SECOND = 20;
			randomness = 1;
			setRed();

			if(hero->current_xp >= 400)
			{
				level = 2;
			}
		}
		else if(difficulty == 0 && level == 2)
		{
			ENNEMI_PER_HUNDRED_SECOND = 15;
			OBSTACLES_PER_HUNDRED_SECOND = 15;
			BONUS_PER_HUNDRED_SECOND = 20;
			randomness = 10;
			car_speed = 0.025;

			if(hero->current_xp >= 900)
			{
				level++;
				setPurple();

			}

		}
		else if(difficulty == 0 && level == 3)
		{
			ENNEMI_PER_HUNDRED_SECOND = 17;
			OBSTACLES_PER_HUNDRED_SECOND = 17;
			BONUS_PER_HUNDRED_SECOND = 20;
			randomness = 20;
			car_speed = 0.0325;


			setPurple();
			
			if(hero->current_xp >= 1600)
			{
				level++;

			}
		}
		else if(difficulty == 0 && level == 4)
		{
			ENNEMI_PER_HUNDRED_SECOND = 19;
			OBSTACLES_PER_HUNDRED_SECOND = 19;
			BONUS_PER_HUNDRED_SECOND = 15;
			randomness = 35;
			car_speed = 0.042;
			setPurpleOrGold();
			
			
			if(hero->current_xp >= 2500)
			{
				level++;
			}

		}
		else if(difficulty == 0 && level == 5)
		{
			ENNEMI_PER_HUNDRED_SECOND = 22;
			OBSTACLES_PER_HUNDRED_SECOND = 22;
			BONUS_PER_HUNDRED_SECOND = 15;
			randomness = 50;
			car_speed = 0.05;
			setGold();
		}





		/*** DIFFICULTY 2 ***/


		if(difficulty == 1 && level == 1)
		{
			ENNEMI_PER_HUNDRED_SECOND = 15;
			OBSTACLES_PER_HUNDRED_SECOND = 15;
			BONUS_PER_HUNDRED_SECOND = 18;
			randomness = 40;
			car_speed = 0.03;

			setRed();

			if(hero->current_xp >= 400)
			{
				level++;
			}
		}
		else if(difficulty == 1 && level == 2)
		{
			ENNEMI_PER_HUNDRED_SECOND = 17;
			OBSTACLES_PER_HUNDRED_SECOND = 17;
			BONUS_PER_HUNDRED_SECOND = 18;
			randomness = 45;
			car_speed = 0.035;

			setPurple();

			if(hero->current_xp >= 900)
			{
				level++;
			}

		}
		else if(difficulty == 1 && level == 3)
		{
			ENNEMI_PER_HUNDRED_SECOND = 22;
			OBSTACLES_PER_HUNDRED_SECOND = 22;
			BONUS_PER_HUNDRED_SECOND = 15;
			randomness = 50;
			car_speed = 0.05;

			setPurpleOrGold();

			if(hero->current_xp >= 1600)
			{
				level++;
			}
		}
		else if(difficulty == 1 && level == 4)
		{
			ENNEMI_PER_HUNDRED_SECOND = 25;
			OBSTACLES_PER_HUNDRED_SECOND = 25;
			BONUS_PER_HUNDRED_SECOND = 15;
			randomness = 55;
			car_speed = 0.06;

			setPurpleOrGold();

			if(hero->current_xp >= 2500)
			{
				level++;
			}

		}
		else if(difficulty == 1 && level == 5)
		{
			ENNEMI_PER_HUNDRED_SECOND = 30;
			OBSTACLES_PER_HUNDRED_SECOND = 30;
			BONUS_PER_HUNDRED_SECOND = 15;
			randomness = 60;
			car_speed = 0.08;

			setGold();
		}





		/*** DIFFICULTY 3 ***/


		if(difficulty == 2 && level == 1)
		{
			ENNEMI_PER_HUNDRED_SECOND = 20;
			OBSTACLES_PER_HUNDRED_SECOND = 20;
			BONUS_PER_HUNDRED_SECOND = 15;
			randomness = 40;
			car_speed = 0.05;

			setRed();

			if(hero->current_xp >= 400)
			{
				level++;
			}
		}
		else if(difficulty == 2 && level == 2)
		{
			ENNEMI_PER_HUNDRED_SECOND = 23;
			OBSTACLES_PER_HUNDRED_SECOND = 23;
			BONUS_PER_HUNDRED_SECOND = 15;
			randomness = 45;
			car_speed = 0.06;

			setPurple();

			if(hero->current_xp >= 900)
			{
				level++;
			}

		}
		else if(difficulty == 2 && level == 3)
		{
			ENNEMI_PER_HUNDRED_SECOND = 27;
			OBSTACLES_PER_HUNDRED_SECOND = 27;
			BONUS_PER_HUNDRED_SECOND = 13;
			randomness = 50;
			car_speed = 0.08;

			setPurpleOrGold();


			if(hero->current_xp >= 1600)
			{
				level++;
			}
		}
		else if(difficulty == 2 && level == 4)
		{
			ENNEMI_PER_HUNDRED_SECOND = 30;
			OBSTACLES_PER_HUNDRED_SECOND = 30;
			BONUS_PER_HUNDRED_SECOND = 13;
			randomness = 60;
			car_speed = 0.10;

			setGold();

			if(hero->current_xp >= 2500)
			{
				level++;
			}

		}
		else if(difficulty == 2 && level == 5)
		{
			ENNEMI_PER_HUNDRED_SECOND = 35;
			OBSTACLES_PER_HUNDRED_SECOND = 35;
			BONUS_PER_HUNDRED_SECOND = 12;
			randomness = 70;
			car_speed = 0.12;

			setGold();

		}




		/*** DIFFICULTY 4 ***/

		if(difficulty == 3 && level == 1)
		{
			ENNEMI_PER_HUNDRED_SECOND = 20;
			OBSTACLES_PER_HUNDRED_SECOND = 20;
			BONUS_PER_HUNDRED_SECOND = 10;
			randomness = 80;
			car_speed = 0.08;

			setPurple();

			if(hero->current_xp >= 400)
			{
				level++;
			}
		}
		else if(difficulty == 3 && level == 2)
		{
			ENNEMI_PER_HUNDRED_SECOND = 25;
			OBSTACLES_PER_HUNDRED_SECOND = 25;
			BONUS_PER_HUNDRED_SECOND = 10;
			randomness = 84;
			car_speed = 0.10;

			setPurpleOrGold();
			
			if(hero->current_xp >= 900)
			{
				level++;
			}

		}
		else if(difficulty == 3 && level == 3)
		{
			ENNEMI_PER_HUNDRED_SECOND = 35;
			OBSTACLES_PER_HUNDRED_SECOND = 35;
			BONUS_PER_HUNDRED_SECOND = 10;
			randomness = 88;
			car_speed = 0.13;

			
			setGold();

			if(hero->current_xp >= 1600)
			{
				level++;
			}
		}
		else if(difficulty == 3 && level == 4)
		{
			ENNEMI_PER_HUNDRED_SECOND = 37;
			OBSTACLES_PER_HUNDRED_SECOND = 37;
			BONUS_PER_HUNDRED_SECOND = 10;
			randomness = 92;
			car_speed = 0.20;

			setGold();

			if(hero->current_xp >= 2500)
			{
				level++;
			}

		}
		else if(difficulty == 3 && level == 5)
		{
			ENNEMI_PER_HUNDRED_SECOND = 40;
			OBSTACLES_PER_HUNDRED_SECOND = 40;
			BONUS_PER_HUNDRED_SECOND = 10;
			randomness = 80;
			car_speed = 0.25;


			setGold();


		}
		

}

// ------------------------------------------------------------------------------------------------------------- //




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
	int key = 1;

	if(key == 1)
	{
		if (b->first != NULL && t->first != NULL)
		{
			checkCollisionTirsBonus(bonus, Sht);
			key = 0;
			if (t->first->next != NULL)
				{
					Sht = Sht->next;	
					checkCollisionTirsBonus(bonus, Sht);
					key = 0;

					
					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsBonus(bonus, Sht);
						key = 0;

					}
				}
			if (b->first->next != NULL)
			{
				bonus = bonus->next;
				Sht = t->first;
				checkCollisionTirsBonus(bonus, Sht);
				key = 0;

				if (t->first->next != NULL)
				{
					Sht = Sht->next;
					checkCollisionTirsBonus(bonus, Sht);
					key = 0;

					while (Sht->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsBonus(bonus, Sht);
						key = 0;

					}
				}
				while (bonus->next != NULL)
				{
					bonus = bonus->next;
					Sht = t->first;
					checkCollisionTirsBonus(bonus, Sht);
					key = 0;

					if (t->first->next != NULL)
					{
						Sht = Sht->next;
						checkCollisionTirsBonus(bonus, Sht);
						key = 0;

						while (Sht->next != NULL)
						{
							Sht = Sht->next;
							checkCollisionTirsBonus(bonus, Sht);
							key = 0;

						}
					}
				}
			}
		}
	}
	BONUS = true;

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

		// si ennemi il y a, il se déplace de 0.50 vers le bas 

		if (car != NULL)
		{
			car = setEnemyLevel(car);

			// si non ralenti 
				if(car->slowness == 0)
				{
					car->pos.y -= 0.05 + (difficulty/100) + car_speed;
				}
				// si ralenti avec bubble
				else if(car->slowness == 1)
				{
					car->pos.y -= 0.025 + (difficulty/100) + car_speed;
				}
			
			
		int z = 100-randomness;
		// déplacement aléatoire vers la position du héro
		int a = rand() % z;
					if(car->pos.y < 90 && a == 2)
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

			if (car->pos.y <= 1)
			{
				hero->current_xp -= 100;
				e->quantite--;
				hero->health -= 1;
				car->active = false;
				endmap = true;

				// le hero perd le bonus en cours	
				hero->bonus_active = 0;

				// le héro perd 1 bonus d'attaque
				if(hero->attack > 5)
				{
					hero->attack -= 1;
				}

				

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
				car = setEnemyLevel(car);


				// si non ralenti 
					if(car->slowness == 0)
					{
						car->pos.y -= 0.5 + (difficulty/100) + car_speed;
					}
					// si ralenti avec bubble
					else if(car->slowness == 1)
					{
						car->pos.y -= 0.025 + (difficulty/100) + car_speed;
					}

			
				

				// déplacement aléatoire vers la position du héro
				if(car->pos.y < 90 && a == 2)
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

				if (car->pos.y <= 1)
				{
					hero->current_xp -= 100;
					hero->health -= 1;
					car->active = false;
					e->quantite--;
					endmap = true;


					// le hero perd le bonus en cours	
					hero->bonus_active = false;

					// le héro perd 1 bonus d'attaque
					if(hero->attack > 5)
					{
						hero->attack -= 1;
					}


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
		}



	

	if(cheatMode == true)
	{	
		if(lock == 0)
		{
			saved_health = hero->health;
			saved_attack = hero->attack;
			lock = 1;
		}

		hero->attack = 999;
		hero->health = 50; 
		hero->weapon_type = 0;
	}
	else if(cheatMode == false && cheatMode_pressed == true)
	{
		hero->attack = saved_attack;
		hero->health = saved_health;;
		cheatMode_pressed = false;
	}


	
	//saveScore(hero);


	glutPostRedisplay();
	glutTimerFunc(1000/ENNEMI_SPEED, updateEnemies, 2);
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
			if(fence->jailed == false)
			{
				if(cheatMode == false)
				{
					fence->pos.y -= 0.18 + (difficulty/100);
				}
				else
				{
					fence->pos.y -= 0.15 + (difficulty/100);
				}
			}
		

			
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


			if(fence->jailed == false)
			{
				if(cheatMode == false)
				{
					fence->pos.y -= 0.18 + (difficulty/100);
				}
				else
				{
					fence->pos.y -= 0.15 + (difficulty/100);
				}			
			}
			
				
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
		}
		glutPostRedisplay();
		glutTimerFunc(1000/OBSTACLE_SPEED, updateObstacle, 7);


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


	if(startgame==true && hero->health != 0)
	{ 

		bonus = b->first;
		if (b->first != NULL)
		{
			if(cheatMode == true || hero->ulti_active == 1)
			{
			bonus->pos.x = 80;
			}

			bonus->pos.y -= 0.2;

			
			if (bonus->pos.x > 38){
				bonus->side = 1;
			}
			
			else if(bonus->pos.x < 10){
				bonus->side = 0;
			}

			if(bonus->side == 1)
			{
				bonus->pos.x -= 0.2;
			}
			
			else if(bonus->side == 0){
				bonus->pos.x += 0.2;
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

				if(cheatMode == true)
				{
					bonus->pos.x = 80;
				}

				bonus->pos.y -= 0.2;


				if (bonus->pos.x > 38){
				bonus->side = 1;
				}
				
				else if(bonus->pos.x < 10){
					bonus->side = 0;
				}

				if(bonus->side == 1)
				{
					bonus->pos.x -= 0.2;
				}

				else if(bonus->side == 0){
					bonus->pos.x += 0.2;
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
		}

		

	glutPostRedisplay();
	glutTimerFunc(1000/BONUS_SPEED, updateBonus, 10);
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
	glutTimerFunc(100000/BONUS_PER_HUNDRED_SECOND, updateNewBonus, 11);
	
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
			if(cheatMode == false)
			{
				shoot->pos.y += 3;
			}
			else if(cheatMode == true)
			{
				shoot->pos.y += 5;
			}



			


			if (shoot->pos.y >= RANGE_MAX)
			{
				shoot->active = false;
			}
			while (shoot->next != NULL)
			{
				shoot = shoot->next;

			if(cheatMode == false)
			{
				shoot->pos.y += 3;
			}
			else if(cheatMode == true)
			{
				shoot->pos.y += 5;
			}

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
	
	// gere les tirs ennemi (en construction)
	if(startgame==true){ 

		shoot = te->first;
		
		if (te->first != NULL)
		{

			/
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
