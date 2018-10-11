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
		Terminal::get() << "[" << GAME_VERSION << "]\n\n";
		//Menu Principal
		Terminal::get() << "Menu principal\n";
		Terminal::get() << "===============\n\n";
		Terminal::get() << "1. Continuer partie\n";
		Terminal::get() << "2. Nouvelle partie\n";
		Terminal::get() << "3. Supprimer profils\n\n";
		Terminal::get() << "4. A Propos\n";
		Terminal::get() << "0. Quitter\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true;
				break;
			case '1':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuChargementPartie(Player, quit);
				break;
			case '2':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCreationPartie(Player, quit);
				break;
			case '3':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuSuppressionPartie();
				break;
			case '4':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuApropos();
				break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
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

	Terminal::get().clearScreen();
	while(quit != true)
	{
		if(!Player.getSauvegardeAuto())
		{
			Terminal::get() << "Menu Jeu\n";
			Terminal::get() << "===============\n\n";
			Terminal::get() << "1. Course\n\n";
			Terminal::get() << "2. Garage\n";
			Terminal::get() << "3. Concessionaire\n";
			Terminal::get() << "4. Stats\n\n";
			Terminal::get() << "5. Sauvegarder\n";
			Terminal::get() << "6. Options\n";
			Terminal::get() << "7. Menu Principal\n\n";
			Terminal::get() << "0. Quitter\n";
			Terminal::get() << "===============\n";
			Terminal::get() << "Choix ? ";
		}
		else
		{
			Terminal::get() << "Menu Jeu\n";
			Terminal::get() << "===============\n\n";
			Terminal::get() << "1. Course\n\n";
			Terminal::get() << "2. Garage\n";
			Terminal::get() << "3. Concessionaire\n";
			Terminal::get() << "4. Stats\n\n";
			Terminal::get() << "5. Options\n";
			Terminal::get() << "6. Menu Principal\n\n";
			Terminal::get() << "0. Quitter\n";
			Terminal::get() << "===============\n";
			Terminal::get() << "Choix ? ";
		}
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
			{
				oss.str("");
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
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
							Terminal::get() << "/!\\ Attention ! /!\\\n";
							Terminal::get() << "====================\n";
							Terminal::get() << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
							Terminal::get() << "====================\n";
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
								Terminal::get().clearScreen();
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
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCourse(Player);
				break;
			case '2':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuGarage(Player);
				break;
			case '3':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConcessionaire(Player);
				break;
			case '4':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuStats(Player);
				break;
			case '5':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				if(Player.getSauvegardeAuto())
				{
					menuOptions(Player);
				}
				else
				{
					menuSauvegarde(Player);
				}
				Terminal::get().clearScreen();
				break;
			case '6':
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				if(Player.getSauvegardeAuto())
				{
					oss.str("");
					Terminal::get().clearScreen(); //On flushe l'ancien ecran
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
								Terminal::get() << "/!\\ Attention ! /!\\\n";
								Terminal::get() << "====================\n";
								Terminal::get() << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
								Terminal::get() << "====================\n";
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
									Terminal::get().clearScreen();
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
				Terminal::get().clearScreen();
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
					Terminal::get().clearScreen(); //On flushe l'ancien ecran
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
								Terminal::get() << "/!\\ Attention ! /!\\\n";
								Terminal::get() << "====================\n";
								Terminal::get() << "Voulez vous sauvegarder votre partie ? [O/n]\n\n";
								Terminal::get() << "====================\n";
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
									Terminal::get().clearScreen();
									saisieInvalide();
								}
							}
						}
					}
					quit = true;
				}
				Terminal::get().clearScreen();
			}
			break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
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
	Terminal::get() << "Charger un Profil: \n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Selectionnez un profil a charger.\n";
	Terminal::get() << "===============\n\n";
	Profil::listerSauvegardes();
	Terminal::get() << "0. Annuler\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Choix ?";
	menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
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
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		error("Ce profil n'existe pas");
	}
}

