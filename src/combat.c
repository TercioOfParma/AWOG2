#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "basic.h"
#endif



void classselect(creature *player, FILE *classfile)
{
	clearscr();
	char *temphold = malloc(sizeof(char) * MAX_BYTESIZE_ITEMS);
	char *classname, *hpbonus, *attackbonus, *xpbonus; 
	fgets(temphold,MAX_BYTESIZE_ITEMS,classfile);
	int noclasses = atoi(temphold);
	int hph,tohith,xph;
	int looper = 0;
	int choice;
	printw("     Name,HPmod,tohitmod,xpmod\n");
	char *classes[noclasses];
	
	
	while(looper < noclasses)
	{
		classes[looper] = malloc(sizeof(char) * 200);
		fgets(classes[looper],200,classfile);
		printw("%d   %s\n", looper+1, classes[looper]);
		looper++;
	
	}
	
	do
	{
		choice = 0;
		printw("Type the valid number of the class you want: ");
		scanw("%d", &choice);
		choice -= 1;
		
		if(choice < 0 || choice >= noclasses)
		{
			printw("Invalid number\n");
		
		}
		else
		{
			break;
		
		}
		
	}while(1 == 1);

	classname = strtok(classes[choice], ",");
	hpbonus = strtok(NULL, ",");
	attackbonus = strtok(NULL,",");
	xpbonus = strtok(NULL,",");
	
	
	strcpy(player->classname, classname);
	hph = atoi(hpbonus);
	tohith = atoi(attackbonus);
	xph = atoi(xpbonus);
	
	
	player->xp = player->xp + xph;
	player->tohit = player->tohit - tohith;
	player->hp = player->hp + hph;
	

}




void mainmenu(creature *player, FILE *wep, FILE *armour, FILE* item, FILE *mon, char *modpath)
{

	int option = 0;
	static int xp, hpbonus, chpbonus, tohitbonus, nhpbonus;  
	xp = 100;
	hpbonus = 100;
	chpbonus = 12;
	nhpbonus = 12;
	tohitbonus = 1;
	char *filename = malloc(sizeof(char) * 40);
	attron(A_BOLD | A_UNDERLINE);
	printw("What do You wish to do now?\n\n");

	attroff(A_BOLD | A_UNDERLINE);
	creature *monster = malloc(sizeof(creature));
	
	while(1 == 1)
	{
	if(player->xp > xp)
	{
		printw("LEVEL UP!");
		player->hp += hpbonus;
		player->chp += chpbonus;
		player->tohit -= tohitbonus;
		player->nhp += nhpbonus;
	
		xp *= 3;
		hpbonus *= 2;
		chpbonus *= 2;
		nhpbonus *= 2;
		tohitbonus *= 2;
		getch();
		
	}
	
	attron(A_BLINK);
	printw("1 : FIGHT!\n");
	attroff(A_BLINK);
	printw("2: Check Equipment\n");
	printw("3: Save \n");
	printw("4: Quit without Saving\n");
	scanw("%d", &option);
	
	switch(option)
	{
		case 1:
			
			generate_enemy(monster,wep,armour,item,mon);
			combat_menu(player,monster);
			break;
		case 2:
			show_equipment(player);
			break;
		case 3:
		clearscr();
			printw("Please type filename here : ");
			scanw("%s", filename);
			save(player, filename, modpath);
			clearscr();
			break;
		case 4:
			return;
			break;
	
	
		default:
			clearscr();
		break;
	}

	}




}

void show_equipment(creature *player)
{
	clearscr();
	
	attron(A_BOLD);
	printw("%s, Level %d %s\n",player->name, player->level, player->classname);
	attroff(A_BOLD);
	attron(A_BOLD);
	printw("Weapon : ");
	attroff(A_BOLD);
	printw("%s, %dd%d damage  %d to hit on d20\n\n", player->weaponname, player->level + player->weapondice, player->weaponvalue, player->tohit);
	
	
	attron(A_BOLD);
	printw("Armour: ");
	attroff(A_BOLD);
	printw("%s, %d protection\n\n", player->armourname, player->armourvalue);

	attron(A_BOLD);
	printw("Consumable: ");
	attroff(A_BOLD);
	printw("%s, %d health impact, %d xp impact, %d armour impact\n\n", player->itemname, player->itemhp, player->itemxp, player->itemarmour);

	getch();

}

