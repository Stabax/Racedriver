
//course.h

#ifndef course
#define course

#include <unistd.h>
#include <cmath>
#include <fstream>

#include "Circuit.h"
#include "fonctions.h"
#include "Profil.h"

bool preparatifsCourse(const Circuit& Map, const Profil& Player, Voiture*& VoiturePlayer, int const& prix = 0);
std::string randNomAdversaire();
bool antiCorruption(const std::string& chemin, const int& nbLignes);
void chargerAdversaires(Voiture* Adversaire[7], int difficulteProfil, int difficulteCircuit);
void chargerMessagesAccidents(std::string messageAccident[8]);
std::string* chargerCommentaireMeteo(const int& meteo);
void calculerScore(int score[8], const Voiture* Adversaire[7], const Voiture* Player1, const Circuit& Map);
void calculerProbaAccident(int probaAccident[8], Voiture* Adversaire[7], const Voiture* Player1, const Circuit Map);

void faireCourseLibre(Circuit Map, Voiture* Player1, Profil& Player);
void faireCourseChampionnat(Circuit Map, Voiture* Player1, Profil& Player);
void faireCourseCarriere(Circuit Map, Voiture* Player1, Profil& Player);

#endif