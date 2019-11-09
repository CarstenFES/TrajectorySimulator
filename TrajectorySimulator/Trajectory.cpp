#include "MyRandom.h"
#include "Trajectory.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Trajectory::Trajectory()
	: m_dynamics(nullptr)
{};

Trajectory::Trajectory(const Dynamics::Type type)
	: m_dynamics(nullptr)
{
	init(type);
};

Trajectory::~Trajectory()
{
	if(m_dynamics)
		delete[] m_dynamics;
}

void Trajectory::init(const Dynamics::Type type)
{
	//m_trj.push_back(0.0);
	m_trj.push_back(g_rand.getNormalNumber(0,0.001));
	setType(type);
}; 

void Trajectory::setType(const Dynamics::Type type)
{
	m_type = type;

	if (m_dynamics)
		delete m_dynamics;

	switch (m_type)
	{
	case Dynamics::Type::PINNED:
		m_dynamics = new Pinned;
		break;
	case Dynamics::Type::HARMONIC:
		m_dynamics = new Harmonic(getValue(getLength() - 1),0, g_rand.getUniformNumber(-1, 1));
		break;
	case Dynamics::Type::DIFFUSIVE:
		m_dynamics = new Diffusion;
		break;
	case Dynamics::Type::ALL_TYPES:
	default:
		std::cout << "Error! Cannot assign dynamics!\n";
		break;
	}
}

void Trajectory::genTrajectory(const int noSteps)
{
	assert(noSteps > 0 && "noSteps has to be a positive number!");

	int startIndex{ getLength() };
	m_trj.resize(startIndex + noSteps);

	for (int step = startIndex; step < getLength(); ++step)
	{
		m_trj[step] = m_dynamics->getNewPos(m_trj[step - 1]);
	}
}

void Trajectory::printTrajectory() const
{
	for (int step = 0; step < getLength(); ++step)
	{
		std::cout << m_trj[step] << "\n";
	}
}

void Trajectory::printTrajectoryToFile(const std::string &filename) const
{
	std::ofstream myfile;
	std::string filename_format = "./output/" + filename + ".txt";
	myfile.open(filename_format);
	
	for (int step = 0; step < getLength(); ++step)
	{
		myfile << m_trj[step] << "\n";
	}

	myfile.close();
}


double Trajectory::getValue(const int index) const
{
	assert(index >= 0 && index < getLength() && "Error! Invalid index!");

	return m_trj[index];
}