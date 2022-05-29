/* 	Author: Daniel Koelzer
	Date:4/16/20
	Instructor: Joseph Helsing
	Description: Function Definitions for HW4.
*/

#include "dlk0138HW4func.h"

void printEUID() {
	cout << "+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
	cout << "|        CSCE 1030 - Computer Science I        |" << endl;
	cout << "| \033[1;34mDaniel Koelzer   dlk0138  dlk0138@my.unt.edu\033[0m |" << endl;
	cout << "+----------------------------------------------+" << endl;
	cout << endl;
}

void openingText() {
	cout << "Welcome to Mr. Mover!" << endl;
	cout << "The goal is to push each of the boxes (represented by B's) into" << endl;
	cout << "a home location (represented by H's). Mr. Mover is represented" << endl;
	cout << "by an A, and you can move Up(U), Down(D), Left(L), and Right(R)." << endl;
	cout << "Once a box is in a home location, it cannot be moved again so be" << endl;
	cout << "careful about how your push the boxes. Good luck!" << endl << endl;
}

void loadFile(Tile** map,Tile initialMap[15][15], int& width, int& height, int& playerXPos, int& playerYPos, bool ResetMap, int& moves) {
	string fileName;
	ifstream in_stream;
	if(ResetMap) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				map[i][j] = initialMap[i][j];
				if(map[i][j].type == Tile::tileType::AVATAR) {
					playerXPos = i;
					playerYPos = j;
				}
			}
		}
	} else {
		do{
		cout << "Please enter the name of the room file:";
		cin >> fileName;
		cout << endl;
	
		in_stream.open(fileName);
	
		if(!in_stream.is_open())
			cout << "\033[1;33mCould not load file.\n\033[0m ";
		} while (!in_stream.is_open());
	
		int maxHeight = 0;
		int maxWidth = 0;
		while(!in_stream.eof()) {
			string str;
			getline(in_stream,str);
			cout << str << endl;
			if(isalpha(str[0])) {
				int iter = 0;
				for(int j = 0; j < str.length(); j++) {
					switch(str[j]){
						case('B'):
						case('X'):
						case('H'):
						case(' '):
							map[maxHeight][iter].type = static_cast<Tile::tileType>(str[j]);
							iter++;
							break;
						case('O'):
							map[maxHeight][iter].type = static_cast<Tile::tileType>('B');
							map[maxHeight][iter].onHomeLocation = true;
							iter++;
							break;
						case('A'):
							playerXPos = maxHeight;
							playerYPos = iter;
							map[maxHeight][iter].type = static_cast<Tile::tileType>(str[j]);
							iter++;
							break;
						default:
							break;
					}
				}
				if(maxWidth < iter)
				{
				maxWidth = iter;
				}
				maxHeight++;
			} else {
				stringstream strStream;
				strStream << str;
				strStream >> moves;
			}
		}
		width = maxWidth;
		height = maxHeight;
		
		in_stream.close();
	}
}

void printMap(Tile** map, int width, int height) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			char temp = toupper(static_cast<char>(map[i][j].type));
			switch(temp) { //Switch statement for character coloring in arrays.
				case(' '):
				case('X'):
				printf("\033[1;0m%c\033[0m ",temp);
				break;
				case('H'):
				printf("\033[1;31m%c\033[0m ",temp);
				break;
				case('B'):
				if(map[i][j].onHomeLocation) {
					printf("\033[1;32m%c\033[0m ",temp);
				} else {
					printf("\033[1;33m%c\033[0m ",temp);
				}
				break;
				case('A'):
				printf("\033[1;32m%c\033[0m ",temp);
				break;
				default:
				cout << temp << " ";
				break;
			}
		}
		cout << endl;
	}
}

