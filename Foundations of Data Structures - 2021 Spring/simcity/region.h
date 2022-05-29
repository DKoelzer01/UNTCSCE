#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <fstream>
#include <string>
#include "cell.h"
#include "residential.h"
#include "industrial.h"
#include "commercial.h"

class Region
{
    private:
        int ySize = 0;
        int xSize = 0;
        int timeStep = 0;
        int maxTimeStep = 0;
        int refreshRate = 0;
		int cellsUpdated = 0;

        int availableWorkers = 0;
        int availableGoods = 0;
		int totalWorkers = 0;
		int totalPollution = 0;
		int totalGoods = 0;

    public:
        Cell*** map;    // 2D cell pointer array
        std::vector<Cell*> sortedMap;

        int GetXSize()  { return xSize; }
        int GetYSize()  { return ySize; }

        int GetTimeStep()     { return timeStep; }  //  These four variables might only be used internally.
        int GetMaxTimeStep()  { return maxTimeStep; }
        int GetRefreshRate()  { return refreshRate; }
		int GetCellsUpdated() { return cellsUpdated; }

        Region(std::string, int, int);
        ~Region();

        void AdvanceTimeStep();
        void PrintRegion(bool noData);
        void PrintPollutionState();
        bool AnalyseRegion(int x1, int y1, int x2, int y2, bool reg);
};
#endif