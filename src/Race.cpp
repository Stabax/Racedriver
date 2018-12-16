#include <chrono>
#include <thread>
#include "Menu.hh"
#include "Race.hh"

std::vector<std::string> Race::crashCollection = std::vector<std::string>();
std::vector<std::string> Race::driversCollection = std::vector<std::string>();

Race::Race(Car &pCar)
{
	track = std::make_shared<Track>(Track::selectTrack());
	playerCar = std::make_shared<Car>(pCar);
	players.push_back(std::pair<std::string, std::shared_ptr<Car>>(Profile::active->name, playerCar));
}

void Race::loadDrivers()
{
	DataFile file("./Data/Events/Drivers.json");

	if (!file.load())
	{
		throw (std::runtime_error("Error loading tracks"));
	}
	const json &data = file.getData();
	for (size_t i = 0; i < data["collection"].size(); i++)
	{
		driversCollection.push_back(data["collection"][i].get<std::string>());
	}
}

void Race::loadCrash()
{
	DataFile file("./Data/Events/Crash.json");

	if (!file.load())
	{
		throw (std::runtime_error("Error loading Crash"));
	}
	const json &data = file.getData();
	for (size_t i = 0; i < data["collection"].size(); i++)
	{
		crashCollection.push_back(data["collection"][i].get<std::string>());
	}
}

bool Race::preparations()
{
	int prixCourse;

	prixCourse = (5 * 0.01f * track->length * 5 /*prix carburant remplace par 5 */);
	if(Profile::active->credits < prixCourse)
	{
		Menu::error("Vous ne disposez pas d'assez de crédits pour payer les preparatifs.");
		return (false);
	}
	else if(playerCar->getEtat() < 20)
	{
		Menu::error("Votre vehicule est trop endommage pour concourir.");
		return (false);
	}
	else if(playerCar->getTires()->getDurability() < 15)
	{
		Menu::error("Vos pneus sont trop uses pour concourir.");
		return (false);
	}
	Terminal::get().clearScreen(); //On flushe l'ancien ecran
	if(playerCar->getNiveauNitro() < playerCar->getNitroMax())
	{
		Menu::msg("Attention: Votre reservoir de nitro n'est pas plein.\n");
	}
	if(playerCar->getTires()->getDurability() < 55)
	{
		Menu::msg("Attention: Tires deteriores.\n");
	}
	Terminal::get() << "\nPreparatifs\n";
	Terminal::get() << "====================\n";
	Terminal::get() << "Credits: " << Profile::active->credits << "c\n";
	Terminal::get() << "====================\n";
	Terminal::get() << "Le montant total des preparatifs du circuit: " << track->name << "\n";
	Terminal::get() << "S'elevent a " << prixCourse << "c\n\n";
	if(Menu::askConfirmation())
	{
			Terminal::get().clearScreen();
			randomizeOpponents(7);
			return (true);
	}
	Terminal::get().clearScreen();
	Menu::error("Paiement annule par l'utilisateur");
	return (false);
}

void Race::randomizeOpponents(int count)
{
	for (size_t i = 0; i < count; i++)
	{
		std::shared_ptr<Car> car = std::make_shared<Car>(Car::collection[0]);
		std::string driver = driversCollection[rand() % driversCollection.size()];
		players.push_back(std::make_pair(driver, car));
	}
}

