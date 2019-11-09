#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>

class Parameters;
class Trajectory;
class Ensemble;

class Simulator
{
public:
	Simulator(const Parameters& params, Ensemble & ens);
	
	void runSimulations();

private:
	void setUpSimulations();
	void shuffleSimulationType(const int run);
	void runSimulationSteps(const int run, const int noSteps);

	const std::string m_name{ "set" };
	const Parameters & m_param;
	Ensemble & m_ensemble;
};


#endif // !SIMULATOR_H





