#include "region.h"

Region::Region(std::string* files, int* vars)
{
	std::ifstream populationStream;
	populationStream.open(files[0]);
	if (populationStream.is_open()) //File IO handling.
	{
		std::string id, pop;
		std::getline(populationStream, id, ':');
		std::getline(populationStream, pop);
		while (!populationStream.eof())
		{
			areas.push_back(new Area(stoi(id), stoi(pop)));
			std::getline(populationStream, id, ':');
			std::getline(populationStream, pop);
		}

		populationStream.close();
	}
	else
	{
		std::cout << "Population file was not found.\n";
	}

	std::ifstream regionStream;
	regionStream.open(files[1]);
	if (regionStream.is_open()) //Region File Parsing
	{
		std::string line;
		getline(regionStream, line);

		for (int i = 0; i < areas.size(); i++)
		{
			getline(regionStream, line);
			std::stringstream ss(line);
			std::string cell;
			getline(ss, cell, ',');
			for (int j = 0; j < areas.size(); j++)
			{
				getline(ss, cell, ',');
				if (cell == "1")
				{
					areas[i]->adjacent.push_back(areas[j]);
				}
			}
		}
		regionStream.close();
	}
	else
	{
		std::cout << "Region file was not found.\n";
	}

	for (int i = 0; i < areas.size(); i++) // Calculate centrality for all areas in region. Assign each with the infectious period.
	{
		areas[i]->CalculateCentrality(areas.size());
		areas[i]->SetInfectiousPeriod(vars[1]);
	}


	infectiousPeriod = vars[1];
	contactRate = vars[2];
	vaccines = vars[3];
	remainingVaccines = vaccines;

	

	strategy = closeness;
}
Region::~Region()
{
}

bool Region::AdvanceTimeStep(int step)
{
	if (step != 0)
		for (int i = 0; i < areas.size(); i++)
		{
			areas[i]->Infect(contactRate * areas[i]->GetInfected()); //Start time step by infecting new population. Doesnt occur on step 0.
		}
	for (int i = 0; i < areas.size(); i++)
	{
		if (areas[i]->GetQueuedStatus()) { //Infect areas with infections queued in the previous step.
			areas[i]->SetQueuedStatus(false);
			areas[i]->Infect(1);
		}
	}
	for (int i = 0; i < areas.size(); i++)
	{
		areas[i]->Recover();
	}
	for (int i = 0; i < areas.size(); i++)
	{
		if (areas[i]->GetInfected() > (areas[i]->GetPopulation() / 2))  // If the number of infected in an area is greater than half of its total population, spread to neighboring areas.
		{
			for (int j = 0; j < areas[i]->adjacent.size(); j++) 
			{
				if (areas[i]->adjacent[j]->GetInfected() == 0 && !areas[i]->adjacent[j]->GetQueuedStatus()) // Only spread to neighboring areas that don't already have an infected population, or an infection queued.
					areas[i]->adjacent[j]->SetQueuedStatus(true); // Queue an infection in the area to be resolved on the next time step.
			}
		}
	}

	UpdateStatistics(step); // Calculate new region statistics.

	std::cout << "DAY " << step << std::endl; //Begin Output for the timestep.
	PrintUpdate();

	int sumInfected = 0;
	for (int i = 0; i < areas.size(); i++)
	{
		sumInfected += areas[i]->GetInfected();
	}
	if (sumInfected == 0) { //If no infected are present, the simulation has reached the end state, and the simulation should finish.
		finalDay = step;
		return false;
	}
	else
		return AdvanceTimeStep(step + 1); //Continue the simulation.
}

