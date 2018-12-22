//Engine.cpp
#include "Engine.hh"
#include "Menu.hh"

Collection<Engine> Engine::collection = Collection<Engine>();

Engine::Engine(const json& data)
 : Part(data), _price(((getPower()+getTorque())*25)+(vRang(rank)*500)), _power(data["power"].get<int>()),
  _torque(data["torque"].get<int>()), _energy(Diesel), _consommation(getPower()+getTorque())
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

float Engine::getPower() const
{
	return (_power);
}


float Engine::getTorque() const
{
	return (_torque);
}


Energy Engine::getTypeCarburant() const
{
	return (_energy);
}


float Engine::getConsommation() const
{
	return (_consommation);
}


int Engine::getPrix() const
{
	return (_price);
}