#include "Ensemble.h"

Ensemble::Ensemble(const std::string & name)
	: isSetUp(false), m_name(name)
{}

int Ensemble::getSize() const 
{ 
	return m_trajectories.size(); 
}

void Ensemble::printEnsembleToFile() const
{
	int index = 0;

	for (auto & trj : m_trajectories) 
	{
		trj.printTrajectoryToFile(m_name + "_" + std::to_string(index));
		++index;
	}
}