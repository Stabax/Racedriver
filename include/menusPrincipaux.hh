//menusPrincipaux.h
#ifndef MENUSPRINCIPAUX_HH_
#define MENUSPRINCIPAUX_HH_

#include "menus.hh"

void menuRacedriver();
void menuJeu(Profile& Player, bool& quitter);

void menuChargementPartie(Profile*& Player, bool& quit);
void menuCreationPartie(Profile*& Player, bool& quit);
void menuSuppressionPartie();

void menuApropos(); //Menu promotionnel

#endif /* !MENUSPRINCIPAUX_HH_ */