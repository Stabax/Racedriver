//sousMenus.cpp
#include "Menu.hh"
#include "sousMenus.hh"

Car* menuChoixCar(Profile& Player)
{
	/*
	std::string sMenu;
	Car* CarSelectionnee = 0;
	Car* CarListee = 0;
	int menu;
	int nbBox = 1;//Player.getNbBox();
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Liste des Boxs\n"
										<< "===============\n"
										<< "Selectionnez le vehicule qui va faire la course.\n"
										<< "===============\n\n";
		for (int numeroBox = 0; numeroBox < nbBox; numeroBox++)
		{
			CarListee = Player.getBox(numeroBox);
			if(Player.boxVide(numeroBox))
			{
				Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
			}
			else
			{
				Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << CarListee->manufacturer << " " << CarListee->name << "]\n";
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
				CarSelectionnee = Player.getBox(menu - 1);
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
	return CarSelectionnee;*/
}

void menuCourseLibre(Profile& Player)
{/*
	std::string sMenu;
	int menu;
	Car* CarPlayer = 0;
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

		CarPlayer = menuChoixCar(Player);
		if(CarPlayer == 0)
		{
			Menu::error("Aucune voiture selectionnee.");
		}
		else
		{
			faireCourseLibre(*CircuitCourant, CarPlayer, Player);
		}
		delete CircuitCourant;
		CircuitCourant = 0;
	}
	else
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		Menu::error("Saisie invalide");
	}*/
}

void menuCourseChampionnat(Profile& Player)
{/*
	std::string sMenu;
	int menu;
	Car* CarPlayer = 0;
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
		CarPlayer = menuChoixCar(Player);
		if(CarPlayer == 0)
		{
			Menu::error("Aucune voiture selectionnee.");
		}
		else
		{
			faireCourseChampionnat(*CircuitCourant, CarPlayer, Player);
		}
		delete CircuitCourant;
		CircuitCourant = 0;
	}
	else
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		Menu::error("Saisie invalide");
	}*/
}

int menuConsulterGarage(Profile& Player, const int& mode)
{
	/*
	std::string sMenu;
	int menu;
	int nbBox = 1;// Player.getNbBox();
	Car* Car = 0;

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
	for (int numeroBox = 0; numeroBox < nbBox; numeroBox++)
	{
		Car = Player.getBox(numeroBox);
		if(Player.boxVide(numeroBox))
		{
			Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [VIDE]\n";
		}
		else
		{
			Terminal::get() << (numeroBox + 1) << ". Box " << (numeroBox + 1) << " [" << Car->manufacturer << " " << Car->name << "]\n";
		}
	}
	for (int numeroBoxVerouille = nbBox; numeroBoxVerouille < 5; numeroBoxVerouille++)
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
			menuVenteCar(Player, menu - 1);
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
	return menu; //On renvoie l'emplacement choisi*/
}

