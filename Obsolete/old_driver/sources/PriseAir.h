
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
	PriseAir(const std::string& modele, const char& rang, const int& aerodynamisme);
	
	//Destructeur
	~PriseAir();
	
	//Methodes statiques
	static PriseAir* chargerPriseAir(const int& id);
	static void infoPriseAir(const int& id, unsigned int& prix);
	static void infoPriseAir(const int& id, std::string& modele, char& rang, int& aero, unsigned int& prix);	
		
	//Accesseurs et Mutateurs
	std::string getNom() const;
	char getRang() const;
	int getAerodynamisme() const;

	//Méthodes
		//Aucune
		
	//Opérateurs méthodes
		//Aucun
		
	protected:
	//Attributs
	std::string m_nom;
	char m_rang;
	int m_aerodynamisme;
};


#endif
