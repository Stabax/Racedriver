
//menusPrincipaux.cpp

#include"menusPrincipaux.h"

void menuRacedriver()
{
	bool quit = false;
	char menu = '0';
	Profil* Player = 0;	//On instancie un joueur non charge

	while(quit != true)
	{
		std::cout << " ________                  ________       _____                    \n";
		std::cout << " ___  __ \\_____ ______________  __ \\_________(_)__   ______________\n";
		std::cout << " __  /_/ /  __ `/  ___/  _ \\_  / / /_  ___/_  /__ | / /  _ \\_  ___/\n";
		std::cout << " _  _, _// /_/ // /__ /  __/  /_/ /_  /   _  / __ |/ //  __/  /    \n";
		std::cout << " /_/ |_| \\__,_/ \\___/ \\___//_____/ /_/    /_/  _____/ \\___//_/     \n";
		std::cout << "[" << GAME_VERSION << "]\n\n";


		//Menu Principal
		std::cout << "Menu principal\n";
		std::cout << "===============\n\n";
		std::cout << "1. Continuer partie\n";
		std::cout << "2. Nouvelle partie\n";
		std::cout << "3. Supprimer profils\n\n";
		std::cout << "4. A Propos\n";
		std::cout << "0. Quitter\n";
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
				menuChargementPartie(Player, quit);
				break;
			case '2':
				clrscreen(); //On flushe l'ancien ecran
				menuCreationPartie(Player, quit);
				break;
			case '3':
				clrscreen(); //On flushe l'ancien ecran
				menuSuppressionPartie();
				break;
			case '4':
				clrscreen(); //On flushe l'ancien ecran
				menuApropos();
				break;
			default:
				clrscreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
	delete Player;
}


void menuJeu(Profil& Player, bool& quitGame)
{
	bool quit = false;
	char menu = '0';
	bool quitVerify = false;
	Profil* PlayerSaved = 0; //On cree un profil temporaire
	std::ostringstream oss;
	std::string numeroProfil;

	clrscreen();
	while(quit != true)
	{
		if(!Player.getSauvegardeAuto())
		{
			std::cout << "Menu Jeu\n";
			std::cout << "===============\n\n";
			std::cout << "1. Course\n\n";
			std::cout << "2. Garage\n";
			std::cout << "3. Concessionaire\n";
			std::cout << "4. Stats\n\n";
			std::cout << "5. Sauvegarder\n";
			std::cout << "6. Options\n";
			std::cout << "7. Menu Principal\n\n";
			std::cout << "0. Quitter\n";
			std::cout << "===============\n";
			std::cout << "Choix ? ";
		}
		else
		{
			std::cout << "Menu Jeu\n";
			std::cout << "===============\n\n";
			std::cout << "1. Course\n\n";
			std::cout << "2. Garage\n";
			std::cout << "3. Concessionaire\n";
			std::cout << "4. Stats\n\n";
			std::cout << "5. Options\n";
			std::cout << "6. Menu Principal\n\n";
			std::cout << "0. Quitter\n";
			std::cout << "===============\n";
			std::cout << "Choix ? ";
		}
		std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
			{
				oss.str("");
				clrscreen(); //On flushe l'ancien ecran
				oss << Player.getNumero();      // on insere le int dans le stream oss
				numeroProfil = oss.str(); // range le int dans la variable numeroSave
				std::ifstream fichier("Saves/Profil"+numeroProfil+".save");

				if(fichier)
				{
					Profil::chargerProfil(Player.getNumero(), PlayerSaved); // On charge le profil du fichier
					if(Player != *PlayerSaved)
					{
						while(quitVerify != true) // Boucle de confirmation
						{
							char verification;
							std::cout << "/!\\ Attention ! /!\\\n";
							std::cout << "====================\n";
							std::cout << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
							std::cout << "====================\n";
							std::cin >> verification;
							videKBuffer();
							if(verification == 'o' || verification == 'O')
							{
								Player.sauvegarderProfil();
								quitVerify = true;
							}
							else if(verification == 'n' || verification == 'N')
							{
								quitVerify = true;
							}
							else
							{
								clrscreen();
								saisieInvalide();
							}
						}
					}
				}
				quit = true;
				quitGame = true;
			}
			break;
			case '1':
				clrscreen(); //On flushe l'ancien ecran
				menuCourse(Player);
				break;
			case '2':
				clrscreen(); //On flushe l'ancien ecran
				menuGarage(Player);
				break;
			case '3':
				clrscreen(); //On flushe l'ancien ecran
				menuConcessionaire(Player);
				break;
			case '4':
				clrscreen(); //On flushe l'ancien ecran
				menuStats(Player);
				break;
			case '5':
				clrscreen(); //On flushe l'ancien ecran
				if(Player.getSauvegardeAuto())
				{
					menuOptions(Player);
				}
				else
				{
					menuSauvegarde(Player);
				}
				clrscreen();
				break;
			case '6':
			{
				clrscreen(); //On flushe l'ancien ecran
				if(Player.getSauvegardeAuto())
				{
					oss.str("");
					clrscreen(); //On flushe l'ancien ecran
					oss << Player.getNumero();      // on insere le int dans le stream oss
					numeroProfil = oss.str(); // range le int dans la variable numeroSave
					std::ifstream fichier("Saves/Profil"+numeroProfil+".save");

					if(fichier)
					{
						Profil::chargerProfil(Player.getNumero(), PlayerSaved); // On charge le profil du fichier
						if(Player != *PlayerSaved)
						{
							while(quitVerify != true) // Boucle de confirmation
							{
								char verification;
								std::cout << "/!\\ Attention ! /!\\\n";
								std::cout << "====================\n";
								std::cout << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
								std::cout << "====================\n";
								std::cin >> verification;
								videKBuffer();
								if(verification == 'o' || verification == 'O')
								{
									Player.sauvegarderProfil();
									quitVerify = true;
								}
								else if(verification == 'n' || verification == 'N')
								{
									quitVerify = true;
								}
								else
								{
									clrscreen();
									saisieInvalide();
								}
							}
						}
					}
					quit = true;
				}
				else
				{
					menuOptions(Player);
				}
				clrscreen();
				break;
			}
			case '7':
			{
				if(Player.getSauvegardeAuto())
				{
					saisieInvalide();
				}
				else
				{
					oss.str("");
					clrscreen(); //On flushe l'ancien ecran
					oss << Player.getNumero();      // on insere le int dans le stream oss
					numeroProfil = oss.str(); // range le int dans la variable numeroSave
					std::ifstream fichier("Saves/Profil"+numeroProfil+".save");

					if(fichier)
					{
						Profil::chargerProfil(Player.getNumero(), PlayerSaved); // On charge le profil du fichier
						if(Player != *PlayerSaved)
						{
							while(quitVerify != true) // Boucle de confirmation
							{
								char verification = 'x';
								std::cout << "/!\\ Attention ! /!\\\n";
								std::cout << "====================\n";
								std::cout << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
								std::cout << "====================\n";
								std::cin >> verification;
								videKBuffer();
								if(verification == 'o' || verification == 'O')
								{
									Player.sauvegarderProfil();
									quitVerify = true;
								}
								else if(verification == 'n' || verification == 'N')
								{
									quitVerify = true;
								}
								else
								{
									clrscreen();
									saisieInvalide();
								}
							}
						}
					}
					quit = true;
				}
				clrscreen();
			}
			break;
			default:
				clrscreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
}


void menuChargementPartie(Profil*& Player, bool& quit)
{
	//Var
	std::string sMenu;
	int menu;
	bool etat; //stocke le resultat du chargement
	std::string nom;

	//Debut
	//Menu Chargement profil
	std::cout << "Charger un Profil: \n";
	std::cout << "===============\n";
	std::cout << "Selectionnez un profil a charger.\n";
	std::cout << "===============\n\n";
	Profil::listerSauvegardes();
	std::cout << "0. Annuler\n";
	std::cout << "===============\n";
	std::cout << "Choix ?";
	std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier


	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			clrscreen(); //On flushe l'ancien ecran
	}
	else if(menu > 0 && menu <= Profil::compterSauvegardes())
	{
				etat = Profil::chargerProfil(menu, Player);
				if(etat == true)
				{
					menuJeu(*Player, quit);//Redirection de l'utilisateur dans le menu de jeu
				}

	}
	else //equivalent de default
	{
		clrscreen(); //On flushe l'ancien ecran
		error("Ce profil n'existe pas");
	}
}


void menuCreationPartie(Profil*& Player, bool& quit)
{
	//Var
	std::string nom;

	//Menu Creation de profil
	std::cout << "Creation de votre Profil\n";
	std::cout << "===============\n\n";
	std::cout << "Saisissez le nom du Profil.\n\n";
	std::cout << "0. Annuler\n";
	std::cout << "===============\n";
	std::cout << "Nom: ";
	std::cin >> nom; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	clrscreen(); //on flushe l'ecran
	if(nom[0] != '0')
	{
		Profil::creerProfil(nom, Player);
		Player->sauvegarderProfil();
		menuJeu(*Player, quit);
	}
}


void menuSuppressionPartie()
{
	//Var
	std::string sMenu;
	char quitVerify = 'x';
	int menu;
	std::string nom;

	//Debut
	//Menu Chargement profil
	std::cout << "Supprimer un Profil: \n";
	std::cout << "===============\n";
	std::cout << "Selectionnez un profil a supprimer.\n";
	std::cout << "===============\n\n";
	Profil::listerSauvegardes();
	std::cout << "0. Annuler\n";
	std::cout << "===============\n";
	std::cout << "Choix ?";
	std::cin >> sMenu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier


	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			clrscreen(); //On flushe l'ancien ecran
	}
	else if(menu > 0 && menu <= Profil::compterSauvegardes())
	{
		for (size_t i = 1; i <= Profil::compterSauvegardes(); i++)
		{
			if(menu == i)
			{
				clrscreen(); //On flushe l'ancien ecran
				while(quitVerify != 'n') // Boucle de confirmation
				{
					std::cout << "/!\\ Attention ! /!\\\n";
					std::cout << "====================\n";
					std::cout << "La partie sera perdue !\n";
					std::cout << "Souhaitez-vous vraiment supprimer Profil" << i << " ? [O/n]\n";
					std::cout << "====================\n";
					std::cin >> quitVerify;
					videKBuffer();
					switch(quitVerify)
					{
						case 'o':
							clrscreen();
							Profil::supprimerProfil(i);
							quitVerify = 'n'; // on quitte la verification
							break;
						case 'O':
							clrscreen();
							Profil::supprimerProfil(i);
							quitVerify = 'n'; // on quitte la verification
							break;
						case 'n':
							clrscreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
							break;
						case 'N':
							clrscreen();
							quitVerify = 'n'; // on quitte la verification
							break;
						default:
							clrscreen();
							saisieInvalide();
							break;
					}
				}
			}
		}
	}
	else //equivalent de default
	{
		clrscreen(); //On flushe l'ancien ecran
		error("Ce profil n'existe pas");
	}
}


