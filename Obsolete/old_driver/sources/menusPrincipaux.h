//menusPrincipaux.h
#ifndef MENUSPRINCIPAUX_HH_
#define MENUSPRINCIPAUX_HH_

#include "menus.h"

void menuRacedriver();
void menuJeu(Profil& Player, bool& quitter);

void menuChargementPartie(Profil*& Player, bool& quit);
void menuCreationPartie(Profil*& Player, bool& quit);
void menuSuppressionPartie();

void menuApropos(); //Menu promotionnel

#endif /* !MENUSPRINCIPAUX_HH_ */