void menuCreationPartie(Profil*& Player, bool& quit)
{
	//Var
	std::string nom;

	//Menu Creation de profil
	Terminal::get() << "Creation de votre Profil\n";
	Terminal::get() << "===============\n\n";
	Terminal::get() << "Saisissez le nom du Profil.\n\n";
	Terminal::get() << "0. Annuler\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Nom: ";
	nom = getString(); // l'utilisateur entre son nom
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
	Terminal::get() << "Supprimer un Profil: \n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Selectionnez un profil a supprimer.\n";
	Terminal::get() << "===============\n\n";
	Profil::listerSauvegardes();
	Terminal::get() << "0. Annuler\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Choix ?";
	sMenu = getString(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	std::istringstream iss;

	iss.str(sMenu); // On extrait la taille du circuit et on le stocke dans la variable de conversion "iss1".
	iss >> menu; // on convertit la string recuperee plus haut en entier
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
	}
	else if(menu > 0 && menu <= Profil::compterSauvegardes())
	{
		for (size_t i = 1; i <= Profil::compterSauvegardes(); i++)
		{
			if(menu == i)
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				while(quitVerify != 'n') // Boucle de confirmation
				{
					Terminal::get() << "/!\\ Attention ! /!\\\n";
					Terminal::get() << "====================\n";
					Terminal::get() << "La partie sera perdue !\n";
					Terminal::get() << "Souhaitez-vous vraiment supprimer Profil" << i << " ? [O/n]\n";
					Terminal::get() << "====================\n";
					quitVerify = getch(); // l'utilisateur confirme
					switch(quitVerify)
					{
						case 'o':
							Terminal::get().clearScreen();
							Profil::supprimerProfil(i);
							quitVerify = 'n'; // on quitte la verification
							break;
						case 'O':
							Terminal::get().clearScreen();
							Profil::supprimerProfil(i);
							quitVerify = 'n'; // on quitte la verification
							break;
						case 'n':
							Terminal::get().clearScreen(); // la variable de verification prend la valeur n donc on sort de la verification, mais quit vaut faux
							break;
						case 'N':
							Terminal::get().clearScreen();
							quitVerify = 'n'; // on quitte la verification
							break;
						default:
							Terminal::get().clearScreen();
							saisieInvalide();
							break;
					}
				}
			}
		}
	}
	else //equivalent de default
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		error("Ce profil n'existe pas");
	}
}

void menuApropos()
{
	//avant d'entrer dans le menu on flushe l'ecran
	Terminal::get().clearScreen();
	//Menu A propos
	Terminal::get() << "A Propos de\n";
	Terminal::get() << "===============\n\n";
	Terminal::get() << " ________                  ________       _____                    \n";		// Dessin de Credits
	sleep(0.2f);
	Terminal::get() << " ___  __ \\_____ ______________  __ \\_________(_)__   ______________\n";		// En ASCII-ART
	sleep(0.2f);
	Terminal::get() << " __  /_/ /  __ `/  ___/  _ \\_  / / /_  ___/_  /__ | / /  _ \\_  ___/\n";		// Caractere \ et " doublement echappes
	sleep(0.2f);
	Terminal::get() << " _  _, _// /_/ // /__ /  __/  /_/ /_  /   _  / __ |/ //  __/  /    \n";		// Pour palier aux warnings de compilo
	sleep(0.2f);
	Terminal::get() << " /_/ |_| \\__,_/ \\___/ \\___//_____/ /_/    /_/  _____/ \\___//_/     \n\n";	// RACEDRIVER Police Speed from patorjk.com
	sleep(0.5f);
	Terminal::get() << "Racedriver est un jeu de course de voitures en console. \n";
	Terminal::get() << "Ce jeu est developpe en C++ par:\n";
	Terminal::get() << "~Baxlan(contact: Cavalioz@Hotmail.fr)\n";
	Terminal::get() << "~Stalker2106(contact: Stalker2106x@GMail.com)\n\n";
	Terminal::get() << "La version actuelle du programme est [Racedriver " << GAME_VERSION << "]\n\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Appuyez sur Entree pour retourner au menu principal...\n";
	getch(); //On appelle le videur de buffer qui va demander la pression d'entree, vu que le buffer est vide. (=pause, en version portable)
	Terminal::get().clearScreen();
}