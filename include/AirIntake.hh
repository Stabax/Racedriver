//AirIntake.h
#ifndef AIRINTAKE_HH_
#define AIRINTAKE_HH_

#include <string>
#include <sstream>
#include "algos.hh"
#include "Part.hpp"

class AirIntake : public Part
{
public:
	AirIntake(const json &data);
	~AirIntake();

	int getAerodynamic() const;
	int getPrice() const;

	static std::map<std::string, AirIntake> collection;

protected:
	int _aerodynamic;
	int _price;
};

#endif /* !AIRINTAKE_HH_ */