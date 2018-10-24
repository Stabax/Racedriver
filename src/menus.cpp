//menus.cpp
#include <unistd.h>
#include "Menu.hh"
#include "menus.hh"

void menuCourse(Profile& Player)
{
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Menu Course\n"
										<< "===============\n"
										<< "Selectionnez un mode de course.\n"
										<< "===============\n\n"
										<< "1. Carriere\n"
										<< "2. Championnat\n"
										<< "3. Course Libre\n\n"
										<< "0. Retour\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case 1:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Non implementee.");
				break;

			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCourseChampionnat(Player);
				break;

			case 3:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuCourseLibre(Player);
				break;

			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
}

void menuGarage(Profile& Player)
{
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Terminal::get() << "Menu Garage\n"
										<< "===============\n"
										<< "Credits: " << Player.credits << "c\n"
										<< "===============\n\n"
										<< "1. Consulter Garage\n"
										<< "2. Visiter Atelier\n"
										<< "3. Maintenance vehicules\n\n"
										<< "4. Acheter Box \n\n"
										<< "0. Retour\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;
			case 1:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 0);
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 1);
				break;
			case 3:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 3);
				break;
			case 4:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuAcheterBox(Player);
				break;
			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
}

void menuConcessionaire(Profile& Player)
{
	//Menu Principal
	Terminal::get() << "Concessionnaire\n"
									<< "===============\n\n"
									<< "1. Achat\n"
									<< "2. Vente\n\n"
									<< "0. Retour\n";
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(Menu::askChoice())
	{
		case 0:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			break;
		case 1:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuConcessionaireAchat(Player);
			break;
		case 2:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			menuConsulterGarage(Player, 4);
			break;
		default:
			Terminal::get().clearScreen(); //On flushe l'ancien ecran
			Menu::error("Saisie invalide");
			break;
	}
}

void menuStats(Profile& Player)
{
	Terminal::get() << "Stats du Profile: " << Player.name << "\n"
									<< "===============\n"
									<< "#Stats Course:\n"
									<< " |Courses effectuees: " << Player.careerStats.races << "\n"
									<< " |\n"
									<< " |Victoires: " << Player.careerStats.victories << "\n"
									<< " |Defaites: " << Player.careerStats.losses << "\n"
									<< " |[V/D Ratio: " << "N/A" << "]\n"
									<< " |\n"
									<< " |Accidents: " << Player.careerStats.accidents << "\n\n"
									<< "#Stats Carriere:\n"
									<< " |Credits remportes: " << Player.careerStats.creditsEarned << "c\n"
									<< " |\n"
									<< " |Cars achetees: " << Player.careerStats.carBought << "\n\n"
									<< "===============\n"
									<< "Appuyez sur [Entree] pour retourner au menu principal...\n";
	getch();
	Terminal::get().clearScreen();
}

void menuSauvegarde(Profile& Player)
{
	std::string cheminFichier = "Saves/Profile.save";

	std::ifstream save(cheminFichier.c_str());

	//Menu de sauvegarde de Profile
	Terminal::get() << "Sauvegarder votre Progression\n"
									<< "===============\n";
	if(save)
	{
		Terminal::get() << "Vous allez ecraser votre derniere sauvegarde (Profile \"" << Player.name << "\")\n\n";
	}
	else
	{
		Terminal::get() << "Votre Profile va etre sauvegarde sur le disque (Profile \"" << Player.name << "\")\n\n";
	}
	if(Menu::askConfirmation())
	{
		Terminal::get().clearScreen(); //on flushe l'ecran
		Terminal::get() << "Sauvegarder votre Progression\n"
										<< "===============\n"
										<< "Sauvegarde en cours...\n"
										<< "===============\n"
										<< "Veuillez patienter";
		sleep(0.4f);
		Player.sauvegarderProfile();
		Terminal::get().clearScreen();
		Terminal::get() << "Sauvegarder votre Progression\n"
										<< "===============\n"
										<< "Partie Sauvegardee !\n"
										<< "===============\n"
										<< "Appuyez sur Entree pour retourner au menu principal...\n";
		getch();
	}
	else
	{
		Terminal::get().clearScreen(); //on flushe l'ecran
		Terminal::get() << "Sauvegarder votre Progression\n"
										<< "===============\n\n"
										<< "Sauvegarde annulee.\n"
										<< "===============\n"
										<< "Appuyez sur Entree pour retourner au menu principal...\n";
		getch();
	}
}

void menuOptions(Profile& Player)
{
	bool quit = false;
	std::string saveAuto;
	while(quit != true)
	{
		//Menu Principal
		saveAuto = "ON";
		Terminal::get() << "Options " << Player.name << "\n"
										<< "===============\n\n"
										<< "1. Sauvegarde auto [" << saveAuto << "]\n"
										<< "2. Difficulte ["<< Player.difficulty <<"]\n"
										<< "3. Raccourcis menus [OFF]\n"
										<< "4. Changer le nom du Profile\n\n"
										<< "0. Retour\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case 1:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				break;
			case 2:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuDifficulte(Player);
				break;
			case 3:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("non implemente");
				break;
			case 4:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				menuChangementNomProfile(Player);
				break;

			default:
				Terminal::get().clearScreen(); //On flushe l'ancien ecran
				Menu::error("Saisie invalide");
				break;
		}
	}
	Player.sauvegarderProfile();
}