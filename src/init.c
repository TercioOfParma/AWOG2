#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "basic.h"
#endif



void init()
{
	
	initscr();
	cbreak();
	echo();
	keypad(stdscr, TRUE);
	start_color();
	
	init_pair(1, COLOR_WHITE, COLOR_BLACK); //main default background
	init_pair(2, COLOR_RED, COLOR_BLACK); //bleeding text
	init_pair(3, COLOR_BLUE, COLOR_BLACK);//nerve damage text
	init_pair(4, COLOR_GREEN, COLOR_BLACK); //critical




}

void deinit()
{
	endwin();
	exit(0);



}

void create_player(creature *player, FILE *wep, FILE *armour, FILE *item)
{
	player->name = malloc(sizeof(char) * 40);
	player->weaponname = malloc(sizeof(char) * 40);
	player->weaponverb = malloc(sizeof(char) * 40);
	player->armourname = malloc(sizeof(char) * 40);
	player->itemname = malloc(sizeof(char) * 40);
	generate_weapon(player, wep);
	generate_item(player, item);
	generate_armour(player, armour);
	





}
void generate_weapon(creature *player, FILE *wep)
{
	printw("Loading Weapon\n");
	int noweapons = 50;
	int looper = 0;
	char *temphold = malloc(sizeof(char) * MAX_BYTESIZE_ITEMS);
	char *weaponname, *weaponkind, *weaponsides, *weapondie;
	fgets(temphold, MAX_BYTESIZE_ITEMS, wep);
	
	char *weapons[noweapons];

	
	while(looper < noweapons)
	{
		weapons[looper] = malloc(sizeof(char) * MAX_THINGSTRING_SIZE);
		fgets(weapons[looper], MAX_THINGSTRING_SIZE, wep);
		
		
		looper++;
	
	}
	
	int chooser = rand() % noweapons;
	int quality = rand () % 10 + 1;
	

	weaponname = strtok(weapons[chooser], ",");
	
	weaponkind = strtok(NULL, ",");
	if(strstr(weaponkind,"edge"))
	{
		player->kind = 'e';
	
	}
	else if(strstr(weaponkind,"blunt"))
	{
		player->kind = 'b';
	
	}
	
	weaponsides = strtok(NULL, ",");
	weapondie = strtok(NULL, ",");
	player->weaponvalue = atoi(weaponsides);
	player->weapondice = atoi(weapondie);
	player->weaponverb = strtok(NULL, ",");

		switch(quality)
		{
			case 1:
				strcpy(player->weaponname, "Barely Functional ");
				player->weaponvalue = player->weaponvalue / 5;
				break;
			case 2:
				strcpy(player->weaponname, "Poor ");
				player->weaponvalue = player->weaponvalue / 2;
				break;
			case 3:
				strcpy(player->weaponname, "Old ");
				player->weaponvalue = player->weaponvalue / 1.5;
				break;
			case 4:
				strcpy(player->weaponname, "Defective ");
				player->weaponvalue = player->weaponvalue - 1;
				break;
			case 5:
				strcpy(player->weaponname, "Average ");
				break;
			case 6:
				strcpy(player->weaponname, "Well Designed ");
				player->weaponvalue = player->weaponvalue + 1;
				break;
			case 7:
				strcpy(player->weaponname, "Great ");
				player->weaponvalue = player->weaponvalue * 1.5;
				break;
			case 8:
				strcpy(player->weaponname, "Fantastic ");
				player->weaponvalue = player->weaponvalue * 2;
				break;
			case 9:
				strcpy(player->weaponname, "Masterwork ");
				player->weaponvalue = player->weaponvalue * 5;
				break;
			case 10:
				strcpy(player->weaponname, "Artifact ");
				player->weaponvalue = player->weaponvalue * 10;
				break;
			default:
				strcpy(player->weaponname, "Average");
				break;
		}
		strcat(player->weaponname, weaponname);
		looper = 0;
		while(looper < noweapons)
		{
		
			free(weapons[looper]);
			looper++;
		
		}

}

