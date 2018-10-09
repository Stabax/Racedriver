//PriseAir.h
#ifndef PRISEAIR_HH_
#define PRISEAIR_HH_

#include <string>
#include <sstream>
#include "fonctions.hh"
#include"algos.hh"

class PriseAir
{
public:
	PriseAir(const std::string& modele, const char& rang, const int& aerodynamisme);
	~PriseAir();

	static PriseAir* chargerPriseAir(const int& id);
	static void infoPriseAir(const int& id, int& prix);
	static void infoPriseAir(const int& id, std::string& modele, char& rang, int& aero, int& prix);	

	std::string getNom() const;
	char getRang() const;
	int getAerodynamisme() const;

protected:
	std::string m_nom;
	char m_rang;
	int m_aerodynamisme;
};

#endif /* !PRISEAIR_HH_ */