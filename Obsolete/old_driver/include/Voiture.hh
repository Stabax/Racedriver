//Voiture.h
#ifndef VOITURE_HH_
#define VOITURE_HH_

#include <string>
#include <cmath>
#include "Moteur.hh"
#include "Spoiler.hh"
#include "PriseAir.hh"
#include "Pneus.hh"

class Voiture
{
public:
	Voiture(const std::string& marque, const std::string& modele, const int& idMoteur, const int& idSpoiler, const int& idPriseAir, const char& rang, const int& nitroMax, const int& aerodynamismeVoiture, const int& idPneus, const int& usurePneus = 100, const int& etat = 100);
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
	int getDurabilitePneus() const;
	char getRangPneus() const;
	std::string getMarquePneus() const;
	int getAerodynamisme() const;
	int getIdMoteur() const;
	int getIdSpoiler() const;
	int getIdPriseAir() const;
	int getNitroMax() const;
	int getNiveauNitro() const;
	int getEtat() const;
	int getAerodynamismeVoiture() const;
	int getConsommation() const;
	int getPrix() const;
	int getIdPneus() const;

	std::string getNomMoteur() const;	//infos moteur
	float getVitesseMoteur() const;
	float getAccelerationMoteur() const;
	float getPrixCarburantMoteur() const;
	int getPrixMoteur() const;

	std::string getNomSpoiler() const;	//infos spoiler
	char getRangSpoiler() const;
	int getAerodynamismeSpoiler() const;

	std::string getNomPriseAir() const;	//info prise d'air
	char getRangPriseAir() const;
	int getAerodynamismePriseAir() const;

	void setMoteur(Moteur* newMoteur, const int& idMoteur);
	void setSpoiler(Spoiler* newSpoiler, const int& idSpoiler);
	void setPriseAir(PriseAir* newPriseAir, const int& idPriseAir);
	void setPneus(const int& ajouter);
	void setNitro(const int& ajouter);

	void retirerEtat(const int& retirer);

	void pleinNitro();
	void changerPneus();

	void pleinCarburant();
	void reparer();

	void updateAttributs();

protected:
	Moteur *m_moteur;
	int m_idMoteur;		//modifiable via paiement
	Spoiler *m_spoiler;
	int m_idSpoiler;		//modifiable via paiement
	PriseAir *m_priseAir;
	int m_idPriseAir;		//modifiable via paiement
	int m_niveauNitro;	//se vide en fonction de la longueur du circuit. le plein est fait manuellement via paiement, juste avant une course
	float m_aerodynamisme;			//géré par spoiler et prise d'air et aerodynamisme voiture
	float m_vitesse;				//géré par moteur et aerodynamisme
	float m_acceleration;			//géré par moteur, aerodynamisme et niveau nitro
	std::string m_marque;
	std::string m_modele;
	char m_rang;
	std::string m_typeCarburant;		//change en fonction du moteur
	float m_consommation;	//change en fonction du moteur
	int m_nitroMax;	//non modifiable pour une voiture donnée
	int m_aerodynamismeVoiture;	//non modifiable pour une voiture donnée
	Pneus *m_pneus;
	int m_idPneus;
	int m_etat;
};

#endif /* !VOITURE_HH_ */
