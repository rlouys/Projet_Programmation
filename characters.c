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
			
				x = i;
				y = j;
			}
		}
	}

	p = malloc(sizeof(player));
	p->vie = 3;
	p->pos.x = x;
	p->pos.y = y;

	return p;
}


// ------------------------------------------------------------------ //

void moveUp(player p)		//la fonction va vérifier si on peut se déplacer vers la gauche et le faire le cas échéant
{
	int x = 0, y = 0;

	x = p->pos.x;
	y = p->pos.y+1;
     
	if (*(*(map + x) + y)!='#')
	{
		p->pos.y = y;
	}

}

// ------------------------------------------------------------------ //

void moveDown(player p)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;
	
	x = p->pos.x;
	y = p->pos.y-1;

     	if (*(*(map + x) + y)!='#' )
	{
		p->pos.y = y;
	}
	
}

// ------------------------------------------------------------------ //

void moveRight(player p)
{
 int  x = 0, y = 0;
      
x = p->pos.x-1;
y = p->pos.y;


if (*(*(map + x) + y)!='#')
 {
	p->pos.x = x;
  }     

}

// ------------------------------------------------------------------ //

void moveLeft(player p)
{
 int  x = 0, y = 0;

   x = p->pos.x+1;
   y = p->pos.y;
  
   
   if (*(*(map + x) + y) !='#')
      {
	p->pos.x = x;
      }
}

// ------------------------------------------------------------------ //

