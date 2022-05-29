#ifndef AREA_H
#define AREA_H

#include <vector>
#include <queue>
#include <iomanip>
#include <iostream>

class Area
{
private:
	int id;
    float closeness;
    int degree;

	int infectiousPeriod;
	bool infectionQueued = false; // Boolean status for infections spreading to a new area for the first time. Allows the simulation to infect the first population at the beginning of the timestep.

	int population;
	int susceptible;
	int infected;
	int recovered;
	int vaccinated;
public:

	std::queue<int> InfectionEventQueue;
    std::vector<Area*> adjacent;

    Area(int, int);
    void CalculateCentrality(int);

	void SetQueuedStatus(bool status) { infectionQueued = status; }
	bool GetQueuedStatus() { return infectionQueued; }

	void SetInfectiousPeriod(int x) { infectiousPeriod = x; }

    int GetID() { return id; }

	float GetCloseness() { return closeness; }
	int GetDegree() { return degree; }

    int GetPopulation() { return population; }
	int GetSusceptible() { return susceptible; }
	int GetInfected() { return infected; }
	int GetRecovered() { return recovered; }
	int GetVaccinated() { return vaccinated; }

	void Print();
	void Reset();

    void Infect(int x);
	void Recover();
	void Vaccinate(int x);
};

#endif