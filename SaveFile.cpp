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

#include "SaveFile.h"

using namespace std;

/* Constructors */
SaveFile::SaveFile() {
	isGood = true;
    slotIndex = 0;
    slotOffset = (slotIndex * 0x3DC0);
    
	myFile.open("FF4.sav", ios::in | ios::out | ios::binary);

	if (!myFile || !myFile.is_open()) {
		cout << "Cannot open file called FF4.sav!" << endl;
		isGood = false;
	} else {
		cout << "Save file succesfully loaded!" << endl;
	}
}
SaveFile::SaveFile(std::string fileName) {
	isGood = true;
    slotIndex = 0;
    slotOffset = (slotIndex * 0x3DC0);

	/* Open up the file */
	myFile.open(fileName, ios::in | ios::out | ios::binary);

	if (!myFile || !myFile.is_open()) {
		cout << "Cannot open file called " << fileName << "!" << endl;
		isGood = false;
	} else {
		cout << "Save file succesfully loaded!" << endl;
	}
}
/* Destructor */
SaveFile::~SaveFile() {
	myFile.close();
}

/*-----
 Configuration
 -----*/
void SaveFile::setSaveSlot(int saveSlot) {
    slotIndex = saveSlot - 1;
    slotOffset = (slotIndex * 0x3DC0);
}
int SaveFile::getSaveSlot() {
    return slotIndex + 1;
}

/*-----
Data Accessors
------*/
uint32_t SaveFile::getGil() {
    myFile.seekg(0x21E8 + slotOffset);

	unsigned char buffer[4]; // 4 Byte buffer
	// Read Gil into buffer
	myFile.read((char*)buffer, 4);
	uint32_t gil = convertCharArrayToUnsignedInt(buffer, 4);

	return gil;
}
/* --------
 Inventory Getters
 ---------*/
uint16_t SaveFile::getNumberOfFilledInventorySlots() {
	myFile.seekg(0x1FE0 + slotOffset);
	unsigned char buffer[2]; // 2 Byte buffer
	// Read quantity into buffer
	myFile.read((char*)buffer, 2);
	uint16_t quantity = convertCharArrayToUnsignedInt(buffer, 2);

	return quantity;
}
item SaveFile::getItemAtIndex(uint16_t index) {
	// If the index is outside the range of inventory memory
	if (index > 0x180) {
		//then return
		return { 1, 0 };
	}
	int seekLocation = 0x19E0 + (index * 4);
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location
	unsigned char buffer[2]; // 2 Byte buffer
	myFile.read((char*)buffer, 2);
	// Get the item id
	uint16_t itemID = convertCharArrayToUnsignedInt(buffer, 2);
	// Read the quantity
	myFile.read((char*)buffer, 2);
	// Get the quantity
	uint16_t quantity = convertCharArrayToUnsignedInt(buffer, 2);


	return { itemID, quantity };
}
item* SaveFile::getAllItemsInInventory() {
	// Number of filled inventory slots
	uint16_t numberOfItems = getNumberOfFilledInventorySlots();
	// Allocate array for items in inventory
	static item* inventory = new item[numberOfItems];

	myFile.seekg(0x19E0 + slotOffset); // Move cursor to item location.
	// Traverse over the items in the inventory. No other function call causes cursor to jump, so we don't need to reset it each iteration
	int i;
	for (i = 0; i < numberOfItems; i++) {
		unsigned char buffer[2]; // 2 Byte buffer
		myFile.read((char*)buffer, 2);
		// Keep the item id
		uint16_t itemID = convertCharArrayToUnsignedInt(buffer, 2);
		// Read the quantity
		myFile.read((char*)buffer, 2);
		// Get the quantity
		uint16_t quantity = convertCharArrayToUnsignedInt(buffer, 2);

		inventory[i] = { itemID, quantity };
	}

	return inventory;
}

/*--------
 Key Item Getters
 ---------*/
