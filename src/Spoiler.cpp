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

void Spoiler::expose(sol::state &lua)
{
    lua.new_usertype<Spoiler>("Spoiler",
      // constructor
      sol::constructors<Spoiler(const json &data)>(),

      "getId", &Spoiler::getId
    );
}

int Spoiler::getAerodynamic() const
{
	return _aerodynamic;
}

int Spoiler::getPrice() const
{
	return _price;
}