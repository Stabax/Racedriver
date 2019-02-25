//Spoiler.cpp
#include "Spoiler.hh"
#include "Menu.hh"

Collection<Spoiler> Spoiler::collection = Collection<Spoiler>();

Spoiler::Spoiler(const json &data)
 : Part(data, TSpoiler), aerodynamic(data["aerodynamic"].get<int>())
{
}

Spoiler::~Spoiler()
{

}

void Spoiler::expose(sol::environment &lua)
{
	lua.new_usertype<Spoiler>("Spoiler",
		// constructor
		sol::constructors<Spoiler(const json &data)>(),

		"getId", &Spoiler::getId,
		"name", &Spoiler::name,
		"manufacturer", &Spoiler::manufacturer,
		"rank", &Spoiler::rank
	);
}
