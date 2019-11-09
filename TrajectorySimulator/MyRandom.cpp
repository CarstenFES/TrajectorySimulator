#include "MyRandom.h"

#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <random>

MyRandom::MyRandom(time_t seed)
:m_mersenne(static_cast<std::mt19937::result_type>(seed)),
m_numbersReady(false)
{
	getUniformNumber(0, 1); //discard first value
};


double MyRandom::getUniformNumber(const double min, const double max) 
{
	std::uniform_real_distribution<> rand(min, max);

	return rand(m_mersenne);
}

int MyRandom::getUniformInt(const int min, const int max)
{
	std::uniform_int_distribution<> rand(min, max);

	return rand(m_mersenne);
}

double MyRandom::getExponentialNumber(const double average)
{
	return -log(getUniformNumber(0, 1)) * average;
}

double MyRandom::getNormalNumber(const double mu, const double sigma)
{
	if (m_numbersReady) {
		m_numbersReady = false;
		return mu + sigma * m_z2;
	}
	else
	{
		BoxMuller();
		m_numbersReady = true;
		return mu + sigma * m_z1;
	}
}


void MyRandom::BoxMuller()
{
	const double u1 = getUniformNumber(0, 1);
	const double u2 = getUniformNumber(0, 1);

	const double tmp = sqrt(-2.0 * log(u1));

	m_z1 = tmp * cos(2 * M_PI * u2);
	m_z2 = tmp * sin(2 * M_PI * u2);

}