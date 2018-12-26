//Engine.cpp
#include "Engine.hh"
#include "Menu.hh"

Collection<Engine> Engine::collection = Collection<Engine>();

Engine::Engine(const json& data)
 : Part(data), _price(((getVitesse()+getAcceleration())*25)+(vRang(rank)*500)), _speed(data["speed"].get<float>()),
  _acceleration(data["acceleration"].get<float>()), _energy(Diesel), _consommation(getVitesse()+getAcceleration())
{

}

Engine::~Engine()
{

}

float Engine::returnPrixCarburant(const std::string& carburant)
{
	if(carburant=="Diesel")
	{
		return 5.0f;
	}
	else if(carburant=="SP95")
	{
		return 8.0f;
	}
	else if(carburant=="GPL")
	{
		return 11.0f;
	}
	else
	{
	 	throw std::runtime_error("Erreur, le carburant " + carburant + " n'existe pas !");
	}
}

std::string Engine::info()
{
	return (Part::info() + " " + std::to_string(_speed) + " " + std::to_string(_acceleration));
}

float Engine::getVitesse() const
{
	return _speed;
}


float Engine::getAcceleration() const
{
	return _acceleration;
}


Energy Engine::getTypeCarburant() const
{
	return _energy;
}


float Engine::getConsommation() const
{
	return _consommation;
}


int Engine::getPrix() const
{
	return _price;
}