
//Engine.h

#ifndef ENGINE_HH_
#define ENGINE_HH_

#include <string>
#include <fstream>
#include <sstream>

#include "algos.hh"
#include "Game.hh"
#include "Part.hpp"
#include "Collection.hpp"

enum Energy {
	Diesel,
	Gasoline
};

class Engine : public Part
{
public:
	Engine(const json &data);
	~Engine();

  static const std::string getPath() { return ("Engines"); };

	static float returnPrixCarburant(const std::string& carburant);

	float getPower() const;
	float getTorque() const;
	Energy getTypeCarburant() const;
	float getConsommation() const;
	int getPrix() const;
	float getPrixCarburant() const;

	static Collection<Engine> collection;

protected:
	int _price;
	int _power;
	int _torque;
	Energy _energy;
	float _consommation;
};


#endif /* !ENGINE_HH_ */
