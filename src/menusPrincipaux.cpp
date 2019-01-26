//menusPrincipaux.cpp
#ifdef __GNUC__
#include <unistd.h>
#endif
#ifdef _MSC_VER
#include <windows.h>
#endif
#include "Menu.hh"
#include "menusPrincipaux.hh"

void menuRacedriver()
{
	bool quit = false;

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
										<< "3. A Propos\n"
										<< "0. Quitter\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				quit = true;
				break;
			case 1:
				menuChargementPartie();
				break;
			case 2:
				menuCreationPartie();
				break;
			case 3:
				menuApropos();
				break;
			default:
				Menu::error("Saisie invalide");
				break;
		}
	}
}

void menuJeu()
{
	bool quit = false;
	std::ostringstream oss;
	std::string numeroProfile;

	while(!quit)
	{
	  Terminal::get().clearScreen();
		Terminal::get() << "Menu Jeu\n"
										<< "===============\n\n"
										<< "1. Course\n"
										<< "2. Garage\n"
										<< "3. Stats\n\n"
										<< "4. Options\n\n"
										<< "0. Quitter\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				Profile::active->save();
				quit = true;
			break;
			case 1:
				menuCourse();
				break;
			case 2:
				menuGarages();
				break;
			case 3:
				menuStatss();
				break;
			case 4:
				menuOptions();
				break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
}

void menuChargementPartie()
{
	int choice;
	std::vector<std::string> saves = DataFile::getFolderContents("./Data/Saves/", ".json");
	saves.insert(saves.begin(), ""); //Dummy to keep index true
	std::string nom;
	Terminal::get().clearScreen(); //On flushe l'ancien ecran
	//Menu Chargement Profile
	Terminal::get() << "Charger un Profile: \n"
									<< "===============\n"
									<< "Selectionnez un Profile a charger.\n"
									<< "===============\n\n";
	Profile::displaySavesList();
	Terminal::get() << "0. Retour\n";
	choice = Menu::askChoice();
	if (choice > 0 && choice < saves.size())
	{
		Profile::load(saves[choice]);
		menuJeu();
	}
}

void menuCreationPartie()
{
	//Var
	std::string nom;

	//Menu Creation de Profile
	Terminal::get().clearScreen(); //On flushe l'ancien ecran
	Terminal::get() << "Creation de votre Profile\n"
									<< "===============\n\n"
									<< "Saisissez le nom du Profile.\n\n"
									<< "0. Annuler\n"
									<< "===============\n"
									<< "Nom: ";
	nom = getString(); // l'utilisateur entre son nom
	if(nom[0] != 0)
	{
		Profile::create(nom);
		Profile::active->save();
		menuJeu();
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