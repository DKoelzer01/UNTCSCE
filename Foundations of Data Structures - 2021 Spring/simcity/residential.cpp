#include "residential.h"


Residential::Residential(int x, int y, int pop, int pol, int actWorkers) : Cell(x, y, pop, pol, RES)
{
    this->activeWorkers = actWorkers;
}

void Residential::AttemptGrowth(int& availWorkers, int& availGoods)
{
	bool adjacentPowerline = false; // Flag for checking growth with 0 pop.
	std::vector<int> popArray;
	for (int i = 0; i < adjacent.size(); i++) 
	{
		popArray.push_back(adjacent[i]->GetPopulation()); // Populate the popArray with the populations of adjacent cells.
		if (adjacent[i]->GetType() == UTIL) // Check if adjacent tile is a utility tile (Road, Powerline, Powerplant)
		{
			if (dynamic_cast<Utility*>(adjacent[i])->IsPowerLine()) // Check if the utility is a Powerline.
			{
				adjacentPowerline = true;
			}
		}
	}

	if (adjacentPowerline && population == 0) // 0 pop & powerline case
	{
		updated = true;
		return;
	}

	if (population == 0 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 1; }) >= 1) //0 pop and 1 or more adjacent pop of 1 or greater
	{
		updated = true;
		return;
	}

	if (population == 1 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 1; }) >= 2) //1 pop and 2 or more adjacent pop of 1 or greater
	{
		updated = true;
		return;
	}
	
	if (population == 2 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 2; }) >= 4) //2 pop and 4 or more adjacent pop of 2 or greater
	{ 
		updated = true;
		return;
	}

	if (population == 3 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 3; }) >= 6) //3 pop and 6 or more adjacent pop of 3 or greater
	{
		updated = true;
		return;
	}

	if (population == 4 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 4; }) >= 8) //4 pop and 8 adjacent pop of 4 or greater
	{
		updated = true;
		return;
	}
	updated = false;
	return;
}
char Residential::PrintCell()
{
	if (population > 0) {
		return '0' + population;	
	}
    return 'R';
}