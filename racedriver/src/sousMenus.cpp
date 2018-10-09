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
		std::cout << "Liste des Boxs\n";
		std::cout << "===============\n";
		std::cout << "Selectionnez le vehicule qui va faire la course.\n";
		std::cout << "===============\n\n";
		for (size_t numeroBox = 0; numeroBox < nbBox; numeroBox++)
		{
			VoitureListee = Player.getBox(numeroBox);
			if(Player.boxVide(numeroBox))
			{
				std::cout << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
			}
			else
			{
				std::cout << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << VoitureListee->getMarque() << " " << VoitureListee->getModele() << "]\n";
			}
		}
		for (size_t j = nbBox; j < 5; j++)
		{
			std::cout << (j + 1) << ". Box " << (j + 1) << " [VEROUILLE]\n";
		}
		std::cout << "\n"; //On separe le bloc
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		std::istringstream iss;

		iss.str(sMenu);
		iss >> menu; // on convertit la string recuperee plus haut en entier	
		if(menu == 0)
		{
			clrscreen(); //On flushe l'ancien ecran
			quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0 && menu <= nbBox)
		{
			if(Player.boxVide(menu - 1))
			{
				clrscreen();
				error("Le box est vide.");
			}
			else
			{
				clrscreen(); //On flushe l'ancien ecran
				VoitureSelectionnee = Player.getBox(menu - 1);
				quit = true; //INSTRUCTION DE SORTIE
			}
		}
		else if(menu > nbBox && menu <= 5)
		{
			clrscreen();
			error("Ce box est verrouille.");
		}
		else
		{
			clrscreen(); //On flushe l'ancien ecran
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
	std::cout << "Course Libre\n";
	std::cout << "===============\n";
	std::cout << "Selectionnez un circuit.\n";
	std::cout << "===============\n\n";
	nombreCircuits = Circuit::listerCircuits();
	std::cout << "0. Annuler\n";
	std::cout << "===============\n";
	std::cout << "Choix ? ";
	std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un if + for.
	if(menu == 0)
	{
			clrscreen(); //On flushe l'ancien ecran et on quitte
	}
	else if(menu > 0 && menu <= nombreCircuits)
	{
		Circuit* CircuitCourant = 0;
		Circuit::chargerCircuit(menu, CircuitCourant);
		clrscreen(); //On flushe l'ancien ecran

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
		clrscreen(); //On flushe l'ancien ecran
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
	std::cout << "Course Libre\n";
	std::cout << "===============\n";
	std::cout << "Selectionnez un circuit.\n";
	std::cout << "===============\n\n";
	nombreCircuits = Circuit::listerCircuits();
	std::cout << "0. Annuler\n";
	std::cout << "===============\n";
	std::cout << "Choix ? ";
	std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un if + for.
	if(menu == 0)
	{
			clrscreen(); //On flushe l'ancien ecran et on quitte
	}
	else if(menu > 0 && menu <= nombreCircuits)
	{
		Circuit* CircuitCourant = 0;
		Circuit::chargerCircuit(menu, CircuitCourant);
		clrscreen(); //On flushe l'ancien ecran
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
		clrscreen(); //On flushe l'ancien ecran
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
	std::cout << "Liste des Boxs\n";
	std::cout << "===============\n";
	if(mode == 0) //On est en visualisation dans le garage
	{
		std::cout << "Selectionnez un vehicule a examiner.\n";
	}
	else if(mode == 1) //On est en selection dans l'atelier
	{
		std::cout << "Selectionnez un vehicule a ameliorer.\n";
	}
	else if(mode == 2) //On selectionne ou stocker une voiture en cours d'achat
	{
		std::cout << "Selectionnez un emplacement pour garer le vehicule.\n";
	}
	else if(mode == 3) //On selectionne ou stocker une voiture en cours d'achat
	{
		std::cout << "Selectionnez un vehicule a entretenir.\n";
	}
	else if(mode == 4) //On selectionne ou stocker une voiture en cours d'achat
	{
		std::cout << "Selectionnez un vehicule a vendre.\n";
	}
	std::cout << "===============\n\n";
	for (size_t numeroBox = 0; numeroBox < nbBox; numeroBox++)
	{
		Voiture = Player.getBox(numeroBox);
		if(Player.boxVide(numeroBox))
		{
			std::cout << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
		}
		else
		{
			std::cout << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << Voiture->getMarque() << " " << Voiture->getModele() << "]\n";
		}
	}
	for (size_t numeroBoxVerouille = nbBox; numeroBoxVerouille < 5; numeroBoxVerouille++)
	{
		std::cout << (numeroBoxVerouille + 1) << ". Box " << (numeroBoxVerouille + 1) << " [VEROUILLE]\n";
	}
	std::cout << "\n"; //On separe le bloc
	std::cout << "0. Retour\n";
	std::cout << "===============\n";
	std::cout << "Choix ? ";
	std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	std::istringstream iss;

	iss.str(sMenu);
	iss >> menu; // on convertit la string recuperee plus haut en entier
	if(menu == 0)
	{
		clrscreen(); //On flushe l'ancien ecran et quitte
	}
	else if(menu > 0 && menu <= nbBox)
	{
		if(Player.boxVide(menu - 1))
		{
			if(mode == 2)
			{
				clrscreen(); //On flushe l'ancien ecran et quitte
			}
			else
			{
				clrscreen();
				error("Le box est vide.");
			}
		}
		else if(mode == 0)
		{
			clrscreen(); //On flushe l'ancien ecran
			menuConsulterBox(Player, menu - 1);
			clrscreen();
		}
		else if(mode == 1)
		{
			clrscreen();
			menuAtelier(Player, menu - 1);
		}
		else if(mode == 2)
		{
			clrscreen();
			error("Le box est deja occupe.");
		}
		else if(mode == 3)
		{
			clrscreen();
			menuMaintenance(Player, menu - 1);
		}
		else if(mode == 4)
		{
			clrscreen();
			menuVenteVoiture(Player, menu - 1);
		}
	}
	else if(menu > nbBox && menu <= 5)
	{
		clrscreen();
		error("Ce box est verrouille.");
	}
	else
	{
		clrscreen(); //On flushe l'ancien ecran
		saisieInvalide();
	}
	return menu; //On renvoie l'emplacement choisi
}

void menuConsulterBox(Profil& Player, const int& numeroBox)
{
	Voiture* Voiture = Player.getBox(numeroBox);
	//Menu Principal
	std::cout << "Vehicule gare dans le Box " << (numeroBox + 1) << "\n";
	std::cout << "===============\n\n";
	std::cout << "#Vehicule\n";
	std::cout << " |Modele: " << Voiture->getModele() << "\n";
	std::cout << " |Marque: " << Voiture->getMarque() << "\n";
	std::cout << " |Rang: " << Voiture->getRang() << "\n";
	std::cout << " |\n";
	std::cout << " |Vitesse Totale: "<< Voiture->getVitesse() << " Km/h\n";
	std::cout << " |Acceleration Totale: " << Voiture->getAcceleration() << " m/s²\n";
	std::cout << " |Capacite Nitro: " << Voiture->getNitroMax() << " L\n";
	std::cout << " |Aerodynamisme: " << Voiture->getAerodynamisme() << " %\n";
	std::cout << " |Nitro Actuelle: " << Voiture->getNiveauNitro() << " L\n";
	std::cout << " |Durabilite Pneus: "<< Voiture->getDurabilitePneus() << "%\n";
	std::cout << " |Etat: " << Voiture->getEtat() << "%\n\n";
	std::cout << "#Moteur\n";
	std::cout << " |Modele: " << Voiture->getNomMoteur() << "\n";
	std::cout << " |Vitesse: "<< Voiture->getVitesseMoteur() << " Km/h\n";
	std::cout << " |Acceleration: " << Voiture->getAccelerationMoteur() << " m/s²\n\n";
	std::cout << "#Spoiler\n";
	std::cout << " |Modele: " << Voiture->getNomSpoiler() << "\n";
	std::cout << " |Rang: "<<  Voiture->getRangSpoiler() << "\n";
	std::cout << " |Aerodynamisme: " <<  Voiture->getAerodynamismeSpoiler() << " %\n\n";
	std::cout << "#Prises d'air\n";
	std::cout << " |Modele: " <<  Voiture->getNomPriseAir() << "\n";
	std::cout << " |Rang: "<<  Voiture->getRangPriseAir() << "\n";
	std::cout << " |Aerodynamisme: " <<  Voiture->getAerodynamismePriseAir() << " %\n\n";
	std::cout << "#Pneus\n";
	std::cout << " |Marque: " <<  Voiture->getMarquePneus() << "\n";
	std::cout << " |Rang: "<<  Voiture->getRangPneus() << "\n\n";
	std::cout << "===============\n";
	std::cout << "Appuyez sur Entree pour revenir au menu precedent";
	videKBuffer();
}

void menuAtelier(Profil& Player, const int& numeroBox)
{
	clrscreen();
	char menu;
	bool quit = false;
	Voiture* Voiture = Player.getBox(numeroBox);

	while(quit != true)
	{
		//Menu Principal
		std::cout << "Menu Atelier\n";
		std::cout << "===============\n";
		std::cout << "Selectionnez une piece a modifier.\n";
		std::cout << "===============\n\n";
		std::cout << "Voiture actuelle: [BOX" << numeroBox + 1 << ": " << Voiture->getMarque() << " " << Voiture->getModele() << "]\n\n";
		std::cout << "1. Moteur\n";
		std::cout << "2. Prise d'air\n";
		std::cout << "3. Spoiler\n\n";
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				clrscreen(); //On flushe l'ancien ecran
				quit = true;
				break;
			case '1':
				clrscreen(); //On flushe l'ancien ecran
				menuAtelierMoteur(Player, numeroBox);
				break;
			case '2':
				clrscreen(); //On flushe l'ancien ecran
				menuAtelierPriseAir(Player, numeroBox);
				break;
			case '3':
				clrscreen(); //On flushe l'ancien ecran
				menuAtelierSpoiler(Player, numeroBox);
				break;
			default:
				clrscreen(); //On flushe l'ancien ecran
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
	clrscreen(); //On flushe l'ancien ecran	
	std::cout << "/!\\ Attention ! /!\\\n";
	std::cout << "====================\n";
	std::cout << "Credits: " << Player.getCredits() << "c\n";
	std::cout << "====================\n";
	std::cout << "Vous allez ameliorer le spoiler de votre vehicule,\n";
	std::cout << "Prix: " << prixCharge << "c\n\n";
	std::cout << "#Nouveau Spoiler\n";
	std::cout << " |Modele: " << modeleCharge << "\n";
	std::cout << " |Rang: " << rangCharge << "\n";
	std::cout << " |Aerodynamisme: " << aerodynamismeCharge << "%\n\n";
	std::cout << "#Spoiler Actuel\n";
	std::cout << " |Modele: " << Voiture->getNomSpoiler() << "\n";
	std::cout << " |Rang: " << Voiture->getRangSpoiler() << "\n";
	std::cout << " |Aerodynamisme: " << Voiture->getAerodynamismeSpoiler() << "%\n\n";
	std::cout << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	std::cout << "====================\n";
	std::cin >> verif;
	videKBuffer();
	if(verif == 'o' || verif == 'O')
	{
		clrscreen();
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
			clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
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
	clrscreen(); //On flushe l'ancien ecran	
	std::cout << "/!\\ Attention ! /!\\\n";
	std::cout << "====================\n";
	std::cout << "Credits: " << Player.getCredits() << "c\n";
	std::cout << "====================\n";
	std::cout << "Vous allez ameliorer les prises d'air de votre vehicule,\n";
	std::cout << "Prix: " << prixCharge << "c\n\n";
	std::cout << "#Nouveau Spoiler\n";
	std::cout << " |Modele: " << modeleCharge << "\n";
	std::cout << " |Rang: " << rangCharge << "\n";
	std::cout << " |Aerodynamisme: " << aerodynamismeCharge << "%\n\n";
	std::cout << "#Spoiler Actuel\n";
	std::cout << " |Modele: " << Voiture->getNomPriseAir() << "\n";
	std::cout << " |Rang: " << Voiture->getRangPriseAir() << "\n";
	std::cout << " |Aerodynamisme: " << Voiture->getAerodynamismePriseAir() << "%\n\n";
	std::cout << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	std::cout << "====================\n";
	std::cin >> verif;
	videKBuffer();
	if(verif == 'o' || verif == 'O')
	{
			clrscreen();
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
			clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
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
	clrscreen();

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
		std::cout << "Changer Moteur\n";
		std::cout << "===============\n";
		std::cout << "Entrez le numero d'un moteur une fois pour afficher ses stats.\n";
		std::cout << "Entrez le a nouveau pour acheter le moteur.\n";
		std::cout << "Remarque: Pour tout achat, l'ancien moteur est automatiquement vendu. (60% du prix d'origine)\n";
		std::cout << "===============\n";
		std::cout << "Credits: " << Player.getCredits() << "C \n";
		std::cout << "===============\n\n";
		std::cout << "#Stats Moteur\n";
		std::cout << " |Modele: " << newNomMoteur << " (Actuel: " << Voiture->getNomMoteur() << ")\n";
		std::cout << " |Vitesse: " << newVitesseMoteur << "      (Actuelle: " << Voiture->getVitesseMoteur() << " [";
		if(diffVitesseMoteur >= 0)
		{
			std::cout << '+';
		}
		std::cout << diffVitesseMoteur << "])\n";
		std::cout << " |Acceleration: " << newAccelerationMoteur << " (Actuelle: " << Voiture->getAccelerationMoteur() << " [";
		if(diffAccelerationMoteur >= 0)
		{
			std::cout << '+';
		}
		std::cout << diffAccelerationMoteur << "])\n";
		std::cout << " |Prix: " << newPrixMoteur << "\n\n";
		Moteur::listerMoteurs(Voiture->getMarque());
		std::cout << "\n";
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		std::istringstream iss;

		iss.str(sMenu);
		iss >> menu; // on convertit la string recuperee plus haut en entier	
		if(menu == 0)
		{
				clrscreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0 && menu <= nbMoteurs)
		{
			clrscreen();
			Moteur::infoMoteur(menu, Voiture->getMarque(), newNomMoteur, newVitesseMoteur, newAccelerationMoteur, newRangMoteur, newPrixMoteur);

			if(menu == Voiture->getIdMoteur())
			{
				clrscreen();
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
						clrscreen();
						while(verifAchat != 'n') // Boucle de confirmation
						{
							std::cout << "Vous allez acheter le moteur suivant:\n\n";
							std::cout << "====================\n";
							std::cout << "#Moteur Selectionne\n";
							std::cout << " |Modele: " << newNomMoteur << "\n";
							std::cout << " |Vitesse: " << newVitesseMoteur << "  (";
							if(diffVitesseMoteur >= 0)
							{ 
								std::cout << '+';
							} 
							std::cout << diffVitesseMoteur << ")\n";
							std::cout << " |Acceleration: " << newAccelerationMoteur << "  (";
							if(diffAccelerationMoteur >= 0)
							{ 
								std::cout << '+';
							}
							std::cout << diffAccelerationMoteur << ")\n";
							std::cout << " |Prix: " << newPrixMoteur << "c\n\n";
							std::cout << "====================\n";
							std::cout << "Credits: " << Player.getCredits() << "C \n";
							std::cout << "====================\n\n";
							std::cout << "#Moteur Actuel\n";
							std::cout << " |Modele: " << Voiture->getNomMoteur() << "\n";
							std::cout << " |Vitesse: "<< Voiture->getVitesseMoteur() << " Km/h\n";
							std::cout << " |Acceleration: " << Voiture->getAccelerationMoteur() << " m/s²\n\n";
							std::cout << "Souhaitez-vous vraiment l'acheter ? [O/n]\n";
							std::cout << "====================\n";
							std::cin >> verifAchat;
							videKBuffer();
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
									clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
									break;
								case 'N':
									clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
									verifAchat = 'n'; // on quitte
									break;
								default:
									clrscreen();
									saisieInvalide();
									break;
							}
							if(achat == true)
							{
								clrscreen();
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
						clrscreen();
						error("La piece choisie n'est pas compatible avec votre voiture.");
					}
				}
			}
		}
		else
		{
				clrscreen(); //On flushe l'ancien ecran
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
	clrscreen();
	char menu;
	bool quit = 0;
	char verifAchat;
	int nitroManquante;
	Voiture* Voiture = Player.getBox(numeroBox);
	int aPayer=0;
	//Menu Principal
	while(quit != 1)
	{
		std::cout << "Menu Maintenance\n";
		std::cout << "===============\n";
		std::cout << "Selectionnez un vehicule a reparer ou entretenir.\n";
		std::cout << "===============\n\n";
		std::cout << "Voiture actuelle: [BOX" << numeroBox + 1 << ": " << Voiture->getMarque() << " " << Voiture->getModele() << "]\n\n";
		std::cout << "1. Changer Pneus\n";
		std::cout << "2. Plein Nitro\n";
		std::cout << "3. Reparer\n\n";
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				clrscreen(); //On flushe l'ancien ecran
				quit = 1;
				break;
			case '1':
				clrscreen(); //On flushe l'ancien ecran
				std::cout << "/!\\ Attention ! /!\\\n";
				std::cout << "====================\n";
				std::cout << "Credits: " << Player.getCredits() << "c\n";
				std::cout << "====================\n";
				std::cout << "Changer les pneus de ce vehicule\n";
				std::cout << "vous coutera 2000c \n";
				std::cout << "Etes-vous sur ? [O/n]\n";
				std::cout << "====================\n";
				std::cin >> verifAchat;
				videKBuffer();
				clrscreen();
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
				clrscreen(); //On flushe l'ancien ecran
				if(Voiture->getNitroMax() == 0)
				{
					error("Votre vehicule n'est pas equipe d'un reservoir de Nitro.");
				}
				else
				{
					nitroManquante = Voiture->getNitroMax() - Voiture->getNiveauNitro();
					std::cout << "/!\\ Attention ! /!\\\n";
					std::cout << "====================\n";
					std::cout << "Credits: " << Player.getCredits() << "c\n";
					std::cout << "====================\n";
					std::cout << "Remplir la Nitro de ce vehicule (Restant: " << Voiture->getNiveauNitro() << "L/" << Voiture->getNitroMax() << "L)\n";
					std::cout << "Pour remplir les " << nitroManquante << "L manquants, cela vous coutera " << nitroManquante * 100 << "c\n";
					std::cout << "Etes-vous sur ? [O/n]\n";
					std::cout << "====================\n";
					std::cin >> verifAchat;
					videKBuffer();
					clrscreen();
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
					clrscreen(); //On flushe l'ancien ecran
					std::cout << "/!\\ Attention ! /!\\\n";
					std::cout << "====================\n";
					std::cout << "Credits: " << Player.getCredits() << "c\n";
					std::cout << "====================\n";
					std::cout << "Reparer ce vehicule\n";
					std::cout << "vous coutera "<<aPayer<<"c\n";
					std::cout << "Etes-vous sur ? [O/n]\n";
					std::cout << "====================\n";
					std::cin >> verifAchat;
					videKBuffer();
					clrscreen();
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
				clrscreen(); //On flushe l'ancien ecran
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
	clrscreen(); //On flushe l'ancien ecran
	std::cout << "/!\\ Attention ! /!\\\n";
	std::cout << "====================\n";
	std::cout << "Credits: " << Player.getCredits() << "c\n";
	std::cout << "====================\n";
	std::cout << "Vous allez acheter un " << Player.getNbBox() + 1 << "eme Box,\n";
	std::cout << "Prix: " << Player.getNbBox() * 20000 << "c\n\n";
	std::cout << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	std::cout << "====================\n";
	std::cin >> verif;
	videKBuffer();
	switch(verif)
	{
		case 'o':
			clrscreen();
			Player.acheterBox();
			verif = 'n'; // on quitte la verification
			break;
		case 'O':
			clrscreen();
			Player.acheterBox();
			verif = 'n'; // on quitte la verification
			break;
		case 'n':
			clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			break;
		case 'N':
			clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			verif = 'n'; // on quitte la verification
			break;
		default:
			clrscreen();
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
		std::cout << "Concessionnaire - [Rang " << rang << "]\n";
		std::cout << "===============\n";
		std::cout << "Entrez le numero d'un vehicule une fois pour le selectionner.\n";
		std::cout << "Entrez le a nouveau pour acheter le vehicule.\n";
		std::cout << "===============\n\n";
		Voiture::listerVoitures(rang);
		std::cout << "\n"; //On separe le bloc
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Credits: " << Player.getCredits() << "c\n";
		std::cout << "===============\n\n";
		std::cout << "#Voiture Selectionnee\n";
		std::cout << " |Marque: " << marqueVoiture << "\n";
		std::cout << " |Modele: " << modeleVoiture << "\n";
		std::cout << " #Moteur" << "\n";
		std::cout << "  |Modele: " << nomMoteurVoiture << "\n";
		std::cout << "  |Vitese: " << vitesseMoteurVoiture << "Km/h\n";
		std::cout << "  |Acceleration: " << accelerationMoteurVoiture << "m/s²\n";
		std::cout << " |Capa. Nitro: " << nitroMaxVoiture << "L\n";
		std::cout << " |Aerodynamisme: " << aerodynamismeVoiture << "%\n";
		std::cout << " |Prix: " << prixVoiture << "c\n\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		std::istringstream iss;

		iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
		iss >> menu; // on convertit la string recuperee plus haut en entier
		if(menu == 0) //Redirection de l'utilisateur selon son choix grâce a un switch.
		{
				clrscreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0  && menu <= Voiture::compterVoitures(rang))
		{
			if(e2tour == 0 || tmenu != menu)
			{
				clrscreen(); //On flushe l'ancien ecran	
				Voiture::infoVoiture(menu, rang, marqueVoiture, modeleVoiture, idMoteurVoiture, nitroMaxVoiture, aerodynamismeVoiture, prixVoiture);
				Moteur::infoMoteur(idMoteurVoiture, marqueVoiture, nomMoteurVoiture, vitesseMoteurVoiture, accelerationMoteurVoiture);
				e2tour = 1;
				tmenu = menu;
			}
			else
			{
				while(verifAchat != 'n') // Boucle de confirmation
				{
					clrscreen(); //On flushe l'ancien ecran
					std::cout << "/!\\ Attention ! /!\\\n";
					std::cout << "====================\n";
					std::cout << "Credits: " << Player.getCredits() << "c\n";
					std::cout << "====================\n";
					std::cout << "Vous allez acheter le vehicule:\n";
					std::cout << marqueVoiture << " " << modeleVoiture << "\n";
					std::cout << "Prix: " << prixVoiture << "c\n\n";
					std::cout << "Etes-vous sur ? [O/n]\n";
					std::cout << "====================\n";
					std::cin >> verifAchat;
					videKBuffer();
					switch(verifAchat)
					{
						case 'o':
							clrscreen();
							verifAchat = 'n'; // on quitte la verification
							achat = true;
							break;
						case 'O':
							clrscreen();
							verifAchat = 'n'; // on quitte la verification
							achat = true;
							break;
						case 'n':
							clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
							msg("Transaction annulee.");
							verifAchat = 'n'; // on quitte
							break;
						case 'N':
							clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
							msg("Transaction annulee.");
							verifAchat = 'n'; // on quitte
							break;
						default:
							clrscreen();
							saisieInvalide();
							break;
					}
					if(achat == true)
					{
						clrscreen();
						numeroBox = menuConsulterGarage(Player, 2); //on demande a l'utilisateur ou stocker la voiture
						clrscreen();
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
				clrscreen(); //On flushe l'ancien ecran
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
	std::cout << "Concessionnaire\n";
	std::cout << "===============\n";
	std::cout << "Selectionnez le rang du vehicule a acheter.\n";
	std::cout << "===============\n\n";
	std::cout << "1. Rang [D]\n";
	std::cout << "2. Rang [C]\n";
	std::cout << "3. Rang [B]\n";
	std::cout << "4. Rang [A]\n";
	std::cout << "5. Rang [S]\n\n";
	std::cout << "0. Retour\n";
	std::cout << "===============\n";
	std::cout << "Choix ? ";
	std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(menu)
	{
		case '0':
			clrscreen(); //On flushe l'ancien ecran
			break;
		case '1':
			clrscreen(); //On flushe l'ancien ecran
			menuAchatVoiture('D', Player);
			break;
		case '2':
			clrscreen(); //On flushe l'ancien ecran
			menuAchatVoiture('C', Player);
			//menuAchatVoiture('C', Player);
			break;
		case '3':
			clrscreen(); //On flushe l'ancien ecran
			menuAchatVoiture('B', Player);
			//menuAchatVoiture('B', Player);
			break;
		case '4':
			clrscreen(); //On flushe l'ancien ecran
			menuAchatVoiture('A', Player);
			//menuAchatVoiture('A', Player);
			break;
		case '5':
			clrscreen(); //On flushe l'ancien ecran
			menuAchatVoiture('S', Player);
			//menuAchatVoiture('S', Player);
			break;
		default:
			clrscreen(); //On flushe l'ancien ecran
			saisieInvalide();
			break;
	}
}

void menuVenteVoiture(Profil& Player, const int& numeroBox)
{
	char verif;
	Voiture* Voiture = Player.getBox(numeroBox);
	std::cout << Voiture->getPrix();
	int prixVente = Voiture->getPrix() * 0.70f;
	std::string sPrixVente;
	std::ostringstream oss;

	oss << prixVente;      // on insere le int dans le stream oss
	sPrixVente = oss.str(); // range le int dans la variable string

	clrscreen(); //On flushe l'ancien ecran	
	std::cout << "/!\\ Attention ! /!\\\n";
	std::cout << "====================\n";
	std::cout << "Credits: " << Player.getCredits() << "c\n";
	std::cout << "====================\n\n";
	std::cout << "Vous allez vendre le vehicule :" << Voiture->getMarque() << " " << Voiture->getModele() << "[Box" << numeroBox << "]\n";
	std::cout << "Prix de vente : " << prixVente << "c\n\n";
	std::cout << "Souhaitez-vous vraiment continuer ? [O/n]\n";
	std::cout << "====================\n";
	std::cin >> verif;
	videKBuffer();
	if(verif == 'o' || verif == 'O')
	{
			clrscreen();
			Player.ajouterCredits(Voiture->getPrix() * 0.5);
			Player.setBox(numeroBox);
			msg(Voiture->getModele()+" vendue avec succes pour "+sPrixVente+"c");
	}
	else if(verif == 'n' || verif == 'N')
	{
			clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
			msg("Transaction annulee par l'utilisateur.");
			verif = 'n'; // on quitte la verification
	}
	else
	{
			clrscreen();
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
	
	std::cout<<"Augmenter la difficulte augmente les gains\n";
	std::cout<<"====================\n";
	std::cout<<"Choisissez une difficulte\n";
	std::cout<<"====================\n\n";
	std::cout << "1. DEBUTANT\n";
	std::cout << "2. FACILE\n";
	std::cout << "3. NORMAL\n";
	std::cout << "4. DIFFICILE\n";
	std::cout << "5. EXPERT\n\n";
	std::cout << "0. Retour\n";
	std::cout << "===============\n";
	std::cout << "Choix ? ";
	std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	std::istringstream iss(menu);
	iss>>difficulte;
	choix=menu[0];
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(choix)
	{
		case '0':
			clrscreen(); //On flushe l'ancien ecran
			break;
		case '1':
			clrscreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			break;
		case '2':
			clrscreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('C', Player);
			break;
		case '3':
			clrscreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('B', Player);
			break;
		case '4':
			clrscreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('A', Player);
			break;
		case '5':
			clrscreen(); //On flushe l'ancien ecran
			Player.setDifficulte(difficulte);
			//menuAchatVoiture('S', Player);
			break;
		default:
			clrscreen(); //On flushe l'ancien ecran
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
	std::cout << "Changement de nom\n";
	std::cout << "===============\n\n";
	std::cout << "Saisissez le nouveau nom du Profil.\n\n";
	std::cout << "0. Annuler\n";
	std::cout << "===============\n";
	std::cout << "Nom: ";
	std::cin >> nom; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	clrscreen(); //on flushe l'ecran
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