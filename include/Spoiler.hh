
//Spoiler.h

#ifndef SPOILER_HH_
#define SPOILER_HH_

#include <string>
#include <sstream>
#include "Part.hpp"
#include "algos.hh"

class Spoiler : public Part
{
public:
	Spoiler(const std::string& modele, const char& rang, const int& aerodynamisme);
	Spoiler(const json &data);
	~Spoiler();

	static Spoiler* chargerSpoiler(const int& id);
	static void infoSpoiler(const int& id, int& prix);
	static void infoSpoiler(const int& id, std::string& modele, char& rang, int& aero, int& prix);

	std::string getName() const;
	char getRank() const;
	int getAerodynamic() const;
	int getPrice() const;

	static std::vector<Spoiler> collection;

protected:
	std::string _name;
	char _rank;
	int _aerodynamic;
	int _price;
};

#endif /* SPOILER_HH_ */
