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

	static void listerCars();

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
	std::shared_ptr<Engine> getEngine();
	std::shared_ptr<Spoiler> getSpoiler();
	std::shared_ptr<AirIntake> getAirIntake();
	std::shared_ptr<Tires> getTires();

	void setEngine(const Engine &newEngine);
	void setSpoiler(const Spoiler &newSpoiler);
	void setAirIntake(const AirIntake &newAirIntake);
	void setTires(const Tires &tires);
	void setNitro(const int& ajouter);

	void retirerEtat(const int& retirer);

	void pleinNitro();

	void pleinCarburant();
	void reparer();

	void updateAttributs();

	static std::map<std::string, Car> collection;

protected:
	std::shared_ptr<Engine> _engine;
	std::shared_ptr<Spoiler> _spoiler;
	std::shared_ptr<AirIntake> _airIntake;
	std::shared_ptr<Tires> _tires;
	int _nitroMax;	//non modifiable pour une voiture donnée
	int _nitro;	//se vide en fonction de la longueur du circuit. le plein est fait manuellement via paiement, juste avant une course
	int _durability;
};

#endif /* !CAR_HH_ */
