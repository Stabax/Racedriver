//sousMenus.cpp
#include "Menu.hh"
#include "sousMenus.hh"

Voiture* menuChoixVoiture(Profil& Player)
{
	std::string sMenu;
	Voiture* VoitureSelectionnee = 0;
	Voiture* VoitureListee = 0;
	int menu;
	int nbBox = Player.getNbBox();
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Liste des Boxs\n"
										<< "===============\n"
										<< "Selectionnez le vehicule qui va faire la course.\n"
										<< "===============\n\n";
		for (size_t numeroBox = 0; numeroBox < nbBox; numeroBox++)
		{
			VoitureListee = Player.getBox(numeroBox);
			if(Player.boxVide(numeroBox))
			{
				Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
			}
			else
			{
				Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << VoitureListee->getMarque() << " " << VoitureListee->getModele() << "]\n";
			}
		}
		for (size_t j = nbBox; j < 5; j++)
		{
			Terminal::get() << (j + 1) << ". Box " << (j + 1) << " [VEROUILLE]\n";
		}
		Terminal::get() << "\n" //On separe le bloc
										<< "0. Retour\n";
		menu = Menu::askChoice();
		if(menu == 0)
		{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0 && menu <= nbBox)
		{
			if(Player.boxVide(menu - 1))
			{
				Terminal::get().clearScreen();
				Menu::error("Le box est vide.");
			}
			else
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				VoitureSelectionnee = Player.getBox(menu - 1);
				quit = true; //INSTRUCTION DE SORTIE
			}
		}
		else if(menu > nbBox && menu <= 5)
		{
			Terminal::get().clearScreen();
			Menu::error("Ce box est verrouille.");
		}
		else
		{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Menu::error("Saisie invalide");
		}
	}
	return VoitureSelectionnee;
}

void menuCourseLibre(Profil& Player)
{
	std::string sMenu;
	int menu;
	Voiture* VoiturePlayer = 0;
	int nombreCircuits;
	//Menu Principal
	Terminal::get() << "Course Libre\n"
									<< "===============\n"
									<< "Selectionnez un circuit.\n"
									<< "===============\n\n";
	nombreCircuits = Circuit::listerCircuits();
	Terminal::get() << "0. Annuler\n";
	menu = Menu::askChoice();
	//Redirection de l'utilisateur selon son choix grâce a un if + for.
	if(menu == 0)
	{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran et on quitte
	}
	else if(menu > 0 && menu <= nombreCircuits)
	{
		Circuit* CircuitCourant = 0;
		Circuit::chargerCircuit(menu, CircuitCourant);
		Terminal::get().clearScreen(); //On flushe l'ancien ecran

		VoiturePlayer = menuChoixVoiture(Player);
		if(VoiturePlayer == 0)
		{
			Menu::error("Aucune voiture selectionnee.");
		}
		else
		{
			faireCourseLibre(*CircuitCourant, VoiturePlayer, Player);
		}
		delete CircuitCourant;
		CircuitCourant = 0;
	}
	else
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		Menu::error("Saisie invalide");
	}
}

void menuCourseChampionnat(Profil& Player)
{
	std::string sMenu;
	int menu;
	Voiture* VoiturePlayer = 0;
	int nombreCircuits;
	//Menu Principal
	Terminal::get() << "Course Libre\n"
									<< "===============\n"
									<< "Selectionnez un circuit.\n"
									<< "===============\n\n";
	nombreCircuits = Circuit::listerCircuits();
	Terminal::get() << "0. Annuler\n";
	menu = Menu::askChoice();
	//Redirection de l'utilisateur selon son choix grâce a un if + for.
	if(menu == 0)
	{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran et on quitte
	}
	else if(menu > 0 && menu <= nombreCircuits)
	{
		Circuit* CircuitCourant = 0;
		Circuit::chargerCircuit(menu, CircuitCourant);
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		VoiturePlayer = menuChoixVoiture(Player);
		if(VoiturePlayer == 0)
		{
			Menu::error("Aucune voiture selectionnee.");
		}
		else
		{
			faireCourseChampionnat(*CircuitCourant, VoiturePlayer, Player);
		}
		delete CircuitCourant;
		CircuitCourant = 0;
	}
	else
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		Menu::error("Saisie invalide");
	}
}

