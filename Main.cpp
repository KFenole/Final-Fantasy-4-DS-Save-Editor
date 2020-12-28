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
	cout << "Please enter the name/path of the file you wish to open (i.e. FF4.sav):" << endl;
	string fName;
	cin >> fName;
	SaveFile save(fName);
	if (!save.isGood) {
		cout << "Error loading save file, exiting!" << endl;
		return -1;
	}

	/* Get user input */
	int in = 0;
	while (in != -1) {
		cout << "What would you like to view/edit?" << endl;
		cout << "1: Characters, 2: Gil, 3: Inventory, 4: Item Ids, 5: Help, -1: Exit" << endl;
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
				for (j = 0; j < 3; j++) {
					cout << j + 6501 << ": " << hammers[j] << endl;
				}
				for (j = 0; j < 4; j++) {
					cout << j + 6601 << ": " << axes[j] << endl;
				}
				for (j = 0; j < 6; j++) {
					cout << j + 6701 << ": " << katana[j] << endl;
				}
				for (j = 0; j < 8; j++) {
					cout << j + 6801 << ": " << rods[j] << endl;
				}
				for (j = 0; j < 7; j++) {
					cout << j + 6901 << ": " << staffs[j] << endl;
				}
				for (j = 0; j < 7; j++) {
					cout << j + 7001 << ": " << bows[j] << endl;
				}
				for (j = 0; j < 12; j++) {
					cout << j + 7101 << ": " << arrows[j] << endl;
				}
				for (j = 0; j < 5; j++) {
					cout << j + 7201 << ": " << whips[j] << endl;
				}
				for (j = 0; j < 2; j++) {
					cout << j + 7301 << ": " << boomerangs[j] << endl;
				}
				for (j = 0; j < 2; j++) {
					cout << j + 7401 << ": " << shuriken[j] << endl;
				}
				for (j = 0; j < 13; j++) {
					cout << j + 8001 << ": " << shields[j] << endl;
				}
				for (j = 0; j < 21; j++) {
					cout << j + 8101 << ": " << caps[j] << endl;
				}
				for (j = 0; j < 28; j++) {
					cout << j + 8201 << ": " << clothes[j] << endl;
				}
				for (j = 0; j < 21; j++) {
					cout << j + 8301 << ": " << rings[j] << endl;
				}
				cout << endl;
				break;
			case 5:
				cout << "-- Manual --" << endl;
				cout << "Select an option from the main menu by typing the corresponding number, then enter. Below you will find details on each options:" << endl;
				cout << "1): Characters. This menu will prompt you to choose a character (again by typing the corresponding number followed by enter). The program will then display the selected character's stats, EXP, level, etc." << endl;
				cout << "2): Gil. This will show your current gil, and you can optionally add gil to your total or set a new total. " << endl;
				cout << "3): Inventory. This will list your inventory with ascending numbers corresponding to each item. Each of these numbers is the index of the item in the same row. Use these to select an inventory slot when editing quantities. In this section you can also insert an item at the end of your inventory. Warning: If you insert an item already in your inventory, it will create a new stack of items, not merge the amounts with the already existing stack." << endl; 
				cout << "4): Displays all the item ids which can be referenced when inserting an item." << endl;
				cout << endl;
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
	cout << "Cecil (DK): 0, Cecil (P): 1, Kain: 2, Rosa: 3, Rydia (C): 4, Rydia (A): 5, Tellah: 6, Porom: 7, Palom: 8, Edward: 9, Yang: 10, Cid: 11 " << endl;
	
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
	} else if (id >= 0x1965 && id <= 0x1967) {
		return hammers[id - 0x1965];
	} else if (id >= 0x19C9 && id <= 0x19CC) {
		return axes[id - 0x19C9];
	} else if (id >= 0x1A2D && id <= 0x1A32) {
		return katana[id - 0x1A2D];
	} else if (id >= 0x1A91 && id <= 0x1A98) {
		return rods[id - 0x1A91];
	} else if (id >= 0x1AF5 && id <= 0x1AFB) {
		return staffs[id - 0x1AF5];
	} else if (id >= 0x1B59 && id <= 0x1B5F) {
		return bows[id - 0x1B59];
	} else if (id >= 0x1BBD && id <= 0x1BC8) {
		return arrows[id - 0x1BBD];
	} else if (id >= 0x1C21 && id <= 0x1C25) {
		return whips[id - 0x1C21];
	} else if (id >= 0x1C85 && id <= 0x1C86) {
		return boomerangs[id - 0x1C85];
	} else if (id >= 0x1CE9 && id <= 0x1CEA) {
		return shuriken[id - 0x1CE9];
	} else if (id >= 0x1F41 && id <= 0x1F4D) {
		return shields[id - 0x1F41];
	} else if (id >= 0x1FA5 && id <= 0x1FB9) {
		return caps[id - 0x1FA5];
	} else if (id >= 0x2009 && id <= 0x2024) {
		return clothes[id - 0x2009];
	} else if (id >= 0x206D && id <= 0x2081) {
		return rings[id - 0x206D];
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

	cout << "Strength: " << (int) save.getStrengthOfCharacterWithId(id);
	cout << "  Stamina: " << (int)save.getStaminaOfCharacterWithId(id);
	cout << "  Speed: " << (int)save.getSpeedOfCharacterWithId(id);
	cout << "  Intellect: " << (int)save.getIntellectOfCharacterWithId(id);
	cout << "  Spirit: " << (int) save.getSpiritOfCharacterWithId(id) << endl;

	cout << endl;

}