uint16_t SaveFile::getNumberOfFilledKeyInventorySlots() {
    myFile.seekg(0x21E4 + slotOffset);
    unsigned char buffer[2]; // 2 Byte buffer
    // Read quantity into buffer
    myFile.read((char*)buffer, 2);
    uint16_t quantity = convertCharArrayToUnsignedInt(buffer, 2);

    return quantity;
}
item SaveFile::getKeyItemAtIndex(uint16_t index) {
    // If the index is outside the range of inventory memory
    if (index > 0x21E3) {
        //then return
        return { 1, 0 };
    }
    int seekLocation = 0x1FE4 + (index * 4);
    myFile.seekg(seekLocation + slotOffset); // Move cursor to item location
    unsigned char buffer[2]; // 2 Byte buffer
    myFile.read((char*)buffer, 2);
    // Get the item id
    uint16_t itemID = convertCharArrayToUnsignedInt(buffer, 2);
    // Read the quantity
    myFile.read((char*)buffer, 2);
    // Get the quantity
    uint16_t quantity = convertCharArrayToUnsignedInt(buffer, 2);


    return { itemID, quantity };
}
item* SaveFile::getAllKeyItemsInInventory() {
    // Number of filled inventory slots
    uint16_t numberOfItems = getNumberOfFilledKeyInventorySlots();
    // Allocate array for items in inventory
    static item* inventory = new item[numberOfItems];

    myFile.seekg(0x1FE4 + slotOffset); // Move cursor to item location.
    // Traverse over the items in the inventory. No other function call causes cursor to jump, so we don't need to reset it each iteration
    int i;
    for (i = 0; i < numberOfItems; i++) {
        unsigned char buffer[2]; // 2 Byte buffer
        myFile.read((char*)buffer, 2);
        // Keep the item id
        uint16_t itemID = convertCharArrayToUnsignedInt(buffer, 2);
        // Read the quantity
        myFile.read((char*)buffer, 2);
        // Get the quantity
        uint16_t quantity = convertCharArrayToUnsignedInt(buffer, 2);

        inventory[i] = { itemID, quantity };
    }

    return inventory;
}

