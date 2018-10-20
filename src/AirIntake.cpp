//AirIntake.cpp
#include "AirIntake.hh"
#include "Menu.hh"

std::vector<AirIntake> AirIntake::collection = std::vector<AirIntake>();

AirIntake::AirIntake(const std::string& modele, const char& rang, const int& aerodynamisme)
 : Part(), _name(modele), _rank(rang), _aerodynamic(aerodynamisme)
{
}

AirIntake::AirIntake(const json &data)
 : Part(), _name(data["name"].get<std::string>()), _rank(data["rank"].get<std::string>()[0]), _aerodynamic(data["aerodynamic"].get<int>()), _price(vRang(_rank) * 1500)
{
}

AirIntake::~AirIntake()
{

}

std::string AirIntake::getName() const
{
	return (_name);
}

char AirIntake::getRank() const
{
	return (_rank);
}

int AirIntake::getAerodynamic() const
{
	return (_aerodynamic);
}

int AirIntake::getPrice() const
{
	return _price;
}