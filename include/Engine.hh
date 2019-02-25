#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Part.hpp"
#include "Collection.hpp"

enum Energy {
	Diesel,
	Gasoline,
	Electric
};

[[maybe_unused]]static const char* EnergyNames[] = { "Diesel", "Gasoline", "Electric" };

[[maybe_unused]]static const float gearMultiplier[] = { 3.36, 1.95, 1.3, 1.03, 0.84, 0.68 };

class Engine : public Part
{
public:
  Engine(const json &data);

  static void expose(sol::environment &lua);

  virtual std::string info();
	void update(omni::KilometerPerHour speed, omni::Inch diameter);

  static const std::string getPath() { return ("Engines"); };
	static Collection<Engine> collection;

	//Manufacturer
	omni::Horsepower mPower;
	omni::revolutionPerMinute<int> mRevolutions;
	omni::NewtonMeter mTorque;
	int mGears;
	Energy energy;
	int price;

	//Instance
	int gear;
	omni::Horsepower power;
	omni::revolutionPerMinute<int> revolutions;
	omni::NewtonMeter torque;
};

#endif /* !ENGINE_HPP_ */