/* Character Getters */
uint32_t SaveFile::getLevelofCharacterWithId(uint8_t id) {
	if (id > 13) {
		return 0;
	}

	int seekLocation = 0xA4 + (id * 0x1C0); // Cecil level is at 0xA4, each character's data is 0x1C0 in length
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location

	unsigned char buffer[4]; // 4 Byte buffer
	myFile.read((char*)buffer, 4);
	// Get the level
	uint32_t level = convertCharArrayToUnsignedInt(buffer, 4);

	return level;
}
uint32_t SaveFile::getEXPofCharacterWithId(uint8_t id) {
	if (id > 13) {
		return 0;
	}

	int seekLocation = 0xA8 + (id * 0x1C0); // Cecil Exp is at 0xA8, each character's data is 0x1C0 in length
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location

	unsigned char buffer[4]; // 4 Byte buffer
	myFile.read((char*)buffer, 4);
	// Get the exp
	uint32_t exp = convertCharArrayToUnsignedInt(buffer, 4);

	return exp;
}
uint16_t SaveFile::getHPofCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id or character hasnt been discovered in game yet
		return UINT16_MAX;
	}

	int seekLocation = 0xB0 + (id * 0x1C0); // Cecil's (0th character in data) HP is at 0xB0, each character's data is 0x1C0 in length
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location

	unsigned char buffer[2]; // 2 Byte buffer
	myFile.read((char*)buffer, 2);
	// Get the exp
	uint16_t hp = convertCharArrayToUnsignedInt(buffer, 2);

	return hp;
}
uint16_t SaveFile::getMaxHPofCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id or character hasnt been discovered in game yet
		return UINT16_MAX;
	}

	int seekLocation = 0xB4 + (id * 0x1C0); // Cecil's (0th character in data) Max HP is at 0xB4, each character's data is 0x1C0 in length
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location

	unsigned char buffer[2]; // 2 Byte buffer
	myFile.read((char*)buffer, 2);
	// Get the exp
	uint16_t maxHp = convertCharArrayToUnsignedInt(buffer, 2);

	return maxHp;
}
uint16_t SaveFile::getMPofCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id or character hasnt been discovered in game yet
		return UINT16_MAX;
	}

	int seekLocation = 0xB8 + (id * 0x1C0); // Cecil's (0th character in data) HP is at 0xB8, each character's data is 0x1C0 in length
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location

	unsigned char buffer[2]; // 2 Byte buffer
	myFile.read((char*)buffer, 2);
	// Get the exp
	uint16_t mp = convertCharArrayToUnsignedInt(buffer, 2);

	return mp;
}
uint16_t SaveFile::getMaxMPofCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id or character hasnt been discovered in game yet
		return UINT16_MAX;
	}

	int seekLocation = 0xBC + (id * 0x1C0); // Cecil's (0th character in data) Max HP is at 0xBC, each character's data is 0x1C0 in length
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location

	unsigned char buffer[2]; // 2 Byte buffer
	myFile.read((char*)buffer, 2);
	// Get the exp
	uint16_t maxMp = convertCharArrayToUnsignedInt(buffer, 2);

	return maxMp;
}
uint32_t SaveFile::getStatusConditionOfCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id
		return UINT32_MAX;
	}

	int seekLoc = 0xC0 + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

	unsigned char buffer[4]; // 4 Byte buffer for new value
	myFile.read((char*)buffer, 4);

	return convertCharArrayToUnsignedInt(buffer, 4);
}
uint8_t SaveFile::getStrengthOfCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id
		return UINT8_MAX;
	}

	int seekLoc = 0x25A + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

	unsigned char buffer[1]; // 1 Byte buffer for new value
	myFile.read((char*)buffer, 1);

	return convertCharArrayToUnsignedInt(buffer, 1);
}
uint8_t SaveFile::getStaminaOfCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id
		return UINT8_MAX;
	}

	int seekLoc = 0x25B + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

	unsigned char buffer[1]; // 1 Byte buffer for new value
	myFile.read((char*)buffer, 1);

	return convertCharArrayToUnsignedInt(buffer, 1);
}
uint8_t SaveFile::getSpeedOfCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id
		return UINT8_MAX;
	}

	int seekLoc = 0x25C + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

	unsigned char buffer[1]; // 1 Byte buffer for new value
	myFile.read((char*)buffer, 1);

	return convertCharArrayToUnsignedInt(buffer, 1);
}
uint8_t SaveFile::getIntellectOfCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id
		return UINT8_MAX;
	}

	int seekLoc = 0x25D + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

	unsigned char buffer[1]; // 1 Byte buffer for new value
	myFile.read((char*)buffer, 1);

	return convertCharArrayToUnsignedInt(buffer, 1);
}
uint8_t SaveFile::getSpiritOfCharacterWithId(uint8_t id) {
	if (id > 13) {
		// Invalid Id
		return UINT8_MAX;
	}

	int seekLoc = 0x25E + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

	unsigned char buffer[1]; // 1 Byte buffer for new value
	myFile.read((char*)buffer, 1);

	return convertCharArrayToUnsignedInt(buffer, 1);
}
uint8_t SaveFile::getPartyMemberCharacterIDAtSlot(uint8_t slot) {
    // 0x30 - party 0
    // 0x44 - party 1 - size 0x14
    if (slot > 5) {
        // Invalid index
        return UINT8_MAX;
    }

    int seekLoc = 0x30 + (slot * 0x14); // The location of the status code
    myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

    unsigned char buffer[1]; // 1 Byte buffer for new value
    myFile.read((char*)buffer, 1);

    return convertCharArrayToUnsignedInt(buffer, 1);
}
bool SaveFile::isPartyMemberSetAtSlot(uint8_t slot) {
    if (slot > 5) {
        // Invalid index
        return false;
    }
    int seekLoc = 0x32 + (slot * 0x14); // The location of the status code
    myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code

    unsigned char buffer[1]; // 1 Byte buffer for new value
    myFile.read((char*)buffer, 1);

    return convertCharArrayToUnsignedInt(buffer, 1);
}
character* SaveFile::getPartyMembers() {
    character* partyMembers = new character[5];
    int i;
    for (i = 0; i < 5; i++) {
        character partyMember;
        if (isPartyMemberSetAtSlot(i)) {
            partyMember.partySlot = i;
            partyMember.id = getPartyMemberCharacterIDAtSlot(i);
            partyMembers[i] = partyMember;
            //cout << i << ": ID #" << (int)getPartyMemberCharacterIDAtSlot(i) << endl;
        } else {
            partyMember.partySlot = -1;
        }
    }
    return partyMembers;
}


/* --- Private Getters --- */
/* Returns Checksum value */
uint32_t SaveFile::getChecksum() {
	myFile.seekg(0x1C + slotOffset);


	unsigned char checksumData[4]; // 4 Byte buffer fo reading values

	myFile.read((char*)checksumData, 4); // checksumData now holds the bytes 

	return convertCharArrayToUnsignedInt(checksumData, 4);
}


