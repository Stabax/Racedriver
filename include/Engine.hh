#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Part.hpp"
#include "Collection.hpp"

enum Energy {
	Diesel,
	Gasoline,
	Electric
};

class Engine : public Part
{
public:
  Engine(const json &data);

  virtual std::string info();
	omni::Horsepower getPower();
	void update(omni::KilometerPerHour speed, omni::Inch radius);

  static const std::string getPath() { return ("Engines"); };
	static Collection<Engine> collection;

	//Manufacturer
	omni::turnPerMinute<int> _mRevolutions;
	omni::Horsepower mPower;
	Energy energy;
	int price;

	//Instance
	omni::Horsepower _power;
	omni::turnPerMinute<int> _revolutions;
	omni::NewtonMeter _torque;
};

#endif /* !ENGINE_HPP_ */