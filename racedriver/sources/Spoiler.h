
//Spoiler.h

#ifndef spoiler
#define spoiler

#include <string>
#include <sstream>

#include "fonctions.h"
#include"algos.h"


class Spoiler
{
	public:
	//Constructeurs
	Spoiler(const std::string& modele, const char& rang, const unsigned short int& aerodynamisme);
	
	//Destructeur
	~Spoiler();
	
	//Méthodes statiques
	static Spoiler* chargerSpoiler(const unsigned short int& id);
	static void infoSpoiler(const unsigned short int& id, unsigned int& prix);
	static void infoSpoiler(const unsigned short int& id, std::string& modele, char& rang, unsigned short int& aero, unsigned int& prix);
	
	//Accesseurs et Mutateurs
	std::string getNom() const;
	char getRang() const;
	unsigned short int getAerodynamisme() const;
	
	//Méthodes
		//Aucune
		
	//Opérateurs Méthodes
		//Aucun

	protected:
	//Attributs
	std::string m_nom;
	char m_rang;
	unsigned short int m_aerodynamisme;
};


#endif