/*-----
Data Setters
------*/
void SaveFile::setGil(uint32_t newValue) {

	uint32_t currentValue = getGil();
	uint32_t difference = newValue - currentValue; // calculate the difference to add to checksum

	// Update checksum by adding difference to current value
	addToChecksum(difference);

	char* buffer; // 4 Byte buffer for new value


	// Actually write the new gil to file
	myFile.seekg(0x21E8 + slotOffset);
	buffer = convertUnsignedIntToCharArray(newValue, 4);
	myFile.write(buffer, 4);
	delete[] buffer; // Deallocate buffer
}
bool SaveFile::addGil(uint32_t valueToAdd) {
	uint32_t currentValue = getGil();
	uint32_t newValue;
	if ((currentValue + valueToAdd) > UINT32_MAX) {
		newValue = UINT32_MAX;
		setGil(newValue);
		return false;
	}
	newValue = currentValue + valueToAdd;
	setGil(newValue);
	return true;
}
/* Inventory Modifiers */
bool SaveFile::addItem(item newItem) {
	// Number of filled inventory slots, and also the index where we will insert
	uint16_t insertionIndex = getNumberOfFilledInventorySlots();
	// If the index is outside the range of inventory memory
	if (insertionIndex > 0x180) {
		//then return
		return false;
	}

	// Add to checksum. First we see if there is any data stored where we want to write. There shouldn't be, but just in case there is, we want to account for it in the checksum
	item currentItem;
	currentItem = getItemAtIndex(insertionIndex);
	addToChecksum(newItem.id - currentItem.id);
	addToChecksum((newItem.quantity - currentItem.quantity) << 16);

	// Increment number of slots used
	incremenetInventorySlotsUsed();

	// Get the location where we want to write
	int seekLocation;
	seekLocation = 0x19E0 + (4 * insertionIndex);
	myFile.seekg(seekLocation + slotOffset);

	// Setup buffers for writing the id and quantity
	char* idBuffer; // 2 Byte buffer for new value
	idBuffer = convertUnsignedIntToCharArray(newItem.id, 2);

	char* quantBuffer; // 2 Byte buffer for new value
	quantBuffer = convertUnsignedIntToCharArray(newItem.quantity, 2);

	// Write the data to the file
	myFile.write(idBuffer, 2);
	myFile.write(quantBuffer, 2);


	return true;
}
bool SaveFile::insertItemAtIndex(item newItem, uint16_t index) {
	// Number of filled inventory slots, and also the index where we will insert
	uint16_t lastIndex = getNumberOfFilledInventorySlots();
	// If the index is outside the range of inventory memory
	if (index > 0x180 || index > lastIndex || index < 0x19E0) { 
		//then return
		return false;
	}

	// Add to checksum. First we see if there is any data stored where we want to write. There shouldn't be, but just in case there is, we want to account for it in the checksum
	item currentItem;
	currentItem = getItemAtIndex(lastIndex);
	addToChecksum(newItem.id - currentItem.id);
	addToChecksum((newItem.quantity - currentItem.quantity) << 16);

	// Increment number of slots used
	incremenetInventorySlotsUsed();

	// Get the location where we want to write
	int seekLocation;
	seekLocation = 0x19E0 + (4 * lastIndex);
	myFile.seekg(seekLocation + slotOffset);

	// Setup buffers for writing the id and quantity
	char* idBuffer; // 2 Byte buffer for new value
	idBuffer = convertUnsignedIntToCharArray(newItem.id, 2);

	char* quantBuffer; // 2 Byte buffer for new value
	quantBuffer = convertUnsignedIntToCharArray(newItem.quantity, 2);

	// Write the data to the file
	myFile.write(idBuffer, 2);
	myFile.write(quantBuffer, 2);


	return true;
}
bool SaveFile::editItemIdAtIndex(uint16_t index, uint16_t newValue) {
    // Number of filled inventory slots, and also the index where we will insert
    uint16_t lastIndex = getNumberOfFilledInventorySlots();
    // If the index is outside the range of inventory memory
    if (index > 400 || index > lastIndex || index < 0) {
        //then return
        return false;
    }

    uint16_t oldValue;
    oldValue = getItemAtIndex(index).id;

    // Calculate the difference and add to the checksum
    addToChecksum(newValue - oldValue);

    // Seek to the write location
    int seekLoc = 0x19E0 + (4 * index); // 0x19E0 - start of inventory + 4 byte per item
    myFile.seekg(seekLoc + slotOffset);
    
    char* writebuffer; // 2 Byte buffer for new value
    writebuffer = convertUnsignedIntToCharArray(newValue, 2);
    myFile.write(writebuffer, 2);
    delete[] writebuffer; // Deallocate the write buffer

    return true;
}
bool SaveFile::editItemQuantityAtIndex(uint16_t index, uint16_t newValue) {
	// Number of filled inventory slots, and also the index where we will insert
	uint16_t lastIndex = getNumberOfFilledInventorySlots();
	// If the index is outside the range of inventory memory
	if (index > 400 || index > lastIndex || index < 0) {
		//then return
		return false;
	}

	uint16_t oldValue;
	oldValue = getItemAtIndex(index).quantity;

	// Calculate the difference and add to the checksum
	addToChecksum((newValue - oldValue) << 16);

	// Seek to the write location
	int seekLoc = 0x19E0 + (4 * index) + (2); // 0x19E0 - start of inventory + 4 byte per item + 2 byte to get to quantity
	myFile.seekg(seekLoc + slotOffset);
	
	char* writebuffer; // 2 Byte buffer for new value
	writebuffer = convertUnsignedIntToCharArray(newValue, 2);
	myFile.write(writebuffer, 2);
	delete[] writebuffer; // Deallocate the write buffer

	return true;
}

