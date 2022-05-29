#include "region.h"

int main()
{
    //  Configuration Variables
    std::string configFile;
    std::string mapFile;
    int maxTimeSteps;
    int refreshRate;

	std::cout << "Beginning simulation" << std::endl;

	std::cout << "Please enter configuration file name:";
    std::cin >> configFile;
    std::ifstream configStream;
    configStream.open(configFile);

    //  Wait until valid file is given.
    while(!configStream.is_open()) 
    {
        configStream.close();
        std::cout << "Invaild configuration file. Please enter vaild configuration file name:" << std::endl;
        std::cin >> configFile;
        configStream.open(configFile);
    }

    //  Parse out relevant data from configuration files
    std::string mapFileLine;
    std::getline(configStream, mapFileLine);
    mapFile = mapFileLine.substr(mapFileLine.find(":") + 1, mapFileLine.length() - 1);
    
    std::string timeStepsLine;
    std::getline(configStream, timeStepsLine);
    maxTimeSteps = stoi(timeStepsLine.substr(timeStepsLine.find(":") + 1, timeStepsLine.length() - 1));
    
    std::string refreshRateLine;
    std::getline(configStream, refreshRateLine);
    refreshRate = stoi(refreshRateLine.substr(refreshRateLine.find(":") + 1, refreshRateLine.length() - 1));

    configStream.close();

    //  Validate variables from config file.
    if(maxTimeSteps < 1 or refreshRate < 1)
    {
        std::cout << "Invalid configuration values." << std::endl;
        return 0;
    }

	Region region(mapFile, maxTimeSteps, refreshRate); //  Main region object.
    
	while (region.GetTimeStep() <= region.GetMaxTimeStep() && region.GetCellsUpdated() != 0) { //Check if current time step is less than max, and atleast 1 cell updated last cycle.
		region.AdvanceTimeStep();
	}

	std::cout << "\n\nFinal Region State\n";
	region.PrintRegion(true);

	std::cout << "\nPollution\n";
    region.PrintPollutionState(); 
	region.AnalyseRegion(0, 0, region.GetXSize() - 1, region.GetYSize() - 1, true);

	//  Allow user to analyse region   
    while(!region.AnalyseRegion(0,0,0,0,false))
    {
        std::cout << "Invalid region parameters.\n";
    }

	std::cout << "Simulation complete" << std::endl;
	return 0;
}