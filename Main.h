// Kyle Fenole
// kfenole.com
//
// Main.h
//
// Feel free to use anything from this project, but please credit me if you do!
// (Also, if you are working on a similar project, I'd be interested to hear about it)

#pragma once

#include "iostream"
//#include <iostream>
#include <string>
#include "SaveFile.h"


/*-------------
Function Declarations
---------------*/
/* Checks cin to see if there are any errors. Not perfect but catches most input errors */
bool checkInput(uint32_t);
/* Prompts user to choose a character and returns the id number */
int characterSelection();
/* Returns the name of an item from a given item id */
std::string itemIdToItemName(uint16_t id);
/*  */
void printStatsofChracterWithId(uint8_t id, SaveFile &save);

std::string	 characters[] = { "Cecil (Dark Knight)", "Cecil (Paladin)", "Kain", "Rosa", "Rydia", "5", "Tellah", "Porom", "Palom", "Edward", "10", "11", "Cid", "13" };
/* --------
 Item Arrays
---------*/
// Items - Indexing Offset 5001. I.e. Potion is at index 0 but translates to 5001 as an id
std::string items[] = { "Potion", "Hi-Potion", "X-Potion", "Ether", "DryEther", "Elixir", "Megalixir", "Phoenix Down", "Gold Needle", "Maiden's Kiss", "Mallet", "Diet Ration", "Echo Herbs", "EyeDrops", "Antidote","Cross", "Remedy","Alarm Clock","Unicorn Horn","Tent","Cottage","Emergency Exit","Gnomish Bread","Gysahl Greens","Gysahl Whistle","Golden Apple","Silver Apple","Soma Drop","Siren","Lustful Lali - Ho","Ninja Sutra","? ? ? ? ?","? ? ? ? ?","? ? ? ? ?","Red Fang","White Fang","Blue Fang","Bomb Fragment","Bomb Crank","Antarctic Wind","Arctic Wind","Zeus's Wrath", "Heavenly Wrath","Gaia Drum","Bomb Core","Stardust","Lilith's Kiss","Vampire Fang","Spider Silk","Silent Bell","Coeurl Whisker","Bestiary","Bronze Hourglass","Silver Hourglass","Gold Hourglass","Bacchus's Wine","Hermes Sandals","Decoy","Light Curtain","Lunar Curtain","Crystal","Member's Writ","? ? ? ? ? ?"};
// Swords - Indexing offset 6001 (0x1771)
std::string swords[] = { "Dark Sword","Shadow Blade","Deathbringer","Mythgraven Blade","Lustrous Sword","Excalibur","Ragnarok","Ancient Sword","Blood Sword","Mythril Sword","Sleep Blade","Flame Sword","Icebrand","Stoneblade","Avenger","Defender","Fireshard","Frostshard","Thundershard", "Onion Sword" };
// Spears - Indexing offset 6101 (0x17D5)
std::string spears[] = { "Spear", "Wind Spear", "Flame Lance","Ice Lance","Blood Lance","Gugnir", "Wyvern Lance", "Holy Lance"};
// Knives - Indexing offset 6201 (0x1839)
std::string knives[] = { "Mythril Knife", "Dancing Dagger", "Mage Masher", "Knife" };
// Harps - Indexing offset 6301 (0x189D)
std::string harps[] = { "Dream Harp", "Lamia Harp" };
// Claws - Indexing offset 6401 (0x1901)
std::string claws[] = { "Flame Claws", "Ice Claws", "Lightning Claws", "Faerie Claws", "Hell Claws", "Cat Claws" };
// Rods - Indexing Offset 6801 (0x1a91)
std::string rods[] = { "Rod", "Flame Rod","Ice Rod","Thunder Rod","Lilith Rod","Polymorph Rod","Faerie Rod","Stardust Rod" };
