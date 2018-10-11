//sousMenus.cpp
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
		Game::instance->getTerm() << "Liste des Boxs\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Selectionnez le vehicule qui va faire la course.\n";
		Game::instance->getTerm() << "===============\n\n";
		for (size_t numeroBox = 0; numeroBox < nbBox; numeroBox++)
		{
			VoitureListee = Player.getBox(numeroBox);
			if(Player.boxVide(numeroBox))
			{
				Game::instance->getTerm() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
			}
			else
			{
				Game::instance->getTerm() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << VoitureListee->getMarque() << " " << VoitureListee->getModele() << "]\n";
			}
		}
		for (size_t j = nbBox; j < 5; j++)
		{
			Game::instance->getTerm() << (j + 1) << ". Box " << (j + 1) << " [VEROUILLE]\n";
		}
		Game::instance->getTerm() << "\n"; //On separe le bloc
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		std::getline(std::cin, sMenu); // l'utilisateur confirme
		std::istringstream iss;

		iss.str(sMenu);
		iss >> menu; // on convertit la string recuperee plus haut en entier	
		if(menu == 0)
		{
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0 && menu <= nbBox)
		{
			if(Player.boxVide(menu - 1))
			{
				Game::instance->getTerm().clearScreen();
				error("Le box est vide.");
			}
			else
			{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				VoitureSelectionnee = Player.getBox(menu - 1);
				quit = true; //INSTRUCTION DE SORTIE
			}
		}
		else if(menu > nbBox && menu <= 5)
		{
			Game::instance->getTerm().clearScreen();
			error("Ce box est verrouille.");
		}
		else
		{
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			saisieInvalide();
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
	Game::instance->getTerm() << "Course Libre\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Selectionnez un circuit.\n";
	Game::instance->getTerm() << "===============\n\n";
	nombreCircuits = Circuit::listerCircuits();
	Game::instance->getTerm() << "0. Annuler\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Choix ? ";
	std::getline(std::cin, sMenu); // l'utilisateur choisit un menu
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un if + for.
	if(menu == 0)
	{
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran et on quitte
	}
	else if(menu > 0 && menu <= nombreCircuits)
	{
		Circuit* CircuitCourant = 0;
		Circuit::chargerCircuit(menu, CircuitCourant);
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran

		VoiturePlayer = menuChoixVoiture(Player);
		if(VoiturePlayer == 0)
		{
			error("Aucune voiture selectionnee.");
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
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
		saisieInvalide();
	}
}

void menuCourseChampionnat(Profil& Player)
{
	std::string sMenu;
	int menu;
	Voiture* VoiturePlayer = 0;
	int nombreCircuits;
	//Menu Principal
	Game::instance->getTerm() << "Course Libre\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Selectionnez un circuit.\n";
	Game::instance->getTerm() << "===============\n\n";
	nombreCircuits = Circuit::listerCircuits();
	Game::instance->getTerm() << "0. Annuler\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Choix ? ";
	std::getline(std::cin, sMenu);
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un if + for.
	if(menu == 0)
	{
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran et on quitte
	}
	else if(menu > 0 && menu <= nombreCircuits)
	{
		Circuit* CircuitCourant = 0;
		Circuit::chargerCircuit(menu, CircuitCourant);
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
		VoiturePlayer = menuChoixVoiture(Player);
		if(VoiturePlayer == 0)
		{
			error("Aucune voiture selectionnee.");
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
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
		saisieInvalide();
	}
}

int menuConsulterGarage(Profil& Player, const int& mode)
{
	std::string sMenu;
	int menu;
	int nbBox = Player.getNbBox();
	Voiture* Voiture = 0;

	//Menu Principal
	Game::instance->getTerm() << "Liste des Boxs\n";
	Game::instance->getTerm() << "===============\n";
	if(mode == 0) //On est en visualisation dans le garage
	{
		Game::instance->getTerm() << "Selectionnez un vehicule a examiner.\n";
	}
	else if(mode == 1) //On est en selection dans l'atelier
	{
		Game::instance->getTerm() << "Selectionnez un vehicule a ameliorer.\n";
	}
	else if(mode == 2) //On selectionne ou stocker une voiture en cours d'achat
	{
		Game::instance->getTerm() << "Selectionnez un emplacement pour garer le vehicule.\n";
	}
	else if(mode == 3) //On selectionne ou stocker une voiture en cours d'achat
	{
		Game::instance->getTerm() << "Selectionnez un vehicule a entretenir.\n";
	}
	else if(mode == 4) //On selectionne ou stocker une voiture en cours d'achat
	{
		Game::instance->getTerm() << "Selectionnez un vehicule a vendre.\n";
	}
	Game::instance->getTerm() << "===============\n\n";
	for (size_t numeroBox = 0; numeroBox < nbBox; numeroBox++)
	{
		Voiture = Player.getBox(numeroBox);
		if(Player.boxVide(numeroBox))
		{
			Game::instance->getTerm() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
		}
		else
		{
			Game::instance->getTerm() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << Voiture->getMarque() << " " << Voiture->getModele() << "]\n";
		}
	}
	for (size_t numeroBoxVerouille = nbBox; numeroBoxVerouille < 5; numeroBoxVerouille++)
	{
		Game::instance->getTerm() << (numeroBoxVerouille + 1) << ". Box " << (numeroBoxVerouille + 1) << " [VEROUILLE]\n";
	}
	Game::instance->getTerm() << "\n"; //On separe le bloc
	Game::instance->getTerm() << "0. Retour\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Choix ? ";
	std::getline(std::cin, sMenu);
	std::istringstream iss;

	iss.str(sMenu);
	iss >> menu; // on convertit la string recuperee plus haut en entier
	if(menu == 0)
	{
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran et quitte
	}
	else if(menu > 0 && menu <= nbBox)
	{
		if(Player.boxVide(menu - 1))
		{
			if(mode == 2)
			{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran et quitte
			}
			else
			{
				Game::instance->getTerm().clearScreen();
				error("Le box est vide.");
			}
		}
		else if(mode == 0)
		{
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			menuConsulterBox(Player, menu - 1);
			Game::instance->getTerm().clearScreen();
		}
		else if(mode == 1)
		{
			Game::instance->getTerm().clearScreen();
			menuAtelier(Player, menu - 1);
		}
		else if(mode == 2)
		{
			Game::instance->getTerm().clearScreen();
			error("Le box est deja occupe.");
		}
		else if(mode == 3)
		{
			Game::instance->getTerm().clearScreen();
			menuMaintenance(Player, menu - 1);
		}
		else if(mode == 4)
		{
			Game::instance->getTerm().clearScreen();
			menuVenteVoiture(Player, menu - 1);
		}
	}
	else if(menu > nbBox && menu <= 5)
	{
		Game::instance->getTerm().clearScreen();
		error("Ce box est verrouille.");
	}
	else
	{
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
		saisieInvalide();
	}
	return menu; //On renvoie l'emplacement choisi
}

void menuConsulterBox(Profil& Player, const int& numeroBox)
{
	Voiture* Voiture = Player.getBox(numeroBox);
	//Menu Principal
	Game::instance->getTerm() << "Vehicule gare dans le Box " << (numeroBox + 1) << "\n";
	Game::instance->getTerm() << "===============\n\n";
	Game::instance->getTerm() << "#Vehicule\n";
	Game::instance->getTerm() << " |Modele: " << Voiture->getModele() << "\n";
	Game::instance->getTerm() << " |Marque: " << Voiture->getMarque() << "\n";
	Game::instance->getTerm() << " |Rang: " << Voiture->getRang() << "\n";
	Game::instance->getTerm() << " |\n";
	Game::instance->getTerm() << " |Vitesse Totale: "<< Voiture->getVitesse() << " Km/h\n";
	Game::instance->getTerm() << " |Acceleration Totale: " << Voiture->getAcceleration() << " m/s²\n";
	Game::instance->getTerm() << " |Capacite Nitro: " << Voiture->getNitroMax() << " L\n";
	Game::instance->getTerm() << " |Aerodynamisme: " << Voiture->getAerodynamisme() << " %\n";
	Game::instance->getTerm() << " |Nitro Actuelle: " << Voiture->getNiveauNitro() << " L\n";
	Game::instance->getTerm() << " |Durabilite Pneus: "<< Voiture->getDurabilitePneus() << "%\n";
	Game::instance->getTerm() << " |Etat: " << Voiture->getEtat() << "%\n\n";
	Game::instance->getTerm() << "#Moteur\n";
	Game::instance->getTerm() << " |Modele: " << Voiture->getNomMoteur() << "\n";
	Game::instance->getTerm() << " |Vitesse: "<< Voiture->getVitesseMoteur() << " Km/h\n";
	Game::instance->getTerm() << " |Acceleration: " << Voiture->getAccelerationMoteur() << " m/s²\n\n";
	Game::instance->getTerm() << "#Spoiler\n";
	Game::instance->getTerm() << " |Modele: " << Voiture->getNomSpoiler() << "\n";
	Game::instance->getTerm() << " |Rang: "<<  Voiture->getRangSpoiler() << "\n";
	Game::instance->getTerm() << " |Aerodynamisme: " <<  Voiture->getAerodynamismeSpoiler() << " %\n\n";
	Game::instance->getTerm() << "#Prises d'air\n";
	Game::instance->getTerm() << " |Modele: " <<  Voiture->getNomPriseAir() << "\n";
	Game::instance->getTerm() << " |Rang: "<<  Voiture->getRangPriseAir() << "\n";
	Game::instance->getTerm() << " |Aerodynamisme: " <<  Voiture->getAerodynamismePriseAir() << " %\n\n";
	Game::instance->getTerm() << "#Pneus\n";
	Game::instance->getTerm() << " |Marque: " <<  Voiture->getMarquePneus() << "\n";
	Game::instance->getTerm() << " |Rang: "<<  Voiture->getRangPneus() << "\n\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Appuyez sur Entree pour revenir au menu precedent";
	getch();
}

void menuAtelier(Profil& Player, const int& numeroBox)
{
	Game::instance->getTerm().clearScreen();
	char menu;
	bool quit = false;
	Voiture* Voiture = Player.getBox(numeroBox);

	while(quit != true)
	{
		//Menu Principal
		Game::instance->getTerm() << "Menu Atelier\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Selectionnez une piece a modifier.\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "Voiture actuelle: [BOX" << numeroBox + 1 << ": " << Voiture->getMarque() << " " << Voiture->getModele() << "]\n\n";
		Game::instance->getTerm() << "1. Moteur\n";
		Game::instance->getTerm() << "2. Prise d'air\n";
		Game::instance->getTerm() << "3. Spoiler\n\n";
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		menu = getch();
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = true;
				break;
			case '1':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuAtelierMoteur(Player, numeroBox);
				break;
			case '2':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuAtelierPriseAir(Player, numeroBox);
				break;
			case '3':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuAtelierSpoiler(Player, numeroBox);
				break;
			default:
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
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
	Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran	
	Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
	Game::instance->getTerm() << "====================\n";
	Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
	Game::instance->getTerm() << "====================\n";
	Game::instance->getTerm() << "Vous allez ameliorer le spoiler de votre vehicule,\n";
	Game::instance->getTerm() << "Prix: " << prixCharge << "c\n\n";
	Game::instance->getTerm() << "#Nouveau Spoiler\n";
	Game::instance->getTerm() << " |Modele: " << modeleCharge << "\n";
	Game::instance->getTerm() << " |Rang: " << rangCharge << "\n";
	Game::instance->getTerm() << " |Aerodynamisme: " << aerodynamismeCharge << "%\n\n";
	Game::instance->getTerm() << "#Spoiler Actuel\n";
	Game::instance->getTerm() << " |Modele: " << Voiture->getNomSpoiler() << "\n";
	Game::instance->getTerm() << " |Rang: " << Voiture->getRangSpoiler() << "\n";
	Game::instance->getTerm() << " |Aerodynamisme: " << Voiture->getAerodynamismeSpoiler() << "%\n\n";
	Game::instance->getTerm() << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	Game::instance->getTerm() << "====================\n";
	verif = getch();
	if(verif == 'o' || verif == 'O')
	{
		Game::instance->getTerm().clearScreen();
		if(Profil::compatible(Player, numeroBox, rangCharge) == true)
		{
			if(Player.payer(prixCharge))
			{
				Voiture->setSpoiler(Spoiler::chargerSpoiler(idCharge), id);
				msg("Spoiler amelioree avec succes !");
			}
		}
		else
		{
			error("Cette pièce n'est pas compatible avec votre vehicule");
		}
		verif = 'n'; // on quitte la verification
	}
	else if(verif == 'n' || verif == 'N')
	{
			Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			verif = 'n'; // on quitte la verification
	}
	else
	{
			saisieInvalide();
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
	Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran	
	Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
	Game::instance->getTerm() << "====================\n";
	Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
	Game::instance->getTerm() << "====================\n";
	Game::instance->getTerm() << "Vous allez ameliorer les prises d'air de votre vehicule,\n";
	Game::instance->getTerm() << "Prix: " << prixCharge << "c\n\n";
	Game::instance->getTerm() << "#Nouveau Spoiler\n";
	Game::instance->getTerm() << " |Modele: " << modeleCharge << "\n";
	Game::instance->getTerm() << " |Rang: " << rangCharge << "\n";
	Game::instance->getTerm() << " |Aerodynamisme: " << aerodynamismeCharge << "%\n\n";
	Game::instance->getTerm() << "#Spoiler Actuel\n";
	Game::instance->getTerm() << " |Modele: " << Voiture->getNomPriseAir() << "\n";
	Game::instance->getTerm() << " |Rang: " << Voiture->getRangPriseAir() << "\n";
	Game::instance->getTerm() << " |Aerodynamisme: " << Voiture->getAerodynamismePriseAir() << "%\n\n";
	Game::instance->getTerm() << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	Game::instance->getTerm() << "====================\n";
	verif = getch();
	if(verif == 'o' || verif == 'O')
	{
			Game::instance->getTerm().clearScreen();
			if(Profil::compatible(Player, numeroBox, rangCharge) == true)
			{
				if(Player.payer(prixCharge))
				{
					Voiture->setPriseAir(PriseAir::chargerPriseAir(idCharge), id);
					msg("Prise d'air amelioree avec succes !");
				}
			}
			else
			{
				error("Cette pièce n'est pas compatible avec votre vehicule");
			}
			verif = 'n'; // on quitte la verification

	}
	else if(verif == 'n' || verif == 'N')
	{
			Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			verif = 'n'; // on quitte la verification
	}
	else
	{
			saisieInvalide();
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuAtelierMoteur(Profil& Player, const int& numeroBox)
{
	Game::instance->getTerm().clearScreen();

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
		Game::instance->getTerm() << "Changer Moteur\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Entrez le numero d'un moteur une fois pour afficher ses stats.\n";
		Game::instance->getTerm() << "Entrez le a nouveau pour acheter le moteur.\n";
		Game::instance->getTerm() << "Remarque: Pour tout achat, l'ancien moteur est automatiquement vendu. (60% du prix d'origine)\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Credits: " << Player.getCredits() << "C \n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "#Stats Moteur\n";
		Game::instance->getTerm() << " |Modele: " << newNomMoteur << " (Actuel: " << Voiture->getNomMoteur() << ")\n";
		Game::instance->getTerm() << " |Vitesse: " << newVitesseMoteur << "      (Actuelle: " << Voiture->getVitesseMoteur() << " [";
		if(diffVitesseMoteur >= 0)
		{
			Game::instance->getTerm() << '+';
		}
		Game::instance->getTerm() << diffVitesseMoteur << "])\n";
		Game::instance->getTerm() << " |Acceleration: " << newAccelerationMoteur << " (Actuelle: " << Voiture->getAccelerationMoteur() << " [";
		if(diffAccelerationMoteur >= 0)
		{
			Game::instance->getTerm() << '+';
		}
		Game::instance->getTerm() << diffAccelerationMoteur << "])\n";
		Game::instance->getTerm() << " |Prix: " << newPrixMoteur << "\n\n";
		Moteur::listerMoteurs(Voiture->getMarque());
		Game::instance->getTerm() << "\n";
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		std::getline(std::cin, sMenu); // l'utilisateur entre le menu qu'il souhaite ouvrir
		std::istringstream iss;

		iss.str(sMenu);
		iss >> menu; // on convertit la string recuperee plus haut en entier	
		if(menu == 0)
		{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0 && menu <= nbMoteurs)
		{
			Game::instance->getTerm().clearScreen();
			Moteur::infoMoteur(menu, Voiture->getMarque(), newNomMoteur, newVitesseMoteur, newAccelerationMoteur, newRangMoteur, newPrixMoteur);

			if(menu == Voiture->getIdMoteur())
			{
				Game::instance->getTerm().clearScreen();
				msg("Votre vehicule est deja equipe de cette piece. ("+newNomMoteur+")");
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
						Game::instance->getTerm().clearScreen();
						while(verifAchat != 'n') // Boucle de confirmation
						{
							Game::instance->getTerm() << "Vous allez acheter le moteur suivant:\n\n";
							Game::instance->getTerm() << "====================\n";
							Game::instance->getTerm() << "#Moteur Selectionne\n";
							Game::instance->getTerm() << " |Modele: " << newNomMoteur << "\n";
							Game::instance->getTerm() << " |Vitesse: " << newVitesseMoteur << "  (";
							if(diffVitesseMoteur >= 0)
							{
								Game::instance->getTerm() << '+';
							}
							Game::instance->getTerm() << diffVitesseMoteur << ")\n";
							Game::instance->getTerm() << " |Acceleration: " << newAccelerationMoteur << "  (";
							if(diffAccelerationMoteur >= 0)
							{
								Game::instance->getTerm() << '+';
							}
							Game::instance->getTerm() << diffAccelerationMoteur << ")\n";
							Game::instance->getTerm() << " |Prix: " << newPrixMoteur << "c\n\n";
							Game::instance->getTerm() << "====================\n";
							Game::instance->getTerm() << "Credits: " << Player.getCredits() << "C \n";
							Game::instance->getTerm() << "====================\n\n";
							Game::instance->getTerm() << "#Moteur Actuel\n";
							Game::instance->getTerm() << " |Modele: " << Voiture->getNomMoteur() << "\n";
							Game::instance->getTerm() << " |Vitesse: "<< Voiture->getVitesseMoteur() << " Km/h\n";
							Game::instance->getTerm() << " |Acceleration: " << Voiture->getAccelerationMoteur() << " m/s²\n\n";
							Game::instance->getTerm() << "Souhaitez-vous vraiment l'acheter ? [O/n]\n";
							Game::instance->getTerm() << "====================\n";
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
									Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
									break;
								case 'N':
									Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
									verifAchat = 'n'; // on quitte
									break;
								default:
									Game::instance->getTerm().clearScreen();
									saisieInvalide();
									break;
							}
							if(achat == true)
							{
								Game::instance->getTerm().clearScreen();
								paye = Player.payer(newPrixMoteur);
								if(paye == true)
								{
									Player.ajouterCredits(Voiture->getPrixMoteur() * 0.6f);
									Player.setMoteurVoiture(numeroBox, Moteur::chargerMoteur(tmenu, Voiture->getMarque()), menu);
									msg("La piece a ete achetee et installee avec succes !");
								}
							}
						}
					}
					else
					{
						Game::instance->getTerm().clearScreen();
						error("La piece choisie n'est pas compatible avec votre voiture.");
					}
				}
			}
		}
		else
		{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuMaintenance(Profil& Player, const int& numeroBox)
{
	Game::instance->getTerm().clearScreen();
	char menu;
	bool quit = 0;
	char verifAchat;
	int nitroManquante;
	Voiture* Voiture = Player.getBox(numeroBox);
	int aPayer=0;
	//Menu Principal
	while(quit != 1)
	{
		Game::instance->getTerm() << "Menu Maintenance\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Selectionnez un vehicule a reparer ou entretenir.\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "Voiture actuelle: [BOX" << numeroBox + 1 << ": " << Voiture->getMarque() << " " << Voiture->getModele() << "]\n\n";
		Game::instance->getTerm() << "1. Changer Pneus\n";
		Game::instance->getTerm() << "2. Plein Nitro\n";
		Game::instance->getTerm() << "3. Reparer\n\n";
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = 1;
				break;
			case '1':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
				Game::instance->getTerm() << "====================\n";
				Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
				Game::instance->getTerm() << "====================\n";
				Game::instance->getTerm() << "Changer les pneus de ce vehicule\n";
				Game::instance->getTerm() << "vous coutera 2000c \n";
				Game::instance->getTerm() << "Etes-vous sur ? [O/n]\n";
				Game::instance->getTerm() << "====================\n";
				verifAchat = getch();
				Game::instance->getTerm().clearScreen();
				if(verifAchat == 'o' || verifAchat == 'O')
				{
					if(Player.payer(2000))
					{
						Voiture->changerPneus();
						msg("Pneus Changes avec succes !");
					}
				}
				else if(verifAchat == 'n' || verifAchat == 'n')
				{
					msg("Transaction annulee.");
				}
				break;
			case '2':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				if(Voiture->getNitroMax() == 0)
				{
					error("Votre vehicule n'est pas equipe d'un reservoir de Nitro.");
				}
				else
				{
					nitroManquante = Voiture->getNitroMax() - Voiture->getNiveauNitro();
					Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
					Game::instance->getTerm() << "====================\n";
					Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
					Game::instance->getTerm() << "====================\n";
					Game::instance->getTerm() << "Remplir la Nitro de ce vehicule (Restant: " << Voiture->getNiveauNitro() << "L/" << Voiture->getNitroMax() << "L)\n";
					Game::instance->getTerm() << "Pour remplir les " << nitroManquante << "L manquants, cela vous coutera " << nitroManquante * 100 << "c\n";
					Game::instance->getTerm() << "Etes-vous sur ? [O/n]\n";
					Game::instance->getTerm() << "====================\n";
					verifAchat = getch();
					Game::instance->getTerm().clearScreen();
					if(verifAchat == 'o' || verifAchat == 'O')
					{
						if(Player.payer(nitroManquante * 100 ))
						{
							Voiture->changerPneus();
							msg("Nitro au max !");
						}
					}
					else if(verifAchat == 'n' || verifAchat == 'n')
					{
						msg("Transaction annulee.");
					}
				}
				break;
			case '3':
				if(Voiture->getEtat()==100)
				{
					msg("Votre voiture est en parfait etat.");
				}
				else
				{
					aPayer = (Voiture->getPrix() * (100 - Voiture->getEtat())) /100 ;
					Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
					Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
					Game::instance->getTerm() << "====================\n";
					Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
					Game::instance->getTerm() << "====================\n";
					Game::instance->getTerm() << "Reparer ce vehicule\n";
					Game::instance->getTerm() << "vous coutera "<<aPayer<<"c\n";
					Game::instance->getTerm() << "Etes-vous sur ? [O/n]\n";
					Game::instance->getTerm() << "====================\n";
					verifAchat = getch();
					Game::instance->getTerm().clearScreen();
					if(verifAchat == 'o' || verifAchat == 'O')
					{
						if(Player.payer(aPayer))
						{
							Voiture->reparer();
							msg("voiture reparee avec succes !");
						}
					}
					else if(verifAchat == 'n' || verifAchat == 'n')
					{
						msg("Transaction annulee.");
					}
				}
				break;
			default:
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
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
	char verif = 'x';
	Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
	Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
	Game::instance->getTerm() << "====================\n";
	Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
	Game::instance->getTerm() << "====================\n";
	Game::instance->getTerm() << "Vous allez acheter un " << Player.getNbBox() + 1 << "eme Box,\n";
	Game::instance->getTerm() << "Prix: " << Player.getNbBox() * 20000 << "c\n\n";
	Game::instance->getTerm() << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	Game::instance->getTerm() << "====================\n";
	verif = getch();
	switch(verif)
	{
		case 'o':
			Game::instance->getTerm().clearScreen();
			Player.acheterBox();
			verif = 'n'; // on quitte la verification
			break;
		case 'O':
			Game::instance->getTerm().clearScreen();
			Player.acheterBox();
			verif = 'n'; // on quitte la verification
			break;
		case 'n':
			Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			break;
		case 'N':
			Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			verif = 'n'; // on quitte la verification
			break;
		default:
			Game::instance->getTerm().clearScreen();
			saisieInvalide();
			break;
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
		char verifAchat = 'x';
		//Menu Principal
		Game::instance->getTerm() << "Concessionnaire - [Rang " << rang << "]\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Entrez le numero d'un vehicule une fois pour le selectionner.\n";
		Game::instance->getTerm() << "Entrez le a nouveau pour acheter le vehicule.\n";
		Game::instance->getTerm() << "===============\n\n";
		Voiture::listerVoitures(rang);
		Game::instance->getTerm() << "\n"; //On separe le bloc
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "#Voiture Selectionnee\n";
		Game::instance->getTerm() << " |Marque: " << marqueVoiture << "\n";
		Game::instance->getTerm() << " |Modele: " << modeleVoiture << "\n";
		Game::instance->getTerm() << " #Moteur" << "\n";
		Game::instance->getTerm() << "  |Modele: " << nomMoteurVoiture << "\n";
		Game::instance->getTerm() << "  |Vitese: " << vitesseMoteurVoiture << "Km/h\n";
		Game::instance->getTerm() << "  |Acceleration: " << accelerationMoteurVoiture << "m/s²\n";
		Game::instance->getTerm() << " |Capa. Nitro: " << nitroMaxVoiture << "L\n";
		Game::instance->getTerm() << " |Aerodynamisme: " << aerodynamismeVoiture << "%\n";
		Game::instance->getTerm() << " |Prix: " << prixVoiture << "c\n\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		std::getline(std::cin, sMenu); // l'utilisateur entre le menu qu'il souhaite ouvrir
		std::istringstream iss;

		iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
		iss >> menu; // on convertit la string recuperee plus haut en entier
		if(menu == 0) //Redirection de l'utilisateur selon son choix grâce a un switch.
		{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0  && menu <= Voiture::compterVoitures(rang))
		{
			if(e2tour == 0 || tmenu != menu)
			{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran	
				Voiture::infoVoiture(menu, rang, marqueVoiture, modeleVoiture, idMoteurVoiture, nitroMaxVoiture, aerodynamismeVoiture, prixVoiture);
				Moteur::infoMoteur(idMoteurVoiture, marqueVoiture, nomMoteurVoiture, vitesseMoteurVoiture, accelerationMoteurVoiture);
				e2tour = 1;
				tmenu = menu;
			}
			else
			{
				while(verifAchat != 'n') // Boucle de confirmation
				{
					Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
					Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
					Game::instance->getTerm() << "====================\n";
					Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
					Game::instance->getTerm() << "====================\n";
					Game::instance->getTerm() << "Vous allez acheter le vehicule:\n";
					Game::instance->getTerm() << marqueVoiture << " " << modeleVoiture << "\n";
					Game::instance->getTerm() << "Prix: " << prixVoiture << "c\n\n";
					Game::instance->getTerm() << "Etes-vous sur ? [O/n]\n";
					Game::instance->getTerm() << "====================\n";
					verifAchat = getch();
					switch(verifAchat)
					{
						case 'o':
							Game::instance->getTerm().clearScreen();
							verifAchat = 'n'; // on quitte la verification
							achat = true;
							break;
						case 'O':
							Game::instance->getTerm().clearScreen();
							verifAchat = 'n'; // on quitte la verification
							achat = true;
							break;
						case 'n':
							Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
							msg("Transaction annulee.");
							verifAchat = 'n'; // on quitte
							break;
						case 'N':
							Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
							msg("Transaction annulee.");
							verifAchat = 'n'; // on quitte
							break;
						default:
							Game::instance->getTerm().clearScreen();
							saisieInvalide();
							break;
					}
					if(achat == true)
					{
						Game::instance->getTerm().clearScreen();
						numeroBox = menuConsulterGarage(Player, 2); //on demande a l'utilisateur ou stocker la voiture
						Game::instance->getTerm().clearScreen();
						if(numeroBox == 0)
						{
							msg("Transaction annulee.");
						}
						else
						{
							numeroBox -= 1;
							if(Player.payer(prixVoiture))
							{
								Player.setBox(numeroBox, Voiture::chargerVoiture(menu, rang));
								Player.ajouterVoitureAchetee();
								msg("Vehicule achete avec succes !");
							}
						}
					}
				}
			}
		}
		else
		{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuConcessionaireAchat(Profil& Player)
{
	char menu;
	//Menu Principal
	Game::instance->getTerm() << "Concessionnaire\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Selectionnez le rang du vehicule a acheter.\n";
	Game::instance->getTerm() << "===============\n\n";
	Game::instance->getTerm() << "1. Rang [D]\n";
	Game::instance->getTerm() << "2. Rang [C]\n";
	Game::instance->getTerm() << "3. Rang [B]\n";
	Game::instance->getTerm() << "4. Rang [A]\n";
	Game::instance->getTerm() << "5. Rang [S]\n\n";
	Game::instance->getTerm() << "0. Retour\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Choix ? ";
	menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(menu)
	{
		case '0':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			break;
		case '1':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('D', Player);
			break;
		case '2':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('C', Player);
			//menuAchatVoiture('C', Player);
			break;
		case '3':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('B', Player);
			//menuAchatVoiture('B', Player);
			break;
		case '4':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('A', Player);
			//menuAchatVoiture('A', Player);
			break;
		case '5':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			menuAchatVoiture('S', Player);
			//menuAchatVoiture('S', Player);
			break;
		default:
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			saisieInvalide();
			break;
	}
}

void menuVenteVoiture(Profil& Player, const int& numeroBox)
{
	char verif;
	Voiture* Voiture = Player.getBox(numeroBox);
	Game::instance->getTerm() << Voiture->getPrix();
	int prixVente = Voiture->getPrix() * 0.70f;
	std::string sPrixVente;
	std::ostringstream oss;

	oss << prixVente;      // on insere le int dans le stream oss
	sPrixVente = oss.str(); // range le int dans la variable string

	Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran	
	Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
	Game::instance->getTerm() << "====================\n";
	Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
	Game::instance->getTerm() << "====================\n\n";
	Game::instance->getTerm() << "Vous allez vendre le vehicule :" << Voiture->getMarque() << " " << Voiture->getModele() << "[Box" << numeroBox << "]\n";
	Game::instance->getTerm() << "Prix de vente : " << prixVente << "c\n\n";
	Game::instance->getTerm() << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	Game::instance->getTerm() << "====================\n";
	verif = getch();
	if(verif == 'o' || verif == 'O')
	{
			Game::instance->getTerm().clearScreen();
			Player.ajouterCredits(Voiture->getPrix() * 0.5);
			Player.setBox(numeroBox);
			msg(Voiture->getModele()+" vendue avec succes pour "+sPrixVente+"c");
	}
	else if(verif == 'n' || verif == 'N')
	{
			Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			msg("Transaction annulee par l'utilisateur.");
			verif = 'n'; // on quitte la verification
	}
	else
	{
			Game::instance->getTerm().clearScreen();
			saisieInvalide();
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}

void menuDifficulte(Profil& Player)
{
	std::string menu;	//un string car le le passe en iss
	char choix;
	int difficulte;
	
	Game::instance->getTerm() <<"Augmenter la difficulte augmente les gains\n";
	Game::instance->getTerm() <<"====================\n";
	Game::instance->getTerm() <<"Choisissez une difficulte\n";
	Game::instance->getTerm() <<"====================\n\n";
	Game::instance->getTerm() << "1. DEBUTANT\n";
	Game::instance->getTerm() << "2. FACILE\n";
	Game::instance->getTerm() << "3. NORMAL\n";
	Game::instance->getTerm() << "4. DIFFICILE\n";
	Game::instance->getTerm() << "5. EXPERT\n\n";
	Game::instance->getTerm() << "0. Retour\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Choix ? ";
	std::getline(std::cin, menu); // l'utilisateur entre le menu qu'il souhaite ouvrir
	std::istringstream iss(menu);
	iss>>difficulte;
	choix=menu[0];
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(choix)
	{
		case '0':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			break;
		case '1':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			break;
		case '2':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('C', Player);
			break;
		case '3':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('B', Player);
			break;
		case '4':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('A', Player);
			break;
		case '5':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('S', Player);
			break;
		default:
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			saisieInvalide();
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
	Game::instance->getTerm() << "Changement de nom\n";
	Game::instance->getTerm() << "===============\n\n";
	Game::instance->getTerm() << "Saisissez le nouveau nom du Profil.\n\n";
	Game::instance->getTerm() << "0. Annuler\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Nom: ";
	std::getline(std::cin, nom); // l'utilisateur entre le menu qu'il souhaite ouvrir
	Game::instance->getTerm().clearScreen(); //on flushe l'ecran
	if(nom != "0")
	{
		Player.changerNom(nom);
		msg("Le nom de votre profil est maintenant : \""+nom+"\"");
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}