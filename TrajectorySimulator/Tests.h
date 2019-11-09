#ifndef TESTS_H
#define TESTS_H

#include "Analysis.h"
#include "Ensemble.h"
#include "Histogram.h"
#include "MyRandom.h"
#include "Parameters.h"
#include "Simulator.h"
#include "Statistics.h"
#include "Trajectory.h"

#include <iostream>


void randomTest()
{
	for (int i = 0; i < 5; i++)
		std::cout << "uniform "  << g_rand.getUniformNumber(-1, 1) << "\n";
	std::cout << "\n";
	for (int i = 0; i < 5; i++)
		std::cout << "normal " << g_rand.getNormalNumber(0, 1) << "\n";
	std::cout << "\n";
	for (int i = 0; i < 5; i++)
		std::cout << "exponential " << g_rand.getExponentialNumber(1) << "\n";
}

void trjTest()
{
	const int noSteps = 75;

	
	Trajectory trj_pin(Dynamics::Type::PINNED);
	Trajectory trj_harm(Dynamics::Type::HARMONIC);
	Trajectory trj_diff(Dynamics::Type::DIFFUSIVE);
	Trajectory trj_mixed(Dynamics::Type::DIFFUSIVE);

	std::cout << "Pinned trajectory ("<< noSteps <<" steps)\n";
	trj_pin.genTrajectory(noSteps);
	trj_pin.printTrajectoryToFile("pinned_test");
	std::cout << "\n";


	std::cout << "Harmonic trajectory (" << noSteps << " steps)\n";
	trj_harm.genTrajectory(noSteps);
	trj_harm.printTrajectoryToFile("harmonic_test");
	std::cout << "\n";

	std::cout << "Diffusive trajectory (" << noSteps << " steps)\n";
	trj_diff.genTrajectory(noSteps);
	trj_diff.printTrajectoryToFile("diffusive_test");
	std::cout << "\n";

	std::cout << "Mixed trajectory (" << noSteps << " steps)\n";
	trj_mixed.genTrajectory(noSteps/3);
	trj_mixed.setType(Dynamics::Type::HARMONIC);
	trj_mixed.genTrajectory(noSteps / 3);
	trj_mixed.setType(Dynamics::Type::PINNED);
	trj_mixed.genTrajectory(noSteps / 3);
	trj_mixed.printTrajectoryToFile("mixed_test");
	std::cout << "\n";

	std::cout << "Access first three Elements of mixed trajectory\n";
	std::cout << trj_mixed.getValue(0) << "\n";
	std::cout << trj_mixed.getValue(1) << "\n";
	std::cout << trj_mixed.getValue(2) << "\n";
}

void statisticTest()
{
	
	const int noValues = 100000;

	Statistics<double> stats;

	std::cout << "Statistics with " << noValues << " uniformly distributed values\n";
	for (int i = 0; i < noValues; ++i)
	{
		stats.addValue(g_rand.getUniformNumber(-1, 1));
	}
	std::cout << "Avg (0.0): " << stats.getAverage() << " , Stddev (0.5773): " << stats.getStddev();
	std::cout << "\n";

	stats.reset();

	std::cout << "Statistics with " << noValues << " normal distributed values\n";
	for (int i = 0; i < noValues; ++i)
	{
		stats.addValue(g_rand.getNormalNumber(0, 1));
	}
	std::cout << "Avg (0.0): " << stats.getAverage() << " , Stddev (1.0): " << stats.getStddev();
	std::cout << "\n";

	stats.reset();

	std::cout << "Statistics with " << noValues << " expoential distributed values\n";
	for (int i = 0; i < noValues; ++i)
	{
		stats.addValue(g_rand.getExponentialNumber(2));
	}
	std::cout << "Avg (2.0): " << stats.getAverage() << " , Stddev (2.0): " << stats.getStddev();
	std::cout << "\n";

}

void parametersTest()
{

	std::cout << "Reading Input Parameters\n\n";
	Parameters param{ 50, 10, 25,0, 75 };
	param.printParameters();
	std::cout << "(50, 10, 25,0, 75)\n";
}

void simulatorTest()
{	
	Parameters param{ 50, 1, 2,0, 3 };
	Ensemble ens(param.getName());
	{
		Simulator sim(param, ens);
		sim.runSimulations();
	}
	ens.printEnsembleToFile();
}

void histogramTest()
{
	const int noValues = 10000;
	std::vector <double> normalValues(noValues);
	std::vector <double> exponValues(noValues);
	std::vector <int> intValues(noValues);

	for (int i = 0; i < noValues; i++)
	{
		normalValues[i] = g_rand.getNormalNumber(0, 100);
		exponValues[i] = g_rand.getExponentialNumber(10);
		intValues[i] = g_rand.getUniformInt(0, 100);
	}
	const int histSize = 10;
	{
		Histogram<double> hist(normalValues, histSize);
		hist.printHistogram();
	}
	std::cout << "\n";
	{
		Histogram<double> hist(exponValues, histSize);
		hist.printHistogram();
	}
	std::cout << "\n";
	{
		Histogram<int> hist(intValues, histSize);
		hist.printHistogram();
	}
}


void analysisTest()
{
	const int noTrjs = 1000;
	const int noSteps = 1000;

	std::cout << "Analyze " << noTrjs << " harmonic walkers.\n";	
	
	Ensemble ens1("harm_test");
	{
		Parameters param{ noSteps, 0, 0,noTrjs,0};
		Simulator sim(param, ens1);
		sim.runSimulations();
	}
	{ 
		Analysis analy(ens1);
		analy.calcMSD();
		analy.calcNGP();
		analy.calcSqt();
		analy.calcVanHove();
		std::cout << "\n";
	}

	std::cout << "Analyze " << noTrjs << " diffusive walkers.\n";
	Ensemble ens2("diff_test");
	{
		Parameters param{ noSteps, 0, 0,0,noTrjs };
		Simulator sim(param, ens2);
		sim.runSimulations();
	}

	{
		Analysis analy(ens2);
		analy.calcMSD();
		analy.calcNGP();
		analy.calcSqt();
		analy.calcVanHove();
		std::cout << "\n";
	}
	
	std::cout << "Analyze " << noTrjs << " mixed walkers.\n";
	Ensemble ens3("mixed_test");
	{
		Parameters param{ noSteps, 0, noTrjs/2,0, noTrjs/2 };
		Simulator sim(param, ens3);
		sim.runSimulations();
	}

	{
		Analysis analy(ens3);
		analy.calcMSD();
		analy.calcNGP();
		analy.calcSqt();
		analy.calcVanHove();
		std::cout << "\n";
	}

	std::cout << "Analyze " << noTrjs << " shuffled walkers.\n";
	Ensemble ens4("shuffled_test");
	{
		Parameters param{ noSteps, 100, noTrjs / 2,0, noTrjs / 2 };
		Simulator sim(param, ens4);
		sim.runSimulations();
	}

	{
		Analysis analy(ens4);
		analy.calcMSD();
		analy.calcNGP();
		analy.calcSqt();
		analy.calcVanHove();
		std::cout << "\n";
	}
}



#endif // !TESTS_H

