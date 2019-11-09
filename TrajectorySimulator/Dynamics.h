#ifndef DYNAMICS_H
#define DYNAMICS_H

/*Just one header for all three dynamics as they are closly related*/

class Dynamics
{
public:
	enum Type
	{
		PINNED,
		HARMONIC,
		DIFFUSIVE,
		ALL_TYPES
	};

	virtual double getNewPos(const double oldPos) = 0;
	virtual ~Dynamics() {};

protected:
	Dynamics() {};
};

class Pinned final : public Dynamics
{
public:
	double getNewPos(const double oldPos) override;
};

class Harmonic final : public Dynamics
{
public:
	Harmonic(const double x0, const int deltaTime, const double amplitude);

	double getNewPos(const double oldPos) override;

private:
	const double m_x0 {};
	int m_deltaTime {};
	const double m_amplitude {};
};

class Diffusion final : public Dynamics
{
public:
	double getNewPos(const double oldPos) override;
};

#endif // !DYNAMICS_H