#include <stdio.h>
#include <stdlib.h>
#include "characters.h"
#include "menus_graphics.h"
#include "game_graphics.h"

bool wrapAround;
int direction;

GLfloat xwcMin, xwcMax;
GLfloat ywcMin, ywcMax;

int xPos;
int yPos;

int mX;
int mY;

int tick;


List new_character(void)
{
	return NULL;
}

// --------------------------------------------------------------------- //


bool is_empty_list(List li)
{
	if(li == NULL)
		return true;

	return false;
}

// --------------------------------------------------------------------- //

void print_character(List Hero)
{
	if(is_empty_list(Hero))
	{
		printf("Rien a afficher, il n'y a pas Hero personnages.\n");
		return;
	}

	while(Hero != NULL)
	{
		printf("\n");
		printf("Personnage principal : \n");
		printf("[%d vies] \n", Hero->health);
		printf("[%d points d'attaque] \n", Hero->attack);
		printf("[%d d'abcisse] \n", Hero->x_pos);
		printf("[%d d'ordonnée] \n", Hero->y_pos);
		printf("[%d point d'expériences] \n", Hero->current_xp);

		if(Hero->weapon_type == 1){
			printf("[Canon à bulles] \n");
		}else{
			printf("[Fusil] \n");

		}


		Hero = Hero->next;
	}

	printf("\n");
}



// --------------------------------------------------------------------- //


List delete_end_list(List li)
{
	if(is_empty_list(li))
		return new_character();

	//Si la liste n'a qu'un seul élément
	if(li->next == NULL)
	{
		free(li);
		li = NULL;

		return new_character();
	}

	Hero *temp = li;
	Hero *before = li;

	while(temp->next != NULL)
	{
		before = temp;
		temp = temp->next;
	}

	before->next = NULL;

	free(temp);
	temp = NULL;

	return li;
}

// --------------------------------------------------------------------- //

List delete_start_list(List li)
{
	Hero *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	if(is_empty_list(li))
		return new_character();

	element = li->next;

	free(li);
	li = NULL;

	return element;
}

// --------------------------------------------------------------------- //

List clear_list(List li)
{
	if(is_empty_list(li))
		return new_character();

	while(li != NULL)
		li = delete_start_list(li);

	return li;
}




// --------------------------------------------------------------------- //


List create_Hero(List li)
{
	Hero *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		printf("Erreur\n");
		exit(EXIT_FAILURE);
	}

	printf("Nombre de vies : ");
	scanf("%d", &element->health);
	printf("Nombre de points d'attaque : ");
	scanf("%d", &element->attack);
	printf("Position x  : ");
	scanf("%d", &element->x_pos);
	printf("Position y : ");
	scanf("%d", &element->y_pos);
	printf("Nombre d'xp' : ");
	scanf("%d", &element->current_xp);
	printf("Type d'arme (1 : canon à bulle ||  2 : fusil) : ");
	scanf("%d", &element->weapon_type);
	element->next = NULL;

	if(is_empty_list(li))
		return element;

	Hero *temp;
	temp = li;

	while(temp->next != NULL)
		temp = temp->next;

	temp->next = element;

	return li;
}
/*
	element->health = 10;
	element->attack = 15;
	element->x_pos = 315;
	element->y_pos = 225;
	element->current_xp = 0;
	element->weapon_type = 1; //1 = canon à bulles || 2 = fusil// enum?
*/

// ------------------------------------------------------------------ //


void HeroCharacter(int direction) {
    int r = 50;

     glPushMatrix();
      while (direction--) {
       glRotatef(90, 0, 0, -1);
      } // permet de changer d'angle lorsqu'on change de direction
    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    int detail = 30;
   // int startPoint = 15 * sin(tick / 15);
    for (int i = 0; i < detail; i++) {
        double deg = (i * (360 - 2 * 1) / detail) + 0;
        double x = r * cos(deg * 3.14 / 180);
        double y = r * sin(deg * 3.14 / 180);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

// ------------------------------------------------------------------ //

void updatePos(int direction) {
    const int SPEED = 1;
    switch (direction) {
    case 0:
        if (xPos < xwcMax + 2 || wrapAround)
            xPos += SPEED;
        break;
    case 1:
        if (yPos > -2 || wrapAround)
            yPos -= SPEED;
        break;
    case 2:
        if (xPos > -2 || wrapAround)
            xPos -= SPEED;
        break;
    case 3:
        if (yPos < ywcMax + 2 || wrapAround)
            yPos += SPEED;
        break;
    };
    if (wrapAround) {
        xPos = (xPos + 600) % 600;
        yPos = (yPos + 600) % 600;
    }
}

