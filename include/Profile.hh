
//Profile.h

#ifndef Profile_h // _h car erreur de compil sinon
#define Profile_h // idem

#include <iostream>
#include <string>
#include <cfloat>
#include "sha/sha.h"
#include "Garage.hh"

struct Stats {
	int races;
	int victories;
	int losses;
	int accidents;
	int creditsEarned;
	int carBought;
};

class Profile
{
public:
	Profile(const json &data);
	~Profile();

	static Profile load(const std::string &path);
	static void listerSauvegardes();
	static int compterSauvegardes();
	static void supprimerProfile(const int& numeroSave);
	static bool chargerProfile(const int& numeroSave, Profile*& ProfileCharge);
	static void creerProfile(std::string& nom, Profile*& ProfileCree);
	static bool compatible(Profile& Player, const int& numeroBox, const char& rangNewPiece);

	bool payer(const int& prix);
	void sauvegarderProfile();

	std::string name;
	int difficulty;
	int credits;
	
	Garage garage;


	//Stats
	Stats careerStats;
	Stats freeStats; //Course Libre

	bool m_sauvegardeAuto;
};

bool operator!=(Profile& Player, Profile& PlayerSaved);

#endif