void Region::InitialInfection(int id) {
	areas[id - 1]->Infect(1); //Infect the Area with matching ID.
}
void Region::DistributeVaccines()
{
	int minmaxId = 0;
	float minCloseness = 999999;
	int maxDegree = 0;
	int minPop = 0;
	int vaccinationCount = 0;

	switch (strategy) {
	//Closeness - Smallest closeness to largest, smaller label priority
	case(closeness): 
		while (remainingVaccines != 0) {
			minCloseness = 999999; 
			for (int i = 0; i < areas.size(); i++) {
				if (areas[i]->GetSusceptible() == 0) {
					continue; //Don't bother considering if the area is already vaccinated
				}

				if (areas[i]->GetCloseness() < minCloseness) { //Find smallest closeness value to give vaccines to. Ignore cases of equal closeness values since the loop is iterating in ascending ID order.
					minmaxId = i;
					minCloseness = areas[minmaxId]->GetCloseness();
				}
			}

			if (remainingVaccines >= areas[minmaxId]->GetSusceptible()) { //Case: more/equal vaccines than susceptible in area
				remainingVaccines -= areas[minmaxId]->GetSusceptible(); 
				areas[minmaxId]->Vaccinate(areas[minmaxId]->GetSusceptible());
			}
			else { // Vaccinate area with as many vaccines as are remaining.
				areas[minmaxId]->Vaccinate(remainingVaccines);
				remainingVaccines = 0;
			}
		}
		break;

	//Degree - Largest degree to smallest, smaller label takes priority
	case(degree): 
		while (remainingVaccines != 0) {
			maxDegree = 0;
			for (int i = 0; i < areas.size(); i++) {
				if (areas[i]->GetSusceptible() == 0) {
					continue;
				} //Don't bother considering if the area is already vaccinated

				if (areas[i]->GetDegree() > maxDegree) { //Find largest degree that hasn't been vaccinated.
					minmaxId = i;
					maxDegree = areas[i]->GetDegree();
				}
			}

			if (remainingVaccines >= areas[minmaxId]->GetSusceptible()) { //Case: More/equal vaccines than susceptible in region.
				remainingVaccines -= areas[minmaxId]->GetSusceptible();
				areas[minmaxId]->Vaccinate(areas[minmaxId]->GetSusceptible());
			}
			else {
				areas[minmaxId]->Vaccinate(remainingVaccines); //Vaccinate with as many vaccines are remaining.
				remainingVaccines = 0;
			}
		}

		break;

	//Random - Smallest label to largest
	case(random_dist): 
		for (int i = 0; i < areas.size(); i++)
		{
			if (areas[i]->GetSusceptible() == 0)
			{
				continue;
			} //Don't bother considering if the area is already vaccinated

			//Random distribution doesn't calculate where to distribute vaccines, simply gives them based on ID. Priority is given in ascending order.

			if (remainingVaccines >= areas[i]->GetSusceptible()) //Case: More/equal vaccines than susceptible in region.
			{
				remainingVaccines -= areas[i]->GetSusceptible();
				areas[i]->Vaccinate(areas[i]->GetSusceptible());
			}
			else //Vaccinate with as many vaccines are remaining.
			{
				areas[i]->Vaccinate(remainingVaccines);
				remainingVaccines = 0;
			}
		}
		break;

	//Equal - Equal amount until smallest region is filled, round robin from lowest label
	case(equal_dist): 
		while (remainingVaccines != 0) {
			minPop = 99999;
			vaccinationCount = 0;
			for (int i = 0; i < areas.size(); i++) {
				if (areas[i]->GetSusceptible() == 0) {
					continue;
				} //Don't bother considering if the area is already vaccinated
				vaccinationCount++; //Find number of areas susceptible
				minPop = areas[i]->GetSusceptible() < minPop ? areas[i]->GetSusceptible() : minPop; //Find smallest susceptible population.
			}
			int vaccinationAmount = 0;
			if (remainingVaccines > minPop * vaccinationCount) //If there are sufficient vaccines to evenly spread among every area, capped at the smallest population, do exactly that.
			{
				vaccinationAmount = minPop;
			}
			else //If there are too few vaccines, evenly spread them to each area
			{
				if (remainingVaccines < vaccinationCount) //Any spare vaccines, spread in a round-robin fashion.
				{
					while (remainingVaccines > 0) {
						for (int i = 0; i < areas.size(); i++)
						{
							if (remainingVaccines == 0) //Once vaccines are spread, break the loop.
								break;
							if (areas[i]->GetSusceptible() == 0)
							{
								continue;
							}
							remainingVaccines--;
							areas[i]->Vaccinate(1);
						}
					}
					
					remainingVaccines = 0;
					break;
				}
				vaccinationAmount = remainingVaccines / vaccinationCount;
			}
			for (int i = 0; i < areas.size(); i++) //Evenly spread vaccines to areas until there are more places to vaccinate than vaccines.
			{
				if (areas[i]->GetSusceptible() == 0)
				{
					continue;
				}
				remainingVaccines -= (vaccinationAmount);
				areas[i]->Vaccinate(vaccinationAmount);
			}
		}
		break;
    case(proportional): //  Bonus
    {
        int totalPopulation = 0;
        for(int i = 0; i < areas.size(); i++)
        {
            totalPopulation += areas[i]->GetSusceptible();
        }
        for(int i = 0; i < areas.size(); i++)  
        {
            float percentage = (float)areas[i]->GetSusceptible() / totalPopulation;
            areas[i]->Vaccinate(floor(percentage * vaccines));//  Distribute vaccines based on percentage of population
            remainingVaccines -= floor(percentage * vaccines);
        }
        while (remainingVaccines > 0) {
            for (int i = 0; i < areas.size(); i++)
            {
                if (remainingVaccines == 0) //Once vaccines are spread, break the loop.
                    break;
                if (areas[i]->GetSusceptible() == 0)
                {
                    continue;
                }
                remainingVaccines--;
                areas[i]->Vaccinate(1);
            }
        }
        break;
    }
	default:
		std::cout << "#ERROR Unrecognized Vaccination Strategy" << std::endl; //Should never occur.
		break;
    }
}
void Region::UpdateStatistics(int step) //Populate the region statistics.
{
	int sumInfected = 0;
	totalInfected = 0;
	for (int i = 0; i < areas.size(); i++)
	{
		sumInfected += areas[i]->GetInfected();
		totalInfected += areas[i]->GetInfected() + areas[i]->GetRecovered();
	}
	if (sumInfected > peakInfected)
	{
		peakInfected = sumInfected;
		peakDay = step;
	}
}

void Region::Reset() //Reset the region to prepare for next simulation.
{
	remainingVaccines = vaccines;
	totalInfected = -1;
	peakInfected = -1;
	peakDay = -1;
	finalDay = -1;
	for (int i = 0; i < areas.size(); i++)
	{
		areas[i]->Reset(); //Reset each area individually.
	}
}
void Region::PrintUpdate() //Print each area's stats
{
	for (int i = 0; i < areas.size(); i++) {
		areas[i]->Print();
	}
	std::cout << std::endl;
}

void Region::PrintAdjacency() // Print adjacency array.
{
	std::cout << "Adjacency List\n";
	for (int i = 0; i < areas.size(); i++)
	{
		std::cout << areas[i]->GetID() << ":";
		for (int j = 0; j < areas[i]->adjacent.size(); j++)
		{
			std::cout << " " << areas[i]->adjacent[j]->GetID();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Region::PrintAreaPopulations() //Print Population array.
{
	std::cout << "Regional Population\n";
	for (int i = 0; i < areas.size(); i++)
	{
		std::cout << areas[i]->GetID() << " " << areas[i]->GetPopulation() << std::endl;
	}
	std::cout << std::endl;
}