int menuConsulterGarage(Profil& Player, const int& mode)
{
	std::string sMenu;
	int menu;
	int nbBox = Player.getNbBox();
	Voiture* Voiture = 0;

	//Menu Principal
	Terminal::get() << "Liste des Boxs\n"
									<< "===============\n";
	if(mode == 0) //On est en visualisation dans le garage
	{
		Terminal::get() << "Selectionnez un vehicule a examiner.\n";
	}
	else if(mode == 1) //On est en selection dans l'atelier
	{
		Terminal::get() << "Selectionnez un vehicule a ameliorer.\n";
	}
	else if(mode == 2) //On selectionne ou stocker une voiture en cours d'achat
	{
		Terminal::get() << "Selectionnez un emplacement pour garer le vehicule.\n";
	}
	else if(mode == 3) //On selectionne ou stocker une voiture en cours d'achat
	{
		Terminal::get() << "Selectionnez un vehicule a entretenir.\n";
	}
	else if(mode == 4) //On selectionne ou stocker une voiture en cours d'achat
	{
		Terminal::get() << "Selectionnez un vehicule a vendre.\n";
	}
	Terminal::get() << "===============\n\n";
	for (size_t numeroBox = 0; numeroBox < nbBox; numeroBox++)
	{
		Voiture = Player.getBox(numeroBox);
		if(Player.boxVide(numeroBox))
		{
			Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
		}
		else
		{
			Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << Voiture->getMarque() << " " << Voiture->getModele() << "]\n";
		}
	}
	for (size_t numeroBoxVerouille = nbBox; numeroBoxVerouille < 5; numeroBoxVerouille++)
	{
		Terminal::get() << (numeroBoxVerouille + 1) << ". Box " << (numeroBoxVerouille + 1) << " [VEROUILLE]\n";
	}
	Terminal::get() << "\n" //On separe le bloc
									<< "0. Retour\n";
	menu = Menu::askChoice();
	if(menu == 0)
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran et quitte
	}
	else if(menu > 0 && menu <= nbBox)
	{
		if(Player.boxVide(menu - 1))
		{
			if(mode == 2)
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran et quitte
			}
			else
			{
				Terminal::get().clearScreen();
				Menu::error("Le box est vide.");
			}
		}
		else if(mode == 0)
		{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuConsulterBox(Player, menu - 1);
			Terminal::get().clearScreen();
		}
		else if(mode == 1)
		{
			Terminal::get().clearScreen();
			menuAtelier(Player, menu - 1);
		}
		else if(mode == 2)
		{
			Terminal::get().clearScreen();
			Menu::error("Le box est deja occupe.");
		}
		else if(mode == 3)
		{
			Terminal::get().clearScreen();
			menuMaintenance(Player, menu - 1);
		}
		else if(mode == 4)
		{
			Terminal::get().clearScreen();
			menuVenteVoiture(Player, menu - 1);
		}
	}
	else if(menu > nbBox && menu <= 5)
	{
		Terminal::get().clearScreen();
		Menu::error("Ce box est verrouille.");
	}
	else
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		Menu::error("Saisie invalide");
	}
	return menu; //On renvoie l'emplacement choisi
}

