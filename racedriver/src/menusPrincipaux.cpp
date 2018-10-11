//menusPrincipaux.cpp
#include <unistd.h>
#include"menusPrincipaux.hh"

void menuRacedriver()
{
	bool quit = false;
	char menu = '0';
	Profil* Player = 0;	//On instancie un joueur non charge

	while(quit != true)
	{
		Game::instance->printASCIILogo();
		Game::instance->getTerm() << "[" << GAME_VERSION << "]\n\n";
		//Menu Principal
		Game::instance->getTerm() << "Menu principal\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "1. Continuer partie\n";
		Game::instance->getTerm() << "2. Nouvelle partie\n";
		Game::instance->getTerm() << "3. Supprimer profils\n\n";
		Game::instance->getTerm() << "4. A Propos\n";
		Game::instance->getTerm() << "0. Quitter\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = true;
				break;
			case '1':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuChargementPartie(Player, quit);
				break;
			case '2':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuCreationPartie(Player, quit);
				break;
			case '3':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuSuppressionPartie();
				break;
			case '4':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuApropos();
				break;
			default:
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
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

	Game::instance->getTerm().clearScreen();
	while(quit != true)
	{
		if(!Player.getSauvegardeAuto())
		{
			Game::instance->getTerm() << "Menu Jeu\n";
			Game::instance->getTerm() << "===============\n\n";
			Game::instance->getTerm() << "1. Course\n\n";
			Game::instance->getTerm() << "2. Garage\n";
			Game::instance->getTerm() << "3. Concessionaire\n";
			Game::instance->getTerm() << "4. Stats\n\n";
			Game::instance->getTerm() << "5. Sauvegarder\n";
			Game::instance->getTerm() << "6. Options\n";
			Game::instance->getTerm() << "7. Menu Principal\n\n";
			Game::instance->getTerm() << "0. Quitter\n";
			Game::instance->getTerm() << "===============\n";
			Game::instance->getTerm() << "Choix ? ";
		}
		else
		{
			Game::instance->getTerm() << "Menu Jeu\n";
			Game::instance->getTerm() << "===============\n\n";
			Game::instance->getTerm() << "1. Course\n\n";
			Game::instance->getTerm() << "2. Garage\n";
			Game::instance->getTerm() << "3. Concessionaire\n";
			Game::instance->getTerm() << "4. Stats\n\n";
			Game::instance->getTerm() << "5. Options\n";
			Game::instance->getTerm() << "6. Menu Principal\n\n";
			Game::instance->getTerm() << "0. Quitter\n";
			Game::instance->getTerm() << "===============\n";
			Game::instance->getTerm() << "Choix ? ";
		}
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
			{
				oss.str("");
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
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
							Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
							Game::instance->getTerm() << "====================\n";
							Game::instance->getTerm() << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
							Game::instance->getTerm() << "====================\n";
							verification = getch();
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
								Game::instance->getTerm().clearScreen();
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
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuCourse(Player);
				break;
			case '2':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuGarage(Player);
				break;
			case '3':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuConcessionaire(Player);
				break;
			case '4':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuStats(Player);
				break;
			case '5':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				if(Player.getSauvegardeAuto())
				{
					menuOptions(Player);
				}
				else
				{
					menuSauvegarde(Player);
				}
				Game::instance->getTerm().clearScreen();
				break;
			case '6':
			{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				if(Player.getSauvegardeAuto())
				{
					oss.str("");
					Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
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
								Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
								Game::instance->getTerm() << "====================\n";
								Game::instance->getTerm() << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
								Game::instance->getTerm() << "====================\n";
								verification = getch();
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
									Game::instance->getTerm().clearScreen();
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
				Game::instance->getTerm().clearScreen();
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
					Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
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
								Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
								Game::instance->getTerm() << "====================\n";
								Game::instance->getTerm() << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
								Game::instance->getTerm() << "====================\n";
								verification = getch();
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
									Game::instance->getTerm().clearScreen();
									saisieInvalide();
								}
							}
						}
					}
					quit = true;
				}
				Game::instance->getTerm().clearScreen();
			}
			break;
			default:
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
}

void menuChargementPartie(Profil*& Player, bool& quit)
{
	std::string sMenu;
	int menu;
	bool etat; //stocke le resultat du chargement
	std::string nom;
	//Menu Chargement profil
	Game::instance->getTerm() << "Charger un Profil: \n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Selectionnez un profil a charger.\n";
	Game::instance->getTerm() << "===============\n\n";
	Profil::listerSauvegardes();
	Game::instance->getTerm() << "0. Annuler\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Choix ?";
	menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
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
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
		error("Ce profil n'existe pas");
	}
}

