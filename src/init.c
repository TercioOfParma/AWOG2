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
	init_pair(2, COLOR_RED, COLOR_WHITE); //bleeding text
	init_pair(3, COLOR_BLUE, COLOR_	WHITE);//nerve damage text
	init_pair(4, COLOR_GREEN, COLOR_BLACK); //critical
	
	


}

void deinit()
{
	clearscr();
	endwin();
	exit(0);



}

void create_player(creature *player, FILE *wep, FILE *armour, FILE *item)
{

	
	player->hp = rand() % 1000 + 20;
	player->chp = rand() % 20 + 12;
	player->nhp = rand() % 20 + 12;
	player->xp = 0;
	player->tohit = rand() % 10 + 5;
	player->level = 1;
	
	generate_weapon(player, wep);
	generate_item(player, item);
	generate_armour(player, armour);
	





}
void generate_weapon(creature *player, FILE *wep)
{
	rewind(wep);
	int noweapons = 0;
	int looper = 0;
	char *temphold = malloc(sizeof(char) * MAX_BYTESIZE_ITEMS);
	char *weaponname, *weaponkind, *weaponsides, *weapondie, *weaponverb;
	fgets(temphold, MAX_BYTESIZE_ITEMS, wep);
	noweapons = atoi(temphold);
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
	weaponverb = strtok(NULL, ",");
	strcpy(player->weaponverb,weaponverb);
		switch(quality)//will make this file portable in AWOG 3 :D
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
		free(temphold);

}

void generate_item(creature *player, FILE *item)
{
	rewind(item);
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
		free(temphold);
}

void generate_armour(creature *player, FILE *armour)
{
		rewind(armour);
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
		free(temphold);
}

void clearscr()
{
	clear();
	refresh();

}




void generate_enemy(creature *monster,FILE *wep, FILE *armour, FILE* item, FILE *mon)
{
	rewind(mon);
	clearscr();
	monster->name = malloc(sizeof(char) * 40);
	monster->weaponname = malloc(sizeof(char) * 40);
	monster->weaponverb = malloc(sizeof(char) * 40);
	monster->armourname = malloc(sizeof(char) * 40);
	monster->itemname = malloc(sizeof(char) * 40);

	monster->level = rand() % 5 + 1;
	generate_armour(monster,armour);
	generate_item(monster,item);
	generate_weapon(monster,wep);
	
	int nomonsters = 50;
	char *enemyname,*enemyhp,*enemycirchp,*enemynervehp,*enemyxp,*enemytohit;
	char *temphold = malloc(sizeof(char) * MAX_BYTESIZE_ITEMS);
	fgets(temphold, MAX_BYTESIZE_ITEMS, mon);
	
	nomonsters = atoi(temphold);
	int looper = 0;
	char *monsters[nomonsters];
	
	
	while(looper < nomonsters)
	{
		monsters[looper] = malloc(sizeof(char) * 200);
		fgets(monsters[looper],MAX_THINGSTRING_SIZE,mon);
		looper++;
	
	
	}
	int chooser = rand() % nomonsters;
	int adjective = rand() % 10 + 1;
	
	enemyname = strtok(monsters[chooser], ",");
	enemyhp = strtok(NULL,",");
	enemycirchp = strtok(NULL, ",");
	enemynervehp = strtok(NULL, ",");
	enemyxp = strtok(NULL, ",");
	enemytohit = strtok(NULL, ",");

	monster->hp = atoi(enemyhp);
	monster->chp = atoi(enemycirchp);
	monster->nhp = atoi(enemynervehp);
	monster->xp = atoi(enemyxp);
	monster->tohit = atoi(enemytohit);

		switch(adjective)
		{
			case 1:
				strcpy(monster->name, "Barely Alive ");
				monster->hp = monster->hp / 5;
				monster->chp = monster->chp / 5;
				monster->nhp = monster->nhp / 5;
				monster->xp = monster->xp / 5;
				monster->tohit = monster->tohit * 5;
				break;
			case 2:
				strcpy(monster->name, "Crippled ");
				monster->hp = monster->hp / 2;
				monster->chp = monster->chp / 2;
				monster->nhp = monster->nhp / 2;
				monster->xp = monster->xp / 2;
				monster->tohit = monster->tohit * 2;
				break;
			case 3:
				strcpy(monster->name, "Old ");
				monster->hp = monster->hp / 1.5;
				monster->chp = monster->chp / 1.5;
				monster->nhp = monster->nhp / 1.5;
				monster->xp = monster->xp / 1.5;
				monster->tohit = monster->tohit * 1.5;
				break;
			case 4:
				strcpy(monster->name, "Weak ");
				monster->hp = monster->hp - 1;
				monster->chp = monster->chp - 1;
				monster->nhp = monster->nhp - 1;
				monster->xp = monster->xp - 1;
				monster->tohit = monster->tohit + 1;
				break;
			case 5:
				strcpy(monster->name, "Average ");
				break;
			case 6:
				strcpy(monster->name, "Large ");
				monster->hp = monster->hp + 1;
				monster->chp = monster->chp + 1;
				monster->nhp = monster->nhp + 1;
				monster->xp = monster->xp + 1;
				monster->tohit = monster->tohit - 1;
				break;
			case 7:
				strcpy(monster->name, "Strong ");
				monster->hp = monster->hp * 1.5;
				monster->chp = monster->chp * 1.5;
				monster->nhp = monster->nhp * 1.5;
				monster->xp = monster->xp * 1.5;
				monster->tohit = monster->tohit / 1.5;
				break;
			case 8:
				strcpy(monster->name, "Powerful ");
				monster->hp = monster->hp * 2;
				monster->chp = monster->chp * 2;
				monster->nhp = monster->nhp * 2;
				monster->xp = monster->xp * 2;
				monster->tohit = monster->tohit / 2;
				break;
			case 9:
				strcpy(monster->name, "Imposing ");
				monster->hp = monster->hp * 5;
				monster->chp = monster->chp * 5;
				monster->nhp = monster->nhp * 5;
				monster->xp = monster->xp * 5;
				monster->tohit = monster->tohit / 5;
				break;
			case 10:
				strcpy(monster->name, "Godlike ");
				monster->hp = monster->hp * 10;
				monster->chp = monster->chp * 10;
				monster->nhp = monster->nhp * 10;
				monster->xp = monster->xp * 10;
				monster->tohit = monster->tohit / 10;
				break;
			default:
				strcpy(monster->armourname, "Average ");
				break;
		}
	strcat(monster->name, enemyname);
	
	looper = 0;
	while(looper < nomonsters)
		{
		
			free(monsters[looper]);
			looper++;
		
		}
		free(temphold);


}
