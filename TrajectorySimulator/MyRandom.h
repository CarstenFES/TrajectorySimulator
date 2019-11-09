#ifndef MYRANDOM_H
#define MYRANDOM_H

#include <ctime>
#include <random>

class MyRandom
{
public:
	MyRandom(time_t seed);

	double getUniformNumber(const double min, const double max);
	int getUniformInt(const int min, const int max);
	double getExponentialNumber(const double average);
	double getNormalNumber(const double mu, const double sigma);

private:
	std::mt19937 m_mersenne;
	void BoxMuller();
	
	double m_z1, m_z2; // belongs to BoxMuller
	bool m_numbersReady = false; // belongs to BoxMuller
};

extern MyRandom g_rand;

#endif // !MYRANDOM_H