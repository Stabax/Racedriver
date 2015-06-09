
//Voiture.h

#ifndef Voiture_h
#define Voiture_h

#include <string>
#include <cmath>

#include "Moteur.h"
#include "Spoiler.h"
#include "PriseAir.h"
#include "Pneus.h"


class Voiture
{

	public:
	
	//Constructeurs
	Voiture(const std::string& marque, const std::string& modele, const unsigned short int& idMoteur, const unsigned short int& idSpoiler, const unsigned short int& idPriseAir, const char& rang, const unsigned short int& nitroMax, const unsigned short int& aerodynamismeVoiture, const unsigned short int& idPneus, const unsigned short int& usurePneus = 100, const unsigned short int& etat = 100);
	
	//Destructeur
	~Voiture();
	
	//Méthodes statiques
	static Voiture* chargerVoiture(const unsigned short int& id, const char& rangCharge);
	static void listerVoitures(const char& rang);
	static void infoVoiture(const unsigned short int& id, const char& rang, std::string& marque, std::string& modele, unsigned short int& idMoteur, unsigned short int& nitroMax, unsigned short int& aerodynamisme, unsigned int& prix);
	static unsigned short int compterVoitures(const char& rang);
	
	//Accesseurs et Mutateurs
	std::string getMarque() const;  //infos voiture
	std::string getModele() const;
	char getRang() const;
	float getVitesse() const;
	float getAcceleration() const;
	unsigned short int getDurabilitePneus() const;
	char getRangPneus() const;
	std::string getMarquePneus() const;
	unsigned short int getAerodynamisme() const;
	unsigned short int getIdMoteur() const;
	unsigned short int getIdSpoiler() const;
	unsigned short int getIdPriseAir() const;
	unsigned short int getNitroMax() const;
	unsigned short int getNiveauNitro() const;
	unsigned short int getEtat() const;
	unsigned short int getAerodynamismeVoiture() const;
	unsigned short int getConsommation() const;
	unsigned int getPrix() const;
	unsigned short int getIdPneus() const;
	
	std::string getNomMoteur() const;	//infos moteur
	float getVitesseMoteur() const;
	float getAccelerationMoteur() const;
	float getPrixCarburantMoteur() const;
	unsigned short int getPrixMoteur() const;
	
	std::string getNomSpoiler() const;	//infos spoiler
	char getRangSpoiler() const;
	unsigned short int getAerodynamismeSpoiler() const;
	
	std::string getNomPriseAir() const;	//info prise d'air
	char getRangPriseAir() const;
	unsigned short int getAerodynamismePriseAir() const;
	
	void setMoteur(Moteur* newMoteur, const unsigned short int& idMoteur);
	void setSpoiler(Spoiler* newSpoiler, const unsigned short int& idSpoiler);
	void setPriseAir(PriseAir* newPriseAir, const unsigned short int& idPriseAir);
	void setPneus(const short int& ajouter);
	void setNitro(const short int& ajouter);
	
	void retirerEtat(const unsigned short int& retirer);
	
	//Méthodes
	
	void pleinNitro();
	void changerPneus();
	
	void pleinCarburant();
	void reparer();
	
	void updateAttributs();
	
	//Opérateurs Méthodes
		//Aucun
	
	
	protected:
	//Attributs
	Moteur *m_moteur;
	unsigned short int m_idMoteur;		//modifiable via paiement
	Spoiler *m_spoiler;
	unsigned short int m_idSpoiler;		//modifiable via paiement
	PriseAir *m_priseAir;
	unsigned short int m_idPriseAir;		//modifiable via paiement
	
	
	unsigned short int m_niveauNitro;	//se vide en fonction de la longueur du circuit. le plein est fait 								manuellement via paiement, juste avant une course
		
	float m_aerodynamisme;			//géré par spoiler et prise d'air et aerodynamisme voiture

	float m_vitesse;				//géré par moteur et aerodynamisme	
	float m_acceleration;			//géré par moteur, aerodynamisme et niveau nitro

	std::string m_marque;
	std::string m_modele;

	char m_rang;
	
	std::string m_typeCarburant;		//change en fonction du moteur
	unsigned short int m_consommation;	//change en fonction du moteur

	unsigned short int m_nitroMax;	//non modifiable pour une voiture donnée
	unsigned short int m_aerodynamismeVoiture;	//non modifiable pour une voiture donnée

	Pneus *m_pneus;
	unsigned short int m_idPneus;
	
	unsigned short int m_etat;
};


#endif
