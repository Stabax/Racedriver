//menusPrincipaux.h
#ifndef MENUSPRINCIPAUX_HH_
#define MENUSPRINCIPAUX_HH_

#include "menus.hh"

void menuRacedriver();
void menuJeu(bool& quitter);

void menuChargementPartie(bool& quit);
void menuCreationPartie(bool& quit);
void menuSuppressionPartie();

void menuApropos(); //Menu promotionnel

#endif /* !MENUSPRINCIPAUX_HH_ */