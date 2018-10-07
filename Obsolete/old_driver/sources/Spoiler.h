
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
	Spoiler(const std::string& modele, const char& rang, const int& aerodynamisme);
	
	//Destructeur
	~Spoiler();
	
	//Méthodes statiques
	static Spoiler* chargerSpoiler(const int& id);
	static void infoSpoiler(const int& id, int& prix);
	static void infoSpoiler(const int& id, std::string& modele, char& rang, int& aero, int& prix);
	
	//Accesseurs et Mutateurs
	std::string getNom() const;
	char getRang() const;
	int getAerodynamisme() const;
	
	//Méthodes
		//Aucune
		
	//Opérateurs Méthodes
		//Aucun

	protected:
	//Attributs
	std::string m_nom;
	char m_rang;
	int m_aerodynamisme;
};


#endif