/* Key Item Modifiers */
bool SaveFile::addKeyItem(item newItem) {
    // Number of filled inventory slots, and also the index where we will insert
    uint16_t insertionIndex = getNumberOfFilledKeyInventorySlots();
    // If the index is outside the range of inventory memory
    if (insertionIndex > 0x21E3) {
        //then return
        return false;
    }

    // Add to checksum. First we see if there is any data stored where we want to write. There shouldn't be, but just in case there is, we want to account for it in the checksum
    item currentItem;
    currentItem = getKeyItemAtIndex(insertionIndex);
    addToChecksum(newItem.id - currentItem.id);
    addToChecksum((newItem.quantity - currentItem.quantity) << 16);

    // Increment number of slots used
    incremenetKeyInventorySlotsUsed();

    // Get the location where we want to write
    int seekLocation;
    seekLocation = 0x1FE4 + (4 * insertionIndex);
    myFile.seekg(seekLocation + slotOffset);

    // Setup buffers for writing the id and quantity
    char* idBuffer; // 2 Byte buffer for new value
    idBuffer = convertUnsignedIntToCharArray(newItem.id, 2);

    char* quantBuffer; // 2 Byte buffer for new value
    quantBuffer = convertUnsignedIntToCharArray(newItem.quantity, 2);

    // Write the data to the file
    myFile.write(idBuffer, 2);
    myFile.write(quantBuffer, 2);


    return true;
}
bool SaveFile::insertKeyItemAtIndex(item newItem, uint16_t index) {
    // Number of filled inventory slots, and also the index where we will insert
    uint16_t lastIndex = getNumberOfFilledKeyInventorySlots();
    // If the index is outside the range of inventory memory
    if (index > 0x21E3 || index > lastIndex || index < 0x1FE4) {
        //then return
        return false;
    }

    // Add to checksum. First we see if there is any data stored where we want to write. There shouldn't be, but just in case there is, we want to account for it in the checksum
    item currentItem;
    currentItem = getKeyItemAtIndex(lastIndex);
    addToChecksum(newItem.id - currentItem.id);
    addToChecksum((newItem.quantity - currentItem.quantity) << 16);

    // Increment number of slots used
    incremenetKeyInventorySlotsUsed();

    // Get the location where we want to write
    int seekLocation;
    seekLocation = 0x1FE4 + (4 * lastIndex);
    myFile.seekg(seekLocation + slotOffset);

    // Setup buffers for writing the id and quantity
    char* idBuffer; // 2 Byte buffer for new value
    idBuffer = convertUnsignedIntToCharArray(newItem.id, 2);

    char* quantBuffer; // 2 Byte buffer for new value
    quantBuffer = convertUnsignedIntToCharArray(newItem.quantity, 2);

    // Write the data to the file
    myFile.write(idBuffer, 2);
    myFile.write(quantBuffer, 2);


    return true;
}
bool SaveFile::editKeyItemIdAtIndex(uint16_t index, uint16_t newValue) {
    // Number of filled inventory slots, and also the index where we will insert
    uint16_t lastIndex = getNumberOfFilledKeyInventorySlots();
    // If the index is outside the range of inventory memory
    if (index > 128 || index > lastIndex || index < 0) {
        //then return
        return false;
    }

    uint16_t oldValue;
    oldValue = getKeyItemAtIndex(index).id;

    // Calculate the difference and add to the checksum
    addToChecksum(newValue - oldValue);

    // Seek to the write location
    int seekLoc = 0x1FE4 + (4 * index); // 0x19E0 - start of inventory + 4 byte per item
    myFile.seekg(seekLoc + slotOffset);
    
    char* writebuffer; // 2 Byte buffer for new value
    writebuffer = convertUnsignedIntToCharArray(newValue, 2);
    myFile.write(writebuffer, 2);
    delete[] writebuffer; // Deallocate the write buffer

    return true;
}
bool SaveFile::editKeyItemQuantityAtIndex(uint16_t index, uint16_t newValue) {
    // Number of filled inventory slots, and also the index where we will insert
    uint16_t lastIndex = getNumberOfFilledKeyInventorySlots();
    // If the index is outside the range of inventory memory
    if (index > 128 || index > lastIndex || index < 0) {
        //then return
        return false;
    }

    uint16_t oldValue;
    oldValue = getKeyItemAtIndex(index).quantity;

    // Calculate the difference and add to the checksum
    addToChecksum((newValue - oldValue) << 16);

    // Seek to the write location
    int seekLoc = 0x1FE4 + (4 * index) + (2); // 0x19E0 - start of inventory + 4 byte per item + 2 byte to get to quantity
    myFile.seekg(seekLoc + slotOffset);
    
    char* writebuffer; // 2 Byte buffer for new value
    writebuffer = convertUnsignedIntToCharArray(newValue, 2);
    myFile.write(writebuffer, 2);
    delete[] writebuffer; // Deallocate the write buffer

    return true;
}

