//Spoiler.cpp
#include "Spoiler.hh"
#include "Menu.hh"

std::vector<Spoiler> Spoiler::collection = std::vector<Spoiler>();

Spoiler::Spoiler(const std::string& modele, const char& rang, const int& aerodynamisme)
 : _name(modele), _rank(rang), _aerodynamic(aerodynamisme), _price(vRang(_rank) * 1500)
{
}

Spoiler::Spoiler(const json &data)
 : _name(data["name"].get<std::string>()), _rank(data["rank"].get<std::string>()[0]), _aerodynamic(data["aerodynamic"].get<int>())
{
}

Spoiler::~Spoiler()
{

}

std::string Spoiler::getName() const
{
	return _name;
}

char Spoiler::getRank() const
{
	return _rank;
}

int Spoiler::getAerodynamic() const
{
	return _aerodynamic;
}

int Spoiler::getPrice() const
{
	return _price;
}