//course.h
#ifndef COURSE_HH_
#define COURSE_HH_

#include <cmath>
#include <fstream>
#include "Circuit.hh"
#include "Profile.hh"

bool preparatifsCourse(const Circuit& Map, const Profile& Player, Car*& CarPlayer, int const& prix = 0);
std::string randNomAdversaire();
bool antiCorruption(const std::string& chemin, const int& nbLignes);
void chargerAdversaires(Car* Adversaire[7], int difficulteProfile, int difficulteCircuit);
void chargerMessagesAccidents(std::string messageAccident[8]);
std::string* chargerCommentaireMeteo(const int& meteo);
void calculerScore(int score[8], const Car* Adversaire[7],  Car* Player1, const Circuit& Map);
void calculerProbaAccident(int probaAccident[8], Car* Adversaire[7], Car* Player1, const Circuit Map);

void faireCourseLibre(Circuit Map, Car* Player1, Profile& Player);
void faireCourseChampionnat(Circuit Map, Car* Player1, Profile& Player);
void faireCourseCarriere(Circuit Map, Car* Player1, Profile& Player);

#endif /* COURSE_HH_ */
