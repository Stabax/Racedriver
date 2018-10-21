//Voiture.h
#ifndef VOITURE_HH_
#define VOITURE_HH_

#include <string>
#include <cmath>
#include "Moteur.hh"
#include "Spoiler.hh"
#include "AirIntake.hh"
#include "Tires.hh"

class Voiture
{
public:
	Voiture(const std::string& marque, const std::string& modele, const int& idMoteur, const int& idSpoiler, const int& idAirIntake, const char& rang, const int& nitroMax, const int& aerodynamismeVoiture, const int& idTires, const int& etat = 100);
	~Voiture();

	static Voiture* chargerVoiture(const int& id, const char& rangCharge);
	static void listerVoitures(const char& rang);
	static void infoVoiture(const int& id, const char& rang, std::string& marque, std::string& modele, int& idMoteur, int& nitroMax, int& aerodynamisme, int& prix);
	static int compterVoitures(const char& rang);

	std::string getMarque() const;  //infos voiture
	std::string getModele() const;
	char getRang() const;
	float getVitesse() const;
	float getAcceleration() const;
	int getAerodynamisme() const;
	int getIdMoteur() const;
	int getIdSpoiler() const;
	int getIdAirIntake() const;
	int getNitroMax() const;
	int getNiveauNitro() const;
	int getEtat() const;
	int getAerodynamismeVoiture() const;
	int getConsommation() const;
	int getPrix() const;
	int getIdTires() const;

	std::string getNomMoteur() const;	//infos moteur
	float getVitesseMoteur() const;
	float getAccelerationMoteur() const;
	float getPrixCarburantMoteur() const;
	int getPrixMoteur() const;

	void changerTires();

	//infos acessoires
	Spoiler &getSpoiler();
	AirIntake &getAirIntake();
	Tires &getTires();

	void setMoteur(Moteur* newMoteur, const int& idMoteur);
	void setSpoiler(Spoiler newSpoiler, const int& idSpoiler);
	void setAirIntake(AirIntake newAirIntake, const int& idAirIntake);
	void setTires(Tires tires);
	void setNitro(const int& ajouter);

	void retirerEtat(const int& retirer);

	void pleinNitro();

	void pleinCarburant();
	void reparer();

	void updateAttributs();

protected:
	Moteur *m_moteur;
	int m_idMoteur;		//modifiable via paiement
	Spoiler m_spoiler;
	int m_idSpoiler;		//modifiable via paiement
	AirIntake m_priseAir;
	int m_idAirIntake;		//modifiable via paiement
	int m_niveauNitro;	//se vide en fonction de la longueur du circuit. le plein est fait manuellement via paiement, juste avant une course
	std::string m_marque;
	std::string m_modele;
	char m_rang;
	std::string m_typeCarburant;		//change en fonction du moteur
	float m_consommation;	//change en fonction du moteur
	int m_nitroMax;	//non modifiable pour une voiture donnée
	int m_aerodynamismeVoiture;	//non modifiable pour une voiture donnée
	Tires m_pneus;
	int m_idTires;
	int m_etat;
};

#endif /* !VOITURE_HH_ */
