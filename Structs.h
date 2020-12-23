// Kyle Fenole
// kfenole.com
//
// Final Fantasy 4 DS Save Editor
// Structs.h
//
// Contains strcutures of different game info
//
// Feel free to use anything from this project, but please credit me if you do!
// (Also, if you are working on a similar project, I'd be interested to hear about it)

#pragma once

#include <iostream>

struct item {
	uint16_t id;
	uint16_t quantity;
};

/* Character. Based on character used in storage. Total length 0x1C0 bytes */
struct character {
	/* Growth Related Values */
	uint32_t level; // 0xA4
	uint32_t totalEXP; // 0xA8

	/* Health Related Values*/
	uint32_t currentHP; // 0xB0
	uint32_t maxHP; // 0xB4
	uint32_t currentMP; // 0xB8
	uint32_t maxMP; // 0xBC
	uint32_t statusCode; // 0xC0

	/* Stat Related Values */
	uint8_t strength; // 0x25A
	uint8_t stamina; // 0x25B
	uint8_t speed; // 0x25C
	uint8_t intellect; // 0x25D
	uint8_t spirit; // 0x25E
};