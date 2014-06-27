#include <curses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BYTESIZE_ITEMS 4
#define MAX_THINGSTRING_SIZE 200


void init();
void deinit();
void clearscr();


typedef struct{
	char *name, *weaponname, *weaponverb, *armourname, *itemname;
	int hp, chp, nhp, xp,armourvalue,weapondice,weaponvalue,itemhp,itemxp,itemarmour, level;
	unsigned char kind;

	/*
		name = name of creature
		weaponname = name of weapon
		weaponverb = verb of the weapon when attacking
		armourname = name of armour
		itemname = name of item
	
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
	
		kind = a differentiator between blunt and edged weapons
	
	*/


}creature;

void create_player(creature *player, FILE *wep, FILE *armour, FILE* item);
void generate_weapon(creature *player, FILE *wep);
void generate_item(creature *player, FILE *item);
void generate_armour(creature *player, FILE *armour);
void generate_enemy(creature *player,FILE *wep, FILE *armour, FILE* item);