/* Character Modifiers */
bool SaveFile::setStatusOfCharacterWithId(uint8_t id, uint16_t statusId) {
	if (id > 13) {
		return false;
	}

	// Add difference to checksum
	addToChecksum(statusId - getStatusConditionOfCharacterWithId(id));

	char* buffer; // 4 Byte buffer for new value
	buffer = convertUnsignedIntToCharArray(statusId, 4);

	int seekLoc = 0xC0 + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code
	// Write buffer to file
	myFile.write(buffer, 4);
	delete[] buffer;

	return true;
}
bool SaveFile::setHPofCharacterWithId(uint8_t id, uint16_t value) {
	if (id > 13) {
		return false;
	}
	
	// Add difference to checksum
	addToChecksum(value - getHPofCharacterWithId(id));

	char* buffer; // 4 Byte buffer for new value
	buffer = convertUnsignedIntToCharArray(value, 2);

	int seekLoc = 0xB0 + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code
	// Write buffer to file
	myFile.write(buffer, 2);
	delete[] buffer;

	return true;
}
bool SaveFile::setMPofCharacterWithId(uint8_t id, uint16_t value) {
	if (id > 13) {
		return false;
	}

	// Add difference to checksum
	addToChecksum(value - getMPofCharacterWithId(id));

	char* buffer; // 4 Byte buffer for new value
	buffer = convertUnsignedIntToCharArray(value, 2);

	int seekLoc = 0xB8 + (id * 0x1C0); // The location of the status code
	myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code
	// Write buffer to file
	myFile.write(buffer, 2);
	delete[] buffer;

	return true;
}
bool SaveFile::addEXPtoCharacterWithId(uint8_t id, uint32_t exp) {
	// Add the new exp addition to the checksum
	addToChecksum(exp);

	// Get the current EXP
	uint32_t currentEXP;
	currentEXP = getEXPofCharacterWithId(id);

	// Calculate new exp
	uint32_t newExp;
	if ((currentEXP + exp) > UINT32_MAX) {
		newExp = UINT32_MAX;
	}
	else {
		newExp = currentEXP + exp;
	}

	char* buffer; // buffer to hold new exp value
	buffer = convertUnsignedIntToCharArray(newExp, 4);

	// Seek to location of EXP
	int seekLocation = 0xA8 + (id * 0x1C0); // Cecil Exp is at 0xA8, each character's data is 0x1C0 in length
	myFile.seekg(seekLocation + slotOffset); // Move cursor to item location
	// Write to file
	myFile.write(buffer, 4);
	delete[] buffer; // dealloc the buffer

	return true;
}
void SaveFile::setStrengthOfCharacterWithId(uint8_t id, uint8_t newStrength) {
    if (id > 13) {
        // Invalid Id
        return;
    }
    
    addToChecksum((newStrength - getStrengthOfCharacterWithId(id)) << 16);

    char* buffer; // 1 Byte buffer for new value
    buffer = convertUnsignedIntToCharArray(newStrength, 1);
    
    int seekLoc = 0x25A + (id * 0x1C0); // The location of the strength
    myFile.seekg(seekLoc + slotOffset); // Jump to given character's strength stat
    
    myFile.write(buffer, 1);
    delete[] buffer;
}
bool SaveFile::setPartyMemberCharacterIDAtSlot(uint8_t slot, uint8_t newId) {
    // 0x30 - party 0
    // 0x44 - party 1 - size 0x14
    if (slot > 5) {
        // Invalid Id
        return false;
    }
    
    addToChecksum(newId - getPartyMemberCharacterIDAtSlot(slot));

    char* buffer; // 1 Byte buffer for new value
    buffer = convertUnsignedIntToCharArray(newId, 1);
    
    int seekLoc = 0x30 + (slot * 0x14); // The location of the status code
    myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code
    
    myFile.write(buffer, 1);
    delete[] buffer;
    
    if (!isPartyMemberSetAtSlot(slot)) { // the flag for this position hasnt been set
        addToChecksum(1 << 16);
        
        buffer = convertUnsignedIntToCharArray(1, 1);
        
        int seekLoc = 0x32 + (slot * 0x14);
        myFile.seekg(seekLoc + slotOffset); // Jump to given character's status code
        
        myFile.write(buffer, 1);
        delete[] buffer;
    }
    
    
    return true;
}


