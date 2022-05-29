#include "commercial.h"


Commercial::Commercial(int x, int y, int pop, int pol) : Cell(x, y, pop, pol, COM)
{

}

void Commercial::AttemptGrowth(int& availWorkers, int& availGoods)
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

    if(availWorkers >= 1 && availGoods >= 1)   // All commercial growth requires 1 available worker and 1 available good.
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
        
        if(updated)
        {
            availWorkers -= 1;
            availGoods -= 1;
        }
    }    
	return;
}

char Commercial::PrintCell()
{
    if(population > 0)
        return '0' + population;
    return 'C';
}