bool tileCheck(Tile* tileA, Tile* tileB, Tile* tileC) {
	//Tile A is the Avatar's position, Tile B is the target tile, Tile C is the tile 1 farther away in-line.
	switch(tileB->type) 
	{
		case(Tile::tileType::NONE):						//Target tile is air.
			if(tileA->onHomeLocation) {					//Check if player was previously on home tile.
				tileA->type = Tile::tileType::HOME;
				tileA->onHomeLocation = false;
				tileB->onHomeLocation = false;
			} else {
				tileA->type = Tile::tileType::NONE;		
			}
			tileB->type = Tile::tileType::AVATAR;		//move player
			return true;
			break;
		case(Tile::tileType::BOX):						//Target is box.
			if(tileB->onHomeLocation) {					//If target is already on a home location, dont move it.
				cout << "\033[1;33mI cannot move this way.\033[0m" << endl;
				return false;
				break;
			} else {
			switch(tileC->type) {						//Check space beyond target.
				case(Tile::tileType::NONE):				//space beyond is empty
					if(tileA->onHomeLocation) {			//Check if player is on home
						tileA->type = Tile::tileType::HOME;
						tileA->onHomeLocation = false;
						tileB->onHomeLocation = false;
					} else {
						tileA->type = Tile::tileType::NONE;
					}
					tileB->type = Tile::tileType::AVATAR; //Move player and box.
					tileC->type = Tile::tileType::BOX;
					return true;
					break;
				case(Tile::tileType::BOX):
				case(Tile::tileType::WALL):
					cout << "\033[1;33mI cannot move this way.\033[0m" << endl; //Cant move onto another box or wall.
					return false;
					break;
				case(Tile::tileType::HOME):						//Move box onto home tile.
					if(tileA->onHomeLocation) {
						tileA->type = Tile::tileType::HOME;
						tileA->onHomeLocation = false;
						tileB->onHomeLocation = false;
					} else {
						tileA->type = Tile::tileType::NONE;
					}
					tileB->type = Tile::tileType::AVATAR;		//move player and box.
					tileC->type = Tile::tileType::BOX;
					tileC->onHomeLocation = true;
					return true;
					break;
				default:
				cout << "\033[1;33mYou shouldn't be seeing this...\033[0m" << endl;
					return false;
					break;
			}
			break;
			}
		case(Tile::tileType::WALL):
			cout << "\033[1;34mI cannot move this way.\033[0m" << endl;	//Can never move into a wall.
			return false;
			break;
		case(Tile::tileType::HOME):						//moving player onto home tile.
			if(tileA->onHomeLocation) {
				tileA->type = Tile::tileType::HOME;
				tileA->onHomeLocation=false;
			} else {
				tileA->type = Tile::tileType::NONE;
			}
			tileB->type = Tile::tileType::AVATAR;
			tileB->onHomeLocation = true;
			return true;
			break;
		default:
			cout << "\033[1;33mI cannot move this way.\033[0m" << endl;
			return false;
			break;
	}
}

