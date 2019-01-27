//menus.cpp
#include <chrono>
#include <thread>
#include "Menu.hh"
#include "menus.hh"

void menuCourse()
{
	//Menu Principal
	Terminal::get().clearScreen();
	Terminal::get() << "Menu Course\n"
									<< "===============\n"
									<< "Selectionnez un mode de course.\n"
									<< "===============\n\n"
									<< "1. Course Libre\n\n"
									<< " <Carriere>\n"
									<< " <Championnat>\n"
									<< "0. Retour\n";
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(Menu::askChoice())
	{
		case 0:
			break;
		case 1:
			menuCourseLibre();
			break;
	}
}

void menuGarages()
{
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Terminal::get().clearScreen();
		Terminal::get() << "Menu Garage\n"
										<< "===============\n"
										<< "Credits: " << Profile::active->credits << "c\n"
										<< "===============\n\n"
										<< "1. Concessionaire\n"
										<< "2. Consulter Garage\n"
										<< "3. Acheter Box\n\n"
										<< "0. Retour\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				quit = true; //INSTRUCTION DE SORTIE
				break;
			case 1:
				menuBuyCars();
				//Pour vendre: menuConsulterGarage(4);
				break;
			case 2:
				menuConsulterGarage(0);
				break;
			case 3:
				menuAcheterBox();
				break;
			default:
				Menu::error("Saisie invalide");
				break;
		}
	}
}

void menuStatss()
{
	Terminal::get().clearScreen();
	Terminal::get() << "Stats du Profile: " << Profile::active->name << "\n"
									<< "===============\n"
									<< "#Stats Course:\n"
									<< " |Courses effectuees: " << Profile::active->careerStats.races << "\n"
									<< " |\n"
									<< " |Victoires: " << Profile::active->careerStats.victories << "\n"
									<< " |Defaites: " << Profile::active->careerStats.losses << "\n"
									<< " |[V/D Ratio: " << "N/A" << "]\n"
									<< " |\n"
									<< " |Accidents: " << Profile::active->careerStats.accidents << "\n\n"
									<< "#Stats Carriere:\n"
									<< " |Credits remportes: " << Profile::active->careerStats.creditsEarned << "c\n"
									<< " |\n"
									<< " |Cars achetees: " << Profile::active->careerStats.carBought << "\n\n"
									<< "===============\n"
									<< "Appuyez sur [Entree] pour retourner au menu principal...\n";
	getch();
}

void menuSauvegarde()
{
	std::string cheminFichier = "Saves/Profile.save";

	std::ifstream save(cheminFichier.c_str());

	//Menu de sauvegarde de Profile
	Terminal::get().clearScreen();
	Terminal::get() << "Sauvegarder votre Progression\n"
									<< "===============\n";
	if(save)
	{
		Terminal::get() << "Vous allez ecraser votre derniere sauvegarde (Profile \"" << Profile::active->name << "\")\n\n";
	}
	else
	{
		Terminal::get() << "Votre Profile va etre sauvegarde sur le disque (Profile \"" << Profile::active->name << "\")\n\n";
	}
	if(Menu::askConfirmation())
	{
		Terminal::get().clearScreen(); //on flushe l'ecran
		Terminal::get() << "Sauvegarder votre Progression\n"
										<< "===============\n"
										<< "Sauvegarde en cours...\n"
										<< "===============\n"
										<< "Veuillez patienter";
		std::this_thread::sleep_for(std::chrono::seconds(4));
		Profile::active->save();
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

void menuOptions()
{
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		Terminal::get().clearScreen();
		Terminal::get() << "Options [" << Profile::active->name << "]\n"
										<< "===============\n\n"
										<< "1. Difficulte ["<< Profile::active->difficulty <<"]\n"
										<< "2. Changer le nom du Profil\n\n"
										<< "0. Retour\n";
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(Menu::askChoice())
		{
			case 0:
				quit = true; //INSTRUCTION DE SORTIE
				break;
			case 1:
				menuDifficulte();
				break;
			case 2:
				menuChangementNomProfile();
				break;
			default:
				Menu::error("Saisie invalide");
				break;
		}
	}
	Profile::active->save();
}