#include "industrial.h"


Industrial::Industrial(int x, int y, int pop, int pol, int avalGoods) : Cell(x, y, pop, pol, IND)
{
    this->availableGoods = availableGoods;
}

void Industrial::AttemptGrowth(int& availWorkers, int& availGoods)
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
	updated = false;

    if(availWorkers >= 2)   // All industrial growth requires 2 available workers.
    {
        if (adjacentPowerline && population == 0) // 0 pop & powerline case
        {
            updated = true;
        }

        if (population == 0 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 1; }) >= 1) //0 pop and 1 or more adjacent pop of 1 or greater
        {
            updated = true;
        }

        if (population == 1 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 1; }) >= 2) //1 pop and 2 or more adjacent pop of 1 or greater
        {
            updated = true;
        }

        if (population == 2 && count_if(popArray.begin(), popArray.end(), [](int i) { return i >= 2; }) >= 4) //2 pop and 4 or more adjacent pop of 2 or greater
        { 
            updated = true;
        }
        
        if(updated)
        {
            availWorkers -= 2;
        }
    }    
	return;
}

void Industrial::Pollute(int ySize, int xSize, Cell*** map) // Needs the map bounds and the map array
{
    for(int i = -population; i <= population; i++)
    {
        for(int j = -population; j <= population; j++)
        {
            if(xPos + i >= 0 && xPos + i < ySize && yPos + j >=0 && yPos + j < xSize)
            {
                map[xPos + i][yPos + j]->AddPollution(population - std::max(std::abs(i), std::abs(j))); //  Adds pollution based on distance from this cell.
            }
        }
    }
}

char Industrial::PrintCell()
{
    if(population > 0)
        return '0' + population;
    return 'I';
}