void menuConsulterBox(Profile& Player, const int& numeroBox)
{
	Car* Car; // = Player.getBox(numeroBox);
	std::shared_ptr<AirIntake> airIntake = Car->getAirIntake();
	std::shared_ptr<Spoiler> spoiler = Car->getSpoiler();
	std::shared_ptr<Tires> tires = Car->getTires();
	//Menu Principal
	Terminal::get() << "Vehicule gare dans le Box " << (numeroBox + 1) << "\n"
									<< "===============\n\n"
									<< "#Vehicule\n"
									<< " |Modele: " << Car->name << "\n"
									<< " |Marque: " << Car->manufacturer << "\n"
									<< " |Rang: " << Car->rank << "\n"
									<< " |\n"
									<< " |Vitesse Totale: "<< Car->getVitesse() << " Km/h\n"
									<< " |Acceleration Totale: " << Car->getAcceleration() << " m/s²\n"
									<< " |Capacite Nitro: " << Car->getNitroMax() << " L\n"
									<< " |Aerodynamisme: " << Car->getAerodynamisme() << " %\n"
									<< " |Nitro Actuelle: " << Car->getNiveauNitro() << " L\n"
									<< " |Durabilite Tires: "<< Car->getTires()->getDurability() << "%\n"
									<< " |Etat: " << Car->getEtat() << "%\n\n"
									<< "#Engine\n"
									<< " |Modele: " << Car->getEngine()->name << "\n"
									<< " |Vitesse: "<< Car->getEngine()->getVitesse() << " Km/h\n"
									<< " |Acceleration: " << Car->getEngine()->getAcceleration() << " m/s²\n\n"
									<< "#Spoiler\n"
									<< " |Modele: " << spoiler->name << "\n"
									<< " |Rang: "<<  spoiler->rank << "\n"
									<< " |Aerodynamisme: " <<  spoiler->getAerodynamic() << " %\n\n"
									<< "#Prises d'air\n"
									<< " |Modele: " << airIntake->name << "\n"
									<< " |Rang: "<<  airIntake->rank << "\n"
									<< " |Aerodynamisme: " <<  airIntake->getAerodynamic() << " %\n\n"
									<< "#Tires\n"
									<< " |Modele: " << tires->name << "\n"
									<< " |Rang: "<<  tires->rank << "\n"
									<< "===============\n"
									<< "Appuyez sur Entree pour revenir au menu precedent";
	getch();
}

void menuAtelier(Profile& Player, const int& numeroBox)
{/*
	Terminal::get().clearScreen();
	bool quit = false;
	Car* Car = Player.getBox(numeroBox);

	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Menu Atelier\n"
										<< "===============\n"
										<< "Selectionnez une piece a modifier.\n"
										<< "===============\n\n"
										<< "Car actuelle: [BOX" << numeroBox + 1 << ": " << Car->manufacturer << " " << Car->name << "]\n\n"
										<< "1. Engine\n"
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
				menuAtelierEngine(Player, numeroBox);
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuAtelierAirIntake(Player, numeroBox);
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
	}*/
}

void menuAtelierSpoiler(Profile& Player, const int& numeroBox)
{
	Menu::error("Non implemente");
	/* No more upgrades...
	Car* Car = Player.getBox(numeroBox);

	Spoiler &newSpoiler = Spoiler::collection[idCharge];
	Terminal::get().clearScreen(); //On flushe l'ancien ecran
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.credits << "c\n"
									<< "====================\n"
									<< "Vous allez ameliorer le spoiler de votre vehicule,\n"
									<< "Prix: " << newSpoiler.getPrice() << "c\n\n"
									<< "#Nouveau Spoiler\n"
									<< " |Modele: " << newSpoiler.name << "\n"
									<< " |Rang: " << newSpoiler.rank << "\n"
									<< " |Aerodynamisme: " << newSpoiler.getAerodynamic() << "%\n\n"
									<< "#Spoiler Actuel\n"
									<< " |Modele: " << Car->getSpoiler().name << "\n"
									<< " |Rang: " << Car->getSpoiler().rank << "\n"
									<< " |Aerodynamisme: " << Car->getSpoiler().getAerodynamic() << "%\n\n";
	if(Menu::askConfirmation())
	{
		Terminal::get().clearScreen();
		if(Profile::compatible(Player, numeroBox, newSpoiler.rank) == true)
		{
			if(Player.payer(newSpoiler.getPrice()))
			{
				Car->setSpoiler(Spoiler::collection[idCharge], id);
				Menu::msg("Spoiler ameliore avec succes !");
			}
		}
		else
		{
			Menu::error("Cette pièce n'est pas compatible avec votre vehicule");
		}
		if(Player.getSauvegardeAuto())
		{
			Player.sauvegarderProfile();
		}
	}
	else
	{
		Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
	}*/
}