/*------
Data Processing Functions
---------*/
uint32_t SaveFile::convertCharArrayToUnsignedInt(unsigned char* arr, uint8_t len) {
	// Convert to Integer
	uint32_t value;
	value = 0;
	int i;
	for (i = 0; i < len; i++) {
		// Data is stord in little-endian (i.e. lowest maginute byte stored first)
		value += (((uint32_t)(arr[i])) << (i * 8));
	}

	return value;
}
char* SaveFile::convertUnsignedIntToCharArray(uint32_t arr, uint8_t len) {
	unsigned char* buffer = new unsigned char[len]; // allocate memory for the buffer

	int i;
	for (i = 0; i < len; i++) {
		uint8_t x = arr >> (i * 8);
		buffer[i] = x;
	}

	return (char*)buffer;
}

/* Add specified amount to checksum */
void SaveFile::addToChecksum(uint32_t value) {
	// Update checksum by adding difference to current value
	uint32_t newChecksum = getChecksum() + value;
	myFile.seekg(0x1C + slotOffset);
	char* buffer; // 4 Byte buffer for new value
	buffer = convertUnsignedIntToCharArray(newChecksum, 4);
	myFile.write(buffer, 4);
	delete[] buffer;
}
void SaveFile::incremenetInventorySlotsUsed() {
	// Get current value
	uint16_t currentSlotsUsed;
	currentSlotsUsed = getNumberOfFilledInventorySlots();

	// Increment Checksum
	addToChecksum(1);

	// Setup buffer for data write
	char* buffer; // 2 Byte buffer for new value
	buffer = convertUnsignedIntToCharArray(currentSlotsUsed + 1, 2);

	// Move cursor to inventory number location
	myFile.seekg(0x1FE0 + slotOffset);
	// Write buffer to file
	myFile.write(buffer, 2);
	delete[] buffer;
}
void SaveFile::incremenetKeyInventorySlotsUsed() {
    // Get current value
    uint16_t currentSlotsUsed;
    currentSlotsUsed = getNumberOfFilledKeyInventorySlots();

    // Increment Checksum
    addToChecksum(1);

    // Setup buffer for data write
    char* buffer; // 2 Byte buffer for new value
    buffer = convertUnsignedIntToCharArray(currentSlotsUsed + 1, 2);

    // Move cursor to inventory number location
    myFile.seekg(0x21E4 + slotOffset);
    // Write buffer to file
    myFile.write(buffer, 2);
    delete[] buffer;
}
