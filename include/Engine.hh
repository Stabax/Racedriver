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
	int getPower();
	void update(int speed, int radius);

  static const std::string getPath() { return ("Engines"); };
	static Collection<Engine> collection;

	//Manufacturer
	int _mRevolutions;
	int mPower;
	Energy energy;
	int price;

	//Instance
	int _power;
	int _revolutions;
	int _torque;
};

#endif /* !ENGINE_HPP_ */