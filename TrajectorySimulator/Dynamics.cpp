#include "Dynamics.h"
#include "MyRandom.h"

#include <cmath>

double Pinned::getNewPos(const double oldPos)
{
	return oldPos;
}

Harmonic::Harmonic(const double x0, const int deltaTime, const double amplitude)
	: m_x0(x0), m_deltaTime(deltaTime), m_amplitude(amplitude)
{
}

double Harmonic::getNewPos(const double oldPos)
{
	return m_x0 - m_amplitude * sin(++m_deltaTime);
}

double Diffusion::getNewPos(const double oldPos)
{
	return oldPos + g_rand.getNormalNumber(0, 1);
}
