#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "basic.h"
#endif



int main(int argc, char *argv[])
{
	init();
	srand(time(0));

	 //would make the below a 2d array but I don't have time to test that theory
	char *pathmon = malloc(sizeof(char) * 50);
	char *pathitem = malloc(sizeof(char) * 50);
	char *patharmour = malloc(sizeof(char) * 50);
	char *pathweapon = malloc(sizeof(char) * 50);
	char *pathclass = malloc(sizeof(char) * 50);
	char *modpath = malloc(sizeof(char) * 50);
	creature *player = malloc(sizeof(creature));
	int choice = 'r';
	
	
		
		strcpy(pathmon, "monsters.txt");
		strcpy(pathitem, "items.txt");
		strcpy(patharmour, "armour.txt");
		strcpy(pathclass, "classes.txt");
		strcpy(pathweapon, "weapons.txt");
		if(argv[1])
		{
			strcpy(modpath, argv[1]);
		}
		else
		{
			strcpy(modpath, "standard");
		}
		chdir("data");
		chdir(modpath);
		
		FILE *monsters = fopen(pathmon,"r");
		FILE *items = fopen(pathitem,"r");
		FILE *armour =  fopen(patharmour, "r");
		FILE *weapons = fopen(pathweapon, "r");
		FILE *class = fopen(pathclass, "r");
		
	player->name = malloc(sizeof(char) * 40);
	player->weaponname = malloc(sizeof(char) * 40);
	player->weaponverb = malloc(sizeof(char) * 40);
	player->armourname = malloc(sizeof(char) * 40);
	player->itemname = malloc(sizeof(char) * 40);
	player->classname = malloc(sizeof(char) * 40);
	printw("Please enter your name, or LOAD to Load : ");
	scanw("%s", player->name);
	
	if(strstr(player->name, "LOAD"))
	{
		if(load(player,weapons,armour,items,monsters,modpath) == 1)
		{
			goto endgamefromload; // dijstra would be proud
		}
	
	}
	
	
	

	while(choice == 'r')
	{
		create_player(player,weapons,armour,items);
		printw("\nName: %s\n", player->name);
		printw("You are carrying a %s that does %c damage, this %s with %dd%d damage\n\n",player->weaponname, player->kind, player->weaponverb, player->weapondice, player->weaponvalue);
		printw("You are wearing a %s that provides %d protection from regular attacks\n\n", player->armourname, player->armourvalue);
		printw("The other item that you carry is an %s, and has : %d hp impact; %d xp impact and %d armour impact\n\n", player->itemname, player->itemhp, player->itemxp, player->itemarmour);
		printw("This Is You NOW, Now please enter the ARENA of Generica!\n\n Please press any key to continue or press r to reroll");
		choice = getch();
		clearscr();
	}
	classselect(player,class);
	mainmenu(player,weapons,armour,items,monsters, modpath);
	
	endgamefromload:
	
		destroy_creature(player);
		deinit();


	return 0;
}
