// Kyle Fenole
// kfenole.com
//
// Final Fantasy 4 DS Save Editor
// SaveFile.h
//
// This class manages IO and data of the game's save file
//
// Feel free to use anything from this project, but please credit me if you do!
// (Also, if you are working on a similar project, I'd be interested to hear about it)

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Structs.h"

class SaveFile {
public:
	/* Constructor - takes input of filename */
	SaveFile();
	SaveFile(std::string fileName);
	/* Destructor */
	~SaveFile();
	/* In case something goes wrong */
	bool isGood;

	/*-----
	Data Accessors
	------*/
	/* Returns the player's gil amount */
	uint32_t getGil();

	/* Returns the number of inventory slots that the game recongizes are filled */
	uint16_t getNumberOfFilledInventorySlots(); 
	/* Returns the item at the given index. Returns item with id 0 and quantity 0 if empty. Returns item with id 1 and quantity 0 if invalid index */
	item getItemAtIndex(uint16_t);
	/* Returns an array of all items */
	item* getAllItemsInInventory();

	/* Returns the current level of the character at the given index. Returns 0 if an error occurred (i.e. invalid id) */
	uint32_t getLevelofCharacterWithId(uint8_t id);
	/* Returns the current EXP of the character at the given index. Returns 0 if an error occurred (i.e. invalid id) */
	uint32_t getEXPofCharacterWithId(uint8_t id);
	/* Returns the 2 Byte current Hp of character with given id */
	uint16_t getHPofCharacterWithId(uint8_t id);
	/* Returns the 2 Byte max Hp of character with given id */
	uint16_t getMaxHPofCharacterWithId(uint8_t id);
	/* Returns the 2 Byte current Hp of character with given id */
	uint16_t getMPofCharacterWithId(uint8_t id);
	/* Returns the 2 Byte max Hp of character with given id */
	uint16_t getMaxMPofCharacterWithId(uint8_t id);
	/* Returns the 4 byte status code of the players current status condition */
	uint32_t getStatusConditionOfCharacterWithId(uint8_t id);
	/* These functions return the corresponding stat of the character of the given id. They return max value when an error occurs (i.e. bad id). Currently these do not work.*/
	uint8_t getStrengthOfCharacterWithId(uint8_t id);
	uint8_t getStaminaOfCharacterWithId(uint8_t id);
	uint8_t getSpeedOfCharacterWithId(uint8_t id);
	uint8_t getIntellectOfCharacterWithId(uint8_t id);
	uint8_t getSpiritOfCharacterWithId(uint8_t id);

	/*-----
	Data Setters
	------*/
	/* Sets the player's gil to the specified amount*/
	void setGil(uint32_t newValue);
	/* Adds specified amount to player's gil total. Returns false if maximum total reached */
	bool addGil(uint32_t valueToAdd);
	/* Inserts an item at the end of the inventory. Returns false if the inventory spaces are all full */
	bool addItem(item newItem);
	/* Inserts item at the given index, overwriting current item. Returns false and fails if adding to unused inventory indexes. */
	bool insertItemAtIndex(item newItem, uint16_t index);
	/* Edits item quantity at given index. Returns false if invalid index. */
	bool editItemQuantityAtIndex(uint16_t index, uint16_t newValue);
	/* Heal Status Condition of given character id. Returns false if invalid id. */
	bool setStatusOfCharacterWithId(uint8_t id, uint16_t statusId);
	/* Sets the HP of a character with the given id to the given value */
	bool setHPofCharacterWithId(uint8_t id, uint16_t value);
	/* Sets the MP of a character with the given id to the given value */
	bool setMPofCharacterWithId(uint8_t id, uint16_t value);
	/* Adds the given EXP to the character at the given index. Returns false if an error occurred (i.e. invalid index) */
	bool addEXPtoCharacterWithId(uint8_t id, uint32_t exp);

private:
	// The save file
	std::fstream myFile;

	/*------
	Helper functions
	--------*/
	uint32_t convertCharArrayToUnsignedInt(unsigned char* arr, uint8_t len);
	char* convertUnsignedIntToCharArray(uint32_t arr, uint8_t len);
	uint32_t getChecksum();
	void addToChecksum(uint32_t value);
	void incremenetInventorySlotsUsed();

};