void menuCreationPartie(Profil*& Player, bool& quit)
{
	//Var
	std::string nom;

	//Menu Creation de profil
	Game::instance->getTerm() << "Creation de votre Profil\n";
	Game::instance->getTerm() << "===============\n\n";
	Game::instance->getTerm() << "Saisissez le nom du Profil.\n\n";
	Game::instance->getTerm() << "0. Annuler\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Nom: ";
	std::getline(std::cin, nom); // l'utilisateur entre son nom
	Game::instance->getTerm().clearScreen(); //on flushe l'ecran
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
	Game::instance->getTerm() << "Supprimer un Profil: \n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Selectionnez un profil a supprimer.\n";
	Game::instance->getTerm() << "===============\n\n";
	Profil::listerSauvegardes();
	Game::instance->getTerm() << "0. Annuler\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Choix ?";
	std::getline(std::cin, sMenu); // l'utilisateur entre le menu qu'il souhaite ouvrir
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
	}
	else if(menu > 0 && menu <= Profil::compterSauvegardes())
	{
		for (size_t i = 1; i <= Profil::compterSauvegardes(); i++)
		{
			if(menu == i)
			{
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				while(quitVerify != 'n') // Boucle de confirmation
				{
					Game::instance->getTerm() << "/!\\ Attention ! /!\\\n";
					Game::instance->getTerm() << "====================\n";
					Game::instance->getTerm() << "La partie sera perdue !\n";
					Game::instance->getTerm() << "Souhaitez-vous vraiment supprimer Profil" << i << " ? [O/n]\n";
					Game::instance->getTerm() << "====================\n";
					quitVerify = getch(); // l'utilisateur confirme
					switch(quitVerify)
					{
						case 'o':
							Game::instance->getTerm().clearScreen();
							Profil::supprimerProfil(i);
							quitVerify = 'n'; // on quitte la verification
							break;
						case 'O':
							Game::instance->getTerm().clearScreen();
							Profil::supprimerProfil(i);
							quitVerify = 'n'; // on quitte la verification
							break;
						case 'n':
							Game::instance->getTerm().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
							break;
						case 'N':
							Game::instance->getTerm().clearScreen();
							quitVerify = 'n'; // on quitte la verification
							break;
						default:
							Game::instance->getTerm().clearScreen();
							saisieInvalide();
							break;
					}
				}
			}
		}
	}
	else //equivalent de default
	{
		Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
		error("Ce profil n'existe pas");
	}
}

void menuApropos()
{
	//avant d'entrer dans le menu on flushe l'ecran
	Game::instance->getTerm().clearScreen();
	//Menu A propos
	Game::instance->getTerm() << "A Propos de\n";
	Game::instance->getTerm() << "===============\n\n";
	Game::instance->getTerm() << " ________                  ________       _____                    \n";		// Dessin de Credits
	sleep(0.2f);
	Game::instance->getTerm() << " ___  __ \\_____ ______________  __ \\_________(_)__   ______________\n";		// En ASCII-ART
	sleep(0.2f);
	Game::instance->getTerm() << " __  /_/ /  __ `/  ___/  _ \\_  / / /_  ___/_  /__ | / /  _ \\_  ___/\n";		// Caractere \ et " doublement echappes
	sleep(0.2f);
	Game::instance->getTerm() << " _  _, _// /_/ // /__ /  __/  /_/ /_  /   _  / __ |/ //  __/  /    \n";		// Pour palier aux warnings de compilo
	sleep(0.2f);
	Game::instance->getTerm() << " /_/ |_| \\__,_/ \\___/ \\___//_____/ /_/    /_/  _____/ \\___//_/     \n\n";	// RACEDRIVER Police Speed from patorjk.com
	sleep(0.5f);
	Game::instance->getTerm() << "Racedriver est un jeu de course de voitures en console. \n";
	Game::instance->getTerm() << "Ce jeu est developpe en C++ par:\n";
	Game::instance->getTerm() << "~Baxlan(contact: Cavalioz@Hotmail.fr)\n";
	Game::instance->getTerm() << "~Stalker2106(contact: Stalker2106x@GMail.com)\n\n";
	Game::instance->getTerm() << "La version actuelle du programme est [Racedriver " << GAME_VERSION << "]\n\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Appuyez sur Entree pour retourner au menu principal...\n";
	getch(); //On appelle le videur de buffer qui va demander la pression d'entree, vu que le buffer est vide. (=pause, en version portable)
	Game::instance->getTerm().clearScreen();
}