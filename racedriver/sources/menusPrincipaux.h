
//menusPrincipaux.h

#ifndef menusPrincipaux_h
#define menusPrincipaux_h

#include"menus.h"

void menuRacedriver();
void menuJeu(Profil& Player, bool& quitter);

void menuChargementPartie(Profil*& Player, bool& quit);
void menuCreationPartie(Profil*& Player, bool& quit);
void menuSuppressionPartie();

void menuApropos(); //Menu promotionnel

#endif