void menuAtelierAirIntake(Profile& Player, const int& numeroBox)
{
	Menu::error("Non implemente");
	/* No more upgrades...
	Car* Car = Player.getBox(numeroBox);
	int id = Car->getIdSpoiler();
	int idCharge = id + 1;

	const AirIntake &newAirIntake = AirIntake::collection[idCharge];
	const AirIntake &currentAirIntake = Car->getAirIntake();
	Terminal::get().clearScreen(); //On flushe l'ancien ecran
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.credits << "c\n"
									<< "====================\n"
									<< "Vous allez ameliorer les prises d'air de votre vehicule,\n"
									<< "Prix: " << newAirIntake.getPrice() << "c\n\n"
									<< "#Nouveau Spoiler\n"
									<< " |Modele: " << newAirIntake.name << "\n"
									<< " |Rang: " << newAirIntake.rank << "\n"
									<< " |Aerodynamisme: " << newAirIntake.getAerodynamic() << "%\n\n"
									<< "#Spoiler Actuel\n"
									<< " |Modele: " << currentAirIntake.name << "\n"
									<< " |Rang: " << currentAirIntake.rank << "\n"
									<< " |Aerodynamisme: " << currentAirIntake.getAerodynamic() << "%\n\n";
	if(Menu::askConfirmation())
	{
		Terminal::get().clearScreen();
		if(Profile::compatible(Player, numeroBox, newAirIntake.rank) == true)
		{
			if(Player.payer(newAirIntake.getPrice()))
			{
				Car->setAirIntake(AirIntake::collection[idCharge], id);
				Menu::msg("Prise d'air amelioree avec succes !");
			}
		}
		else
		{
			Menu::error("Cette pièce n'est pas compatible avec votre vehicule");
		}
		if(Player.getSauvegardeAuto())
		{
			Player.sauvegarderProfile();
		}
	}
	else
	{
			Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
	}*/
}

