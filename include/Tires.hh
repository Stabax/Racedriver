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

  static const std::string getPath() { return ("Tires"); };

	static void listerTires();

	int getPrice() const;

	static Collection<Tires> collection;

	omni::Inch radius;
	omni::Bar pressure, mPressure;
	int integrity;

protected:
	int _price;
};

#endif /* !TIRES_HH_ */