void menuConsulterBox(Profil& Player, const int& numeroBox)
{
	Voiture* Voiture = Player.getBox(numeroBox);
	//Menu Principal
	Terminal::get() << "Vehicule gare dans le Box " << (numeroBox + 1) << "\n"
									<< "===============\n\n"
									<< "#Vehicule\n"
									<< " |Modele: " << Voiture->getModele() << "\n"
									<< " |Marque: " << Voiture->getMarque() << "\n"
									<< " |Rang: " << Voiture->getRang() << "\n"
									<< " |\n"
									<< " |Vitesse Totale: "<< Voiture->getVitesse() << " Km/h\n"
									<< " |Acceleration Totale: " << Voiture->getAcceleration() << " m/s²\n"
									<< " |Capacite Nitro: " << Voiture->getNitroMax() << " L\n"
									<< " |Aerodynamisme: " << Voiture->getAerodynamisme() << " %\n"
									<< " |Nitro Actuelle: " << Voiture->getNiveauNitro() << " L\n"
									<< " |Durabilite Pneus: "<< Voiture->getDurabilitePneus() << "%\n"
									<< " |Etat: " << Voiture->getEtat() << "%\n\n"
									<< "#Moteur\n"
									<< " |Modele: " << Voiture->getNomMoteur() << "\n"
									<< " |Vitesse: "<< Voiture->getVitesseMoteur() << " Km/h\n"
									<< " |Acceleration: " << Voiture->getAccelerationMoteur() << " m/s²\n\n"
									<< "#Spoiler\n"
									<< " |Modele: " << Voiture->getNomSpoiler() << "\n"
									<< " |Rang: "<<  Voiture->getRangSpoiler() << "\n"
									<< " |Aerodynamisme: " <<  Voiture->getAerodynamismeSpoiler() << " %\n\n"
									<< "#Prises d'air\n"
									<< " |Modele: " <<  Voiture->getNomPriseAir() << "\n"
									<< " |Rang: "<<  Voiture->getRangPriseAir() << "\n"
									<< " |Aerodynamisme: " <<  Voiture->getAerodynamismePriseAir() << " %\n\n"
									<< "#Pneus\n"
									<< " |Marque: " <<  Voiture->getMarquePneus() << "\n"
									<< " |Rang: "<<  Voiture->getRangPneus() << "\n\n"
									<< "===============\n"
									<< "Appuyez sur Entree pour revenir au menu precedent";
	getch();
}

void menuAtelier(Profil& Player, const int& numeroBox)
{
	Terminal::get().clearScreen();
	bool quit = false;
	Voiture* Voiture = Player.getBox(numeroBox);

	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Menu Atelier\n"
										<< "===============\n"
										<< "Selectionnez une piece a modifier.\n"
										<< "===============\n\n"
										<< "Voiture actuelle: [BOX" << numeroBox + 1 << ": " << Voiture->getMarque() << " " << Voiture->getModele() << "]\n\n"
										<< "1. Moteur\n"
										<< "2. Prise d'air\n"
										<< "3. Spoiler\n\n"
										<< "0. Retour\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true;
				break;
			case 1:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuAtelierMoteur(Player, numeroBox);
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuAtelierPriseAir(Player, numeroBox);
				break;
			case 3:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuAtelierSpoiler(Player, numeroBox);
				break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
}

