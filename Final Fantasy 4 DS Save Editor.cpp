// Kyle Fenole
// kfenole.com
// 
// Final Fantasy 4 DS Save Editor.cpp
//

#include "Final Fantasy 4 DS Save Editor.h"

using namespace std;

fstream file;

int main()
{
	cout << "Welcome to Final Fantasy IV DS Save Editor." << endl;
	cout << "Version 0.3 beta" << endl;


	/* Open up the file */
	file.open("FF4.sav", ios::in | ios::out | ios::binary);
	if (!file) {
		cout << "Cannot open file! Must be called 'FF4.sav'" << endl;
		return 1;
	}

	/* Get user input */
	cout << "Save file succesfully loaded!" << endl;
	int in = 0;
	while (in != -1) {
		cout << "1: View Party Info" << endl << "2: View Character" << endl << "3: View Current Gil" << endl << "4: Set Gil" << endl <<  "5: View Inventory" << endl << "6: Edit Inventory" << endl << "-1: Exit" << endl;
		cin >> in;
		switch (in) {
		case 0:
			printChecksum();
			break;
		case 1:
			printPartyInfo();
			break;
		case 2:
			viewCharacter(characterSelection());
			break;
		case 3:
			printGil();
			break;
		case 4:
			setGil();
			break;
		case 5:
			printInventory();
			break;
		case 6:
			editInventory();
			break;
		default:
			break;
		}
	}

	

	
	file.close();

	return 0;
}

/* Data Processing Functions */
uint32_t convertCharArrayToUnsignedInt(unsigned char * arr, uint8_t len) {
	/* Convert to Integer */
	uint32_t value;
	value = 0;
	int i;
	for (i = 0; i < len; i++) {
		value += (((uint32_t) (arr[i])) << (i * 8));
	}

	return value;
}
char* convertUnsignedIntToCharArray(uint32_t arr, uint8_t len) {
	unsigned char* buffer = new unsigned char[len]; // allocate memory for the buffer

	int i;
	for (i = 0; i < len; i++) {
		int bitfield = 0; // UINT32_MAX << (i * 8);
		uint8_t x = arr >> (i * 8);
		buffer[i] = bitfield ^ x;
	}

	return (char*) buffer;
}

/* Checksum Functions */
uint32_t getChecksum() {
	file.seekg(0x1C);
	if (!file) {
		cout << "Error Seeking" << endl;
	}

	unsigned char checksumData[4]; // 4 Byte buffer fo reading values

	file.read((char*)checksumData, 4); // checksumData now holds the bytes 

	return convertCharArrayToUnsignedInt(checksumData, 4);
}
void printChecksum() {
	file.seekg(0x1C);
	if (!file) {
		cout << "Error Seeking" << endl;
	}

	unsigned char checksumData[4]; // 4 Byte buffer fo reading values

	file.read((char*)checksumData, 4); // checksumData now holds the bytes 
	if (!file) {
		cout << "Error Reading" << endl;
	}

	/* Convert to Integer */
	uint32_t checksum;
	checksum = 0;
	int i;
	for (i = 0; i < 4; i++) {
		checksum += (((uint32_t) (checksumData[i])) << (i * 8));
	}

	cout << checksum << endl;
}
void addToChecksum(uint32_t value) {
	// Update checksum by adding difference to current value
	uint32_t newChecksum = getChecksum() + value;
	file.seekg(0x1C);
	char* buffer; // 4 Byte buffer for new value
	buffer = convertUnsignedIntToCharArray(newChecksum, 4);
	file.write(buffer, 4);
	delete[] buffer;
}

/* Gil Functions*/
uint32_t getGil() {
	file.seekg(0x94);

	unsigned char buffer[4]; // 4 Byte buffer
	// Read Gil into buffer
	file.read((char*)buffer, 4);
	uint32_t gil = convertCharArrayToUnsignedInt(buffer, 4);

	return gil;
}
void printGil() {
	file.seekg(0x94);

	unsigned char buffer[4]; // 4 Byte buffer
	// Read Gil into buffer
	file.read((char*)buffer, 4);
	uint32_t gil = convertCharArrayToUnsignedInt(buffer, 4);
	cout << "Current Gil: " << gil << endl << endl;
}
int setGil() {
	// See how much gil the user wants
	uint32_t newValue = 0;
	cout << "Please enter a number for the new gil: ";
	cin >> newValue;
	// Try and catch invalid input
	if (!cin) {
		cout << "Invalid input, try again with a number, max value is " << UINT32_MAX << "!" << endl << endl;
		// Reset cin
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		return -1;
	}


	uint32_t currentValue = getGil();
	uint32_t difference = newValue - currentValue; // calculate the difference to add to checksum

	// Update checksum by adding difference to current value
	addToChecksum(difference);

	char* buffer; // 4 Byte buffer for new value


	// Actually write the new gil to file
	file.seekg(0x94);
	buffer = convertUnsignedIntToCharArray(newValue, 4);
	file.write(buffer, 4);
	delete[] buffer; // Deallocate buffer

	cout << "You now have " << newValue << " gil!" << endl << endl;

	return 0;
}


