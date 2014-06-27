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
	int choice = -1;
	printw("     Name,HPmod,tohitmod,xpmod\n");
	char *classes[noclasses];
	
	
	while(looper < noclasses)
	{
		classes[looper] = malloc(sizeof(char) * 200);
		fgets(classes[looper],200,classfile);
		printw("%d   %s\n", looper+1, classes[looper]);
		looper++;
	
	}
	printw("Type the valid number of the class you want: ");
	while(choice == -1 || choice > noclasses)
	{
		scanw("%d", &choice);
		choice -= 1;
		
	}

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




void mainmenu(creature *player, FILE *wep, FILE *armour, FILE* item, FILE *mon)
{

	int option = 0;
	attron(A_BOLD | A_UNDERLINE);
	printw("What do You wish to do now?\n\n");

	attroff(A_BOLD | A_UNDERLINE);
	creature *monster = malloc(sizeof(creature));
	
	while(1 == 1)
	{
	attron(A_BLINK);
	printw("1 : FIGHT!\n");
	attroff(A_BLINK);
	printw("2: Check Equipment\n");
	printw("3: Save [WIP NOT FUNCTIONAL]\n");
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
			printw("Not Yet\n\n");
			getch();
			clearscr();
			break;
		case 4:
			deinit();
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
	
	
	while(monster->hp >= 0 && player->hp > 0)
		{
			stunenemy: //a neccessary evil
			srand(time(0));
			int enemyai = rand() % 100 + 1;//great AI I know
			int enemyattackdie = monster->weapondice + monster->level;
			int playerattackdie = player->weapondice + player->level;
			int playertohit = rand() % 20 + 1;
			int enemytohit = rand() % 20 + 1;
			int looper, pholder, eholder, playernervedmg, playercircdamage, enemycircdamage, enemynervedmg, pbleed, ebleed;
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
			
			switch(option)
			{
				case 1:
					if(playertohit > player->tohit + 2)
					{

						pholder = pholder * 2; //there are easier ways of doing this however this is for what little readability I can salvage
						printw("You %s the %s's head directly!\n This causes %d damage, %d nerve damage and %d circulatory damage\n\n", player->weaponverb, monster->name, pholder, playernervedmg,playercircdamage);
						monster->hp -= pholder;
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					}
					else if(playertohit > player->tohit + 1)
					{
						pholder = pholder * 1.5;
						printw("You slip slightly and miss the head of the %s. However, you %s the %s in the torso for %d damage, %d nerve damage, and %d circulatory damage\n\n", monster->name, player->weaponverb, monster->name, pholder, playernervedmg, playercircdamage);
						monster->hp -= pholder;
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
						monster->hp -= pholder;
						monster->nhp -= playernervedmg;
						monster->chp -= playercircdamage;
					}
					else if(playertohit > player->tohit)
					{
						printw("You miss the torso barely, but you still are able to %s the %s's upper extremities, causing %d damage, %d nerve damage and %d circulatory damage\n\n",player->weaponverb, monster->name, pholder,playernervedmg,playercircdamage);
						monster->hp -= pholder;
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
						monster->hp -= pholder;
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
						monster->hp -= pholder;
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
							player->itemname = malloc(sizeof(char) * 40);
							player->itemhp = 0;
							player->itemxp = 0;
							player->itemarmour = 0;
					break;
					case 6:
						printw("You flee like a coward");
						getch();
						return;
						break;
					default:
						printw("Your character spasms visibly as you press the wrong key on your keyboard\n\n");
						break;
			
			
			}
		
		if(enemyai > 50 && monster->nhp < 0)
		{
			attron(COLOR_PAIR(3));
			printw("NERVOUS STUN, CANNOT HIT THIS TURN!\n");
			attroff(COLOR_PAIR(3));
			goto stunenemy;
			
		
		}
		if(enemyai < 50 && monster->chp < 0)
		{
				attron(COLOR_PAIR(2));
				ebleed = rand() % 6 + 1;
				printw("BLEED, CAUSING %d DAMAGE!\n", ebleed);
				attroff(COLOR_PAIR(2));
		
		
		
		}
		else if(enemyai < 80 && enemytohit > monster->tohit + 2)
			{
				eholder = eholder * 2;
				printw("The %s of the %s's %s stings against your skull, causing %d damage, %d nerve damage and %d circulatory damage\n\n", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  eholder;
				player->nhp = player->nhp - enemynervedmg;
				player->chp = player->chp - enemycircdamage;
			
			}
		else if(enemyai < 95 && enemytohit > monster->tohit + 1)
			{
				eholder = eholder * 1.5;
				printw("The %s of the %s's %s roars in pain against your thorax, causing %d damage, %d nerve damage and %d circulatory damage\n\n", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  eholder;
				player->nhp = player->nhp - enemynervedmg;
				player->chp = player->chp - enemycircdamage;
			
			}
		else if(enemyai < 85 && enemytohit > monster->tohit)
		{
				printw("Your arm is %s by the %s's %s, causing %d damage, %d nerve damage and %d circulatory damage\n\n ", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  eholder;
				player->nhp = player->nhp - enemynervedmg;
				player->chp = player->chp - enemycircdamage;
		
		
		}
		else if(enemyai < 90 && enemytohit > monster->tohit)
		{
				printw("Your legs is %s by the %s's %s, causing %d damage, %d nerve damage and %d circulatory damage\n\n ", monster->weaponverb, monster->name, monster->weaponname, eholder, enemynervedmg, enemycircdamage);
				player->hp = player->hp -  eholder;
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
			getch();
			return;
		
		}




}