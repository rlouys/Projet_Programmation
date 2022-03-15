#ifndef __CHARACTERS_H__
#define __CHARACTERS__H__

#include <stdbool.h>



	// Définition du héro //

	typedef struct Hero
	{
		int evolution;
		int health;
		int attack;
		int x_pos;
		int y_pos;
		int current_xp;
		int weapon_type;

		struct Hero *next;
	}Hero, *List;


// --------------------------------------------- // 

	// Définition du jeu // 
/*
typedef struct Game
	{
		struct *Hero;
		struct *Ennemy;
		struct *Objects;
		struct *Weapons;
		int *scores;
		char map[width][height]; //defined as a constant

		struct Hero *next;
	}Game;

*/
// --------------------------------------------- // 



	// Fonctions //

	List new_character(void);
	bool is_empty_list(List li);
	void print_character(List li);
	int list_length(List li);
	List create_Hero(List li);
	List delete_end_list(List li);
	List delete_start_list(List li);
	List clear_list(List li);

#endif

	