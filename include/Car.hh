//Car.h
#ifndef CAR_HH_
#define CAR_HH_

#include <string>
#include <cmath>
#include "Part.hpp"
#include "Engine.hh"
#include "Spoiler.hh"
#include "Tires.hh"

//Custom unit definition
template <typename Rep = OMNI_DEFAULT_TYPE>
using millinewtonHour2PerKilometer2 = omni::Unit<omni::Dimension<-1,1,0,0,0,0,0>, Rep, typename omni::Ratio_over_value<typename omni::Ratio_power<omni::Ratio<omni::secondsPerHour, omni::E3>, 2>::type, omni::E3>::type, omni::zero>;

typedef millinewtonHour2PerKilometer2<> MillinewtonHour2PerKilometer2;

template <typename Rep = OMNI_DEFAULT_TYPE>
using millinewtonHourPerKilometer = omni::Unit<omni::Dimension<0,1,-1,0,0,0,0>, Rep, omni::Ratio<omni::secondsPerHour, omni::E6>, omni::zero>;

typedef millinewtonHourPerKilometer<> MillinewtonHourPerKilometer;

class Car : public Part
{
public:
	Car();
	Car(const json &data);
	~Car();

	static void expose(sol::state &lua);

  static const std::string getPath() { return ("Cars"); };

	static void listerCars();

	void update(omni::Minute tickDuration, omni::Meter gradient);

	void copy(const std::string &id);
	void displayInfo() const;
	int getPrice() const;
	omni::KilometerPerHour getSpeed() const;
	omni::MeterPerSecond2 getAcceleration() const;
	omni::Percent getAerodynamic() const;
	omni::Liter getNiveauNitro() const;
	int getConsommation() const;

	void replaceTires();

	//infos acessoires
	std::shared_ptr<Engine> getEngine() const;
	std::shared_ptr<Spoiler> getSpoiler() const;
	std::shared_ptr<Tires> getTires() const;

	void setEngine(const Engine &newEngine);
	void setSpoiler(const Spoiler &newSpoiler);
	void setTires(const Tires &tires);
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
protected:
	std::shared_ptr<Engine> _engine;
	std::shared_ptr<Spoiler> _spoiler;
	std::shared_ptr<Tires> _tires;
};

void to_json(json& j, const Car& car);

#endif /* !CAR_HH_ */
