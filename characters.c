/*** LIBS ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "characters.h"
#include "menus_graphics.h"
#include "game_graphics.h"

/*** VARIABLES ***/

int xPos;
int yPos;
int mX;
int mY;


/*** FUNCTIONS ***/

// ------------------------------------------------------------------ //
player createPlayer(int *maxX, int *maxY)
{
	player p;


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

	p = malloc(sizeof(player));
	p->vie = 3;
	p->pos.x = x;
	p->pos.y = y;
	p->current_xp = 0;
	//p->weapon_type = 0;
	p->attack = 1;

	return p;
}


// ------------------------------------------------------------------ //

void moveUp(player p)		//la fonction va vérifier si on peut se déplacer vers la gauche et le faire le cas échéant
{
	int x = 0, y = 0;

	x = p->pos.x;
	y = p->pos.y+1;
     
	
	if (p->pos.y < 11)
	{
		p->pos.y = y;
	}
		printf("*** p->pos.y : %i ***\n", p->pos.y);

	  		  printf("char : %c\n", *(*(map + y) + x));
				printf("---------------------\n");

}

// ------------------------------------------------------------------ //

void moveDown(player p)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;
	
	x = p->pos.x;
	y = p->pos.y-1;

     	if (*(*(map + y) + x)!='#' )
	{
		p->pos.y = y;
	}
		printf("char : %c\n", *(*(map + y) + x));

}

// ------------------------------------------------------------------ //

void moveRight(player p)
{
 int  x = 0, y = 0;
      
x = p->pos.x+1;
y = p->pos.y;


if (*(*(map + y) + x)!='@')
 {
	p->pos.x = x;
  }     
	  		  printf("char : %c\n", *(*(map + y) + x));

}

// ------------------------------------------------------------------ //

void moveLeft(player p)
{
 int  x = 0, y = 0;

   x = p->pos.x-1;
   y = p->pos.y;
  
   
   if (*(*(map + y) + x) !='#')
      {
	p->pos.x = x;
      }

	  
	  		  printf("char : %c\n", *(*(map + y) + x));

}

// ------------------------------------------------------------------ //

