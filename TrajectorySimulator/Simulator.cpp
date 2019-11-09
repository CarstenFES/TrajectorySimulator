#include "Ensemble.h"
#include "MyRandom.h"
#include "Parameters.h"
#include "Simulator.h"

#include <algorithm>

Simulator::Simulator(const Parameters& params, Ensemble& ens)
	: m_param(params),m_ensemble(ens)
{
	m_ensemble.m_trajectories.resize(params.getNoTrajectories());
	setUpSimulations();
};

void Simulator::runSimulations()
{
	std::cout << "\nRun simulations of " << m_param.getNoTrajectories() << " trajectories for "
		<< m_param.getNoSteps() << " in total.\n";

	if(m_param.getLagTime() == 0)
	{
		for (int run = 0; run < m_ensemble.getSize(); ++run)
		{
			runSimulationSteps(run,m_param.getNoSteps());
		}
	}
	else
	{
		for(int run = 0; run<m_ensemble.getSize(); ++run){

			int steps{0};
			while(steps< m_param.getNoSteps())
			{
				int cycleTime = 1+static_cast<int>(g_rand.getExponentialNumber(m_param.getLagTime()));
				cycleTime = std::min(cycleTime, m_param.getNoSteps()-steps);
				runSimulationSteps(run,cycleTime);
				shuffleSimulationType(run);
				steps += cycleTime;
			}
		}
	}
}

void Simulator::runSimulationSteps(const int run, const int noSteps)
{
		//std::cout << "Running simulations for " << noSteps << " steps\n";
	m_ensemble[run].genTrajectory(noSteps);
}

void Simulator::shuffleSimulationType(const int run)
{
		double rand = g_rand.getUniformNumber(0, 1);

		if (rand < m_param.getPercPinned())
			m_ensemble[run].setType(Dynamics::Type::PINNED);
		else if (rand < m_param.getPercPinned() + m_param.getPercHarmonic())
			m_ensemble[run].setType(Dynamics::Type::HARMONIC);
		else
			m_ensemble[run].setType(Dynamics::Type::DIFFUSIVE);
}



void Simulator::setUpSimulations()
{
	for (int run = 0; run < m_param.getNoPinned(); ++run)
	{
		m_ensemble[run].init(Dynamics::Type::PINNED);
	}
	for (int run = m_param.getNoPinned(); run < m_param.getNoPinned() + m_param.getNoHarmonic(); ++run)
	{
		m_ensemble[run].init(Dynamics::Type::HARMONIC);
	}
	for (int run = m_param.getNoPinned() + m_param.getNoHarmonic(); run < m_param.getNoTrajectories(); ++run)
	{
		m_ensemble[run].init(Dynamics::Type::DIFFUSIVE);
	}
	m_ensemble.isSetUp = true;
}