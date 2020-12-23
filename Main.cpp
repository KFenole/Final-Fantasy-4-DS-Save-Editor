// Kyle Fenole
// kfenole.com
// 
// Main.cpp
//
// Feel free to use anything from this project, but please credit me if you do!
// (Also, if you are working on a similar project, I'd be interested to hear about it)

#include "Main.h"

using namespace std;

int main()
{
	cout << "Welcome to Final Fantasy IV DS Save Editor." << endl;
	cout << "Version 0.4 beta" << endl;

	// Ininitialize the save file with the file name
	SaveFile save("FF4.sav");
	if (!save.isGood) {
		cout << "Error loading save file!" << endl;
		return -1;
	}

	/* Get user input */
	int in = 0;
	while (in != -1) {
		cout << "What would you like to view/edit?" << endl;
		cout << "1: Characters, " << "2: Gil, " << "3: Inventory, 4: Item Ids, "  << "-1: Exit" << endl;
		cin >> in;
		int act;
		if (!checkInput(in)) {
			break;
		} else {
			switch (in) {
			case 0:
				break;
			case 1:
				//printPartyInfo();
				int id;
				id = characterSelection();
				printStatsofChracterWithId(id, save);
				cout << "What would you like to do with this character? 0: Nothing, 1: Heal, 2: Add EXP" << endl;
				cin >> act;
				if (act == 1) {
					save.setHPofCharacterWithId(id, save.getMaxHPofCharacterWithId(id));
					save.setMPofCharacterWithId(id, save.getMaxMPofCharacterWithId(id));
					save.setStatusOfCharacterWithId(id, 0);
					cout << characters[id] << " has full HP & MP, and is cured of their status condition(s)." << endl << endl;
				} else if (act == 2) {
					int exp;
					cout << "Please enter exp to add: ";
					cin >> exp;
					save.addEXPtoCharacterWithId(id, exp);
					cout << "Added " << exp << " EXP to " << characters[id] << "!" << endl << endl;
				}
				else {
					cout << endl << endl;
				}
				break;
			case 2:
				cout << "You have " << save.getGil() << " gil!" << endl;
				cout << "Would you like to do 0: Nothing, 1: Add Gil, 2: Set Gil?" << endl;
				cin >> act;
				int gil;
				if (act == 1) {
					cout << "How much gil would you like to add?: ";
					cin >> gil;
					save.addGil(gil);
					cout << "Added " << gil << " gil, you now have " << save.getGil() << " gil" << endl << endl;
				} else if (act == 2) {
					cout << "Please enter a new gil value: ";
					cin >> gil;
					save.setGil(gil);
					cout << "You now have " << save.getGil() << " gil!" << endl;
				} else {
					cout << endl << endl;
				}
				break;
			case 3:
				uint16_t len;
				len = save.getNumberOfFilledInventorySlots();
				item* inventory;
				inventory = save.getAllItemsInInventory();
				int i;
				for (i = 0; i < len; i++) {
					cout << i << ": " << itemIdToItemName(inventory[i].id) << " (x" << inventory[i].quantity << ")" << endl;
				}
				cout << "Would you like to do 0: Nothing, 1: Edit Quantity, 2: Insert Item" << endl;
				cin >> act;
				if (act == 1) {
					uint16_t index;
					// Get the item id for the item
					cout << "Please enter the index of the item you wish to edit: ";
					cin >> index;
					if (!checkInput(index)) {
						break;
					}
					// Get the quantity
					cout << "Please enter the new quantity of the item: ";
					int newQuantity;
					cin >> newQuantity;
					if (!checkInput(newQuantity)) {
						break;
					}
					save.editItemQuantityAtIndex(index, newQuantity);
				}
				else if (act == 2) {
					item newItem;
					uint16_t newId;
					// Get the item id for the item
					cout << "Please enter the id of the item you wish to insert: ";
					cin >> newId;
					if (!checkInput(newId)) {
						break;
					}
					newItem.id = newId; // set the item id
					uint16_t newQuantity;
					// Get the quantity
					cout << "Please enter the quantity of the item you wish to insert: ";
					cin >> newQuantity;
					if (!checkInput(newQuantity)) {
						break;
					}
					newItem.quantity = newQuantity;
					save.addItem(newItem);
				} else {
					cout << endl << endl;
				}
				break;
			case 4:
				int j;
				cout << "Items Ids: Item Names" << endl;
				for (j = 0; j < 63; j++) {
					cout << j + 5001 << ": " << items[j] << endl;
				}
				for (j = 0; j < 20; j++) {
					cout << j + 6001 << ": " << swords[j] << endl;
				}
				for (j = 0; j < 8; j++) {
					cout << j + 6101 << ": " << spears[j] << endl;
				}
				for (j = 0; j < 4; j++) {
					cout << j + 6201 << ": " << knives[j] << endl;
				}
				for (j = 0; j < 2; j++) {
					cout << j + 6301 << ": " << harps[j] << endl;
				}
				for (j = 0; j < 6; j++) {
					cout << j + 6401 << ": " << claws[j] << endl;
				}
				for (j = 0; j < 8; j++) {
					cout << j + 6801 << ": " << rods[j] << endl;
				}
				break;
			default:
				break;
			}
		}
	}

	

	

	return 0;
}
bool checkInput(uint32_t) {
	// Try and catch invalid input
	if (!cin) {
		cout << "Invalid input, try again with a number, max value is " << UINT32_MAX << "!" << endl << endl;
		// Reset cin
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	return true;
}

int characterSelection() {
	// Gets user input and returns the character id
	cout << endl << "Choose a character whose stats you wish to view/modify: " << endl;
	cout << "Cecil (DK): 0, Cecil (P): 1, Kain: 2, Rosa: 3, Rydia: 4, Tellah: 6, Porom: 7, Palom: 8, Edward: 9, Cid: 11 " << endl;
	
	int in;
	cin >> in;
	// Catch invalid input like letters
	if (!cin) {
		cout << "Invalid input, defaulting to Cecil" << endl << endl;
		// Reset cin
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return 0;
	}

	return in;
}
string itemIdToItemName(uint16_t id) {
	if (id >= 0x1389 && id <= 0x13C6) {
		return items[id - 0x1389];
	} else if (id >= 0x1771 && id <= 0x1784) {
		return swords[id - 0x1771];
	} else if (id >= 0x17D5 && id <= 0x17DC) {
		return spears[id - 0x17D5];
	} else if (id >= 0x1839 && id <= 0x183C) {
		return knives[id - 0x1839];
	} else if (id >= 0x189D && id <= 0x189E) {
		return harps[id - 0x189D];
	} else if (id >= 0x1901 && id <= 0x1906) {
		return claws[id - 0x1901];
	} else if (id >= 0x1A91 && id <= 0x1A98) {
		return rods[id - 0x1A91];
	} else {
		return "?????";
	}
}
void printStatsofChracterWithId(uint8_t id, SaveFile &save) {
	cout << "-- " << characters[id] << " --" << endl;

	cout << "Level: " << save.getLevelofCharacterWithId(id);
	cout << "  EXP: " << save.getEXPofCharacterWithId(id) << endl;

	cout << "HP: " << save.getHPofCharacterWithId(id);
	cout << " / " << save.getMaxHPofCharacterWithId(id);
	cout << "  "; 
	cout << "MP: " << save.getMPofCharacterWithId(id);
	cout << " / " << save.getMaxMPofCharacterWithId(id) << endl;

	//cout << "Strength: " << save.getStrengthOfCharacterWithId(id);
	//cout << "Strength: " << save.getStrengthOfCharacterWithId(id);
	/*
	cout << "  Stamina: " << save.getStaminaOfCharacterWithId(id);
	cout << "  Speed: " << save.getSpeedOfCharacterWithId(id);
	cout << "  Intellect: " << save.getIntellectOfCharacterWithId(id);
	cout << "  Spirit: " << save.getSpiritOfCharacterWithId(id) << endl;
	*/
	cout << endl;

}