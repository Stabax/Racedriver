
//sousMenus.h

#ifndef sousMenus_h
#define sousMenus_h

#include <iostream>

#include "fonctions.h"
#include "Profil.h"
#include "Circuit.h"
#include "course.h"


Voiture* menuChoixVoiture(Profil& Player);

void menuCourseLibre(Profil& Player); //Menu de Course libre (lobby sp)
void menuCourseChampionnat(Profil& Player);

unsigned short int menuConsulterGarage(Profil& Player, const unsigned short int& mode = 0);
void menuConsulterBox(Profil& Player, const unsigned short int& numeroBox);
void menuAtelier(Profil& Player, const unsigned short int& numeroBox);
	void menuAtelierSpoiler(Profil& Player, const unsigned short int& numeroBox);
	void menuAtelierPriseAir(Profil& Player, const unsigned short int& numeroBox);
	void menuAtelierMoteur(Profil& Player, const unsigned short int& numeroBox);
void menuMaintenance(Profil& Player, const unsigned short int& numeroBox);
void menuAcheterBox(Profil& Player);

void menuAchatVoiture(const char& rang, Profil& Player);
void menuConcessionaireAchat(Profil& Player);
void menuVenteVoiture(Profil& Player, const unsigned short int& numeroBox);

void menuDifficulte(Profil& Player);
void menuChangementNomProfil(Profil& Player);


#endif
