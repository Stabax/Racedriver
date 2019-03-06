//Tires.cpp
#include "Tires.hh"
#include "Menu/Menu.hh"

Collection<Tires> Tires::collection = Collection<Tires>();

Tires::Tires(const json &data)
 : Part(data, TTires), diameter(data["diameter"].get<int>()),
 pressure(2.5f), mPressure(2.5f), integrity(100)
{
}

Tires::~Tires()
{
}


void Tires::expose(sol::environment &lua)
{
	lua.new_usertype<Tires>("Tires",
		// constructor
		sol::constructors<Tires(const json &data)>(),

		"getId", &Tires::getId,
		"name", &Tires::name,
		"manufacturer", &Tires::manufacturer,
		"price", &Tires::price
	);
}