//sousMenus.h
#ifndef SOUSMENUS_HH_
#define SOUSMENUS_HH_

#include <iostream>
#include "Profile.hh"
#include "Circuit.hh"
#include "course.hh"
#include"Game.hh"

Car* menuChoixCar(Profile& Player);

void menuCourseLibre(Profile& Player); //Menu de Course libre (lobby sp)
void menuCourseChampionnat(Profile& Player);

int menuConsulterGarage(Profile& Player, const int& mode = 0);
void menuConsulterBox(Profile& Player, const int& numeroBox);
void menuAtelier(Profile& Player, const int& numeroBox);
void menuAtelierSpoiler(Profile& Player, const int& numeroBox);
void menuAtelierAirIntake(Profile& Player, const int& numeroBox);
void menuAtelierEngine(Profile& Player, const int& numeroBox);
void menuMaintenance(Profile& Player, const int& numeroBox);
void menuAcheterBox(Profile& Player);

void menuAchatCar(const char& rang, Profile& Player);
void menuConcessionaireAchat(Profile& Player);
void menuVenteCar(Profile& Player, const int& numeroBox);

void menuDifficulte(Profile& Player);
void menuChangementNomProfile(Profile& Player);

#endif /* !SOUSMENUS_HH_ */
