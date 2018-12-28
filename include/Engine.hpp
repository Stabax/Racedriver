#ifndef ENGINE_HPP_
#define ENGINE_HPP_

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

  static const std::string getPath() { return ("Engines"); };
  virtual std::string info();
	static Collection<Engine> collection;

	int power;
	Energy energy;
	int price;
};

#endif /* !ENGINE_HPP_ */