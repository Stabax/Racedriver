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
	Pneus(const std::string& marque, const char& rang, const int& usure);
	~Pneus();

	static Pneus* chargerPneus(const int& id, const int& usure = 100);
	static void listerPneus();

	std::string getMarque() const;
	int getDurabilite() const;
	int getPrix() const;
	char getRang() const;

	void setDurabilite(const int& valeur);

protected:
	std::string m_marque;
	int m_rang; //definit la voiture qui peut les porter
	int m_durabilite; //definit la vitesse d'usure des pneus
	int m_prix;
};


#endif
