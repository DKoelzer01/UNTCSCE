#include "region.h"


int main()
{
    std::string configFile;
    std::string inputFiles[2];
    int configVariables[4];

	std::cout << "Please enter configuration file name:" << std::endl;
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

    std::string temp;
    //  Parse out relevant data from configuration files
    for(int i = 0; i < 2; i++)
    {
        std::getline(configStream, temp);
        inputFiles[i] = temp.substr(temp.find(":") + 1, temp.length() - 1);
    }

    std::getline(configStream, temp);   // Skip empty line
    //  Read configuration variables
    for (int i = 0; i < 4; i++)
    {
        std::string temp;
        std::getline(configStream, temp);
        configVariables[i] = stoi(temp.substr(temp.find(":") + 1, temp.length() - 1));
    }

    Region region(inputFiles, configVariables);

    region.PrintAreaPopulations();
    region.PrintAdjacency();
    
	std::stringstream SimulationStats; //String Stream used to buffer all of the simulation data such as the Peak # infected and Day, as well as the Final day and Total Infected of each simulation.

	//Closeness
	region.Reset();
	region.SetStrategy(closeness);
	region.DistributeVaccines();
	region.InitialInfection(configVariables[0]); //configVariables[0] is the starting area.

	std::cout << "CLOSENESS DISTRIBUTION" << std::endl;
	while (region.AdvanceTimeStep(0));
	SimulationStats << "closeness centrality" << "\n" << region.GetPeakInfected() << "\n" << region.GetPeakDay() << "\n" << region.GetFinalDay() << "\n" << region.GetTotalInfected() << "\n";
	
	//Degree
	region.Reset();
	region.SetStrategy(degree);
	region.DistributeVaccines();
	region.InitialInfection(configVariables[0]); //configVariables[0] is the starting area.

	std::cout << "DEGREE DISTRIBUTION" << std::endl;
	while (region.AdvanceTimeStep(0));
	SimulationStats << "degree centrality" << "\n" << region.GetPeakInfected() << "\n" << region.GetPeakDay() << "\n" << region.GetFinalDay() << "\n" << region.GetTotalInfected() << "\n";

	//Random
	region.Reset();
	region.SetStrategy(random_dist);
	region.DistributeVaccines();
	region.InitialInfection(configVariables[0]); //configVariables[0] is the starting area.

	std::cout << "RANDOM DISTRIBUTION" << std::endl;
	while (region.AdvanceTimeStep(0));
	SimulationStats << "random" << "\n" << region.GetPeakInfected() << "\n" << region.GetPeakDay() << "\n" << region.GetFinalDay() << "\n" << region.GetTotalInfected() << "\n";

	//Equal -> Round-robin
	region.Reset();
	region.SetStrategy(equal_dist);
	region.DistributeVaccines();
	region.InitialInfection(configVariables[0]); //configVariables[0] is the starting area.

	std::cout << "EQUAL DISTRIBUTION" << std::endl;
	while (region.AdvanceTimeStep(0));
	SimulationStats << "equal" << "\n" << region.GetPeakInfected() << "\n" << region.GetPeakDay() << "\n" << region.GetFinalDay() << "\n" << region.GetTotalInfected() << "\n";

    //Proportional
	region.Reset();
	region.SetStrategy(proportional);
	region.DistributeVaccines();
	region.InitialInfection(configVariables[0]); //configVariables[0] is the starting area.

	std::cout << "WEIGHTED DISTRIBUTION" << std::endl;
	while (region.AdvanceTimeStep(0));
	SimulationStats << "weighted" << "\n" << region.GetPeakInfected() << "\n" << region.GetPeakDay() << "\n" << region.GetFinalDay() << "\n" << region.GetTotalInfected() << "\n";


	std::string method, peakDay, peakInf, fDay, totalInf;

	for (int i = 0; i < 5; i++) { // Parse the SimulationStats stream, output formatted data.
		getline(SimulationStats, method);
		getline(SimulationStats, peakInf);
		getline(SimulationStats, peakDay);
		getline(SimulationStats, fDay);
		getline(SimulationStats, totalInf);
		std::cout << "Using the " << method << " distribution method, the peak number of infected was " << peakInf << " on day " << peakDay << ". The outbreak ended on day " << fDay << " and the total number of infected individuals was " << totalInf << "." << std::endl;
	}
    return 0;
}