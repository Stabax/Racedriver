//Tires.h

#ifndef TIRES_HH_
#define TIRES_HH_

#include <string>
#include <sstream>
#include "Part.hpp"
#include "Collection.hpp"
#include "DataFile.hh"

#include "algos.hh"
#include "Game.hh"

class Tires : public Part
{
public:
	Tires(const json &data);
	~Tires();

	static void expose(sol::state &lua);

  static const std::string getPath() { return ("Tires"); };

	static Collection<Tires> collection;

	omni::Inch diameter;
	omni::Bar pressure, mPressure;
	omni::Percent integrity;

	int price;
};

#endif /* !TIRES_HH_ */
