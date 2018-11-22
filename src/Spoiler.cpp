//Spoiler.cpp
#include "Spoiler.hh"
#include "Menu.hh"

Collection<Spoiler> Spoiler::collection = Collection<Spoiler>();

Spoiler::Spoiler(const json &data)
 : Part(data), _aerodynamic(data["aerodynamic"].get<int>())
{
}

Spoiler::~Spoiler()
{

}
int Spoiler::getAerodynamic() const
{
	return _aerodynamic;
}

int Spoiler::getPrice() const
{
	return _price;
}