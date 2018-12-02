//AirIntake.h
#ifndef AIRINTAKE_HH_
#define AIRINTAKE_HH_

#include <string>
#include <sstream>
#include "algos.hh"
#include "Part.hpp"
#include "Collection.hpp"

class AirIntake : public Part
{
public:
	AirIntake(const json &data);
	~AirIntake();

  static const std::string getPath() { return ("AirIntakes"); };

	int getAerodynamic() const;
	int getPrice() const;

	static Collection<AirIntake> collection;

protected:
	int _aerodynamic;
	int _price;
};

#endif /* !AIRINTAKE_HH_ */