void menuApropos()
{
	//avant d'entrer dans le menu on flushe l'ecran
	clrscreen();
	//Menu A propos
	std::cout << "A Propos de\n";
	std::cout << "===============\n\n";
	std::cout << " ________                  ________       _____                    \n";		// Dessin de Credits
	sleep(0.2f);
	std::cout << " ___  __ \\_____ ______________  __ \\_________(_)__   ______________\n";		// En ASCII-ART
	sleep(0.2f);
	std::cout << " __  /_/ /  __ `/  ___/  _ \\_  / / /_  ___/_  /__ | / /  _ \\_  ___/\n";		// Caractere \ et " doublement echappes
	sleep(0.2f);
	std::cout << " _  _, _// /_/ // /__ /  __/  /_/ /_  /   _  / __ |/ //  __/  /    \n";		// Pour palier aux warnings de compilo
	sleep(0.2f);
	std::cout << " /_/ |_| \\__,_/ \\___/ \\___//_____/ /_/    /_/  _____/ \\___//_/     \n\n";	// RACEDRIVER Police Speed from patorjk.com
	sleep(0.5f);
	std::cout << "Racedriver est un jeu de course de voitures en console. \n";
	std::cout << "Ce jeu est developpe en C++ par:\n";
	std::cout << "~Baxlan(contact: Cavalioz@Hotmail.fr)\n";
	std::cout << "~Stalker2106(contact: Stalker2106x@GMail.com)\n\n";
	std::cout << "La version actuelle du programme est [Racedriver " << GAME_VERSION << "]\n\n";
	std::cout << "===============\n";
	std::cout << "Appuyez sur Entree pour retourner au menu principal...\n";
	videKBuffer(); //On appelle le videur de buffer qui va demander la pression d'entree, vu que le buffer est vide. (=pause, en version portable)
	clrscreen();
}
