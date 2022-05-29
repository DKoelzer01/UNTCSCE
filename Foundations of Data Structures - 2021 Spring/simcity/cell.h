#ifndef CELL_H
#define CELL_H

#include <vector>
#include <iostream>
#include <algorithm>

enum CellType { // Cell type for identification rather than comparing with std::is_base_of.
	NONE = 0,
	RES = 1,
	IND = 2,
	COM = 3,
	UTIL = 4
};

class Cell
{
    protected:
		CellType type;
        int xPos;
        int yPos;
        int population;
        int pollution;
		bool updated;
		bool roadAccess;
        bool active;    //  Used for empty cells and cells not in range of a utility.
		std::vector<Cell*> adjacent; // vector containing pointers to all adjacent cells. 3 min, 8 max.
        
    public:
        int GetXPos()   { return xPos; }
        int GetYPos()   { return yPos; }
        int GetPopulation() { return population; }
        int GetPollution() { return pollution; }
		bool GetRoadAccess() { return roadAccess; }
		bool GetUpdated() { return updated; }
		CellType GetType() { return type; }
		std::vector<Cell*> GetAdjacent() { return adjacent; }
        bool GetActive() { return active; }

        void SetActive(bool act) { this->active = act; }

        Cell(int, int, CellType);
        Cell(int, int, int, int, CellType);

        void AddPopulation(int);
        void AddPollution(int); 
		void SetRoadAccess(bool access) { roadAccess = access; }
		void SetAdjacent(std::vector<Cell*> i) { adjacent = i; }
		bool IsPowerLine() { return false; }
		bool IsRoad() { return false; }
		bool IsPowerPlant() { return false; }

        virtual void AttemptGrowth(int&, int&) = 0;
        virtual char PrintCell() = 0;
};
#endif