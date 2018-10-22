
//Engine.h

#ifndef ENGINE_HH_
#define ENGINE_HH_

#include <string>
#include <fstream>
#include <sstream>

#include "algos.hh"
#include "Game.hh"
#include "Part.hpp"

enum Energy {
	Diesel,
	Gasoline
};

class Engine : public Part
{
public:
	Engine(const json &data);
	~Engine();

	static void listerEngines(const std::string& marque);
	static void infoEngine(const int& id, const std::string& marque, std::string& modele);
	static void infoEngine(const int& id, const std::string& marque, int& prix);
	static void infoEngine(const int& id, const std::string& marque, std::string& modele, int& vitesse, int& acceleration);
	static void infoEngine(const int& id, const std::string& marque, std::string& modele, int& vitesse, int& acceleration, char& rang, int& prix);
	static int compterEngines(const std::string& marque);
	static float returnPrixCarburant(const std::string& carburant);

	float getVitesse() const;
	float getAcceleration() const;
	Energy getTypeCarburant() const;
	float getConsommation() const;
	int getPrix() const;
	float getPrixCarburant() const;

	static std::map<std::string, Engine> collection;

protected:
	int _price;
	float _speed;
	float _acceleration;
	Energy _energy;
	float _consommation;
};


#endif /* !ENGINE_HH_ */
