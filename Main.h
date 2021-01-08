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

std::string	 characters[] = { "Cecil (Dark Knight)", "Cecil (Paladin)", "Kain", "Rosa", "Rydia (Child)", "Rydia (Adult)", "Tellah", "Porom", "Palom", "Edward", "Yang", "Cid", "Edge", "Fusoya" };
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
// Hammers - Indexing offset 6501 (0x1965)
std::string hammers[] = { "Wooden Hammer", "Mythril Hammer", "Gaia Hammer" };
// Axes - Indexing offset 6601 (0x19C9)
std::string axes[] = { "Dwarven Axe", "Ogrekiller", "Poison Axe", "Rune Axe" };
// Katana - Indexing offset 6701 (0x1A2D)
std::string katana[] = { "Kunai", "Ashura", "Kotetsu", "Kiku-ichimonji", "Murasame", "Masamune" };
// Rods - Indexing Offset 6801 (0x1a91)
std::string rods[] = { "Rod", "Flame Rod","Ice Rod","Thunder Rod","Lilith Rod","Polymorph Rod","Faerie Rod","Stardust Rod" };
// Staffs - Indexing Offset 6901 (0x1AF5)
std::string staffs[] = { "Staff", "Healing Staff", "Mythril Staff", "Power Staff", "Aura Staff", "Sage's Staff", "Rune Staff" };
// Bows - Indexing Offset 7001 (0x1B59)
std::string bows[] = { "Bow", "Power Bow", "Great Bow", "Killer Bow", "Elven Bow", "Yoichi Bow", "Artemis Bow" };
// Arrows - Indexing Offset 7101 (0x1BBD)
std::string arrows[] = { "Medusa Arrows", "Iron Arrows", "Holy Arrows", "Fire Arrows", "Ice Arrows", "Lightning Arrows", "Blinding Arrows", "Poison Arrows", "Silencing Arrows", "Angel Arrows", "Yoichi Arrows", "Artemis Arrows" };
// Whips - Indexing Offset 7201 (0x1C21)
std::string whips[] = { "Whip", "Chain Whip", "Blitz Whip", "Flame Whip", "Dragon Whisker" };
// Boomerangs - Indexing Offset 7301 (0x1C85)
std::string boomerangs[] = { "Boomerang", "Moonring Blade" };
// Shuriken - Indexing Offset 7401 (0x1CE9)
std::string shuriken[] = { "Shuriken", "Fuma Shuriken" };
// Shields - Indexing Offset 8001 (0x1F41)
std::string shields[] = { "Iron Shield", "Dark Shiled", "Demon Shield", "Lustrous Shield", "Mythril Shield", "Flame Shield", "Ice Shield", "Diamond Shield", "Aegis Shield", "Genji Shield", "Dragon Shield", "Crystal Shield", "Onion Shield" };
// Caps - Indexing Offset 8101 (0x1FA5)
std::string caps[] = { "Leather Cap", "Headband", "Feathered Cap", "Iron Helm", "Wizard's Hat", "Green Beret", "Dark Helm", "Hades Helm", "Sage's Miter", "Black Cowl", "Demon Helm", "Lustrous Helm", "Gold Hairpin", "Mythril Helm", "Diamond Helm", "Ribbon", "Genji Helm", "Dragon Helm", "Crystal Helm", "Glass Mask", "Onion Helm" };
// Clothes - Indexing Offset 8201 (0x2009)
std::string clothes[] = { "Clothing", "Prison Garb", "Leather Clothing", "Bard's Tunic", "Gaia Gear", "Iron Armor", "Dark Armor", "Sage's Surplice", "Kenpo Gi", "Hades Armor", "Black Robe", "Demon Armor", "Black Belt Gi", "Knight's Armor", "Luminous Robes", "Mythril Armor", "Flame Mail", "Power Sash", "Ice Armor", "White Robe", "Diamond Armor", "Minerva Bustier", "Genji Armor", "Dragon Mail", "Black Garb", "Crystal Mail", "Adamant Armor", "Onion Armor" };
// Rings - Indexing Offset 8301 (0x206D)
std::string rings[] = { "Ruby Rings", "Cursed Ring", "Iron Gloves", "Dark Gloves", "Iron Armlet", "Power Armlet", "Hades Gloves", "Demon Gloves", "Silver Armlet", "Gauntlets", "Rune Armlet", "Mythril Gloves", "Diamond Armlet", "Diamond Gloves", "Genji Gloves", "Dragon Gloves", "Giant's Gloves", "Crystal Gloves", "Protect Ring", "Crytal Ring", "Onion Gloves" };

// Key Items
// Story Key Items - Indexing Offset 0x2329 (x15)
std::string keyItems1[] = { "Frying Pan", "Adamantite", "????", "Sand Pearl", "Dark Matter", "Earth Crystal", "Rat Tail", "Barron Key", "Whisperweed", "Pink Tail", "Carnelian Signet", "Magma Stone", "Dark Crystal", "Luca’s Necklace", "Lugae’s Key" };
// Summon Items & Augments - Indexing Offset 0x238C (x23)
std::string keyItems2[] = { "Goblin", "Bomb", "Cockatrice", "Mindflayer", "Bardsong", "Salve", "Hide", "Twincast", "Cry", "Bluff", "Recall", "Fast Talker", "Dualcast", "Analyze", "Upgrade", "Adrenaline", "Focus", "Brace", "Kick", "Bless", "Last Stand", "Phoenix", "Limit Break" };
// Indexing offset 0x23B0 (x23)
std::string keyItems3[] = { "Auto Potion", "Omnicasting", "Item Lore", "Counter", "MP +50%", "?????", "Piercing Magic", "HP +50%", "?????", "Reach", "Level Lust", "Gil Farmer", "Treasure Hunter", "Curse", "Tsunami", "Whirlwind", "Inferno", "Draw Attacks", "Eye Gouge", "Safe Travel", "Twincast", "Twincast", "Darkness" };