void menuAtelierEngine(Profile& Player, const int& numeroBox)
{
	Menu::error("Non implemente");
	/* No more silly menus...

	Car* Car = Player.getBox(numeroBox);

	char verifAchat;
	std::string sMenu;
	int menu;
	int tmenu = 0;
	bool paye = false;
	bool achat = false;
	bool quit = false;
	bool e2tour = false;
	int nbEngines = Engine::compterEngines(Car->manufacturer);
	std::string newNomEngine = "Aucun";
	char newRangEngine = ' ';
	int newPrixEngine = 0;
	int newVitesseEngine = 0;
	int newAccelerationEngine = 0;
	int diffVitesseEngine = 0;
	int diffAccelerationEngine = 0;

	Terminal::get().clearScreen();
	while(quit != true)
	{
		verifAchat = 'x';
		//Menu Principal
		Terminal::get() << "Changer Engine\n"
										<< "===============\n"
										<< "Entrez le numero d'un moteur une fois pour afficher ses stats.\n"
										<< "Entrez le a nouveau pour acheter le moteur.\n"
										<< "Remarque: Pour tout achat, l'ancien moteur est automatiquement vendu. (60% du prix d'origine)\n"
										<< "===============\n"
										<< "Credits: " << Player.credits << "C \n"
										<< "===============\n\n"
										<< "#Stats Engine\n"
										<< " |Modele: " << newNomEngine << " (Actuel: " << Car->getEngine()->name << ")\n"
										<< " |Vitesse: " << newVitesseEngine << "      (Actuelle: " << Car->getEngine()->getVitesse() << " [";
		if(diffVitesseEngine >= 0)
		{
			Terminal::get() << '+';
		}
		Terminal::get() << diffVitesseEngine << "])\n"
										<< " |Acceleration: " << newAccelerationEngine << " (Actuelle: " << Car->getEngine()->getAcceleration() << " [";
		if(diffAccelerationEngine >= 0)
		{
			Terminal::get() << '+';
		}
		Terminal::get() << diffAccelerationEngine << "])\n"
										<< " |Prix: " << newPrixEngine << "\n\n";
		Engine::listerEngines(Car->manufacturer);
		Terminal::get() << "\n"
										<< "0. Retour\n";
		menu = Menu::askChoice();
		if(menu == 0)
		{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0 && menu <= nbEngines)
		{
			Terminal::get().clearScreen();
			Engine::infoEngine(menu, Car->manufacturer, newNomEngine, newVitesseEngine, newAccelerationEngine, newRangEngine, newPrixEngine);

			if(menu == Car->getEngine())
			{
				Terminal::get().clearScreen();
				Menu::msg("Votre vehicule est deja equipe de cette piece. ("+newNomEngine+")");
				newNomEngine = "N/A";
				newVitesseEngine = 0;
				newAccelerationEngine = 0;
				newPrixEngine = 0;
				newRangEngine = ' ';
				diffVitesseEngine = 0;
				diffAccelerationEngine = 0;
			}
			else
			{
				if(e2tour == 0 || tmenu != menu)
				{
					diffVitesseEngine = newVitesseEngine - Car->getEngine()->getVitesse();
					diffAccelerationEngine = newAccelerationEngine - Car->getEngine()->getAcceleration();
					e2tour = 1;
					tmenu = menu;
				}
				else if(e2tour == 1 && tmenu == menu) //Si c'est la 2e pression sur le MEME menu
				{
					if(Profile::compatible(Player, numeroBox, newRangEngine) == 1)
					{
						Terminal::get().clearScreen();
						while(verifAchat != 'n') // Boucle de confirmation
						{
							Terminal::get() << "Vous allez acheter le moteur suivant:\n\n"
															<< "====================\n"
															<< "#Engine Selectionne\n"
															<< " |Modele: " << newNomEngine << "\n"
															<< " |Vitesse: " << newVitesseEngine << "  (";
							if(diffVitesseEngine >= 0)
							{
								Terminal::get() << '+';
							}
							Terminal::get() << diffVitesseEngine << ")\n"
															<< " |Acceleration: " << newAccelerationEngine << "  (";
							if(diffAccelerationEngine >= 0)
							{
								Terminal::get() << '+';
							}
							Terminal::get() << diffAccelerationEngine << ")\n"
															<< " |Prix: " << newPrixEngine << "c\n\n"
															<< "====================\n"
															<< "Credits: " << Player.credits << "C \n"
															<< "====================\n\n"
															<< "#Engine Actuel\n"
															<< " |Modele: " << Car->getEngine()->name << "\n"
															<< " |Vitesse: "<< Car->getEngine()->getVitesse() << " Km/h\n"
															<< " |Acceleration: " << Car->getEngine()->getAcceleration() << " m/s²\n\n"
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
								paye = Player.payer(newPrixEngine);
								if(paye == true)
								{
									Player.ajouterCredits(Car->getEngine()->getPrix() * 0.6f);
									Player.setEngineCar(numeroBox, &Engine::collection[0], menu);
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
		Player.sauvegarderProfile();
	}*/
}

