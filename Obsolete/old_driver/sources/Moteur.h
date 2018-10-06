
//Moteur.h

#ifndef moteur
#define moteur

#include <string>
#include <fstream>
#include <sstream>

#include "fonctions.h"
#include"algos.h"


class Moteur
{
	//Fonctions amies
		//Aucune
		
	public:
	//constructeurs
	Moteur(const std::string& marque, const std::string& modele, const char& rang, const int& vitesse, const int& acceleration, const std::string& carburant);

	//Destructeur
	~Moteur();
	
	//Methodes statiques
	static Moteur* chargerMoteur(const int& id, const std::string& marqueChargee);
	static void listerMoteurs(const std::string& marque);
	static void infoMoteur(const int& id, const std::string& marque, std::string& modele);
	static void infoMoteur(const int& id, const std::string& marque, unsigned int& prix);
	static void infoMoteur(const int& id, const std::string& marque, std::string& modele, int& vitesse, int& acceleration);
	static void infoMoteur(const int& id, const std::string& marque, std::string& modele, int& vitesse, int& acceleration, char& rang, unsigned int& prix);
	static int compterMoteurs(const std::string& marque);
	static float returnPrixCarburant(const std::string& carburant);
	
	//Accesseurs	
	std::string getModele() const;
	std::string getMarque() const;
	char getRang() const;
	float getVitesse() const;
	float getAcceleration() const;
	std::string getTypeCarburant() const;
	float getConsommation() const;
	int getPrix() const;
	float getPrixCarburant() const;

	//mutateurs
	
	//Méthodes
		//Aucune

	//Opérateurs méthodes
		//Aucun
	
	
	protected:
	//Attributs
	std::string m_marque;
	std::string m_modele;
	int m_prix;
	char m_rang;
	float m_vitesse;
	float m_acceleration;
	std::string m_typeCarburant;
	float m_consommation;
	float m_prixCarburant;
};


#endif
