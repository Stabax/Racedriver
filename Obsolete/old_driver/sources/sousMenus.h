//sousMenus.h
#ifndef SOUSMENUS_HH_
#define SOUSMENUS_HH_

#include <iostream>
#include "fonctions.h"
#include "Profil.h"
#include "Circuit.h"
#include "course.h"

Voiture* menuChoixVoiture(Profil& Player);

void menuCourseLibre(Profil& Player); //Menu de Course libre (lobby sp)
void menuCourseChampionnat(Profil& Player);

int menuConsulterGarage(Profil& Player, const int& mode = 0);
void menuConsulterBox(Profil& Player, const int& numeroBox);
void menuAtelier(Profil& Player, const int& numeroBox);
void menuAtelierSpoiler(Profil& Player, const int& numeroBox);
void menuAtelierPriseAir(Profil& Player, const int& numeroBox);
void menuAtelierMoteur(Profil& Player, const int& numeroBox);
void menuMaintenance(Profil& Player, const int& numeroBox);
void menuAcheterBox(Profil& Player);

void menuAchatVoiture(const char& rang, Profil& Player);
void menuConcessionaireAchat(Profil& Player);
void menuVenteVoiture(Profil& Player, const int& numeroBox);

void menuDifficulte(Profil& Player);
void menuChangementNomProfil(Profil& Player);

#endif /* !SOUSMENUS_HH_ */
