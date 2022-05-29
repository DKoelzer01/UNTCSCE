#ifndef REGION_H
#define REGION_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include "area.h"



enum VaccineStrategy
{
    closeness = 0,
    degree = 1,
    random_dist = 2,
    equal_dist = 3,
    proportional = 4
};
class Region
{
    private:
        std::vector<Area*> areas;
        
        int infectiousPeriod;
        int contactRate;
        int vaccines;
		int remainingVaccines;
        VaccineStrategy strategy;

		int totalInfected = -1;
		int peakInfected = -1;
		int peakDay = -1;
		int finalDay = -1;
    public:
        Region(std::string*, int*);
        ~Region();

        bool AdvanceTimeStep(int step);
        void DistributeVaccines();
        void UpdateStatistics(int step);
        void Reset();

        void PrintUpdate();
        void PrintAdjacency();
        void PrintAreaPopulations();

		void SetStrategy(VaccineStrategy s) { strategy = s; }

		void InitialInfection(int id);

		int GetPeakInfected() { return peakInfected; }
		int GetPeakDay() { return peakDay; }
		int GetFinalDay() { return finalDay; }
		int GetTotalInfected() { return totalInfected; }

};


#endif