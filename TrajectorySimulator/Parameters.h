#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <initializer_list>
#include <iostream>
#include <string>

class Parameters
{
public:
	Parameters();

	Parameters(std::initializer_list<int> list);

	const std::string& getName() const { return m_name; };

	int getNoSteps() const { return m_noSteps; };
	int getLagTime() const { return m_lagTime; };

	int getNoPinned() const { return m_noPinned; };
	int getNoHarmonic() const { return m_noHarmonic; };
	int getNoDiffusive() const { return m_noDiffusive; };
	int getNoTrajectories() const { return m_noTotal; };

	double getPercPinned() const { return m_percPinned; };
	double getPercHarmonic() const { return m_percHarmonic; };
	double getPercDiffusive() const { return m_percDiffusive; };

	void readParameters();
	void printParameters() const;
	void printParametersToFile() const;

private:
	
	std::string m_name{"set"};

	template <class T>
	bool extraction(T& value, bool (*check)(T&));

	int m_noSteps{};
	int m_lagTime{};

	int m_noPinned{};
	int m_noHarmonic{};
	int m_noDiffusive{};
	int m_noTotal{};

	double m_percPinned{};
	double m_percHarmonic{};
	double m_percDiffusive{};

};
#endif // !PARAMETERS_H