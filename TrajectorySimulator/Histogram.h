#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <class T>
class Histogram
{
public:
	Histogram(const std::vector<T> &values, const int size);

	int getSize() const { return m_size; };
	double getBin(const int index) const { return m_bins[index]; };
	double getDensity(const int index) const { return m_density[index]; };

	void printHistogram() const;

private:
	const int m_size;
	std::vector<double> m_bins;
	std::vector<double> m_density;

	void calcHistogram(const std::vector<T>& values);
	int computeBin(const T value) const ;
	const T& m_min;
	const T& m_max;
	double m_width;

};

template <class T>
Histogram<T>::Histogram(const std::vector<T>& values, const int size)
	: m_min(*std::min_element(values.begin(), values.end())),
	m_max(*std::max_element(values.begin(), values.end())),
	m_size(size)
{
	assert(size > 0 && "Cannot create histogram of no size");

	m_bins.resize(m_size + 1);
	m_density.resize(m_size + 1);

	assert((m_max - m_min) > 0 && "Cannot create histogram of single values");

	m_width = (m_max - m_min) / (m_size);
	calcHistogram(values);
}

template <class T>
void Histogram<T>::calcHistogram(const std::vector<T>& values)
{

	for (size_t i = 0; i < values.size(); ++i)
	{
		++m_density[computeBin(values[i])];
	}

	for (int j = 0; j < m_size; ++j)
	{
		m_bins[j] = j * m_width + m_min;
		m_density[j] /= (values.size() * m_width);
	}
}

template <class T>
int Histogram<T>::computeBin(const T value) const
{
	return static_cast <int>((value - m_min) / m_width);
}

template <class T>
void Histogram<T>::printHistogram() const
{
	for (int index = 0; index < m_size; ++index)
	{
		std::cout << m_bins[index] << " " << m_density[index] << "\n";
	}
}


#endif // !HISTOGRAM_H