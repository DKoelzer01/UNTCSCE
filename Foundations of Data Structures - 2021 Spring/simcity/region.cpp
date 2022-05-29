#include <vector>
#include <sstream>
#include <algorithm>
#include "region.h"


bool CompareCells(Cell*, Cell*); //  Define from Cell.cpp

Region::Region(std::string mapFile, int maxTime, int refreshRate)
{
	this->maxTimeStep = maxTime;
	this->refreshRate = refreshRate;

	//  Parse region file.
	std::ifstream mapStream;
	mapStream.open(mapFile);

	if (mapStream.is_open())
	{
		//  Parse first line length to determine width of array
		std::vector<std::vector<std::string>> stringMap;

		while (!mapStream.eof())
		{
			std::vector<std::string> temp;
			std::string line;
			getline(mapStream, line);
			std::stringstream ss(line);
			std::string cellChar;
			while (getline(ss, cellChar, ','))
			{
				temp.push_back(cellChar);
			}

			stringMap.push_back(temp);
		}
		stringMap.pop_back(); //    Remove last empty line.
		this->ySize = stringMap.size();
		this->xSize = stringMap[0].size();

		map = new Cell**[ySize];
		for (int i = 0; i < ySize; i++)
		{
			map[i] = new Cell*[xSize];
			for (int j = 0; j < xSize; j++)
			{
				//  Assign class by character
				if (stringMap[i][j] == "R")
				{
					map[i][j] = new Residential(i, j);
				}
				else if (stringMap[i][j] == "I")
				{
					map[i][j] = new Industrial(i, j);
				}
				else if (stringMap[i][j] == "C")
				{
					map[i][j] = new Commercial(i, j);
				}
				//  Utilities
				else if (stringMap[i][j] == "-")
				{
					map[i][j] = new Utility(i, j, false, true, false);
				}
				else if (stringMap[i][j] == "T")
				{
					map[i][j] = new Utility(i, j, true, false, false);
				}
				else if (stringMap[i][j] == "#")
				{
					map[i][j] = new Utility(i, j, true, true, false);
				}
				else if (stringMap[i][j] == "P")
				{
					map[i][j] = new Utility(i, j, false, false, true);
				}
				else if (stringMap[i][j] == " ")
				{
					map[i][j] = new Utility(i, j, false, false, false);
					map[i][j]->SetActive(false);
				}
				//  Utilities don't grow, therefore are unnecessary in the sorted map vector
				if (map[i][j]->GetType() != UTIL) 
				{
					sortedMap.push_back(map[i][j]);
				}
			}
		}
		for (int i = 0; i < ySize; i++)
		{
			for (int j = 0; j < xSize; j++)
			{
				std::vector<Cell*> temp;
				for (int y = i - 1; y <= i + 1; y++)
				{
					for (int x = j - 1; x <= j + 1; x++)
					{
						if (x < 0 || x >= xSize) {
							continue;
						}
						if (y < 0 || y >= ySize) {
							continue;
						}
						if (x == j && y == i) {
							continue;
						}
						temp.push_back(map[y][x]);
					}
				}
				map[i][j]->SetAdjacent(temp);
			}
		}

		for (int i = 0; i < ySize; i++)
		{
			for (int j = 0; j < xSize; j++)
			{
				if (map[i][j]->GetType() == UTIL && dynamic_cast<Utility*>(map[i][j])->IsRoad())
				{
					for (int y = i - 3; y <= i + 3; y++)
					{
						for (int x = j - 3; x <= j + 3; x++)
						{
							if (x < 0 || x >= xSize) {
								continue;
							}
							if (y < 0 || y >= ySize) {
								continue;
							}
							if (x == j && y == i)
								continue;
							map[y][x]->SetRoadAccess(true);

						}
					}
				}
			}
		}
		for (int i = 0; i < ySize; i++)
		{
			for (int j = 0; j < xSize; j++)
			{
				if (!map[i][j]->GetRoadAccess())
				{
					map[i][j]->SetActive(false);
				}
			}
		}
		this->AdvanceTimeStep();
	}
	else
	{
		std::cout << "Region file was not found." << std::endl;
	}
}
Region::~Region()
{
	for (int i = 0; i < ySize; i++)
	{

		for (int j = 0; j < xSize; j++)
		{
			delete map[i][j];
		}
		delete[] map[i];
	}
	map = NULL;
}
void Region::AdvanceTimeStep()
{
	cellsUpdated = 0; //Reset number of cells updated this time step to 0.
	PrintRegion(false);

	//  Sort vector based on prioritization rules

	std::sort(sortedMap.rbegin(), sortedMap.rend(), CompareCells);

	for (int i = 0; i < sortedMap.size(); i++)
	{
		if (sortedMap[i]->GetActive())
		{
			sortedMap[i]->AttemptGrowth(availableWorkers, availableGoods);  // Iterate through every cell and attempt growth. If successful, the "updated" flag will be set to "true"
		}
	}
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			if (map[i][j]->GetUpdated()) //Every cell that has been flagged to update this cycle gets updated.
			{
				if (map[i][j]->GetType() == RES) {
					map[i][j]->AddPopulation(1);
					availableWorkers++;
				}
				if (map[i][j]->GetType() == IND) {
					map[i][j]->AddPopulation(1);
					availableGoods++;
				}
				if (map[i][j]->GetType() == COM)
				{
					map[i][j]->AddPopulation(1);
				}
				cellsUpdated++;
			}
			if (map[i][j]->GetType() == IND) //  Pollute area
			{
				dynamic_cast<Industrial*>(map[i][j])->Pollute(ySize, xSize, map);
			}
		}
	}
	timeStep++;
}

