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
	Pneus(const std::string& marque, const char& rang, const int& usure);
	
	//Destructeur
	~Pneus();
	
	//Méthodes statiques
	static Pneus* chargerPneus(const int& id, const int& usure = 100);
	static void listerPneus();
	
	//Accesseurs
	std::string getMarque() const;
	int getDurabilite() const;
	int getPrix() const;
	char getRang() const;
	
	
	//Mutateurs
	void setDurabilite(const int& valeur);
	
	//Méthodes
		//Aucune
		
	//Opérateurs méthodes
		//Aucune
	
	protected:
	//Attributs
	std::string m_marque;
	int m_rang;
	int m_durabilite;
	int m_prix;
		//definit la voiture qui peut les porter, ainsi que la vitesse d'usure  des pneus
};


#endif
