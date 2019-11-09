#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include "Trajectory.h"

#include <string>
#include <vector>

class Simulator;

class Ensemble
{
public:
	Ensemble(const std::string &name);

	const std::string &getName() const { return m_name; };
	int getSize() const ;
	const std::vector<Trajectory>& getTrajectories() const { return m_trajectories; };

	void printEnsembleToFile() const;

	friend Simulator;

	const Trajectory& operator[](const int index) const { return m_trajectories[index]; };

private:
	int isSetUp;
	const std::string m_name{ "" };
	std::vector<Trajectory> m_trajectories;

	Trajectory& operator[](const int index) { return m_trajectories[index]; };
};


#endif // !ENSEMBLE_H



