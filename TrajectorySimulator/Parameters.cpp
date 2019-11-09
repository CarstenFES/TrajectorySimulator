#include "Parameters.h"

#include <cassert>
#include <fstream>
#include <initializer_list>
#include <iostream>

/*Not sure, how to transfer these checking routines into member functions...*/
bool checkInt(int& x)
{
	return x >= 0;
}

bool checkString(std::string & name)
{
	return name != "";
}

Parameters::Parameters()
{
	readParameters();
	m_noTotal = m_noPinned + m_noHarmonic + m_noDiffusive;

	m_percPinned = static_cast<double>(m_noPinned) / m_noTotal;
	m_percHarmonic = static_cast<double>(m_noHarmonic) / m_noTotal;
	m_percDiffusive = static_cast<double>(m_noDiffusive) / m_noTotal;

}

Parameters::Parameters(std::initializer_list<int> list)
{
	std::cout << "Parameter initialization via list... No name is provided, using 'set'!\n";

	assert(list.size() >= 5 && "Initializer list must have at least 5 members" );

	m_noSteps = *(list.begin());
	m_lagTime = *(list.begin()+1);

	m_noPinned = *(list.begin() + 2);
	m_noHarmonic = *(list.begin() + 3);
	m_noDiffusive = *(list.begin() + 4);

	m_noTotal = m_noPinned + m_noHarmonic + m_noDiffusive;

	m_percPinned = static_cast<double>(m_noPinned) / m_noTotal;
	m_percHarmonic = static_cast<double>(m_noHarmonic) / m_noTotal;
	m_percDiffusive = static_cast<double>(m_noDiffusive) / m_noTotal;
}


void Parameters::readParameters() 
{

	do
	{
		std::cout << "Enter name for trajectory: ";
	} while (!extraction(m_name,checkString));

	do
	{
		std::cout << "Enter number of steps: ";
		;
	} while (!extraction(m_noSteps,checkInt));

	do
	{
		std::cout << "Enter lag time between switches (or 0 for no switching): ";
	} while (!extraction(m_lagTime, checkInt));

	do
	{
		std::cout << "\nEnter number of pinned particles: ";
	} while (!extraction(m_noPinned, checkInt));

	do
	{
		std::cout << "Enter number of harmonically constraint particles: ";
	} while (!extraction(m_noHarmonic, checkInt));

	do
	{
		std::cout << "Enter number of diffusive particles: ";
	} while (!extraction(m_noDiffusive, checkInt));

}

template <class T>
bool Parameters::extraction(T& value, bool (*check)(T&))
{
	T in{};
	std::cin >> in;

	if (std::cin.fail()) // has a previous extraction failed or overflowed?	
	{
		// yep, so let's handle the failure
		std::cin.clear(); // put us back in 'normal' operation mode
		std::cin.ignore(32767, '\n'); // and remove the bad input
		return false;
	}
	else if (check(in))
	{
		std::cin.ignore(32767, '\n');
		value = in;
		return true;
	}
	else
	{
		return false;
	}
}

void Parameters::printParameters() const
{
	std::cout << "\nI read:\n";
	std::cout << "Name: " << m_name << "\n";
	std::cout << m_noSteps << " steps\n";
	std::cout << m_lagTime << " lag time\n";
	std::cout << m_noPinned << " pinned particles (" << m_percPinned << ")\n";
	std::cout << m_noHarmonic << " harmonic particles (" << m_percHarmonic << ")\n";
	std::cout << m_noDiffusive << " diffusive particles (" << m_percDiffusive << ")\n\n";
}

void Parameters::printParametersToFile() const
{
	std::ofstream myfile;
	std::string filename_format = "./output/" + m_name + ".in";
	myfile.open(filename_format);

	myfile << "\nI read:\n";
	myfile << "Name: " << m_name << "\n";
	myfile << m_noSteps << " steps\n";
	myfile << m_lagTime << " lag time\n";
	myfile << m_noPinned << " pinned particles (" << m_percPinned << ")\n";
	myfile << m_noHarmonic << " harmonic particles (" << m_percHarmonic << ")\n";
	myfile << m_noDiffusive << " diffusive particles (" << m_percDiffusive << ")\n\n";

	myfile.close();


}