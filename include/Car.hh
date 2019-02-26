//Car.h
#ifndef CAR_HH_
#define CAR_HH_

#include <string>
#include <cmath>
#include "Part.hpp"
#include "Engine.hh"
#include "Spoiler.hh"
#include "Tires.hh"
#include "Track.hh"

class Car : public Part
{
public:
	Car(const json &data);
	~Car();

	static void expose(sol::environment &lua);

  static const std::string getPath() { return ("Cars"); };

	bool update(const omni::Minute &tickDuration, const Segment &segment);

	void copy(const std::string &id);
	int getTotalPrice() const;
	omni::KilometerPerHour getSpeed() const;
	omni::MeterPerSecond2 getAcceleration() const;
	omni::Percent getAerodynamic() const;
	omni::Liter getNiveauNitro() const;
	int getConsommation() const;

	void replaceTires();

	//infos acessoires
	Engine &getEngine() const;
	Spoiler &getSpoiler() const;
	Tires &getTires() const;

	void buyEngine(const Engine &newEngine);
	void buySpoiler(const Spoiler &newSpoiler);
	void buyTires(const Tires &tires);
	void setNitro(omni::Liter ajouter);

	void pleinNitro();

	void pleinCarburant();
	void reparer();

	void updateAttributs();

	static Collection<Car> collection;

	//instance
	omni::Percent integrity;
	omni::Liter nitro;	//se vide en fonction de la longueur du circuit. le plein est fait manuellement via paiement, juste avant une course
	omni::Liter fuel;
	omni::KilometerPerHour speed;
	omni::MeterPerSecond2 acceleration;
	omni::Newton fc;
protected:
	std::shared_ptr<Engine> _engine;
	std::shared_ptr<Spoiler> _spoiler;
	std::shared_ptr<Tires> _tires;
};

void to_json(json& j, const Car& car);

#endif /* !CAR_HH_ */
