#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>

class Ensemble;
class Trajectory;

class Analysis
{
public:
	Analysis(const Ensemble &rawData);

	void calcMSD() const;
	void calcNGP() const;
	void calcSqt() const;
	void calcVanHove() const;

private:
	const Ensemble & m_rawData;
	
	const int m_noTrjs;
	int m_noSteps;

	static const std::vector <double> q;
};
#endif // !ANALYSIS_H