void generate_item(creature *player, FILE *item)
{
	char *itemname, *hpimp, *xpimp, *armourimp;
	char *temphold = malloc(sizeof(char) * MAX_BYTESIZE_ITEMS);
	int looper = 0;
	int noitems = 50;
	
	fgets(temphold,MAX_BYTESIZE_ITEMS,item);
	noitems = atoi(temphold);
	
	char *items[noitems];
	
	
	while(looper < noitems)
	{
		items[looper] = malloc(sizeof(char) * MAX_THINGSTRING_SIZE);
		fgets(items[looper], MAX_THINGSTRING_SIZE, item);
	
		looper++;
	}
	int chooser = rand() % noitems;
	int quality = rand () % 10 + 1;
	
	
	itemname = strtok(items[chooser],",");
	
	hpimp = strtok(NULL,",");
	xpimp = strtok(NULL,",");
	armourimp = strtok(NULL,",");
	
	
	player->itemhp = atoi(hpimp);
	player->itemxp = atoi(xpimp);
	player->itemarmour = atoi(armourimp);
	
	switch(quality)
	{
			case 1:
				strcpy(player->itemname, "Barely Functional ");
				player->itemhp = player->itemhp / 5;
				player->itemxp = player->itemxp / 5;
				player->itemarmour = player->itemarmour / 5;
				break;
			case 2:
				strcpy(player->itemname, "Poor ");
				player->itemhp = player->itemhp / 2;
				player->itemxp = player->itemxp / 2;
				player->itemarmour = player->itemarmour / 2;
				break;
			case 3:
				strcpy(player->itemname, "Old ");
				player->itemhp = player->itemhp / 1.5;
				player->itemxp = player->itemxp / 1.5;
				player->itemarmour = player->itemarmour / 1.5;
				break;
			case 4:
				strcpy(player->itemname, "Defective ");
				player->itemhp = player->itemhp - 1;
				player->itemxp = player->itemxp - 1;
				player->itemarmour = player->itemarmour - 1;
				break;
			case 5:
				strcpy(player->itemname, "Average ");
				break;
			case 6:
				strcpy(player->itemname, "Well Designed ");
				player->itemhp = player->itemhp + 1;
				player->itemxp = player->itemxp + 1;
				player->itemarmour = player->itemarmour + 1;
				break;
			case 7:
				strcpy(player->itemname, "Great ");
				player->itemhp = player->itemhp * 1.5;
				player->itemxp = player->itemxp * 1.5;
				player->itemarmour = player->itemarmour * 1.5;
				break;
			case 8:
				strcpy(player->itemname, "Fantastic ");
				player->itemhp = player->itemhp * 2;
				player->itemxp = player->itemxp * 2;
				player->itemarmour = player->itemarmour * 2;
				break;
			case 9:
				strcpy(player->itemname, "Masterwork ");
				player->itemhp = player->itemhp * 5;
				player->itemxp = player->itemxp * 5;
				player->itemarmour = player->itemarmour * 5;
				break;
			case 10:
				strcpy(player->itemname, "Artifact ");
				player->itemhp = player->itemhp * 10;
				player->itemxp = player->itemxp * 10;
				player->itemarmour = player->itemarmour * 10;
				break;
			default:
				strcpy(player->itemname, "Average");
				break;
		}
		strcat(player->itemname, itemname);
		looper = 0;
		while(looper < noitems)
		{
		
			free(items[looper]);
			looper++;
		
		}
}

void generate_armour(creature *player, FILE *armour)
{
		char *armourname, *armourvalue, *temphold;
		int looper = 0;
		int noarmour = 0;
		temphold = malloc(sizeof(char) * MAX_BYTESIZE_ITEMS);
		fgets(temphold, MAX_BYTESIZE_ITEMS, armour);
		noarmour = atoi(temphold);
		
		char *armours[noarmour];
		
		while(looper < noarmour)
		{
		
			armours[looper] = malloc(sizeof(char) * MAX_THINGSTRING_SIZE);
			fgets(armours[looper], MAX_THINGSTRING_SIZE, armour);
			looper++;
		
		}
		int chooser = rand() % noarmour;
		int quality = rand () % 10 + 1;

		armourname = strtok(armours[chooser],",");
		armourvalue = strtok(NULL,",");
		player->armourvalue = atoi(armourvalue);
		
		switch(quality)
		{
			case 1:
				strcpy(player->armourname, "Barely Functional ");
				player->armourvalue = player->armourvalue / 5;
				break;
			case 2:
				strcpy(player->armourname, "Poor ");
				player->armourvalue = player->armourvalue / 2;
				break;
			case 3:
				strcpy(player->armourname, "Old ");
				player->armourvalue = player->armourvalue / 1.5;
				break;
			case 4:
				strcpy(player->armourname, "Defective ");
				player->armourvalue = player->armourvalue - 1;
				break;
			case 5:
				strcpy(player->armourname, "Average ");
				break;
			case 6:
				strcpy(player->armourname, "Well Designed ");
				player->armourvalue = player->armourvalue + 1;
				break;
			case 7:
				strcpy(player->armourname, "Great ");
				player->armourvalue = player->armourvalue * 1.5;
				break;
			case 8:
				strcpy(player->armourname, "Fantastic ");
				player->armourvalue = player->armourvalue * 2;
				break;
			case 9:
				strcpy(player->armourname, "Masterwork ");
				player->armourvalue = player->armourvalue * 5;
				break;
			case 10:
				strcpy(player->armourname, "Artifact ");
				player->armourvalue = player->armourvalue * 10;
				break;
			default:
				strcpy(player->armourname, "Average ");
				break;
		}
		strcat(player->armourname, armourname);
		looper = 0;
		while(looper < noarmour)
		{
		
			free(armours[looper]);
			looper++;
		
		}
}

void clearscr()
{
	int x, y;
	
	while(x < LINES)
		{
		while(y < COLS)
			{
				mvaddch(' ', y, x);
				x++;
			}
			x = 0;
			y++;
		}



}