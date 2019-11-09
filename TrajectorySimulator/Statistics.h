#ifndef STATISTICS_H
#define STATISTICS_H

#include <cmath>

template <class T>
class Statistics
{
public:
	Statistics();
	void addValue(const T value);
	double getAverage() const;
	double getStddev() const;
	void reset();

private:
	T m_sum{};
	T m_squareSum{};
	int m_count{};

};

template <class T>
Statistics<T>::Statistics()
	: m_sum(0.0), m_squareSum(0.0), m_count(0) {};

template <class T>
void Statistics<T>::reset()
{
	m_sum = 0;
	m_squareSum = 0;
	m_count = 0;
}

template <class T>
void Statistics<T>::addValue(const T value)
{
	m_sum += value;
	m_squareSum += value * value;
	++m_count;
}

template <class T>
double Statistics<T>::getAverage() const
{
	return m_sum / static_cast<double>(m_count);
}

template <class T>
double Statistics<T>::getStddev() const
{
	double avg = getAverage();
	return sqrt(m_squareSum / static_cast<double>(m_count) - avg * avg);
}

#endif // !STATISTICS_H