/* Character and Party Functions*/
int printPartyInfo() {
	cout << endl << "Party Info: " << endl;
	unsigned char buffer[2]; // 2 Byte buffer

	int i;
	for (i = 0; i < 3; i++) {
		cout << "Slot " << i;
		// Seek to beginning of character
		file.seekg(0x30 + (i * 0x14));
		file.read((char*)buffer, 1);
		uint8_t charID = convertCharArrayToUnsignedInt(buffer, 1);
		switch (charID) {
		case 0x00:
			cout << ": Cecil ";
			break;
		case 0x04:
			cout << ": Rydia ";
			break;
		case 0x06:
			cout << ": Tellah ";
			break;
		default:
			cout << ": Unknown ";
			break;
		}
		file.read((char*)buffer, 1);
		cout << "Level " << convertCharArrayToUnsignedInt(buffer, 1);

		// Seek to the character's health
		file.seekg(0x34 + (i * 0x14));

		//Read in and display the HP values
		file.read((char*)buffer, 2);
		cout << "  HP: " << convertCharArrayToUnsignedInt(buffer, 2) << " / ";
		file.read((char*)buffer, 2);
		cout << convertCharArrayToUnsignedInt(buffer, 2);

		// MP
		file.read((char*)buffer, 2);
		cout << "  MP: " << convertCharArrayToUnsignedInt(buffer, 2) << " / ";
		file.read((char*)buffer, 2);
		cout << convertCharArrayToUnsignedInt(buffer, 2) << endl;
	}
	
	cout << endl;


	return 0;
}

