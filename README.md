AWOG2
=====

A remake of AWOG text combat game with C and NCurses. Part of the 72 hour challenge


It will be designed to run using the previous game's mod files and will work under the same syntax and achieve hopefully that is better and more functional and more stable than the cobbled together original.


More design notes incoming. Work will begin on June 27th

AWOG 2 rough plan:

Day 1: 
- All loading features functional X
- Basic combat system X
- monsters carry weapon. Armour and a consumable X
- universal structure for all creatures: X
- Base stats( HP, XP, Level): X
- Level influences how much attack is added onto a weapon EG: a sword is 2d6 and the user is level 3, and so gains 2d9 X
- Basic menu interface for combat X


Day 2:
Adjectives to items and monsters X
Coloured text X
Menu for loading saves, new ones, settings
Modding interface X
More stuff to do on combat menu X
Saving and autosaving
Combat effects (bleed, stun, nerve and circulatory damage) X


Day 3:
Polish, debugging, any stuff not already done
Maybe a map
Linux port
DOS port



Structure of a creature(all in one line)(only first 6 stored)

Name, hp, nerve hp, circulatory hp, xp, to hit on d20, level ,weapon name, weapon damage base, damage type,weapon damage dice, armour name, armour value, consumable name, impact hp, impact xp, impact armour.

Eg in file
Rat, 10, 3, 3, 5, 15

Eg in game
Rat, 10, 3, 3, 5,15 , 2 , Naginata, edge, 12, 2, chainmail, 10, orange, 5, 5, 0

This would create a level 2 rat carrying a Naginata with an attack value of 4d12, wearing chainmail with defense of 5 and an orange that heals 5 points and gives 5 point of xp. Health is 20 ( hp x level)

Actions AI and person can take:
Hit head: dice roll in excess of +2 to minimum hit value of max dice value and inflicts double the damage the
Thing attacked

Hit body: requires +1 to minimum, gives full damage

Hit lower/upper extremity : requires the minimum or higher, inflicts 3/4 of the damage

Take consumable: takes the consumable to whatever effect

Flee: attempts to flee based on level comparisons 

Critical (hidden in release version):
In any case of natural 20 damage is tripled. Shown in bold white

Circulatory damage is 1d3 on edged, 1d2 blunt( shown in the prompt as red)

When circulatory hp is 0, bleed is 1d4( shown as cyan)

Nerve damage is 1d3 on blunt, 1d2 edged

When nerve is 0, there is a half chance of stun each turn.


Non combat menu will have these options:

View equipment: views weapon, armour and consumables

Save game: prompts for filename and saves game in save folder

Fight/ move : generates encounter if no map feature is added otherwise prompts with where to move

Main menu will have this:
New game

Load game

Options:

Load a mod
Colour on or off


Quit



10 adjectives ( brackets to values hp for monsters, everything for items, armour value for armour, dice sides for weapons)
Barely functionial(item) / barely alive (/ 5)
Poor / crippled (/ 2)
Old / old ( / 1.5)
Defective / weak ( -1)
Average
Well designed / large(+ 1)
Great / strong ( x 1.5 )
Fantastic / powerful ( x 2 )
Masterwork / Imposing ( x 5)
Artifact / godlike ( x 10)



Classes will be editable and addable in the same way as enemies and such are, and will have a randomly generated weapon, armour and consumable with them as well
in the form

classname, bonus hp, attack modifier, xp modifier(representative of the skill of a base class so different levels)


IMPORTANT: TO COMPILE ON YOUR PLATFORM


Select Makefilewin and rename makefile if you are on windows
select Makefilelin for linux and rename the same

This is known not to work on the latest version of FreeDOS