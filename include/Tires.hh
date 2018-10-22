//Tires.h

#ifndef TIRES_HH_
#define TIRES_HH_

#include <string>
#include <sstream>
#include "Part.hpp"
#include "DataFile.hh"

#include"algos.hh"
#include"Game.hh"

class Tires : public Part
{
public:
	Tires(const json &data);
	~Tires();

	static void listerTires();

	int getDurability() const;
	int getPrice() const;

	void setDurability(int value);

	static std::map<std::string, Tires> collection;

protected:
	int _durability; //definit la vitesse d'usure des pneus
	int _price;
};

#endif /* !TIRES_HH_ */
