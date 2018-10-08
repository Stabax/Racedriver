//Circuit.h
#ifndef CIRCUIT_HH_
#define CIRCUIT_HH_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include"fonctions.h"

class Circuit
{
public:
	Circuit(const std::string& nom, const int& taille, const int& virages, const int& climat, const int& difficulte, const int& denivele);
	~Circuit();

	static void chargerCircuit(const int& id, Circuit*& CircuitCourant);
	static int listerCircuits();
	static int construireMeteo(const int& climat);
	static int construireVent();
	static std::string construireClimat(const int& climat);

	std::string getNom() const;
	int getTaille() const;
	int getVirages() const;
	int getMeteo() const;
	int getVent() const;
	int getDifficulte() const;
	int getDenivele() const;

protected:
	std::string m_nom;
	int m_taille;
	int m_virages;
	int m_meteo;
	int m_vent;
	std::string m_climat;
	int m_difficulte;
	int m_denivele;
};

#endif /* !CIRCUIT_HH_ */
