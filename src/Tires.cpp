//Tires.cpp
#include "Tires.hh"
#include "Menu.hh"

Collection<Tires> Tires::collection = Collection<Tires>();

Tires::Tires(const json &data)
 : Part(data, TTires), diameter(data["diameter"].get<int>()),
 pressure(2.5f), mPressure(2.5f), integrity(100), price(vRang(rank) * 1500)
{
}

Tires::~Tires()
{
}


void Tires::expose(sol::state &lua)
{
	lua.new_usertype<Tires>("Tires",
		// constructor
		sol::constructors<Tires(const json &data)>(),

		"getId", &Tires::getId,
		"name", &Tires::name,
		"manufacturer", &Tires::manufacturer,
		"rank", &Tires::rank
	);
}