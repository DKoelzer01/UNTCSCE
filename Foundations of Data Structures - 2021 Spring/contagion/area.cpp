#include "area.h"

Area::Area(int id, int pop)
{
    this->id = id;
    this->population = pop;
	this->susceptible = pop;
}

void Area::CalculateCentrality(int regionSize)
{
    //  Calulate distance to each area
    int distance[regionSize];
    for (int i = 0; i < regionSize; i++)
    {
        distance[i] = 0;
    }
    std::queue<Area*> check;
    for(int i = 0; i < adjacent.size(); i++)
    {
        check.push(adjacent[i]);
        distance[adjacent[i]->GetID() - 1] = 1;
    }
    distance[GetID() - 1] = -1; // Cause algorithm to skip over self
    while(check.size() > 0)
    {
        int thisDistance = distance[check.front()->GetID() - 1];   //  Distance of current area being checked.
        for(int i = 0; i < check.front()->adjacent.size(); i++)
        {
            if(!distance[check.front()->adjacent[i]->GetID() - 1] || distance[check.front()->adjacent[i]->GetID() - 1] > thisDistance + 1)    //  Check if distance has already been assigned to or is a faster route
            {
                distance[check.front()->adjacent[i]->GetID() - 1] = thisDistance + 1;
                check.push(check.front()->adjacent[i]);
            }
        }
        check.pop();
    }
    
    //  Calculate average closeness
    int total = 0;
    for(int i = 0; i < regionSize; i++)
    {
        total += distance[i];
    }
    total += 1; //  Offset ingnore self
    closeness = (float)total / (regionSize - 1);

    degree = adjacent.size();
}

void Area::Reset() { // Reset all values to defaults between simulation runs.
	this->susceptible = this->population;
	this->infected = 0;
	this->recovered = 0;
	this->vaccinated = 0;

	std::queue<int> emptyQueue; 
	std::swap(this->InfectionEventQueue, emptyQueue); //Clear infection event queue by swapping with an empty queue.
	for (int i = 0; i < infectiousPeriod; i++) {
		this->InfectionEventQueue.push(0); // Insert x empty events at the beginning of the queue, where x is the infectious period of the simulated virus.
	}
}

void Area::Vaccinate(int x) {
	this->vaccinated += x;
	this->susceptible -= x;
}

void Area::Print() {
	std::cout << std::left << std::setw(4) << this->id 
		<< "POP: " << std::setw(7) << this->population
		<< "S: " << std::setw(7) << this->susceptible
		<< "I: " << std::setw(7) << this->infected
		<< "R: " << std::setw(7) << this->recovered
		<< "V: " << std::setw(7) << this->vaccinated << std::right << std::endl;
}

void Area::Infect(int x)
{
	if (x > this->susceptible) { // Case: Attempting to infect more people than are susceptible
		this->infected += this->susceptible;
		this->InfectionEventQueue.push(this->susceptible); // Queue the number of people infected this time step. Offset during the Reset() function by adding empty events at the beginning of the queue.
		this->susceptible = 0;
	}
	else { 
		this->susceptible -= x;
		this->infected += x;
		this->InfectionEventQueue.push(x); 
	}
	
}

void Area::Recover() 
{
	int val = this->InfectionEventQueue.front(); //At the end of every time step, take the value off of the front of the infection queue. This corresponds to the number of people who were infected X days ago, where X is the infectious period.
	this->InfectionEventQueue.pop();
	this->infected -= val;
	this->recovered += val;
}