bool move(Tile** map,Tile initialMap[15][15], int width, int height, char input, int& playerXPos, int& playerYPos,int& moves) {
	bool status = false;
	switch(toupper(input)) {
		case('L'): 
			status = tileCheck(&map[playerXPos][playerYPos],&map[playerXPos][playerYPos-1],&map[playerXPos][playerYPos-2]);
			if(status) { playerYPos--; } //Check left, move left.
			break;
		case('R'):		
			status = tileCheck(&map[playerXPos][playerYPos],&map[playerXPos][playerYPos+1],&map[playerXPos][playerYPos+2]);
			if(status) { playerYPos++; } //Check right, move right.
			break;
		case('U'):
			status = tileCheck(&map[playerXPos][playerYPos],&map[playerXPos-1][playerYPos],&map[playerXPos-2][playerYPos]);
			if(status) { playerXPos--; } //Check up, move up.
			break;
		case('D'):
			status = tileCheck(&map[playerXPos][playerYPos],&map[playerXPos+1][playerYPos],&map[playerXPos+2][playerYPos]);
			if(status) { playerXPos++; } //Check down, move down.
			break;
		case('X'):	//Reset
			cout << "Are you sure you want to reset? (\033[1;32mY\033[0m/\033[1;31mN\033[0m) ";
			char resetChoice;
			cin >> resetChoice;
			if(toupper(resetChoice) == 'Y') {
				moves = -1;
				loadFile(map,initialMap,width,height,playerXPos,playerYPos,true,moves);
				return true;
			} else {
				return false;
			}
		case('Q'):	//Quit
			cout << "Are you sure you want to quit? (\033[1;32mY\033[0m/\033[1;31mN\033[0m) ";
			char quitChoice;
			cin >> quitChoice;
			if(toupper(quitChoice) == 'Y') {
				system("clear");
				cout << "Goodbye.\n";
				exit(EXIT_SUCCESS);
			} else {
				return false;
			}
			break;
		case('S'): //Save.
			cout << "Would you like to save? (\033[1;32mY\033[0m/\033[1;31mN\033[0m) ";
			char saveChoice;
			cin >> saveChoice;
			if(toupper(saveChoice) == 'Y') {
				ofstream out_stream;
				string outputName;
				do{
					
				cout << "Enter a file name to save your progress: ";
				cin >> outputName;
				out_stream.open(outputName);
				
				if(!out_stream.is_open())
				cout << "\033[1;33mCould not load file.\n\033[0m ";
				} while (!out_stream.is_open());
				
				
				for(int i = 0; i < height; i++) {
					for(int j = 0; j < width; j++) {
						if(map[i][j].type == Tile::tileType::BOX && map[i][j].onHomeLocation) { 
							out_stream << 'O' << ","; //New tile type exclusive to save/load. Prevent's loss of data upon saving with a box on a home.
						} else {
							out_stream << static_cast<char>(map[i][j].type) << ",";
						}
					}
					out_stream << endl;
				}
				out_stream << moves;
				out_stream.close();
				
				
				cout << "Would you like to continue? (\033[1;32mY\033[0m/\033[1;31mN\033[0m) ";
				char quitChoice;
				cin >> quitChoice;
				if(toupper(quitChoice) == 'N') {
					system("clear");
					cout << "Goodbye.\n";
					exit(EXIT_SUCCESS);
				} else {
					return false;
				}
			} else {
				return false;
			}
		case('G'): //Load
			cout << "Would you like to load? (\033[1;32mY\033[0m/\033[1;31mN\033[0m) ";
			char loadChoice;
			cin >> loadChoice;
			if(toupper(loadChoice) == 'Y') {
				moves = -1;
				loadFile(map,initialMap,width,height,playerXPos,playerYPos,false,moves);
				return true;
			} else {
				return false;
			}
		default:
			cout << "Unknown input\n";
			return false;
			
	}
	return status;
}

bool winCheck(Tile** map, int width, int height) { //Check if all boxes are on home tiles.
	int boxCount = 0;
	int boxesOnHome = 0;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(map[i][j].type == Tile::tileType::BOX) {
				if(map[i][j].onHomeLocation) {
					boxesOnHome++;
				}
				boxCount++;
			}
		}
	}
	return(boxCount == boxesOnHome);
}	

bool update(Tile** map,Tile initialMap[15][15], int width, int height, int& playerX, int& playerY, int& moves) { //Map update function.
	system("clear");
	char choice;
	printMap(map,width,height);
	bool success = false;
	do{	
	cout << moves << " Moves." << endl;
	cout << "Please enter direction to move: \n";
	cout << "\033[1;33mU\033[0m for Up, \033[1;33mD\033[0m for Down, \033[1;33mL\033[0m for Left, \033[1;33mR\033[0m for Right\n";
	cout << "\033[1;31mX\033[0m for Reset, \033[1;31mS\033[0m for Save,\033[1;31mG\033[0m for load \033[1;31mQ\033[0m for Quit: ";
	cin >> choice;
	success = move(map,initialMap,width,height,choice,playerX,playerY,moves);
	} while(!success);
	moves++;
	bool cont = winCheck(map,width,height);
	return(cont);
}