//menus.cpp
#include <unistd.h>
#include "menus.hh"

void menuCourse(Profil& Player)
{
	char menu;
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Game::instance->getTerm() << "Menu Course\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Selectionnez un mode de course.\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "1. Carriere\n";
		Game::instance->getTerm() << "2. Championnat\n";
		Game::instance->getTerm() << "3. Course Libre\n\n";
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case '1':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				error("Non implementee.");
				break;

			case '2':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuCourseChampionnat(Player);
				break;

			case '3':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuCourseLibre(Player);
				break;

			default:
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
}

void menuGarage(Profil& Player)
{
	char menu;
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Game::instance->getTerm() << "Menu Garage\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Credits: " << Player.getCredits() << "c\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "1. Consulter Garage\n";
		Game::instance->getTerm() << "2. Visiter Atelier\n";
		Game::instance->getTerm() << "3. Maintenance vehicules\n\n";
		Game::instance->getTerm() << "4. Acheter Box \n\n";
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;
			case '1':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 0);
				break;
			case '2':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 1);
				break;
			case '3':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 3);
				break;
			case '4':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuAcheterBox(Player);
				break;
			default:
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
}

void menuConcessionaire(Profil& Player)
{
	char menu;
	//Menu Principal
	Game::instance->getTerm() << "Concessionnaire\n";
	Game::instance->getTerm() << "===============\n\n";
	Game::instance->getTerm() << "1. Achat\n";
	Game::instance->getTerm() << "2. Vente\n\n";
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
			menuConcessionaireAchat(Player);
			break;
		case '2':
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			menuConsulterGarage(Player, 4);
			break;
		default:
			Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
			saisieInvalide();
			break;
	}
}

void menuStats(Profil& Player)
{
	Game::instance->getTerm() << "Stats du Profil: " << Player.getNom() << "\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "[UUID: " << Player.getUuid() << "]\n\n";
	Game::instance->getTerm() << "#Stats Course:\n";
	Game::instance->getTerm() << " |Courses effectuees: " << Player.getNbCourses() << "\n";
	Game::instance->getTerm() << " |\n";
	Game::instance->getTerm() << " |Victoires: " << Player.getVictoires() << "\n";
	Game::instance->getTerm() << " |Defaites: " << Player.getDefaites() << "\n";
	Game::instance->getTerm() << " |[V/D Ratio: " << Player.getVDRatio() << "]\n";
	Game::instance->getTerm() << " |\n";
	Game::instance->getTerm() << " |Accidents: " << Player.getAccidents() << "\n\n";
	Game::instance->getTerm() << "#Stats Carriere:\n";
	Game::instance->getTerm() << " |Credits remportes: " << Player.getCreditsGagnes() << "c\n";
	Game::instance->getTerm() << " |\n";
	Game::instance->getTerm() << " |Voitures achetees: " << Player.getVoituresAchetees() << "\n\n";
	Game::instance->getTerm() << "===============\n";
	Game::instance->getTerm() << "Appuyez sur [Entree] pour retourner au menu principal...\n";
	getch();
	Game::instance->getTerm().clearScreen();
}

void menuSauvegarde(Profil& Player)
{
	char menu;
	std::ostringstream oss;
	oss << Player.getNumero();
	std::string numeroSave = oss.str();

	std::string cheminFichier = "Saves/Profil"+numeroSave+".save";

	std::ifstream save(cheminFichier.c_str());

	//Menu de sauvegarde de profil
	Game::instance->getTerm() << "Sauvegarder votre Progression\n";
	Game::instance->getTerm() << "===============\n";
	if(save)
	{
		Game::instance->getTerm() << "Vous allez ecraser votre derniere sauvegarde (Profil" << Player.getNumero() << ": \"" << Player.getNom() << "\")\n\n";
	}
	else
	{
		Game::instance->getTerm() << "Votre profil va etre sauvegarde sur le disque (Profil" << Player.getNumero() << ": \"" << Player.getNom() << "\")\n\n";
	}
	Game::instance->getTerm() << "Etes vous sur ? [O/n]\n";
	Game::instance->getTerm() << "===============\n";
	menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	Game::instance->getTerm().clearScreen(); //on flushe l'ecran
	if(menu == 'o' || menu == 'O')
	{
		Game::instance->getTerm() << "Sauvegarder votre Progression\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Sauvegarde en cours...\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Veuillez patienter";
		sleep(0.4f);
		Player.sauvegarderProfil();
		Game::instance->getTerm().clearScreen();
		Game::instance->getTerm() << "Sauvegarder votre Progression\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Partie Sauvegardee !\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Appuyez sur Entree pour retourner au menu principal...\n";
		getch();
		Game::instance->getTerm().clearScreen();
	}
	else
	{
		Game::instance->getTerm() << "Sauvegarder votre Progression\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "Sauvegarde annulee.\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Appuyez sur Entree pour retourner au menu principal...\n";
		getch();
		Game::instance->getTerm().clearScreen();
	}
}

void menuOptions(Profil& Player)
{
	char menu;
	bool quit = false;
	std::string saveAuto;
	while(quit != true)
	{
		//Menu Principal
		saveAuto = Player.getSauvegardeAuto() ? "ON" : "OFF";
		Game::instance->getTerm() << "Options " << Player.getNom() << "\n";
		Game::instance->getTerm() << "===============\n\n";
		Game::instance->getTerm() << "1. Sauvegarde auto [" << saveAuto << "]\n";
		Game::instance->getTerm() << "2. Difficulte ["<< Player.getDifficulteString() <<"]\n";
		Game::instance->getTerm() << "3. Raccourcis menus [OFF]\n";
		Game::instance->getTerm() << "4. Changer le nom du profil\n\n";
		Game::instance->getTerm() << "0. Retour\n";
		Game::instance->getTerm() << "===============\n";
		Game::instance->getTerm() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case '1':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				if(Player.getSauvegardeAuto())
				{
					Player.setSauvegardeAuto(false);
				}
				else
				{
					Player.setSauvegardeAuto(true);
				}
				break;
			case '2':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuDifficulte(Player);
				break;
			case '3':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				error("non implemente");
				break;
			case '4':
				Game::instance->getTerm().clearScreen(); //On flushe l'ancien ecran
				menuChangementNomProfil(Player);
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