void combat_menu(creature *player, creature *monster)
{
	int option = 0;
	printw("You see a %s, he is carrying a %s and %s", monster->name, monster->weaponname, monster->armourname);

	getch();
	clearscr();
	int looper, pholder, eholder, playernervedmg, playercircdamage, enemycircdamage, enemynervedmg, pbleed, ebleed;
	int enemyai = rand() % 100 + 1;//great AI I know
	int bleedstundecide = rand() % 100 + 1;
	int enemyattackdie = monster->weapondice + monster->level;
	int playerattackdie = player->weapondice + player->level;
	int playertohit = rand() % 20 + 1;
	int enemytohit = rand() % 20 + 1;
	
	
	while(monster->hp >= 0 && player->hp > 0)
		{
			stunenemy: //a neccessary evil, dijstrka wouldn't be proud
			clearscr();
			srand(time(0));
			enemyai = rand() % 100 + 1;//great AI I know
			bleedstundecide = rand() % 100 + 1;
			enemyattackdie = monster->weapondice + monster->level;
			playerattackdie = player->weapondice + player->level;
			playertohit = rand() % 20 + 1;
			enemytohit = rand() % 20 + 1;
			
			looper = 0;
			pholder =0;
			eholder = 0;
			while(looper < playerattackdie)
			{
				pholder += rand() % player->weaponvalue + 1;
				looper++;
			
			}
			while(looper < enemyattackdie)
			{
				eholder += rand() % monster->weaponvalue + 1;
				looper++;
			
			}
			if(player->kind = 'e')
			{
				playercircdamage = rand() % 3 + 1; 
				playernervedmg = rand() % 2 + 1;
			}
			else
			{
			playernervedmg = rand() % 3 + 1;
			playercircdamage = rand() % 2 + 1;
			}
			
			if(monster->kind = 'e')
			{
				enemycircdamage = rand() % 3 + 1; 
				enemynervedmg = rand() % 2 + 1;
			}
			else
			{
			enemynervedmg = rand() % 3 + 1;
			enemycircdamage = rand() % 2 + 1;
			}
			looper =  0;
			attron(A_BOLD);
			mvprintw(0,0,"%s, Level %d , Wielding %s\n\n", monster->name, monster->level, monster->weaponname);
			attroff(A_BOLD);
			
			
			printw("What do you wish to do?\n");
			printw("1: Attack Head\n");
			printw("2: Attack Body\n");
			printw("3:Lower extremities\n");
			printw("4:Upper extremities\n");
			printw("5: Consume item\n");
			printw("6:Flee\n");
			printw("Your tohit :", player->tohit);
			scanw("%d", &option);
			
		if(bleedstundecide > 50 && player->nhp < 0)
		{
			attron(COLOR_PAIR(3));
			printw("NERVOUS STUN, YOU CANNOT HIT THIS TURN!\n");
			attroff(COLOR_PAIR(3));
			goto stunplayer;
			
		
		}
		if(bleedstundecide < 50 && player->chp < 0)
		{
				attron(COLOR_PAIR(2));
				pbleed = rand() % 6 + 1;
				printw("YOU BLEED, CAUSING %d DAMAGE!\n", pbleed);
				attroff(COLOR_PAIR(2));
				player->hp = player->hp - pbleed;
		
		
		}
			
			switch(option)
			{
				case 1:
					if(playertohit > player->tohit + 2)
					{

						pholder = pholder * 2; //there are easier ways of doing this however this is for what little readability I can salvage
						printw("You %s the %s's head directly!\n This causes %d damage, %d nerve damage and %d circulatory damage\n\n", monster->weaponverb, monster->name, pholder, playernervedmg,playercircdamage);
						monster->hp = monster->hp -  (pholder/3) * 2;
						if(monster->armourvalue > 0)
						{
							monster->armourvalue = monster->armourvalue - (pholder / 3);
						}
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					}
					else if(playertohit > player->tohit + 1)
					{
						pholder = pholder * 1.5;
						printw("You slip slightly and miss the head of the %s. However, you %s the %s in the torso for %d damage, %d nerve damage, and %d circulatory damage\n\n", monster->name, player->weaponverb, monster->name, pholder, playernervedmg, playercircdamage);
						monster->hp = monster->hp -  (pholder/3) * 2;
						if(monster->armourvalue > 0)
						{
							monster->armourvalue = monster->armourvalue - (pholder / 3);
						}
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					}
					else
					{
						printw("The %s dodges your inept blow\n\n", monster->name);
					}
					break;
				case 2:
					if(playertohit > player->tohit + 1)
					{
						pholder = pholder * 1.5;
						printw("You %s the %s in the chest. This causes %d damage, %d nerve damage and %d circulatory damage\n\n", player->weaponverb, monster->name, pholder,playernervedmg,playercircdamage); 
						monster->hp = monster->hp -  (pholder/3) * 2;
						if(monster->armourvalue > 0)
						{
							monster->armourvalue = monster->armourvalue - (eholder / 3);
						}
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					}
					else if(playertohit > player->tohit)
					{
						printw("You miss the torso barely, but you still are able to %s the %s's upper extremities, causing %d damage, %d nerve damage and %d circulatory damage\n\n",player->weaponverb, monster->name, pholder,playernervedmg,playercircdamage);
						monster->hp = monster->hp -  (pholder/3) * 2;
						if(monster->armourvalue > 0)
						{
							monster->armourvalue = monster->armourvalue - (pholder / 3);
						}
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					
					}
					else
					{
					
						printw("The %s deftly dodges your cumbersome blow\n\n", monster->name);
					
					}
					break;
				case 3:
					if(playertohit > player->tohit)
					{
					
						printw("You quickly %s the %s's knees, inflicting %d damage, %d nerve damage and %d circulatory damage\n\n", player->weaponverb, monster->name, pholder,playernervedmg,playercircdamage);
						monster->hp = monster->hp -  (pholder/3) * 2;
						if(monster->armourvalue > 0)
						{
							monster->armourvalue = monster->armourvalue - (pholder / 3);
						}
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					
					}
					else
					{
						printw("As you attempt to %s the %s's legs, you stumble and fall. Luckily, it is too slow to react\n\n", player->weaponverb, monster->name);
					
					
					}
					break;
				case 4:
					if(playertohit > player->tohit)
					{
					
						printw("You %s the %s's arms with finesse, inflicting %d damage, %d nerve damage and %d circulatory damage\n\n", player->weaponverb, monster->name, pholder,playernervedmg,playercircdamage);
						monster->hp = monster->hp -  (pholder/3) * 2;
						if(monster->armourvalue > 0)
						{
							monster->armourvalue = monster->armourvalue - (pholder / 3);
						}
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					
					}
					else
					{
						printw("As you attempt to %s the %s's arms, you flail wildly and fall over. Luckily, it is too slow to react\n\n", player->weaponverb, monster->name);
					
					
					}
					break;
					case 5:
							printw("You consume your %s, granting you %d health, %d xp and %d armour\n\n", player->itemname, player->itemhp, player->itemxp, player->itemarmour);
							player->itemname = malloc(sizeof(char) * 40); //yes you can technically consume something that doesn't exist
							player->itemhp = 0;
							player->itemxp = 0;
							player->itemarmour = 0;
					break;
					case 6:
						printw("You flee like a coward");
						getch();
						clearscr();
						return;
						break;
					default:
						printw("Your character spasms visibly as you press the wrong key on your keyboard\n\n");
						break;
			
			
			}
		stunplayer:
		if(enemyai > 50 && monster->nhp < 0)
		{
			attron(COLOR_PAIR(3));
			printw("NERVOUS STUN, THE %s CANNOT HIT THIS TURN!\n", monster->name);
			attroff(COLOR_PAIR(3));
			goto stunenemy;
			
		
		}
		if(enemyai < 50 && monster->chp < 0)
		{
				ebleed = 0;
				attron(COLOR_PAIR(2));
				ebleed = rand() % 6 + 1;
				printw("BLEED, CAUSING %d DAMAGE!\n", ebleed);
				attroff(COLOR_PAIR(2));
		
		
		
		}
		if(enemyai < 80 && enemytohit > monster->tohit + 2)
			{
				eholder = eholder * 2;
				printw("The %s of the %s's %s stings against your skull, causing %d damage, %d nerve damage and %d circulatory damage\n\n", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  (eholder/3) * 2;
				player->armourvalue = player->armourvalue - (eholder / 3);
				player->nhp = player->nhp - enemynervedmg;
				player->chp = player->chp - enemycircdamage;
			
			}
		else if(enemyai < 95 && enemytohit > monster->tohit + 1)
			{
				eholder = eholder * 1.5;
				printw("The %s of the %s's %s roars in pain against your thorax, causing %d damage, %d nerve damage and %d circulatory damage\n\n", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  (eholder/3) * 2;
				if(player->armourvalue > 0)
				{
					player->armourvalue = player->armourvalue - (eholder / 3);
				}
				player->nhp = player->nhp - enemynervedmg;
				player->chp = player->chp - enemycircdamage;
			
			}
		else if(enemyai < 85 && enemytohit > monster->tohit)
		{
				printw("Your arm is %s by the %s's %s, causing %d damage, %d nerve damage and %d circulatory damage\n\n ", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  (eholder/3) * 2;
				if(player->armourvalue > 0)
				{
					player->armourvalue = player->armourvalue - (eholder / 3);
				}
				player->nhp = player->nhp - enemynervedmg;
				player->chp = player->chp - enemycircdamage;
		
		
		}
		else if(enemyai < 90 && enemytohit > monster->tohit)
		{
				printw("Your legs is %s by the %s's %s, causing %d damage, %d nerve damage and %d circulatory damage\n\n ", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  (eholder/3) * 2;
				if(player->armourvalue > 0)
				{
					player->armourvalue = player->armourvalue - (eholder / 3);
				}
				player->nhp = player->nhp - enemynervedmg;
				player->chp = player->chp - enemycircdamage;
		
		}
		
		else if(monster->itemhp > 0 || monster->itemxp > 0 || monster->itemarmour > 0)
		{
			printw("The %s consumes its %s", monster->name, monster->itemname);
			monster->hp += monster->itemhp;
			monster->xp += monster->itemxp;
			monster->armourvalue += monster->itemarmour;
			
			monster->itemhp = 0;
			monster->itemxp = 0;
			monster->itemarmour = 0;
			monster->itemname = malloc(sizeof(char) * 40);
			strcpy(monster->itemname, "EMPTY");
		
		
		}
		else
		{
			printw("The %s misses outright", monster->name);
		
		
		}
			getch();
			clearscr();
			
			
		}
		
	if(player->hp < 0)
		{
			clearscr();
			attron(A_BLINK);
			printw("You have died, please press enter to continue\n");
			getch();
			deinit();
		
		
		}
	else if(monster->hp < 0)
		{
			clearscr();
			attron(A_BLINK);
			printw("You have killed the %s, please press enter to continue\n", monster->name);
			attroff(A_BLINK);
			printw("Please choose an item to pickup from the monster (0 for nothing)\n\n");
			printw("1: %s, %dd%d damage\n\n", monster->weaponname, monster->weapondice, monster->weaponvalue);
			printw("2: %s, %d protection\n\n", monster->armourname, monster->armourvalue);
			if(!strstr(monster->name, "EMPTY"))//for some strange reason this means that the monster ISN'T carrying an empty consumable
			{
			printw("3: %s, providing %d hp, %d xp, and %d armour\n\n", monster->itemname, monster->itemhp, monster->itemxp, monster->itemarmour);
			
			
			}
			option = 0;
			scanw("%d", &option);
			
			if(option == 1)
			{
				player->weaponname = malloc(sizeof(char) * 40); //clears the strings
				player->weaponverb = malloc(sizeof(char) * 40);
				strcpy(player->weaponname, monster->weaponname);
				strcpy(player->weaponverb, monster->weaponverb);
				player->weapondice = monster->weapondice;
				player->weaponvalue = monster->weaponvalue;
				printw("You pick up the %s\n", player->weaponname);
				
			
			
			
			}
			else if(option == 2)
			{
				player->armourname = malloc(sizeof(char) * 40);
				strcpy(player->armourname, monster->armourname);
				player->armourvalue = monster->armourvalue;
				printw("You pick up the %s\n", player->armourname);
			
			
			}
			else if(option == 3 && !strstr(monster->itemname, "EMPTY"))
			{
				player->itemname = malloc(sizeof(char) * 40);
				strcpy(player->itemname, monster->itemname);
				player->itemhp = monster->itemhp;
				player->itemxp = monster->itemxp;
				player->itemarmour = monster->itemarmour;
				printw("You pick up the %s\n", player->itemname);
			
			
			}
			else
			{
				printw("Alright suit yourself, you get nothing and nothing changes in your inventory\n");
			
			
			}
			player->xp += monster->xp;
			getch();
			clearscr();
			return;
		
		}




}

void save(creature *player, char *filename, char *modpath)
{
	chdir("..");
	chdir("..");
	chdir("Save");
	
	FILE* save = fopen(filename, "w");
	
	fprintf(save,"AWOG SAVE FILE\n"); //makes sure doesn't read in anything bad
	fprintf(save,"%s \n", player->name);
	fprintf(save,"%s \n",player->classname);
	fprintf(save,"%d \n",player->hp);
	fprintf(save,"%d \n",player->chp);
	fprintf(save,"%d \n",player->nhp);
	fprintf(save,"%d \n",player->xp);
	fprintf(save,"%d \n",player->level);
	fprintf(save,"%d \n",player->tohit);
	fprintf(save,"%s \n",player->weaponname);
	fprintf(save,"%s \n",player->weaponverb);
	fprintf(save,"%d \n",player->weaponvalue);
	fprintf(save,"%d \n",player->weapondice);
	fprintf(save,"%c \n",player->kind);
	fprintf(save,"%s \n",player->armourname);
	fprintf(save,"%d \n",player->armourvalue);
	fprintf(save,"%s \n",player->itemname);
	fprintf(save,"%d \n",player->itemhp);
	fprintf(save,"%d \n",player->itemxp);
	fprintf(save,"%d \n",player->itemarmour);
	
	beep();
	attron(A_BLINK);
	printw("COMPLETE: PRESS ANY KEY TO CONTINUE");
	attroff(A_BLINK);
	getch();
	fclose(save);
	
	chdir("..");
	chdir("data");
	chdir(modpath);

	return;



}

int load (creature *player, FILE *wep, FILE *armour, FILE* item, FILE *mon, char *modpath)
{
	int looper = 0;
	chdir("..");
	chdir("..");
	chdir("Save");

	
	char *filename = malloc(sizeof(char) * 50);
	char *contents[20];
	FILE *save; 
	do 
	{
		printw("Please type the name of the file you wish to load or cancel to cancel: ");
		scanw("%s", filename);
		if(strstr(filename,"cancel"))
		{
			return 0;
	
		}
		save = fopen(filename, "r");
		if(!save)
		{
			printw("\nFile not found in save directory, please try again\n");
	
	
		}
	}while(!save);
	while(looper < 20)
	{	
		
		contents[looper] = malloc(sizeof(char) * MAX_THINGSTRING_SIZE);
		fgets(contents[looper],MAX_THINGSTRING_SIZE,save);
		looper++;
	}
	
	if(!strstr(contents[0],"AWOG SAVE FILE"))
	{
		printw("FILE INVALID, PLEASE TRY AGAIN (press any key to continue)");
		getch();
		load(player,wep,armour,item,mon, modpath);
		
		
	}
	
	strcpy(player->name, contents[1]);
	strcpy(player->classname, contents[2]);
	player->hp = atoi(contents[3]);
	player->chp = atoi(contents[4]);
	player->nhp = atoi(contents[5]);
	player->xp = atoi(contents[6]);
	player->level = atoi(contents[7]);
	player->tohit = atoi(contents[8]);
	strcpy(player->weaponname, contents[9]);
	strcpy(player->weaponverb, contents[10]);
	player->weaponvalue = atoi(contents[11]);
	player->weapondice = atoi(contents[12]);
	player->kind = contents[13][0];
	strcpy(player->armourname, contents[14]);
	player->armourvalue = atoi(contents[15]);
	strcpy(player->itemname, contents[16]);
	player->itemhp = atoi(contents[17]);
	player->itemxp = atoi(contents[18]);
	player->itemarmour = atoi(contents[19]);
	
	
	chdir("..");
	chdir("data");
	chdir(modpath);
	beep();
	printw("Game file loaded successfully, please press any key to continue");
	getch();
	
	
	mainmenu(player,wep,armour,item,mon,modpath);
	return 1;
	

}
