//sousMenus.h
#ifndef SOUSMENUS_HH_
#define SOUSMENUS_HH_

#include <iostream>
#include "Profil.hh"
#include "Circuit.hh"
#include "course.hh"
#include"Game.hh"

Car* menuChoixCar(Profil& Player);

void menuCourseLibre(Profil& Player); //Menu de Course libre (lobby sp)
void menuCourseChampionnat(Profil& Player);

int menuConsulterGarage(Profil& Player, const int& mode = 0);
void menuConsulterBox(Profil& Player, const int& numeroBox);
void menuAtelier(Profil& Player, const int& numeroBox);
void menuAtelierSpoiler(Profil& Player, const int& numeroBox);
void menuAtelierAirIntake(Profil& Player, const int& numeroBox);
void menuAtelierEngine(Profil& Player, const int& numeroBox);
void menuMaintenance(Profil& Player, const int& numeroBox);
void menuAcheterBox(Profil& Player);

void menuAchatCar(const char& rang, Profil& Player);
void menuConcessionaireAchat(Profil& Player);
void menuVenteCar(Profil& Player, const int& numeroBox);

void menuDifficulte(Profil& Player);
void menuChangementNomProfil(Profil& Player);

#endif /* !SOUSMENUS_HH_ */
