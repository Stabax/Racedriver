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
	Tires(const std::string& marque, const char& rang, const int& usure);
	Tires(const json &data);
	~Tires();

	static Tires* chargerTires(const int& id, const int& usure = 100);
	static void listerTires();

	std::string getName() const;
	int getDurability() const;
	char getRank() const;
	int getPrice() const;

	void setDurability(int value);

	static std::vector<Tires> collection;
protected:

	std::string _name;
	char _rank; //definit la voiture qui peut les porter
	int _durability; //definit la vitesse d'usure des pneus
	int _price;
};

#endif /* !TIRES_HH_ */
