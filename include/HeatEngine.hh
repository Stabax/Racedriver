#ifndef HEATENGINE_HH_
#define HEATENGINE_HH_

#include "Engine.hpp"

class HeatEngine : public Engine
{
public:
	HeatEngine(const json &data);
	~HeatEngine();

protected:
	//Manufacturer
	int _torque;

	//Instance
	int _revolutions;
};

#endif /* !HEATENGINE_HH_ */