void Region::PrintRegion(bool finalState)
{
	if (timeStep == 0) {
		std::cout << "Initial Region State\n";
	}

	//  Region Data
	if (!finalState) {
		if (timeStep != 0) {
			std::cout << std::endl;
			std::cout << "Time step: " << timeStep << std::endl;
			std::cout << "Available Workers " << availableWorkers << " ";
			std::cout << "Available Goods " << availableGoods << std::endl;
		}
	}
	//  END REGION DATA
	//  Region Map w/ Borders
	if (timeStep % refreshRate == 0 || finalState) {
		//  Top border.
		for (int j = 0; j < (xSize * 2) + 2; j++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;

		totalWorkers = 0;
		totalPollution = 0;
		for (int i = 0; i < ySize; i++)
		{
			std::cout << "|";
			for (int j = 0; j < xSize; j++)
			{
				std::cout << map[i][j]->PrintCell() << " "; //Update total goods, workers, and pollution at this time.
				totalWorkers += map[i][j]->GetPopulation();
				totalPollution += map[i][j]->GetPollution();  
			}												
			std::cout << "|" << std::endl;
		}

		//  Bottom border.
		for (int j = 0; j < (xSize * 2) + 2; j++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
	}
	//  END REGION MAP
}


void Region::PrintPollutionState()
{
    //  Top border.
    for (int j = 0; j < (xSize*2) + 2; j++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int x = 0; x < ySize; x++)
    {
        std::cout << "|";
        for (int y = 0; y < xSize; y++)
        {
            std::cout << map[x][y]->GetPollution() << " ";
        }												
        std::cout << "|" << std::endl;
    }
    //  Bottom border.
    for (int j = 0; j < (xSize*2) + 2; j++)
    {
        std::cout << "-";
    }
    std::cout << std::endl << std::endl;
}


bool Region::AnalyseRegion(int x1, int y1, int x2, int y2, bool reg)
{
	if (!reg) {
		std::cout << "Please enter the diagonal corners of the area you wish to have more information about. (MinX = 0, MinY = 0, MaxX = " << xSize - 1 << ", MaxY = " << ySize - 1 << ")\n";
		std::cout << "X1:";
		std::cin >> x1;
		std::cout << "Y1:";
		std::cin >> y1;
		std::cout << "X2:";
		std::cin >> x2;
		std::cout << "Y2:";
		std::cin >> y2;
	}
    if( x1 > x2 || y1 > y2 ||
        x1 < 0 || y1 < 0 ||
        x2 >= xSize || y2 >= ySize)
    {
		std::cout << "FAILED" << std::endl;
        std::cout << (x1 > x2) << std::endl;
        std::cout << (y1 > y2) << std::endl;
        std::cout << (x1 < 0) << std::endl;
        std::cout << (y1 < 0) << std::endl;
        std::cout << (x2 >= xSize) << std::endl;
        std::cout << (y2 >= ySize) << std::endl;
        return false;
    }

    int totalRes = 0;
    int totalInd = 0;
    int totalCom = 0;
    int totalPol = 0;;
    for(int y = y1; y < y2 + 1; y++)
    {
        for(int x = x1; x < x2 + 1; x++)
        {
            switch (map[y][x]->GetType())
            {
            case RES:
                totalRes += map[y][x]->GetPopulation();
                break;
            case IND:
                totalInd += map[y][x]->GetPopulation();
                break;
            case COM:
                totalCom += map[y][x]->GetPopulation();
                break;
            default:
                break;
            }
            totalPol += map[y][x]->GetPollution();
        }
    }

	if (reg) 
	{
		std::cout << "The total populations for the region are:\n";
		std::cout << "Residential: " << totalRes << std::endl;
		std::cout << "Industrial: " << totalInd << std::endl;
		std::cout << "Commercial: " << totalCom << std::endl;
		std::cout << "The total amount of pollution in the region is " << totalPol << " units.\n";
	}
	else 
	{
		std::cout << "The total populations for the requested area are:\n";
		std::cout << "Residential: " << totalRes << std::endl;
		std::cout << "Industrial: " << totalInd << std::endl;
		std::cout << "Commercial: " << totalCom << std::endl;
		std::cout << "The total amount of pollution for the requested area is " << totalPol << " units.\n";
	}

    return true;
}