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
	AirIntake(const std::string& modele, const char& rang, const int& aerodynamisme);
	AirIntake(const json &data);
	~AirIntake();

	std::string getName() const;
	char getRank() const;
	int getAerodynamic() const;
	int getPrice() const;

	static std::vector<AirIntake> collection;

protected:
	std::string _name;
	char _rank;
	int _aerodynamic;
	int _price;
};

#endif /* !AIRINTAKE_HH_ */