void viewCharacter(int charID) {
	// Identify Stats of chosen Character
	cout << "Current Stats: " << endl;
	switch (charID) {
	case 0x00:
		cout << "-- Cecil --" << endl;
		break;
	case 0x04:
		cout << "-- Rydia --" << endl;
		break;
	case 0x06:
		cout << "-- Tellah --" << endl;
		break;
	default:
		cout << "-- Unknown --" << endl;
		break;
	}

	// Start Reading in Values
	unsigned char buffer[4]; // 4 Byte buffer
	// Level
	file.seekg(0xA4 + (charID * 0x1C0));
	file.read((char*)buffer, 4);
	cout << "Level: " << convertCharArrayToUnsignedInt(buffer, 4);

	// EXP
	file.read((char*)buffer, 4);
	cout << " EXP: " << convertCharArrayToUnsignedInt(buffer, 4) << endl;

	// HP
	file.seekg(0xB0 + (charID * 0x1C0));
	file.read((char*)buffer, 4);
	cout << "HP: " << convertCharArrayToUnsignedInt(buffer, 4);

	// Max HP
	file.read((char*)buffer, 4);
	cout << " / " << convertCharArrayToUnsignedInt(buffer, 4);

	// MP
	file.read((char*)buffer, 4);
	cout << "  MP: " << convertCharArrayToUnsignedInt(buffer, 4);

	// Max MP
	file.read((char*)buffer, 4);
	cout << " / " << convertCharArrayToUnsignedInt(buffer, 4);

	// Strength
	file.seekg(0x25A + (charID * 0x1C0));
	file.read((char*)buffer, 1);
	cout << endl << "Strength: " << convertCharArrayToUnsignedInt(buffer, 1);

	// Stamina
	file.read((char*)buffer, 1);
	cout << "  Stamina: " << convertCharArrayToUnsignedInt(buffer, 1);

	// Speed
	file.read((char*)buffer, 1);
	cout << "  Speed: " << convertCharArrayToUnsignedInt(buffer, 1);

	// Intellect
	file.read((char*)buffer, 1);
	cout <<  "  Intellect: " << convertCharArrayToUnsignedInt(buffer, 1);

	// Spirit
	file.read((char*)buffer, 1);
	cout << "  Spirit: " << convertCharArrayToUnsignedInt(buffer, 1);

	cout << endl << "Would you like to edit this character? (y/n)" << endl;
	char in;
	cin >> in;
	if (tolower(in) == 'y') {
		editCharacter(charID);
	}
	else {
		cout << endl << endl;
	}
}
int characterSelection() {
	// Gets user input and returns the character id
	cout << endl << "Choose a character whose stats you wish to view/modify: " << endl;
	cout << "Cecil: 0, Rydia: 4, Tellah: 6" << endl;
	
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
int editCharacter(int charID) {
	// Get User input for which stat they want to change and to what value
	cout << "Which stat do you wish to modify: " << endl;
	cout << "(Warning: Changing EXP or Level doesn't really affect stats!)" << endl;

	cout << "Level: 0, EXP: 1, HP: 2, MaxHP: 3, MP: 4, MaxMP: 5, Strength: 6, Stamina: 7, Speed: 8, Intellect: 9, Spirit: 10, Exit: -1" << endl;
	int statID;
	cin >> statID;
	// Catch invalid input like letters
	if (!cin) {
		cout << "Invalid input, try again!" << endl << endl;
		// Reset cin
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return -1;
	}
	// If the user changes their mind on editing
	if (statID == -1) {
		return 2;
	}

	cout << "What value do you want to set it to?" << endl;
	uint32_t newValue;
	cin >> newValue;
	// Catch invalid input like letters
	if (!cin) {
		cout << "Invalid input, try again!" << endl << endl;
		// Reset cin
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return -1;
	}

	uint32_t ogValue;
	unsigned char buffer[4]; // 4 Byte buffer
	int seekLoc;
	// Handle the input
	switch (statID) {
	case 0:
		seekLoc = (0xA4 + (charID * 0x1C0));
		cout << "Character's level is now ";
		break;
	case 1:
		seekLoc = (0xA8 + (charID * 0x1C0));
		cout << "Character's EXP is now ";
		break;
	case 2:
		seekLoc = (0xB0 + (charID * 0x1C0));
		cout << "Character's HP is now ";
		break;
	case 3:
		seekLoc = (0xB4 + (charID * 0x1C0));
		cout << "Character's Max HP is now ";
		break;
	case 4:
		seekLoc = (0xB8 + (charID * 0x1C0));
		cout << "Character's MP is now ";
		break;
	case 5:
		seekLoc = (0xBC + (charID * 0x1C0));
		cout << "Character's Max MP is now ";
		break;
	case 6:
		seekLoc = (0x25A + (charID * 0x1C0));
		cout << "Character's Strength is now ";
		break;
	case 7:
		seekLoc = (0x25B + (charID * 0x1C0));
		cout << "Character's Stamina is now ";
		break;
	case 8:
		seekLoc = (0x25C + (charID * 0x1C0));
		cout << "Character's Speed is now ";
		break;
	case 9:
		seekLoc = (0x25D + (charID * 0x1C0));
		cout << "Character's Intellect is now ";
		break;
	case 10:
		seekLoc = (0x25E + (charID * 0x1C0));
		cout << "Character's Spirit is now ";
		break;
	default:
		cout << "Error Invalid StatID" << endl << endl;
		return -1;
	}

	file.seekg(seekLoc);
	// If reading the stats before ID #6, 4 Bytes, otherwise 1 Byte
	if (statID < 6) {
		file.read((char*)buffer, 4);
		ogValue = convertCharArrayToUnsignedInt(buffer, 4);
	} else {
		// Also cap the value to 8 bit maximum if it's larger
		newValue = (newValue > UINT8_MAX) ? UINT8_MAX : newValue;

		file.read((char*)buffer, 1);
		ogValue = convertCharArrayToUnsignedInt(buffer, 1);
	}
	

	// Update Checksum, ID#6+ weighted in checksum (probably condensed in a 32 bit number or structure)
	if (statID < 6) {
		addToChecksum(newValue - ogValue);
	}
	else if (statID == 6) {
		addToChecksum((newValue - ogValue) << 16);
	}
	else if (statID == 7) {
		addToChecksum((newValue - ogValue) << 24);
	}
	else if (statID == 9) {
		addToChecksum((newValue - ogValue) << 8);
	}
	else if (statID == 10) {
		addToChecksum((newValue - ogValue) << 16);
	}
	else {
		addToChecksum(newValue - ogValue);
	}

	// Update Value
	file.seekg(seekLoc);
	char *writeBuffer;
	// If reading the stats before ID #6, 4 Bytes, otherwise 1 Byte
	if (statID < 6) {
		writeBuffer = convertUnsignedIntToCharArray(newValue, 4);
		file.write(writeBuffer, 4);
	} else {
		writeBuffer = convertUnsignedIntToCharArray(newValue, 1);
		file.write(writeBuffer, 1);
	}
	delete[] writeBuffer; // Deallocate the buffer

	// Finish the message
	cout << newValue << "!" << endl << endl;

	return 0;
}


/* Inventory Functions */
int printInventory() {
	cout << "Inventory:" << endl;
	int c;
	c = 0;
	bool end;
	end = false;
	file.seekg(0x19E0);
	while (end == false && file.tellg() < 0x1FE0) {
		unsigned char buffer[2]; // 2 Byte buffer
		file.read((char*)buffer, 2);
		uint16_t val = convertCharArrayToUnsignedInt(buffer, 2);
		if (c % 2 == 0) {
			// If we reach the end of the used inventory
			if (val == 0) {
				end = true;
				break;
			}

			cout << c / 2 << ": ";
			// Check and see if we have the item in the names array
			if (val >= 0x1389 && val <= 0x13C6) {
				cout << items[val - 0x1389];
			}
			else if (val >= 0x1A91 && val <= 0x1A98) {
				cout << items[val - 0x1A91];
			} else {
				cout << "?????";
			}
			//cout << itemNumberToName(val);
		} else {
			cout << " (x" << val << ")" << endl;
		}
		c++;
	}
	cout << c / 2 << ": Empty" << endl;
	cout << endl;
	return (c / 2); // first index of blank inventory slot. 
}
void editInventory() {
	// Show the user their current inventory and get the last index
	int last = printInventory(); // the first free index.

	// Ask them what they want to change
	cout << "Which index would you like to change?" << endl;
	int in;
	cin >> in;
	// Catch invalid input like letters
	if (!cin) {
		cout << "Invalid input, try again!" << endl << endl;
		// Reset cin
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	int act;
	uint16_t newValue;
	// If they are editing a blank index, change the type and quantity at the same time (i.e. insert).
	if (in == last) {
		act = 0;
		cout << "Inserting item. What item ID would you like to insert? (-1 to exit) " << endl;
		cin >> newValue;
		// Try and catch invalid input
		if (!cin) {
			cout << "Invalid input, try again!" << endl << endl;
			// Reset cin
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}
		// Return if they change their mind
		if (newValue == -1) {
			return;
		}
		// Update the number of active slots in the inventory
		file.seekg(0x1FE0);
		char* writebuffer; // 1 Byte buffer for new value
		writebuffer = convertUnsignedIntToCharArray(last + 1, 2); // The new total number of inventory slots
		file.write(writebuffer, 1);
		delete[] writebuffer; // Deallocate the write buffer

		// Now update the checksum by 1
		addToChecksum(1);
	} else {
		cout << "Would you like to 0: Edit Type or 1: Edit quantity?" << endl;
		cin >> act;
		// Try and catch invalid input
		if (!cin) {
			cout << "Invalid input, try again!" << endl << endl;
			// Reset cin
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}
		// If they change their minds and try to leave
		if (act != 0 && act != 1) {
			return;
		}
		cout << "What value would you like to set?" << endl;
		cin >> newValue;
	}

	
	while (act == 0 || act == 1) {
		file.seekg(0x19E0 + (4 * in) + (2 * act));
		unsigned char readBuffer[2];
		file.read((char*)readBuffer, 2);
		uint16_t oldValue = convertCharArrayToUnsignedInt(readBuffer, 2);

		// Update Checksum
		if (act == 1) {
			addToChecksum((newValue - oldValue) << 16);
		} else {
			addToChecksum(newValue - oldValue);
		}

		file.seekg(0x19E0 + (4 * in) + (2 * act));
		char* writebuffer; // 2 Byte buffer for new value
		writebuffer = convertUnsignedIntToCharArray(newValue, 2);
		file.write(writebuffer, 2);
		delete[] writebuffer; // Deallocate the write buffer

		// Change action to exit loop or set up for next iteration
		if ((in != last) || (act  == 1)) { // handles both cases where we are just editing, and handles the case we are done inserting
			act = 2;
		} else if (in == last && act == 0) { // handles the case we are inserting, but have only set the item so far
			cout << "How many would you like to insert? " << endl;
			cin >> newValue;
			act++;
		}
	}
	cout << "Successfully Made Change" << endl << endl;
}