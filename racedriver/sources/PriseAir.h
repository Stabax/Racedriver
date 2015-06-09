
//PriseAir.h

#ifndef priseair
#define priseair

#include <string>
#include <sstream>

#include "fonctions.h"
#include"algos.h"


class PriseAir
{
	//Fonctions amies
		//Aucune
		
	public:
	//Constructeurs
	PriseAir(const std::string& modele, const char& rang, const unsigned short int& aerodynamisme);
	
	//Destructeur
	~PriseAir();
	
	//Methodes statiques
	static PriseAir* chargerPriseAir(const unsigned short int& id);
	static void infoPriseAir(const unsigned short int& id, unsigned int& prix);
	static void infoPriseAir(const unsigned short int& id, std::string& modele, char& rang, unsigned short int& aero, unsigned int& prix);	
		
	//Accesseurs et Mutateurs
	std::string getNom() const;
	char getRang() const;
	unsigned short int getAerodynamisme() const;

	//Méthodes
		//Aucune
		
	//Opérateurs méthodes
		//Aucun
		
	protected:
	//Attributs
	std::string m_nom;
	char m_rang;
	unsigned short int m_aerodynamisme;
};


#endif
