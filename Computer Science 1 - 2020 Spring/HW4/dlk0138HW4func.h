/* 	Author: Daniel Koelzer
	Date:4/16/20
	Instructor: Joseph Helsing
	Description: Header for HW4. Includes all libraries, struct, and prototypes.
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <sstream>

struct Tile {
	enum tileType {
		NONE = ' ',
		BOX = 'B',
		AVATAR = 'A',
		WALL = 'X',
		HOME = 'H',
	};
	
	tileType type;
	bool onHomeLocation;
	
	Tile() {
		type = tileType::NONE;
		onHomeLocation = false;
	}
};

using namespace std;

void printEUID();
bool winCheck(Tile** map, int width, int height);
void loadFile(Tile** map, Tile initialMap[15][15], int& width, int& height, int& playerXPos, int& playerYPos, bool ResetMap, int& moves);
void printMap(Tile** map, int width, int height);
void openingText();
bool move(Tile** map, Tile initialMap[15][15], int width, int height, char input, int& playerXPos, int& playerYPos);
bool tileCheck(Tile* tileA, Tile* tileB, Tile* tileC);
bool update(Tile** map, Tile initialMap[15][15], int width, int height, int& playerX, int& playerY, int& moves);