void menuMaintenance(Profile& Player, const int& numeroBox)
{
	Terminal::get().clearScreen();
	bool quit = 0;
	char verifAchat;
	int nitroManquante;
	Car* Car; // = Player.getBox(numeroBox);
	int aPayer=0;
	//Menu Principal
	while(quit != 1)
	{
		Terminal::get() << "Menu Maintenance\n"
										<< "===============\n"
										<< "Selectionnez un vehicule a reparer ou entretenir.\n"
										<< "===============\n\n"
										<< "Car actuelle: [BOX" << numeroBox + 1 << ": " << Car->manufacturer << " " << Car->name << "]\n\n"
										<< "1. Changer Tires\n"
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
												<< "Credits: " << Player.credits << "c\n"
												<< "====================\n"
												<< "Changer les pneus de ce vehicule vous coutera 2000c\n";
				if(Menu::askConfirmation())
				{
					if(Player.payer(2000))
					{
						Car->changerTires();
						Menu::msg("Tires Changes avec succes !");
					}
				}
				else
				{
					Menu::msg("Transaction annulee.");
				}
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				if(Car->getNitroMax() == 0)
				{
					Menu::error("Votre vehicule n'est pas equipe d'un reservoir de Nitro.");
				}
				else
				{
					nitroManquante = Car->getNitroMax() - Car->getNiveauNitro();
					Terminal::get() << "/!\\ Attention ! /!\\\n"
													<< "====================\n"
													<< "Credits: " << Player.credits << "c\n"
													<< "====================\n"
													<< "Remplir la Nitro de ce vehicule (Restant: " << Car->getNiveauNitro() << "L/" << Car->getNitroMax() << "L)\n"
													<< "Pour remplir les " << nitroManquante << "L manquants, cela vous coutera " << nitroManquante * 100 << "c\n";
					if (Menu::askConfirmation())
					{
						if(Player.payer(nitroManquante * 100 ))
						{
							Car->changerTires();
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
				if(Car->getEtat()==100)
				{
					Menu::msg("Votre voiture est en parfait etat.");
				}
				else
				{
					aPayer = (Car->getPrix() * (100 - Car->getEtat())) /100 ;
					Terminal::get().clearScreen(); //On flushe l'ancien ecran
					Terminal::get() << "/!\\ Attention ! /!\\\n"
													<< "====================\n"
													<< "Credits: " << Player.credits << "c\n"
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
							Car->reparer();
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
	Player.sauvegarderProfile();
}

void menuAcheterBox(Profile& Player)
{
	Terminal::get().clearScreen(); //On flushe l'ancien ecran
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.credits << "c\n"
									<< "====================\n"
									<< "Vous allez acheter un " << 1 + 1 << "eme Box,\n"
									<< "Prix: " << 1 * 20000 << "c\n\n";
	if(Menu::askConfirmation())
	{
		//Player.acheterBox();
	}
	Player.sauvegarderProfile();
}

void menuAchatCar(const char& rang, Profile& Player)
{
	std::string sMenu;
	int menu;
	int tmenu = 0;
	bool quit = false;
	bool achat = false;
	bool e2tour = false;
	int numeroBox = 0;
	std::string marqueCar = "N/A";
	std::string modeleCar = "N/A";
	int nitroMaxCar = 0;
	int aerodynamismeCar = 0;
	int idEngineCar =0;
	std::string nomEngineCar = "N/A";
	int vitesseEngineCar = 0;
	int accelerationEngineCar = 0;
	int prixCar = 0;

	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Concessionnaire - [Rang " << rang << "]\n"
										<< "===============\n"
										<< "Entrez le numero d'un vehicule une fois pour le selectionner.\n"
										<< "Entrez le a nouveau pour acheter le vehicule.\n"
										<< "===============\n\n";
		Car::listerCars(rang);
		Terminal::get() << "\n" //On separe le blo
										<< "0. Retour\n"
										<< "===============\n"
										<< "Credits: " << Player.credits << "c\n"
										<< "===============\n\n"
										<< "#Car Selectionnee\n"
										<< " |Marque: " << marqueCar << "\n"
										<< " |Modele: " << modeleCar << "\n"
										<< " #Engine" << "\n"
										<< "  |Modele: " << nomEngineCar << "\n"
										<< "  |Vitese: " << vitesseEngineCar << "Km/h\n"
										<< "  |Acceleration: " << accelerationEngineCar << "m/s²\n"
										<< " |Capa. Nitro: " << nitroMaxCar << "L\n"
										<< " |Aerodynamisme: " << aerodynamismeCar << "%\n"
										<< " |Prix: " << prixCar << "c\n\n";
		menu = Menu::askChoice();
		if(menu == 0) //Redirection de l'utilisateur selon son choix grâce a un switch.
		{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
		}
		else if(menu > 0  && menu <= Car::compterCars(rang))
		{
			if(e2tour == 0 || tmenu != menu)
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran	
				Car::infoCar(menu, rang, marqueCar, modeleCar, idEngineCar, nitroMaxCar, aerodynamismeCar, prixCar);
				Engine::infoEngine(idEngineCar, marqueCar, nomEngineCar, vitesseEngineCar, accelerationEngineCar);
				e2tour = 1;
				tmenu = menu;
			}
			else
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Terminal::get() << "/!\\ Attention ! /!\\\n"
												<< "====================\n"
												<< "Credits: " << Player.credits << "c\n"
												<< "====================\n"
												<< "Vous allez acheter le vehicule:\n"
												<< marqueCar << " " << modeleCar << "\n"
												<< "Prix: " << prixCar << "c\n\n";
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
						if(Player.payer(prixCar))
						{
							//Player.setBox(numeroBox, Car::collection.at("Eses")); //TMP
							Player.careerStats.carBought++;
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
	Player.sauvegarderProfile();
}

void menuConcessionaireAchat(Profile& Player)
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
			menuAchatCar('D', Player);
			break;
		case 2:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatCar('C', Player);
			//menuAchatCar('C', Player);
			break;
		case 3:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatCar('B', Player);
			//menuAchatCar('B', Player);
			break;
		case 4:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatCar('A', Player);
			//menuAchatCar('A', Player);
			break;
		case 5:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuAchatCar('S', Player);
			//menuAchatCar('S', Player);
			break;
		default:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Menu::error("Saisie invalide");
			break;
	}
}

void menuVenteCar(Profile& Player, const int& numeroBox)
{
	char verif;
	Car* Car; // = Player.getBox(numeroBox);
	Terminal::get() << Car->getPrix();
	int prixVente = Car->getPrix() * 0.70f;
	std::string sPrixVente;
	std::ostringstream oss;

	oss << prixVente;      // on insere le int dans le stream oss
	sPrixVente = oss.str(); // range le int dans la variable string

	Terminal::get().clearScreen(); //On flushe l'ancien ecran	
	Terminal::get() << "/!\\ Attention ! /!\\\n"
									<< "====================\n"
									<< "Credits: " << Player.credits << "c\n"
									<< "====================\n\n"
									<< "Vous allez vendre le vehicule :" << Car->manufacturer << " " << Car->name << "[Box" << numeroBox << "]\n"
									<< "Prix de vente : " << prixVente << "c\n\n"
									<< "Souhaitez-vous vraiment continuer ? [O/n]\n"
									<< "====================\n";
	verif = getch();
	if(verif == 'o' || verif == 'O')
	{
			Terminal::get().clearScreen();
			Player.credits += Car->getPrix() * 0.5;
			//Player.setBox(numeroBox);
			Menu::msg(Car->name+" vendue avec succes pour "+sPrixVente+"c");
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
	Player.sauvegarderProfile();
}

void menuDifficulte(Profile& Player)
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
			Player.difficulty = 1;
			break;
		case 2:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.difficulty = 2;
			//menuAchatCar('C', Player);
			break;
		case 3:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.difficulty = 3;
			//menuAchatCar('B', Player);
			break;
		case 4:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.difficulty = 4;
			//menuAchatCar('A', Player);
			break;
		case 5:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Player.difficulty = 5;
			//menuAchatCar('S', Player);
			break;
		default:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Menu::error("Saisie invalide");
			break;
	}
	Player.sauvegarderProfile();
}

void menuChangementNomProfile(Profile& Player)
{
	std::string nom;

	//Menu Creation de Profile
	Terminal::get() << "Changement de nom\n"
									<< "===============\n\n"
									<< "Saisissez le nouveau nom du Profile.\n\n"
									<< "0. Annuler\n"
									<< "===============\n"
									<< "Nom: ";
	nom = getString(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	Terminal::get().clearScreen(); //on flushe l'ecran
	if(nom != "0")
	{
		Menu::msg("Le nom de votre Profile est maintenant : \""+nom+"\"");
	}
	Player.sauvegarderProfile();
}