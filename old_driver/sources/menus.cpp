
//menus.cpp

#include "menus.h"


void menuCourse(Profil& Player)
{
	char menu;
	bool quit = false;
	while(quit != true)
	{
		//Menu Principal
		std::cout << "Menu Course\n";
		std::cout << "===============\n";
		std::cout << "Selectionnez un mode de course.\n";
		std::cout << "===============\n\n";
		std::cout << "1. Carriere\n";
		std::cout << "2. Championnat\n";
		std::cout << "3. Course Libre\n\n";
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				clrscreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case '1':
				clrscreen(); //On flushe l'ancien ecran
				error("Non implementee.");
				break;

			case '2':
				clrscreen(); //On flushe l'ancien ecran
				menuCourseChampionnat(Player);
				break;

			case '3':
				clrscreen(); //On flushe l'ancien ecran
				menuCourseLibre(Player);
				break;

			default:
				clrscreen(); //On flushe l'ancien ecran
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
		std::cout << "Menu Garage\n";
		std::cout << "===============\n";
		std::cout << "Credits: " << Player.getCredits() << "c\n";
		std::cout << "===============\n\n";
		std::cout << "1. Consulter Garage\n";
		std::cout << "2. Visiter Atelier\n";
		std::cout << "3. Maintenance vehicules\n\n";
		std::cout << "4. Acheter Box \n\n";
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				clrscreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;
			case '1':
				clrscreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 0);
				break;
			case '2':
				clrscreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 1);
				break;
			case '3':
				clrscreen(); //On flushe l'ancien ecran
				menuConsulterGarage(Player, 3);
				break;
			case '4':
				clrscreen(); //On flushe l'ancien ecran
				menuAcheterBox(Player);
				break;
			default:
				clrscreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
}


void menuConcessionaire(Profil& Player)
{
	char menu;
	//Menu Principal
	std::cout << "Concessionnaire\n";
	std::cout << "===============\n\n";
	std::cout << "1. Achat\n";
	std::cout << "2. Vente\n\n";
	std::cout << "0. Retour\n";
	std::cout << "===============\n";
	std::cout << "Choix ? ";
	std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
	videKBuffer();
	//Redirection de l'utilisateur selon son choix grâce a un switch.
	switch(menu)
	{
		case '0':
			clrscreen(); //On flushe l'ancien ecran
			break;
		case '1':
			clrscreen(); //On flushe l'ancien ecran
			menuConcessionaireAchat(Player);
			break;
		case '2':
			clrscreen(); //On flushe l'ancien ecran
			menuConsulterGarage(Player, 4);
			break;
		default:
			clrscreen(); //On flushe l'ancien ecran
			saisieInvalide();
			break;
	}
}


void menuStats(Profil& Player)
{
	std::cout << "Stats du Profil: " << Player.getNom() << "\n";
	std::cout << "===============\n";
	std::cout << "[UUID: " << Player.getUuid() << "]\n\n";
	std::cout << "#Stats Course:\n";
	std::cout << " |Courses effectuees: " << Player.getNbCourses() << "\n";
	std::cout << " |\n";
	std::cout << " |Victoires: " << Player.getVictoires() << "\n";
	std::cout << " |Defaites: " << Player.getDefaites() << "\n";
	std::cout << " |[V/D Ratio: " << Player.getVDRatio() << "]\n";
	std::cout << " |\n";
	std::cout << " |Accidents: " << Player.getAccidents() << "\n\n";
	std::cout << "#Stats Carriere:\n";
	std::cout << " |Credits remportes: " << Player.getCreditsGagnes() << "c\n";
	std::cout << " |\n";
	std::cout << " |Voitures achetees: " << Player.getVoituresAchetees() << "\n\n";
	std::cout << "===============\n";
	std::cout << "Appuyez sur Entree pour retourner au menu principal...\n";
	videKBuffer();
	clrscreen();
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
	std::cout << "Sauvegarder votre Progression\n";
	std::cout << "===============\n";
	if(save)
	{
		std::cout << "Vous allez ecraser votre derniere sauvegarde (Profil" << Player.getNumero() << ": \"" << Player.getNom() << "\")\n\n";
	}
	else
	{
		std::cout << "Votre profil va etre sauvegarde sur le disque (Profil" << Player.getNumero() << ": \"" << Player.getNom() << "\")\n\n";
	}
	std::cout << "Etes vous sur ? [O/n]\n";
	std::cout << "===============\n";
	std::cin >> menu; // l'utilisateur entre son choix
	videKBuffer();
	clrscreen(); //on flushe l'ecran
	if(menu == 'o' || menu == 'O')
	{
		std::cout << "Sauvegarder votre Progression\n";
		std::cout << "===============\n";
		std::cout << "Sauvegarde en cours...\n";
		std::cout << "===============\n";
		std::cout << "Veuillez patienter";
		sleep(0.4f);
		Player.sauvegarderProfil();
		clrscreen();
		std::cout << "Sauvegarder votre Progression\n";
		std::cout << "===============\n";
		std::cout << "Partie Sauvegardee !\n";
		std::cout << "===============\n";
		std::cout << "Appuyez sur Entree pour retourner au menu principal...\n";
		videKBuffer();
		clrscreen();
	}
	else
	{
		std::cout << "Sauvegarder votre Progression\n";
		std::cout << "===============\n\n";
		std::cout << "Sauvegarde annulee.\n";
		std::cout << "===============\n";
		std::cout << "Appuyez sur Entree pour retourner au menu principal...\n";
		videKBuffer();
		clrscreen();
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
		std::cout << "Options " << Player.getNom() << "\n";
		std::cout << "===============\n\n";
		std::cout << "1. Sauvegarde auto [" << saveAuto << "]\n";
		std::cout << "2. Difficulte ["<< Player.getDifficulteString() <<"]\n";
		std::cout << "3. Raccourcis menus [OFF]\n";
		std::cout << "4. Changer le nom du profil\n\n";
		std::cout << "0. Retour\n";
		std::cout << "===============\n";
		std::cout << "Choix ? ";
		std::cin >> menu; // l'utilisateur entre le menu qu'il souhaite ouvrir
		videKBuffer();
		//Redirection de l'utilisateur selon son choix grâce a un switch.
		switch(menu)
		{
			case '0':
				clrscreen(); //On flushe l'ancien ecran
				quit = true; //INSTRUCTION DE SORTIE
				break;

			case '1':
				clrscreen(); //On flushe l'ancien ecran
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
				clrscreen(); //On flushe l'ancien ecran
				menuDifficulte(Player);
				break;
			case '3':
				clrscreen(); //On flushe l'ancien ecran
				error("non implemente");
				break;
			case '4':
				clrscreen(); //On flushe l'ancien ecran
				menuChangementNomProfil(Player);
				break;

			default:
				clrscreen(); //On flushe l'ancien ecran
				saisieInvalide();
				break;
		}
	}
	if(Player.getSauvegardeAuto())
	{
		Player.sauvegarderProfil();
	}
}
