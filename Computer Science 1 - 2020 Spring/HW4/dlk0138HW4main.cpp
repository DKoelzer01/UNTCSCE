/* 	Author: Daniel Koelzer
	Date:4/16/20
	Instructor: Joseph Helsing
	Description: Main file for HW4. Contains general event flow.
*/

#include "dlk0138HW4func.h"

int main() {
	printEUID();
	int moves = 0;
	int width = 15;
	int height = 15;
	int avatarX, avatarY;
	
	Tile** map = new Tile*[height];
	
	for(int i = 0; i < height; i++) {
		map[i] = new Tile[width];
	}
	
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			map[i][j] = Tile();
		}
	}
	Tile initialMap[15][15];
	loadFile(map,initialMap,width,height,avatarX,avatarY,false,moves);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			initialMap[i][j] = map[i][j];
		}
	}

	openingText();
	while(!update(map,initialMap,width,height,avatarX,avatarY,moves));
	printMap(map,width,height);
	printf("\033[1;33mCongratulations!\033[0m \033[1;32mYou won in %d moves!\033[0m\n",moves);
	delete[] map;
	return 0;
}
