
//Spoiler.h

#ifndef SPOILER_HH_
#define SPOILER_HH_

#include <string>
#include <sstream>
#include "fonctions.h"
#include "algos.h"

class Spoiler
{
public:
	Spoiler(const std::string& modele, const char& rang, const int& aerodynamisme);
	~Spoiler();

	static Spoiler* chargerSpoiler(const int& id);
	static void infoSpoiler(const int& id, int& prix);
	static void infoSpoiler(const int& id, std::string& modele, char& rang, int& aero, int& prix);

	std::string getNom() const;
	char getRang() const;
	int getAerodynamisme() const;

protected:
	std::string m_nom;
	char m_rang;
	int m_aerodynamisme;
};

#endif /* SPOILER_HH_ */
