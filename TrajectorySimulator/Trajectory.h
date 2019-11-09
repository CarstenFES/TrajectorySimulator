#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "Dynamics.h"

#include <string>
#include <vector>


class Trajectory
{
public:
	
	
	Trajectory();
	Trajectory(const Dynamics::Type type);
	~Trajectory();

	void init(const Dynamics::Type type);
	void setType(const Dynamics::Type type);

	int getLength() const { return m_trj.size(); };
	double getValue(const int index) const;
	
	void genTrajectory(const int noSteps);
	void printTrajectory() const;
	void printTrajectoryToFile(const std::string &name) const;

	double operator[](const int index) const{ return getValue(index); };

private:

	Dynamics* m_dynamics{nullptr};
	Dynamics::Type m_type  { Dynamics::Type::ALL_TYPES };
	std::vector<double> m_trj;
	
};


#endif // !TRAJECTORY_H