#include "Analysis.h"
#include "Ensemble.h"
#include "Histogram.h"
#include "Statistics.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

const std::vector <double> Analysis::q = { 0.01, 0.025, 0.05, 0.1, 0.25, 0.5, 1 };

Analysis::Analysis(const Ensemble& rawData)
	: m_rawData(rawData), m_noTrjs(rawData.getSize())
{
	assert(m_noTrjs > 0 && "Error! rawdata are empty");
	m_noSteps = m_rawData[0].getLength();
	if (m_noSteps == 0) {
		std::cout << "\nTrajectories are empty... you sure that this is right?\n";
		exit(1);
	}
}

void Analysis::calcMSD() const
{
	Statistics<double> stat;

	std::ofstream outfile;
	std::string name = "./output/msd_" + m_rawData.getName() + ".txt";
	outfile.open(name);
	outfile << "# time \t MSD \n";

	for (int step = 0; step < m_noSteps; ++step)
	{
		for (int run = 0; run < m_noTrjs; ++run) {

			double dx = m_rawData[run][step] - m_rawData[run][0];
			stat.addValue(dx * dx);
		}

		outfile << step << "\t" << stat.getAverage() << "\n";
		stat.reset();
	}
	outfile.close();
}

void Analysis::calcNGP() const
{
	Statistics<double> m4d;
	Statistics<double> m2d;

	std::ofstream outfile;
	std::string name = "./output/ngp_" + m_rawData.getName() + ".txt";
	outfile.open(name);
	outfile << "# time \t <x**4> \t <x**2> \n";

	for (int step = 0; step < m_noSteps; ++step)
	{
		for (int run = 0; run < m_noTrjs; ++run) {

			double dx = m_rawData[run][step] - m_rawData[run][0];
			m4d.addValue(dx * dx * dx * dx);
			m2d.addValue(dx * dx);
		}

		outfile << step << "\t" << m4d.getAverage() << "\t" << m2d.getAverage() << "\n";
		m4d.reset();
		m2d.reset();
	}
	outfile.close();
}


void Analysis::calcSqt() const
{
	Statistics<double> stat;

	std::ofstream outfile;
	std::string name = "./output/sqt_" + m_rawData.getName() + ".txt";
	outfile.open(name);
	outfile << "# q << time \t MSD \n";

	for (size_t qindex = 0; qindex < q.size(); ++qindex)
	{
		for (int step = 0; step < m_noSteps; ++step)
		{
			for (int run = 0; run < m_noTrjs; ++run) {

				double dx = m_rawData[run][step] - m_rawData[run][0];
				stat.addValue(cos(q[qindex] * dx));
			}

			outfile << q[qindex] << "\t" << step << "\t" << stat.getAverage() << "\n";
			stat.reset();
		}
	}
	outfile.close();
}

void Analysis::calcVanHove() const {

	const int histSize = 100;

	std::ofstream outfile;
	std::string name = "./output/vanHove_" + m_rawData.getName() + ".txt";
	outfile.open(name);
	outfile << "# time \t position \t vanHove \n";

	for (int step = 1; step < m_noSteps; step += 10)
	{
		std::vector<double> values(m_noTrjs);

		for (int run = 0; run < m_noTrjs; ++run) {
			values[run] = m_rawData[run][step] - m_rawData[run][0];
		}

		Histogram<double> hist(values, histSize);
		for (int binIndex = 0; binIndex < histSize; ++binIndex)
		{
			outfile << step << "\t" << hist.getBin(binIndex) << "\t" << hist.getDensity(binIndex) << "\n";
		}
	}
	outfile.close();
}