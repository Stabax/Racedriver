//Car.h
#ifndef CAR_HH_
#define CAR_HH_

#include <string>
#include <cmath>
#include "Part.hpp"
#include "Engine.hh"
#include "Spoiler.hh"
#include "AirIntake.hh"
#include "Tires.hh"

class Car : public Part
{
public:
	Car(const json &data);
	~Car();

	static void listerCars(const char& rang);
	static void infoCar(const int& id, const char& rang, std::string& marque, std::string& modele, int& idEngine, int& nitroMax, int& aerodynamisme, int& prix);
	static int compterCars(const char& rang);

	float getVitesse() const;
	float getAcceleration() const;
	int getAerodynamisme() const;
	int getNitroMax() const;
	int getNiveauNitro() const;
	int getEtat() const;
	int getAerodynamismeCar() const;
	int getConsommation() const;
	int getPrix() const;

	void changerTires();

	//infos acessoires
	Engine &getEngine();
	Spoiler &getSpoiler();
	AirIntake &getAirIntake();
	Tires &getTires();

	void setEngine(Engine newEngine);
	void setSpoiler(Spoiler newSpoiler);
	void setAirIntake(AirIntake newAirIntake);
	void setTires(Tires tires);
	void setNitro(const int& ajouter);

	void retirerEtat(const int& retirer);

	void pleinNitro();

	void pleinCarburant();
	void reparer();

	void updateAttributs();

	static std::map<std::string, Car> collection;

protected:
	Engine _engine;
	Spoiler _spoiler;
	AirIntake _airIntake;
	Tires _tires;
	int _nitro;	//se vide en fonction de la longueur du circuit. le plein est fait manuellement via paiement, juste avant une course
	int _nitroMax;	//non modifiable pour une voiture donnée
	int _durability;
};

#endif /* !CAR_HH_ */