bool Race::start()
{
	Terminal::get() << "Bienvenue à tous et a toutes !\n"
									<< "Aujourd'hui va se derouler l'evenement tant attendu par tous les fans de sportives,"
									<< "tout le monde s'est reuni et l'ambiance est a son comble sur le circuit: " << track->name << ".\n"
									<< "On m'annonce qu'il totalise " << track->length << " Km, et comprend pas moins de " << track->curves << " virages serres !\n"
									<< "<Inserer commentaire meteo>" << "\n"
									<< "D'autre part, il y a un vent de Force <ZAIREAU> dans l'enceinte du circuit.\n\n"
									<< "Sans attendre passons tout de suite a la liste des Participants:\n\n";
	//on liste les concurrents
	for (size_t i = 0; i < players.size(); i++)
	{
		Terminal::get() << "En position " << i << ", " << players[i].first << " - " << players[i].second->manufacturer << " " << players[i].second->name << "\n";
	}
	Terminal::get() <<"\n\nPressez [ENTREE] pour commencer la course.\n";
	getch();

	Terminal::get().clearScreen();
	Menu::msg("Depart dans 3...");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Terminal::get().clearScreen();
	Menu::msg("Depart dans 2...");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Terminal::get().clearScreen();
	Menu::msg("Depart dans 1...");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Terminal::get().clearScreen();
	Menu::msg("GO !");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//on calcule Score: celui qui a le plus grand est le vainqueur
	std::vector<int> score = calculerScore();
	//on calcule la probabilite que les voitures aient des accidents
	std::vector<int> probaAccident = calculerProbaAccident();

	//on calcule les voitures ayant un accident en fonction de la probabilite calculee precedement
	for (size_t njoueur = 0; njoueur <= players.size(); njoueur++)
	{
		if(std::rand()%101 < probaAccident[njoueur])
		{
			score[njoueur]=0;
			if(njoueur == 0)
			{
				Profile::active->careerStats.accidents++;
			}
			Terminal::get() << "Le joueur " << players[njoueur].first << " " << crashCollection[rand()%crashCollection.size()] <<"\n";
		}
	}
	Terminal::get() <<"\n\nPressez [ENTREE] pour voir les resultats.\n";
	getch();
	int scoreJoueur[8];
	scoreJoueur[0] = score[0];
	scoreJoueur[1] = score[1];
	scoreJoueur[2] = score[2];
	scoreJoueur[3] = score[3];		//variables pour suivre le joueur
	scoreJoueur[4] = score[4];
	scoreJoueur[5] = score[5];
	scoreJoueur[6] = score[6];
	scoreJoueur[7] = score[7];
	//classement des joueurs
	int temp;
	while(score[0] < score[1] || score[1] < score[2] || score[2]<score[3] || score[3]<score[4] || score[4]<score[5] || score[5]<score[6] || score[6]<score[7])
	{
		for (size_t i = 1;i <= 7;i++)
		{
			if( score[i - 1] < score[i])
			{
				temp = score[i - 1]; 	//On fait une copie de la variable score[X] dans temp
				score[i - 1] = score[i];	//On fait glisser vers la gauche le plus grand des chiffres
				score[i] = temp; 	//On remplace le chiffre qu'on a fait glisse par le chiffre de gauche
			}
		}
	}
	//on affiche les resultats
	bool exclu[8] = {false};
	bool placeExclue[8] = {false};
	int joueur;
	Terminal::get() <<"\n\n";
	for (size_t placeClassement = 0; placeClassement <=7 ;placeClassement++)
	{
		if(placeExclue[placeClassement] == true)
		{
			placeClassement += 1;

		}
		Terminal::get() << "[" << placeClassement + 1 << "e] "; //On affiche le numéro de la place en début de ligne
		joueur = 0;

		if(exclu[0] == true)
		{
			while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
			{
				joueur++;
			}
		}
		while(score[placeClassement] != scoreJoueur[joueur] && joueur < 8) //On trouve le joueur correspondant au score de la place
		{
			joueur++;
			while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
			{
				joueur++;
			}

		}
		if(joueur == 0 && exclu[0] == false) //Si le joueur est le Joueur1 on affiche son nom
		{
			Terminal::get() << Profile::active->name << " - " << score[placeClassement] << " Points.\n";
			exclu[0] = true;
		}
		else //Sinon on met des nom d'IA
		{

			Terminal::get() << players[joueur - 1].first << " - " << score[placeClassement] << " Points.\n";
			exclu[joueur] = true;
		}
		if(joueur == 0 && placeClassement < 3) //Si le joueur finit sur le podium
		{
			Profile::active->careerStats.victories++;
		}
		else if (joueur == 0 && placeClassement > 3 ) //sinon si il finit ailleurs
		{
			Profile::active->careerStats.losses++;
		}
		placeExclue[placeClassement]=true;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	Profile::active->careerStats.races++;
	Terminal::get() <<"\n\nPressez [ENTREE] pour continuer.\n";
	getch();
	Terminal::get().clearScreen();
	Profile::active->save();
	return (true);
}

std::vector<int> Race::calculerScore()
{
	std::vector<int> results;

	for (size_t i = 0; i < players.size(); i++)
	{
		results.push_back(((players[i].second->getVitesse()/2)+(players[i].second->getAcceleration()*2/track->curves))*((std::rand()%26)+75)/100);
	}
	return (results);
}


std::vector<int> Race::calculerProbaAccident()
{
	std::vector<int> results;

	for (size_t i = 0; i < players.size(); i++)
	{
		results.push_back(((((track->curves*0)/(players[i].second->getTires()->getDurability()/8))+(0/(players[i].second->getAerodynamisme()*0.75)))/2) + std::rand()%5); //0 is meteo, then wind
	}
	return (results);
}

void faireCourseChampionnat(Track Map, Car* Player1)
{
	/*
	if(Player1 == 0)
	{
		Menu::error("Vous n'avez pas de voiture disponible !");
	}
	else if(antiCorruption("Data/console/pilotes.txt", 7) == false)
	{
		Menu::error("Le fichier pilotes.txt ne contient pas assez d'informations.");
	}
	else if(antiCorruption("Data/console/accident.txt", 8) == false)
	{
		Menu::error("Le fichier pilotes.txt ne contient pas assez d'informations.");
	}
	else if(Player1->getEtat() < 20)
	{
		Menu::error("Votre vehicule est trop endommage pour concourir.");
	}
	else if(Player1->getTires()->getDurability() < 15)
	{
		Menu::error("Vos pneus sont trop uses pour concourir.");
	}
	else //Si tout va bien
	{
		if(true) // REMOVED::::preparatifsCourse(Map, Player1)
		//REVOIR CE CALCUL
		{
			Profile::active->payer(5 * 0.01f * Map.getTaille() * 5); //prix carburant et conso remplace par 5
			Car* Adversaire[7];
			chargerAdversaires(Adversaire, Profile::active->difficulty, Map.getDifficulte());

			std::string *commentaireMeteo = chargerCommentaireMeteo(Map.getMeteo());

			std::string messageAccident[8];
			chargerMessagesAccidents(messageAccident);

			//On initialise les noms des adversaires
			std::string nomJoueur[7];
			std::string pseudo;
			for (size_t numero = 0; numero <= 6; numero++)
			{
				pseudo = randNomAdversaire(); //On randomise un nom dans le tableau pseudo.
				while(pseudo == nomJoueur[0] || pseudo == nomJoueur[1] || pseudo == nomJoueur[2] || pseudo == nomJoueur[3] || pseudo == nomJoueur[4] || pseudo == nomJoueur[5] || pseudo == nomJoueur[6])
				{
					pseudo = randNomAdversaire(); //Tant que le pseudo a deja été tiré, on re-genere un nouveau
				}
				nomJoueur[numero] = pseudo;
			}
			Terminal::get() << "Bienvenue à tous et a toutes ! Aujourd'hui va se derouler l'evenement tant attendu par tous les fans de sportives, tout le monde s'est reuni et l'ambiance est a son comble sur le circuit: " << Map.getNom() << ".\nOn m'annonce qu'il totalise " << Map.getTaille() << " Km, et comprend pas moins de " << Map.getVirages() << " virages serres !\n" << *commentaireMeteo << " D'autre part, il y a un vent de Force " << Map.getVent() << " dans l'enceinte du circuit.\n\nSans attendre passons tout de suite a la liste des Participants:\n\n";
			//on liste les concurants
			for (size_t numero = 0; numero <= 7; numero++)
			{
				if(numero == 0)
				{
					Terminal::get() << Profile::active->name << " - " << Player1->manufacturer << " " << Player1->name << "\n";
				}
				else
				{
					Terminal::get() << nomJoueur[numero - 1] << " - " << Adversaire[numero - 1]->manufacturer << " " << Adversaire[numero - 1]->name << "\n";
				}
			}
			delete commentaireMeteo;
			Terminal::get() <<"\n\nPressez [ENTREE] pour commencer la course.\n";
			getch();
			Terminal::get().clearScreen();
			Menu::msg("Depart dans 3...");
			sleep(1.0f);
			Terminal::get().clearScreen();
			Menu::msg("Depart dans 2...");
			sleep(1.0f);
			Terminal::get().clearScreen();
			Menu::msg("Depart dans 1...");
			sleep(1.0f);
			Terminal::get().clearScreen();
			Menu::msg("GO !");
			sleep(1.0f);
			int score[8];
			int probaAccident[8];
			//on calcule Score: celui qui a le plus grand est le vainqueur
			calculerScore(score, Adversaire, Player1, Map);

			//on calcule la probabilite que les voitures aient des accidents
			calculerProbaAccident(score, Adversaire, Player1, Map);

			//on calcule les voitures ayant un accident en fonction de la probabilite calculee precedement
			for (size_t njoueur = 0; njoueur <= 7; njoueur++)
			{
				if(std::rand()%101 < probaAccident[njoueur])
				{
					score[njoueur]=0;
					if(njoueur == 0)
					{
						Profile::active->careerStats.accidents++;
						Player1->retirerEtat(16); //cette valeur changera selon le parchoque
					}
				}
				if(score[njoueur] == 0)
				{
					if(njoueur == 0)
					{
						Terminal::get() << "Le joueur " << Profile::active->name << " " << messageAccident[njoueur - 1] <<"\n";
					}
					else
					{
						Terminal::get() << "Le joueur " << nomJoueur[njoueur - 1]<< " " << messageAccident[njoueur - 1] <<"\n";
					}
				}
			}
			Terminal::get() <<"\n\nPressez [ENTREE] pour voir les resultats.\n";
			getch();
			int joueur;
			int scoreJoueur[8];
			scoreJoueur[0] = score[0];
			scoreJoueur[1] = score[1];
			scoreJoueur[2] = score[2];
			scoreJoueur[3] = score[3];		//variables pour suivre le joueur
			scoreJoueur[4] = score[4];
			scoreJoueur[5] = score[5];
			scoreJoueur[6] = score[6];
			scoreJoueur[7] = score[7];
			//classement des joueurs
			int temp;
			while(score[0] < score[1] || score[1] < score[2] || score[2]<score[3] || score[3]<score[4] || score[4]<score[5] || score[5]<score[6] || score[6]<score[7])
			{
				for (size_t i = 1;i <= 7;i++)
				{
					if( score[i - 1] < score[i])
					{
						temp = score[i - 1]; 	//On fait une copie de la variable score[X] dans temp
						score[i - 1] = score[i];	//On fait glisser vers la gauche le plus grand des chiffres
						score[i] = temp; 	//On remplace le chiffre qu'on a fait glisse par le chiffre de gauche
					}
				}
			}
			//on affiche les resultats
			bool exclu[8] = {false};
			bool placeExclue[8] = {false};
			Terminal::get() <<"\n\n";
			for (size_t placeClassement = 0; placeClassement <=7 ;placeClassement++)
			{
				if(placeExclue[placeClassement] == true)
				{
					placeClassement += 1;

				}
				Terminal::get() << "[" << placeClassement + 1 << "e] "; //On affiche le numéro de la place en début de ligne
				joueur = 0;

				if(exclu[0] == true)
				{
					while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
					{
						joueur++;
					}
				}
				while(score[placeClassement] != scoreJoueur[joueur] && joueur < 8) //On trouve le joueur correspondant au score de la place
				{
					joueur++;
					while(exclu[joueur] == true) //Si le joueur a deja ete classé, on passe au suivant
					{
						joueur++;
					}
				}
				if(joueur == 0 && exclu[0] == false) //Si le joueur est le Joueur1 on affiche son nom
				{
					Terminal::get() << Profile::active->name << " - " << score[placeClassement] << " Points.\n";
					exclu[0] = true;
				}
				else //Sinon on met des nom d'IA
				{
					Terminal::get() << nomJoueur[joueur - 1] << " - " << score[placeClassement] << " Points.\n";
					exclu[joueur] = true;
				}
				if(joueur == 0 && placeClassement < 3) //Si le joueur finit sur le podium
				{
					Profile::active->careerStats.victories++;
					Profile::active->credits += (600 / (placeClassement + 1));
					Profile::active->careerStats.creditsEarned += (600 / (placeClassement + 1));
				}
				else if (joueur == 0 && placeClassement > 3 ) //sinon si il finit ailleurs
				{
					Profile::active->careerStats.losses++;
				}
				placeExclue[placeClassement]=true;
				sleep(0.5f);
			}
			Profile::active->careerStats.races++;
			Terminal::get() <<"\n\nPressez [ENTREE] pour continuer.\n";
			getch();
			Terminal::get().clearScreen();
			for (size_t compteur = 0; compteur <= 6; ++compteur)
			{
				delete Adversaire[compteur];
			}
			Player1->getTires()->setDurability(-1 * (( Map.getTaille() + Map.getVirages() ) / 10));
			Player1->setNitro(-1 * (Map.getTaille() / 4));
		}
		Profile::active->save();
	}*/
}