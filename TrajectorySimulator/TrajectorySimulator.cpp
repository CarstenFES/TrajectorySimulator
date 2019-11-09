#include "Analysis.h"
#include "Ensemble.h" 
#include "MyRandom.h"
#include "Parameters.h"
#include "Simulator.h"
//#include "Tests.h"	// Include for running the tests

#include <iostream>
#include <filesystem>
#include <vector>


#ifdef TESTS_H
MyRandom g_rand(0);
#else
MyRandom g_rand(std::time(nullptr));
#endif // TESTS_H


int main()
{
	std::filesystem::create_directory("./output");

#ifdef TESTS_H
	randomTest();
	trjTest();
	statisticTest();	
	parametersTest();
	simulatorTest();
	histogramTest();
	analysisTest();

	return 0;
#endif // TESTS_H

	Parameters param;
	param.printParametersToFile();
	Ensemble ens(param.getName());

	{
		Simulator sim(param, ens);
		sim.runSimulations();
	}
	if (param.getNoTrajectories() <= 10)
	{
		ens.printEnsembleToFile();
	}

	Analysis analy(ens);
	analy.calcVanHove();
	analy.calcMSD();
	analy.calcSqt();
	analy.calcNGP();

	return 0;
}