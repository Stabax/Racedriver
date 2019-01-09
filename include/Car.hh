//Car.h
#ifndef CAR_HH_
#define CAR_HH_

#include <string>
#include <cmath>
#include "Part.hpp"
#include "Engine.hh"
#include "Spoiler.hh"
#include "Tires.hh"

class Car : public Part
{
public:
	Car(const json &data);
	~Car();

  static const std::string getPath() { return ("Cars"); };

	static void listerCars();

	void update(omni::Millisecond tickDuration, omni::Meter gradient);

	void copy(const std::string &id);
	void displayInfo() const;
	omni::KilometerPerHour getVitesse() const;
	omni::MeterPerSecond2 getAcceleration() const;
	int getAerodynamisme() const;
	omni::Liter getNiveauNitro() const;
	int getDurability() const;
	omni::Liter getFuel() const;
	int getAerodynamismeCar() const;
	int getConsommation() const;
	int getPrix() const;

	void replaceTires();

	//infos acessoires
	std::shared_ptr<Engine> getEngine() const;
	std::shared_ptr<Spoiler> getSpoiler() const;
	std::shared_ptr<Tires> getTires() const;

	void setEngine(const Engine &newEngine);
	void setSpoiler(const Spoiler &newSpoiler);
	void setTires(const Tires &tires);
	void setNitro(omni::Liter ajouter);

	void damage(int value);

	void pleinNitro();

	void pleinCarburant();
	void reparer();

	void updateAttributs();

	static Collection<Car> collection;

protected:
	std::shared_ptr<Engine> _engine;
	std::shared_ptr<Spoiler> _spoiler;
	std::shared_ptr<Tires> _tires;
	int _integrity;
	omni::Kilogram _mass;

	//instance
	omni::Liter _nitro;	//se vide en fonction de la longueur du circuit. le plein est fait manuellement via paiement, juste avant une course
	omni::Liter _fuel;
	omni::KilometerPerHour _speed;
	omni::MeterPerSecond2 _acceleration;
};

void to_json(json& j, const Car& car);

#endif /* !CAR_HH_ */
