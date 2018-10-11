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
		Terminal::get() << "Menu Course\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Selectionnez un mode de course.\n";
		Terminal::get() << "===============\n\n";
		Terminal::get() << "1. Carriere\n";
		Terminal::get() << "2. Championnat\n";
		Terminal::get() << "3. Course Libre\n\n";
		Terminal::get() << "0. Retour\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case '1':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Non implementee.");
				break;

			case '2':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCourseChampionnat(Player);
				break;

			case '3':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCourseLibre(Player);
				break;

			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
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
		Terminal::get() << "Menu Garage\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Credits: " << Player.getCredits() << "c\n";
		Terminal::get() << "===============\n\n";
		Terminal::get() << "1. Consulter Garage\n";
		Terminal::get() << "2. Visiter Atelier\n";
		Terminal::get() << "3. Maintenance vehicules\n\n";
		Terminal::get() << "4. Acheter Box \n\n";
		Terminal::get() << "0. Retour\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;
			case '1':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 0);
				break;
			case '2':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 1);
				break;
			case '3':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 3);
				break;
			case '4':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuAcheterBox(Player);
				break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
}

void menuConcessionaire(Profil& Player)
{
	char menu;
	//Menu Principal
	Terminal::get() << "Concessionnaire\n";
	Terminal::get() << "===============\n\n";
	Terminal::get() << "1. Achat\n";
	Terminal::get() << "2. Vente\n\n";
	Terminal::get() << "0. Retour\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Choix ? ";
	menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(menu)
	{
		case '0':
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			break;
		case '1':
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuConcessionaireAchat(Player);
			break;
		case '2':
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuConsulterGarage(Player, 4);
			break;
		default:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			saisieInvalide();
			break;
	}
}

void menuStats(Profil& Player)
{
	Terminal::get() << "Stats du Profil: " << Player.getNom() << "\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "[UUID: " << Player.getUuid() << "]\n\n";
	Terminal::get() << "#Stats Course:\n";
	Terminal::get() << " |Courses effectuees: " << Player.getNbCourses() << "\n";
	Terminal::get() << " |\n";
	Terminal::get() << " |Victoires: " << Player.getVictoires() << "\n";
	Terminal::get() << " |Defaites: " << Player.getDefaites() << "\n";
	Terminal::get() << " |[V/D Ratio: " << Player.getVDRatio() << "]\n";
	Terminal::get() << " |\n";
	Terminal::get() << " |Accidents: " << Player.getAccidents() << "\n\n";
	Terminal::get() << "#Stats Carriere:\n";
	Terminal::get() << " |Credits remportes: " << Player.getCreditsGagnes() << "c\n";
	Terminal::get() << " |\n";
	Terminal::get() << " |Voitures achetees: " << Player.getVoituresAchetees() << "\n\n";
	Terminal::get() << "===============\n";
	Terminal::get() << "Appuyez sur [Entree] pour retourner au menu principal...\n";
	getch();
	Terminal::get().clearScreen();
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
	Terminal::get() << "Sauvegarder votre Progression\n";
	Terminal::get() << "===============\n";
	if(save)
	{
		Terminal::get() << "Vous allez ecraser votre derniere sauvegarde (Profil" << Player.getNumero() << ": \"" << Player.getNom() << "\")\n\n";
	}
	else
	{
		Terminal::get() << "Votre profil va etre sauvegarde sur le disque (Profil" << Player.getNumero() << ": \"" << Player.getNom() << "\")\n\n";
	}
	Terminal::get() << "Etes vous sur ? [O/n]\n";
	Terminal::get() << "===============\n";
	menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
	Terminal::get().clearScreen(); //on flushe l'ecran
	if(menu == 'o' || menu == 'O')
	{
		Terminal::get() << "Sauvegarder votre Progression\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Sauvegarde en cours...\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Veuillez patienter";
		sleep(0.4f);
		Player.sauvegarderProfil();
		Terminal::get().clearScreen();
		Terminal::get() << "Sauvegarder votre Progression\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Partie Sauvegardee !\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Appuyez sur Entree pour retourner au menu principal...\n";
		getch();
		Terminal::get().clearScreen();
	}
	else
	{
		Terminal::get() << "Sauvegarder votre Progression\n";
		Terminal::get() << "===============\n\n";
		Terminal::get() << "Sauvegarde annulee.\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Appuyez sur Entree pour retourner au menu principal...\n";
		getch();
		Terminal::get().clearScreen();
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
		Terminal::get() << "Options " << Player.getNom() << "\n";
		Terminal::get() << "===============\n\n";
		Terminal::get() << "1. Sauvegarde auto [" << saveAuto << "]\n";
		Terminal::get() << "2. Difficulte ["<< Player.getDifficulteString() <<"]\n";
		Terminal::get() << "3. Raccourcis menus [OFF]\n";
		Terminal::get() << "4. Changer le nom du profil\n\n";
		Terminal::get() << "0. Retour\n";
		Terminal::get() << "===============\n";
		Terminal::get() << "Choix ? ";
		menu = getch(); // l'utilisateur entre le menu qu'il souhaite ouvrir
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case '1':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
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
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuDifficulte(Player);
				break;
			case '3':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("non implemente");
				break;
			case '4':
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuChangementNomProfil(Player);
				break;

			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}