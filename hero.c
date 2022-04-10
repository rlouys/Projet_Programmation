/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*** FILES ***/

#include "hero.h"
#include "menus_graphics.h"
#include "game_graphics.h"

/*** FUNCTIONS ***/

// ------------------------------------------------------------------ //

// Initialize the hero and initialize its stats

Hero createHero(int *maxX, int *maxY)
{
	Hero hero;

	int x = 0, y = 0;

	for (int i = 0; i < *maxX; ++i)
	{
		for (int j = 0; j < *maxY; ++j)
		{
			if(*(*(map + i) + j) == 'X')
			{
				x = j;
				y = i;
			}
		}
	}

	// Stats initialisation
	hero = malloc(sizeof(Hero));
	hero->health = 3;
	hero->pos.x = x;
	hero->pos.y = y;
	hero->current_xp = 0;
	//hero->weapon_type = 0;
	hero->attack = 1;
	hero->killed = 0;

	return hero;
}


// ------------------------------------------------------------------ //

// Verify if the hero can move up or not

void moveUp(Hero hero)		
{
	int y = 0;

	y = hero->pos.y+1;
     	
	if (hero->pos.y < 11)
	{
		hero->pos.y = y;
	}
	/*printf("*** hero->pos.y : %i ***\n", hero->pos.y);
	printf("char : %c\n", *(*(map + y) + x));
	printf("---------------------\n");*/
}

// ------------------------------------------------------------------ //

// Verify if the hero can move down or not

void moveDown(Hero hero)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;
	
	x = hero->pos.x;
	y = hero->pos.y-1;

     	if (*(*(map + y) + x)!='#' )
	{
		hero->pos.y = y;
	}
	//printf("char : %c\n", *(*(map + y) + x));
}

// ------------------------------------------------------------------ //

// Verify if the hero can move right or not

void moveRight(Hero hero)
{
	int  x = 0, y = 0;
		
	x = hero->pos.x+1;
	y = hero->pos.y;

	if (*(*(map + y) + x)!='@')
	{
		hero->pos.x = x;
	}     
	
	//printf("char : %c\n", *(*(map + y) + x));
}

// ------------------------------------------------------------------ //

// Verify if the hero can move left or not

void moveLeft(Hero hero)
{
	int  x = 0, y = 0;

	x = hero->pos.x-1;
	y = hero->pos.y;

	if (*(*(map + y) + x) !='#')
	{
		hero->pos.x = x;
	}
	//printf("char : %c\n", *(*(map + y) + x));
}

// ------------------------------------------------------------------ //

