// Final Fantasy 4 DS Save Editor.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <string>


/*-------------
Function Declarations
---------------*/
/* Take an unsigned char array and rerturns a 32 bit unsigned integer of the unsigned little endian representation or vice versa */
uint32_t convertCharArrayToUnsignedInt(unsigned char* arr, uint8_t len);
char* convertUnsignedIntToCharArray(uint32_t arr, uint8_t len);

/* Functions for retreiving, printing and editing the checksum */
uint32_t getChecksum();
void printChecksum();
void addToChecksum(uint32_t value);

/* Functions for printing and editing characters */
uint32_t getGil();
void printGil();
int setGil();

/* Functions for printing and editing characters */
int printPartyInfo(); // Prints the info of the characters currently in the party
int characterSelection(); // Converts user input to character ID
void viewCharacter(int charID);
int editCharacter(int charID);

/* Functions for printing and editing inventory */
int printInventory(); // prints inventory and returns index of first free slot
void editInventory(); // Allows for editing of existing items or insertion into inventory


/* --------
 Item Arrays
---------*/
// Items - Indexing Offset 5001. I.e. Potion is at index 0 but translates to 5001
std::string items [] = { "Potion", "Hi-Potion", "X-Potion", "Ether", "DryEther", "Elixir", "Megalixir", "PhoenixDown", "GoldNeedle", "MaidensKiss", "Mallet", "DietRation", "EchoHerbs", "EyeDrops", "Antidote","Cross", "Remedy","Alarm Clock","Unicorn Horn","Tent","Cottage","Emergency Exit","Gnomish Bread","Gysahl Greens","Gysahl Whistle","Golden Apple","Silver Apple","Soma Drop","Siren","Lustful Lali - Ho","Ninja Sutra","? ? ? ? ?","? ? ? ? ?","? ? ? ? ?","Red Fang","White Fang","Blue Fang","Bomb Fragment","Bomb Crank","Antarctic Wind","Arctic Wind","Zeus's Wrath", "Heavenly Wrath","Gaia Drum","Bomb Core","Stardust","Lilith's Kiss","Vampire Fang","Spider Silk","Silent Bell","Coeurl Whisker","Bestiary","Bronze Hourglass","Silver Hourglass","Gold Hourglass","Bacchus's Wine","Hermes Sandals","Decoy","Light Curtain","Lunar Curtain","Crystal","Member's Writ","? ? ? ? ? ?"};
//Rods - Indexing Offset 37146 (0x1a91)
std::string rods[] = { "Rod", "Flame Rod","Ice Rod","Thunder Rod","Lilith Rod","Polymorph Rod","Faerie Rod","Stardust Rod" };