void menuAtelierSpoiler(Profil& Player, const int& numeroBox)
{
	Voiture* Voiture = Player.getBox(numeroBox);
	char verif = 'x';
	int id = Voiture->getIdSpoiler();
	int idCharge = id + 1;
	std::string modeleCharge;
	int prixCharge;
	int aerodynamismeCharge;
	char rangCharge;

	Spoiler::infoSpoiler(idCharge, modeleCharge, rangCharge, aerodynamismeCharge, prixCharge);
	Terminal::get().clearScreen(); //On flushe l'ancien ecran	
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.getCredits() << "c\n"
									<< "====================\n"
									<< "Vous allez ameliorer le spoiler de votre vehicule,\n"
									<< "Prix: " << prixCharge << "c\n\n"
									<< "#Nouveau Spoiler\n"
									<< " |Modele: " << modeleCharge << "\n"
									<< " |Rang: " << rangCharge << "\n"
									<< " |Aerodynamisme: " << aerodynamismeCharge << "%\n\n"
									<< "#Spoiler Actuel\n"
									<< " |Modele: " << Voiture->getNomSpoiler() << "\n"
									<< " |Rang: " << Voiture->getRangSpoiler() << "\n"
									<< " |Aerodynamisme: " << Voiture->getAerodynamismeSpoiler() << "%\n\n"
									<< "Souhaitez-vous vraiment continuer ? [O/n]\n"
									<< "====================\n";
	verif = getch();
	if(verif == 'o' || verif == 'O')
	{
		Terminal::get().clearScreen();
		if(Profil::compatible(Player, numeroBox, rangCharge) == true)
		{
			if(Player.payer(prixCharge))
			{
				Voiture->setSpoiler(Spoiler::chargerSpoiler(idCharge), id);
				Menu::msg("Spoiler amelioree avec succes !");
			}
		}
		else
		{
			Menu::error("Cette pièce n'est pas compatible avec votre vehicule");
		}
		verif = 'n'; // on quitte la verification
	}
	else if(verif == 'n' || verif == 'N')
	{
			Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			verif = 'n'; // on quitte la verification
	}
	else
	{
			Menu::error("Saisie invalide");
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuAtelierPriseAir(Profil& Player, const int& numeroBox)
{
	Voiture* Voiture = Player.getBox(numeroBox);
	char verif = 'x';

	int id = Voiture->getIdSpoiler();

	int idCharge = id + 1;
	std::string modeleCharge;
	int prixCharge;
	int aerodynamismeCharge;
	char rangCharge;

	PriseAir::infoPriseAir(idCharge, modeleCharge, rangCharge, aerodynamismeCharge, prixCharge);
	Terminal::get().clearScreen(); //On flushe l'ancien ecran	
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.getCredits() << "c\n"
									<< "====================\n"
									<< "Vous allez ameliorer les prises d'air de votre vehicule,\n"
									<< "Prix: " << prixCharge << "c\n\n"
									<< "#Nouveau Spoiler\n"
									<< " |Modele: " << modeleCharge << "\n"
									<< " |Rang: " << rangCharge << "\n"
									<< " |Aerodynamisme: " << aerodynamismeCharge << "%\n\n"
									<< "#Spoiler Actuel\n"
									<< " |Modele: " << Voiture->getNomPriseAir() << "\n"
									<< " |Rang: " << Voiture->getRangPriseAir() << "\n"
									<< " |Aerodynamisme: " << Voiture->getAerodynamismePriseAir() << "%\n\n"
									<< "Souhaitez-vous vraiment continuer ? [O/n]\n"
									<< "====================\n";
	verif = getch();
	if(verif == 'o' || verif == 'O')
	{
			Terminal::get().clearScreen();
			if(Profil::compatible(Player, numeroBox, rangCharge) == true)
			{
				if(Player.payer(prixCharge))
				{
					Voiture->setPriseAir(PriseAir::chargerPriseAir(idCharge), id);
					Menu::msg("Prise d'air amelioree avec succes !");
				}
			}
			else
			{
				Menu::error("Cette pièce n'est pas compatible avec votre vehicule");
			}
			verif = 'n'; // on quitte la verification

	}
	else if(verif == 'n' || verif == 'N')
	{
			Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			verif = 'n'; // on quitte la verification
	}
	else
	{
			Menu::error("Saisie invalide");
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuAtelierMoteur(Profil& Player, const int& numeroBox)
{
	Terminal::get().clearScreen();

	Voiture* Voiture = Player.getBox(numeroBox);

	char verifAchat;
	std::string sMenu;
	int menu;
	int tmenu = 0;
	bool paye = false;
	bool achat = false;
	bool quit = false;
	bool e2tour = false;
	int nbMoteurs = Moteur::compterMoteurs(Voiture->getMarque());
	std::string newNomMoteur = "Aucun";
	char newRangMoteur = ' ';
	int newPrixMoteur = 0;
	int newVitesseMoteur = 0;
	int newAccelerationMoteur = 0;
	int diffVitesseMoteur = 0;
	int diffAccelerationMoteur = 0;

	while(quit != true)
	{
		verifAchat = 'x';
		//Menu Principal
		Terminal::get() << "Changer Moteur\n"
										<< "===============\n"
										<< "Entrez le numero d'un moteur une fois pour afficher ses stats.\n"
										<< "Entrez le a nouveau pour acheter le moteur.\n"
										<< "Remarque: Pour tout achat, l'ancien moteur est automatiquement vendu. (60% du prix d'origine)\n"
										<< "===============\n"
										<< "Credits: " << Player.getCredits() << "C \n"
										<< "===============\n\n"
										<< "#Stats Moteur\n"
										<< " |Modele: " << newNomMoteur << " (Actuel: " << Voiture->getNomMoteur() << ")\n"
										<< " |Vitesse: " << newVitesseMoteur << "      (Actuelle: " << Voiture->getVitesseMoteur() << " [";
		if(diffVitesseMoteur >= 0)
		{
			Terminal::get() << '+';
		}
		Terminal::get() << diffVitesseMoteur << "])\n"
										<< " |Acceleration: " << newAccelerationMoteur << " (Actuelle: " << Voiture->getAccelerationMoteur() << " [";
		if(diffAccelerationMoteur >= 0)
		{
			Terminal::get() << '+';
		}
		Terminal::get() << diffAccelerationMoteur << "])\n"
										<< " |Prix: " << newPrixMoteur << "\n\n";
		Moteur::listerMoteurs(Voiture->getMarque());
		Terminal::get() << "\n"
										<< "0. Retour\n";
		menu = Menu::askChoice();
		if(menu == 0)
		{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0 && menu <= nbMoteurs)
		{
			Terminal::get().clearScreen();
			Moteur::infoMoteur(menu, Voiture->getMarque(), newNomMoteur, newVitesseMoteur, newAccelerationMoteur, newRangMoteur, newPrixMoteur);

			if(menu == Voiture->getIdMoteur())
			{
				Terminal::get().clearScreen();
				Menu::msg("Votre vehicule est deja equipe de cette piece. ("+newNomMoteur+")");
				newNomMoteur = "N/A";
				newVitesseMoteur = 0;
				newAccelerationMoteur = 0;
				newPrixMoteur = 0;
				newRangMoteur = ' ';
				diffVitesseMoteur = 0;
				diffAccelerationMoteur = 0;
			}
			else
			{
				if(e2tour == 0 || tmenu != menu)
				{
					diffVitesseMoteur = newVitesseMoteur - Voiture->getVitesseMoteur();
					diffAccelerationMoteur = newAccelerationMoteur - Voiture->getAccelerationMoteur();
					e2tour = 1;
					tmenu = menu;
				}
				else if(e2tour == 1 && tmenu == menu) //Si c'est la 2e pression sur le MEME menu
				{
					if(Profil::compatible(Player, numeroBox, newRangMoteur) == 1)
					{
						Terminal::get().clearScreen();
						while(verifAchat != 'n') // Boucle de confirmation
						{
							Terminal::get() << "Vous allez acheter le moteur suivant:\n\n"
															<< "====================\n"
															<< "#Moteur Selectionne\n"
															<< " |Modele: " << newNomMoteur << "\n"
															<< " |Vitesse: " << newVitesseMoteur << "  (";
							if(diffVitesseMoteur >= 0)
							{
								Terminal::get() << '+';
							}
							Terminal::get() << diffVitesseMoteur << ")\n"
															<< " |Acceleration: " << newAccelerationMoteur << "  (";
							if(diffAccelerationMoteur >= 0)
							{
								Terminal::get() << '+';
							}
							Terminal::get() << diffAccelerationMoteur << ")\n"
															<< " |Prix: " << newPrixMoteur << "c\n\n"
															<< "====================\n"
															<< "Credits: " << Player.getCredits() << "C \n"
															<< "====================\n\n"
															<< "#Moteur Actuel\n"
															<< " |Modele: " << Voiture->getNomMoteur() << "\n"
															<< " |Vitesse: "<< Voiture->getVitesseMoteur() << " Km/h\n"
															<< " |Acceleration: " << Voiture->getAccelerationMoteur() << " m/s²\n\n"
															<< "Souhaitez-vous vraiment l'acheter ? [O/n]\n"
															<< "====================\n";
							verifAchat = getch();
							switch(verifAchat)
							{
								case 'o':
									verifAchat = 'n'; // on quitte la verification
									achat = true;
									break;
								case 'O':
									verifAchat = 'n'; // on quitte la verification
									achat = true;
									break;
								case 'n':
									Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
									break;
								case 'N':
									Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
									verifAchat = 'n'; // on quitte
									break;
								default:
									Terminal::get().clearScreen();
									Menu::error("Saisie invalide");
									break;
							}
							if(achat == true)
							{
								Terminal::get().clearScreen();
								paye = Player.payer(newPrixMoteur);
								if(paye == true)
								{
									Player.ajouterCredits(Voiture->getPrixMoteur() * 0.6f);
									Player.setMoteurVoiture(numeroBox, Moteur::chargerMoteur(tmenu, Voiture->getMarque()), menu);
									Menu::msg("La piece a ete achetee et installee avec succes !");
								}
							}
						}
					}
					else
					{
						Terminal::get().clearScreen();
						Menu::error("La piece choisie n'est pas compatible avec votre voiture.");
					}
				}
			}
		}
		else
		{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuMaintenance(Profil& Player, const int& numeroBox)
{
	Terminal::get().clearScreen();
	bool quit = 0;
	char verifAchat;
	int nitroManquante;
	Voiture* Voiture = Player.getBox(numeroBox);
	int aPayer=0;
	//Menu Principal
	while(quit != 1)
	{
		Terminal::get() << "Menu Maintenance\n"
										<< "===============\n"
										<< "Selectionnez un vehicule a reparer ou entretenir.\n"
										<< "===============\n\n"
										<< "Voiture actuelle: [BOX" << numeroBox + 1 << ": " << Voiture->getMarque() << " " << Voiture->getModele() << "]\n\n"
										<< "1. Changer Pneus\n"
										<< "2. Plein Nitro\n"
										<< "3. Reparer\n\n"
										<< "0. Retour\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = 1;
				break;
			case 1:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Terminal::get() << "/!\\ Attention ! /!\\\n"
												<< "====================\n"
												<< "Credits: " << Player.getCredits() << "c\n"
												<< "====================\n"
												<< "Changer les pneus de ce vehicule vous coutera 2000c\n";
				if(Menu::askConfirmation())
				{
					if(Player.payer(2000))
					{
						Voiture->changerPneus();
						Menu::msg("Pneus Changes avec succes !");
					}
				}
				else
				{
					Menu::msg("Transaction annulee.");
				}
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				if(Voiture->getNitroMax() == 0)
				{
					Menu::error("Votre vehicule n'est pas equipe d'un reservoir de Nitro.");
				}
				else
				{
					nitroManquante = Voiture->getNitroMax() - Voiture->getNiveauNitro();
					Terminal::get() << "/!\\ Attention ! /!\\\n"
													<< "====================\n"
													<< "Credits: " << Player.getCredits() << "c\n"
													<< "====================\n"
													<< "Remplir la Nitro de ce vehicule (Restant: " << Voiture->getNiveauNitro() << "L/" << Voiture->getNitroMax() << "L)\n"
													<< "Pour remplir les " << nitroManquante << "L manquants, cela vous coutera " << nitroManquante * 100 << "c\n";
					if (Menu::askConfirmation())
					{
						if(Player.payer(nitroManquante * 100 ))
						{
							Voiture->changerPneus();
							Menu::msg("Nitro au max !");
						}
					}
					else
					{
						Menu::msg("Transaction annulee.");
					}
				}
				break;
			case 3:
				if(Voiture->getEtat()==100)
				{
					Menu::msg("Votre voiture est en parfait etat.");
				}
				else
				{
					aPayer = (Voiture->getPrix() * (100 - Voiture->getEtat())) /100 ;
					Terminal::get().clearScreen(); //On flushe l'ancien ecran
					Terminal::get() << "/!\\ Attention ! /!\\\n"
													<< "====================\n"
													<< "Credits: " << Player.getCredits() << "c\n"
													<< "====================\n"
													<< "Reparer ce vehicule\n"
													<< "vous coutera "<<aPayer<<"c\n"
													<< "Etes-vous sur ? [O/n]\n"
													<< "====================\n";
					verifAchat = getch();
					Terminal::get().clearScreen();
					if(verifAchat == 'o' || verifAchat == 'O')
					{
						if(Player.payer(aPayer))
						{
							Voiture->reparer();
							Menu::msg("voiture reparee avec succes !");
						}
					}
					else if(verifAchat == 'n' || verifAchat == 'n')
					{
						Menu::msg("Transaction annulee.");
					}
				}
				break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuAcheterBox(Profil& Player)
{
	Terminal::get().clearScreen(); //On flushe l'ancien ecran
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.getCredits() << "c\n"
									<< "====================\n"
									<< "Vous allez acheter un " << Player.getNbBox() + 1 << "eme Box,\n"
									<< "Prix: " << Player.getNbBox() * 20000 << "c\n\n";
	if(Menu::askConfirmation())
	{
		Player.acheterBox();
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuAchatVoiture(const char& rang, Profil& Player)
{
	std::string sMenu;
	int menu;
	int tmenu = 0;
	bool quit = false;
	bool achat = false;
	bool e2tour = false;
	int numeroBox = 0;
	std::string marqueVoiture = "N/A";
	std::string modeleVoiture = "N/A";
	int nitroMaxVoiture = 0;
	int aerodynamismeVoiture = 0;
	int idMoteurVoiture =0;
	std::string nomMoteurVoiture = "N/A";
	int vitesseMoteurVoiture = 0;
	int accelerationMoteurVoiture = 0;
	int prixVoiture = 0;

	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Concessionnaire - [Rang " << rang << "]\n"
										<< "===============\n"
										<< "Entrez le numero d'un vehicule une fois pour le selectionner.\n"
										<< "Entrez le a nouveau pour acheter le vehicule.\n"
										<< "===============\n\n";
		Voiture::listerVoitures(rang);
		Terminal::get() << "\n" //On separe le blo
										<< "0. Retour\n"
										<< "===============\n"
										<< "Credits: " << Player.getCredits() << "c\n"
										<< "===============\n\n"
										<< "#Voiture Selectionnee\n"
										<< " |Marque: " << marqueVoiture << "\n"
										<< " |Modele: " << modeleVoiture << "\n"
										<< " #Moteur" << "\n"
										<< "  |Modele: " << nomMoteurVoiture << "\n"
										<< "  |Vitese: " << vitesseMoteurVoiture << "Km/h\n"
										<< "  |Acceleration: " << accelerationMoteurVoiture << "m/s²\n"
										<< " |Capa. Nitro: " << nitroMaxVoiture << "L\n"
										<< " |Aerodynamisme: " << aerodynamismeVoiture << "%\n"
										<< " |Prix: " << prixVoiture << "c\n\n";
		menu = Menu::askChoice();
		if(menu == 0) //Redirection de l'utilisateur selon son choix grâce a un switch.
		{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0  && menu <= Voiture::compterVoitures(rang))
		{
			if(e2tour == 0 || tmenu != menu)
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran	
				Voiture::infoVoiture(menu, rang, marqueVoiture, modeleVoiture, idMoteurVoiture, nitroMaxVoiture, aerodynamismeVoiture, prixVoiture);
				Moteur::infoMoteur(idMoteurVoiture, marqueVoiture, nomMoteurVoiture, vitesseMoteurVoiture, accelerationMoteurVoiture);
				e2tour = 1;
				tmenu = menu;
			}
			else
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Terminal::get() << "/!\\ Attention ! /!\\\n"
												<< "====================\n"
												<< "Credits: " << Player.getCredits() << "c\n"
												<< "====================\n"
												<< "Vous allez acheter le vehicule:\n"
												<< marqueVoiture << " " << modeleVoiture << "\n"
												<< "Prix: " << prixVoiture << "c\n\n";
				if (Menu::askConfirmation())
				{
					Terminal::get().clearScreen();
					achat = true;
				}
				else
				{
					Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
					Menu::msg("Transaction annulee.");
				}
				if(achat == true)
				{
					Terminal::get().clearScreen();
					numeroBox = menuConsulterGarage(Player, 2); //on demande a l'utilisateur ou stocker la voiture
					Terminal::get().clearScreen();
					if(numeroBox == 0)
					{
						Menu::msg("Transaction annulee.");
					}
					else
					{
						numeroBox -= 1;
						if(Player.payer(prixVoiture))
						{
							Player.setBox(numeroBox, Voiture::chargerVoiture(menu, rang));
							Player.ajouterVoitureAchetee();
							Menu::msg("Vehicule achete avec succes !");
						}
					}
				}
			}
		}
		else
		{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuConcessionaireAchat(Profil& Player)
{
	//Menu Principal
	Terminal::get() << "Concessionnaire\n"
									<< "===============\n"
									<< "Selectionnez le rang du vehicule a acheter.\n"
									<< "===============\n\n"
									<< "1. Rang [D]\n"
									<< "2. Rang [C]\n"
									<< "3. Rang [B]\n"
									<< "4. Rang [A]\n"
									<< "5. Rang [S]\n\n"
									<< "0. Retour\n";
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(Menu::askChoice())
	{
		case 0:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			break;
		case 1:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('D', Player);
			break;
		case 2:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('C', Player);
			//menuAchatVoiture('C', Player);
			break;
		case 3:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('B', Player);
			//menuAchatVoiture('B', Player);
			break;
		case 4:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('A', Player);
			//menuAchatVoiture('A', Player);
			break;
		case 5:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('S', Player);
			//menuAchatVoiture('S', Player);
			break;
		default:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Menu::error("Saisie invalide");
			break;
	}
}

void menuVenteVoiture(Profil& Player, const int& numeroBox)
{
	char verif;
	Voiture* Voiture = Player.getBox(numeroBox);
	Terminal::get() << Voiture->getPrix();
	int prixVente = Voiture->getPrix() * 0.70f;
	std::string sPrixVente;
	std::ostringstream oss;

	oss << prixVente;      // on insere le int dans le stream oss
	sPrixVente = oss.str(); // range le int dans la variable string

	Terminal::get().clearScreen(); //On flushe l'ancien ecran	
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.getCredits() << "c\n"
									<< "====================\n\n"
									<< "Vous allez vendre le vehicule :" << Voiture->getMarque() << " " << Voiture->getModele() << "[Box" << numeroBox << "]\n"
									<< "Prix de vente : " << prixVente << "c\n\n"
									<< "Souhaitez-vous vraiment continuer ? [O/n]\n"
									<< "====================\n";
	verif = getch();
	if(verif == 'o' || verif == 'O')
	{
			Terminal::get().clearScreen();
			Player.ajouterCredits(Voiture->getPrix() * 0.5);
			Player.setBox(numeroBox);
			Menu::msg(Voiture->getModele()+" vendue avec succes pour "+sPrixVente+"c");
	}
	else if(verif == 'n' || verif == 'N')
	{
			Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			Menu::msg("Transaction annulee par l'utilisateur.");
			verif = 'n'; // on quitte la verification
	}
	else
	{
			Terminal::get().clearScreen();
			Menu::error("Saisie invalide");
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuDifficulte(Profil& Player)
{
	std::string menu;	//un string car le le passe en iss
	int difficulte;
	
	Terminal::get() <<"Augmenter la difficulte augmente les gains\n"
									<<"====================\n"
									<<"Choisissez une difficulte\n"
									<<"====================\n\n"
									<< "1. DEBUTANT\n"
									<< "2. FACILE\n"
									<< "3. NORMAL\n"
									<< "4. DIFFICILE\n"
									<< "5. EXPERT\n\n"
									<< "0. Retour\n";
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(Menu::askChoice())
	{
		case 0:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			break;
		case 1:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			break;
		case 2:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('C', Player);
			break;
		case 3:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('B', Player);
			break;
		case 4:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('A', Player);
			break;
		case 5:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('S', Player);
			break;
		default:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Menu::error("Saisie invalide");
			break;
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuChangementNomProfil(Profil& Player)
{
	std::string nom;

	//Menu Creation de profil
	Terminal::get() << "Changement de nom\n"
									<< "===============\n\n"
									<< "Saisissez le nouveau nom du Profil.\n\n"
									<< "0. Annuler\n"
									<< "===============\n"
									<< "Nom: ";
	nom = getString(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	Terminal::get().clearScreen(); //on flushe l'ecran
	if(nom != "0")
	{
		Player.changerNom(nom);
		Menu::msg("Le nom de votre profil est maintenant : \""+nom+"\"");
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}