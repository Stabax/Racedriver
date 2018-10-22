//AirIntake.cpp
#include "AirIntake.hh"
#include "Menu.hh"

std::map<std::string, AirIntake> AirIntake::collection = std::map<std::string, AirIntake>();

AirIntake::AirIntake(const json &data)
 : Part(data), _aerodynamic(data["aerodynamic"].get<int>()), _price(vRang(rank) * 1500)
{
}

AirIntake::~AirIntake()
{

}

int AirIntake::getAerodynamic() const
{
	return (_aerodynamic);
}

int AirIntake::getPrice() const
{
	return _price;
}