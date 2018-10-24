//menusPrincipaux.cpp
#include <unistd.h>
#include "Menu.hh"
#include "menusPrincipaux.hh"

void menuRacedriver()
{
	bool quit = false;
	Profile* Player = 0;	//On instancie un joueur non charge

	while(quit != true)
	{
		Terminal::get().clearScreen();
		Game::instance->printASCIILogo();
		Terminal::get() << "[" << GAME_VERSION << "]\n\n";
		//Menu Principal
		Terminal::get() << "Menu principal\n"
										<< "===============\n\n"
										<< "1. Continuer partie\n"
										<< "2. Nouvelle partie\n"
										<< "3. Supprimer Profiles\n\n"
										<< "4. A Propos\n"
										<< "0. Quitter\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true;
				break;
			case 1:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuChargementPartie(Player, quit);
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCreationPartie(Player, quit);
				break;
			case 3:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuSuppressionPartie();
				break;
			case 4:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuApropos();
				break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
	delete Player;
}

void menuJeu(Profile& Player, bool& quitGame)
{
	bool quit = false;
	Profile* PlayerSaved = 0; //On cree un Profile temporaire
	std::ostringstream oss;
	std::string numeroProfile;

	Terminal::get().clearScreen();
	while(quit != true)
	{
		Terminal::get() << "Menu Jeu\n"
										<< "===============\n\n"
										<< "1. Course\n\n"
										<< "2. Garage\n"
										<< "3. Concessionaire\n"
										<< "4. Stats\n\n";
		Terminal::get() << "5. Sauvegarder\n"
										<< "6. Options\n"
										<< "7. Menu Principal\n\n"
										<< "0. Quitter\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				std::ifstream fichier("Saves/Profile.save");

				if(fichier)
				{
					//Profile::chargerProfile(Player.getNumero(), PlayerSaved); // On charge le Profile du fichier
					Terminal::get() << "/!\\ Attention ! /!\\\n"
													<< "====================\n"
													<< "La partie va etre sauvegardee\n";
					if(Menu::askConfirmation())
					{
						Player.sauvegarderProfile();
					}
				}
				quit = true;
				quitGame = true;
			}
			break;
			case 1:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCourse(Player);
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuGarage(Player);
				break;
			case 3:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConcessionaire(Player);
				break;
			case 4:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuStats(Player);
				break;
			case 5:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuOptions(Player);
				Terminal::get().clearScreen();
				break;
			case 6:
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				std::ifstream fichier("Saves/Profile.save");

				if(fichier)
				{
					//Profile::chargerProfile(Player.getNumero(), PlayerSaved); // On charge le Profile du fichier
					Terminal::get() << "/!\\ Attention ! /!\\\n"
												<< "====================\n"
												<< "La partie va etre sauvegardee\n";
					if(Menu::askConfirmation())
					{
						Player.sauvegarderProfile();
					}
				}
				quit = true;
				Terminal::get().clearScreen();
				break;
			}
			case 7:
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				std::ifstream fichier("Saves/Profile.save");

				if(fichier)
				{
					//Profile::chargerProfile(Player.getNumero(), PlayerSaved); // On charge le Profile du fichier
					Terminal::get() << "/!\\ Attention ! /!\\\n"
												<< "====================\n"
												<< "La partie va etre sauvegardee\n";
					if(Menu::askConfirmation())
					{
						Player.sauvegarderProfile();
					}
				}
				quit = true;
			}
			break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
}

void menuChargementPartie(Profile*& Player, bool& quit)
{
	std::string sMenu;
	int menu;
	bool etat; //stocke le resultat du chargement
	std::string nom;
	//Menu Chargement Profile
	Terminal::get() << "Charger un Profile: \n"
									<< "===============\n"
									<< "Selectionnez un Profile a charger.\n"
									<< "===============\n\n";
	Profile::listerSauvegardes();
	Terminal::get() << "0. Annuler\n";
	menu = Menu::askChoice();
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
	}
	else if(menu > 0 && menu <= Profile::compterSauvegardes())
	{
				etat = Profile::chargerProfile(menu, Player);
				if(etat == true)
				{
					menuJeu(*Player, quit);//Redirection de l'utilisateur dans le menu de jeu
				}
	}
	else //equivalent de default
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		Menu::error("Ce Profile n'existe pas");
	}
}

void menuCreationPartie(Profile*& Player, bool& quit)
{
	//Var
	std::string nom;

	//Menu Creation de Profile
	Terminal::get() << "Creation de votre Profile\n"
									<< "===============\n\n"
									<< "Saisissez le nom du Profile.\n\n"
									<< "0. Annuler\n"
									<< "===============\n"
									<< "Nom: ";
	nom = getString(); // l'utilisateur entre son nom
	if(nom[0] != 0)
	{
		Profile::creerProfile(nom, Player);
		Player->sauvegarderProfile();
		menuJeu(*Player, quit);
	}
}

void menuSuppressionPartie()
{
	//Var
	char quitVerify = 'x';
	int menu;
	std::string nom;

	//Debut
	//Menu Chargement Profile
	Terminal::get() << "Supprimer un Profile: \n"
									<< "===============\n"
									<< "Selectionnez un Profile a supprimer.\n"
									<< "===============\n\n";
	Profile::listerSauvegardes();
	Terminal::get() << "0. Annuler\n";
	menu = Menu::askChoice(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	if(menu == 0)
	{
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
	}
	else if(menu > 0 && menu <= Profile::compterSauvegardes())
	{
		for (int i = 1; i <= Profile::compterSauvegardes(); i++)
		{
			if(menu == i)
			{
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				while(quitVerify != 'n') // Boucle de confirmation
				{
					Terminal::get() << "/!\\ Attention ! /!\\\n"
													<< "====================\n"
													<< "La partie sera perdue !\n"
													<< "Souhaitez-vous vraiment supprimer Profile" << i << " ? [O/n]\n"
													<< "====================\n";
					quitVerify = getch(); // l'utilisateur confirme
					switch(quitVerify)
					{
						case 'o':
							Terminal::get().clearScreen();
							Profile::supprimerProfile(i);
							quitVerify = 'n'; // on quitte la verification
							break;
						case 'O':
							Terminal::get().clearScreen();
							Profile::supprimerProfile(i);
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
							Menu::error("Saisie invalide");
							break;
					}
				}
			}
		}
	}
	else //equivalent de default
	{
		Terminal::get().clearScreen(); //On flushe l'ancien ecran
		Menu::error("Ce Profile n'existe pas");
	}
}

void menuApropos()
{
	//avant d'entrer dans le menu on flushe l'ecran
	Terminal::get().clearScreen();
	//Menu A propos
	Terminal::get() << "A Propos de\n";
	Terminal::get() << "===============\n\n";
	Game::instance->printASCIILogo();
	Terminal::get() << "Racedriver est un jeu de course de voitures en console. \n";
	Terminal::get() << "Ce jeu est developpe en C++ par:\n";
	Terminal::get() << "~Baxlan(contact: Cavalioz@Hotmail.fr)\n";
	Terminal::get() << "~Stalker2106(contact: Stalker2106x@GMail.com)\n\n";
	Terminal::get() << "La version actuelle du programme est [Racedriver " << GAME_VERSION << "]\n\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Appuyez sur Entree pour retourner au menu principal...\n";
	getch(); //On appelle le videur de buffer qui va demander la pression d'entree, vu que le buffer est vide. (=pause, en version portable)
}