#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_BYTESIZE_ITEMS 4
#define MAX_THINGSTRING_SIZE 200
#define LINES_H 70
#define COLS_H 140

void init();
void deinit();
void clearscr();


typedef struct{
	char *name, *weaponname, *weaponverb, *armourname, *itemname, *classname;
	int hp, chp, nhp, xp,armourvalue,weapondice,weaponvalue,itemhp,itemxp,itemarmour, level,tohit;
	unsigned char kind;

	/*
		name = name of creature
		weaponname = name of weapon
		weaponverb = verb of the weapon when attacking
		armourname = name of armour
		itemname = name of item
		classname = name of the class the creature is in (player only)
		
	
		hp = base hp
		chp= circulatory hp (essentially how many points before bleeding the creature is
		nhp= nervous hp (the number before the creature begins to experience stuns half of the time
		xp = experience dropped
		armourvalue= the amount of armour you have (takes half an attack)
		weapon dice = how many dice a weapon has
		weapon value = how many sides the dice have
		itemhp = modification to hp
		itemxp = modification to xp
		itemarmour = modification to armour
		level = duh
		tohit = the required roll on a d20 to hit
		
		
		kind = a differentiator between blunt and edged weapons
	
	*/


}creature;

void create_player(creature *player, FILE *wep, FILE *armour, FILE* item);
void generate_weapon(creature *player, FILE *wep);
void generate_item(creature *player, FILE *item);
void generate_armour(creature *player, FILE *armour);
void generate_enemy(creature *monster,FILE *wep, FILE *armour, FILE* item, FILE *mon);
void save(creature *player, char *filename, char *modpath);
void load (creature *player, FILE *wep, FILE *armour, FILE* item, FILE *mon, char *modpath);



void combat_menu(creature *player, creature *monster);//main combat engine
void droppickup(creature *player, creature *monster);//handles pickups and such
void mainmenu(creature *player, FILE *wep, FILE *armour, FILE* item, FILE *mon, char *modpath);
void classselect(creature *player, FILE *classfile);
void show_equipment(creature *player);
