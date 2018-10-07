
//Profil.h

#ifndef Profil_h // _h car erreur de compil sinon
#define Profil_h // idem

#include <iostream>
#include <string>
#include <cfloat>
#include "sha.h"
#include "fonctions.h"
#include "Voiture.h"

class Profil
{
	//Fonctions amies
		//Aucune

	public:
	//constructeurs
	Profil(const std::string& uuid, const int& numero, const std::string& nom); //Nouveau Profil
	Profil(const std::string& uuid, const int& numero, const std::string& nom, const int& credits, const bool& sauvegardeAuto, const int& difficulte, const int& nbBox, const int& nbCourses, const int& victoires, const int& defaites, const int& accidents, const int& creditsGagnes, const int& nbCoursesCL, const int& victoiresCL, const int& defaitesCL, const int& accidentsCL, const int& creditsGagnesCL, const int& voituresAchetees); //Profil Chargé

	//Destructeur
	~Profil();

	//Methodes statiques
	static void listerSauvegardes();
	static int compterSauvegardes();
	static void supprimerProfil(const int& numeroSave);
	static bool chargerProfil(const int& numeroSave, Profil*& ProfilCharge);
	static void creerProfil(std::string& nom, Profil*& ProfilCree);
	static bool compatible(Profil& Player, const int& numeroBox, const char& rangNewPiece);

	//Accesseurs et Mutateurs
	std::string getUuid() const;	//profil
	int getNumero() const;
	std::string getNom() const;
	int getCredits() const;
	int getNbBox() const;
	Voiture* getBox(const int& numeroBox) const;
	int getDifficulte() const;
	std::string getDifficulteString() const;
	bool getSauvegardeAuto() const;

	int getNbCourses() const;	//stats
	int getVictoires() const;
	int getDefaites() const;
	int getAccidents() const;
	float getVDRatio() const;
	int getCreditsGagnes() const;
	int getVoituresAchetees() const;

	void setMoteurVoiture(const int& numeroBox, Moteur* newMoteur, const int& idMoteur);
	void setBox(const int& numeroBox, const std::string& marque, const std::string& modele, const int& idMoteur, const int& idSpoiler, const int& idPriseAir, const char& rang, const int& nitroMax, const int& aerodynamismeVoiture, const int& idPneus, const int& pneus, const int& etat);
	void setBox(const int& numeroBox, Voiture* Voiture);
	void setBox(const int& numeroBox);
	void setDifficulte(const int& newDifficulte);
	void setSauvegardeAuto(const bool& valeur);

	void ajouterVoitureAchetee();
	void ajouterCreditsGagnes(const int& somme);
	void ajouterCredits(const int& somme);
	void ajouterCourse();
	void ajouterVictoire();
	void ajouterDefaite();
	void ajouterAccident();

	//Méthodes
	bool boxVide(int numeroBox);

	void changerNom(const std::string& newNom);

	void acheterBox();
	bool payer(const int& prix);
	void sauvegarderProfil();

	//Opérateurs méthodes
		//Aucun

	protected:
	//Attributs
	std::string m_uuid; //unique identifier
	int m_numero;
	std::string m_nom;
	int m_credits;

	int m_difficulte;
	int m_nbBox;  //gestion vehicules
	Voiture* m_box[5];

	//Stats
	int m_nbCourses;
	int m_victoires;
	int m_defaites;
	int m_accidents;
	int m_creditsGagnes;
	int m_voituresAchetees;

	//Stats course libre
	int m_nbCoursesCL;
	int m_victoiresCL;
	int m_defaitesCL;
	int m_accidentsCL;
	int m_creditsGagnesCL;

	bool m_sauvegardeAuto;
};

bool operator!=(Profil& Player, Profil& PlayerSaved);

#endif
