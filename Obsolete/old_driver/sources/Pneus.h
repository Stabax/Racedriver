//Pneu.h

#ifndef Pneus_h
#define Pneus_h

#include <string>
#include <sstream>

#include "fonctions.h"
#include"algos.h"

class Pneus
{
	public:
	
	//Constructeurs
	Pneus(const std::string& marque, const char& rang, const unsigned short int& usure);
	
	//Destructeur
	~Pneus();
	
	//Méthodes statiques
	static Pneus* chargerPneus(const unsigned short int& id, const unsigned short int& usure = 100);
	static void listerPneus();
	
	//Accesseurs
	std::string getMarque() const;
	unsigned short int getDurabilite() const;
	unsigned short int getPrix() const;
	char getRang() const;
	
	
	//Mutateurs
	void setDurabilite(const unsigned short int& valeur);
	
	//Méthodes
		//Aucune
		
	//Opérateurs méthodes
		//Aucune
	
	protected:
	//Attributs
	std::string m_marque;
	unsigned short int m_rang;
	unsigned short int m_durabilite;
	unsigned short int m_prix;
		//definit la voiture qui peut les porter, ainsi que la vitesse d'usure  des pneus
};


#endif
