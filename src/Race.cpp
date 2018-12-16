#include <chrono>
#include <thread>
#include <functional>
#include "Menu.hh"
#include "Race.hh"

std::vector<std::string> Race::crashCollection = std::vector<std::string>();
std::vector<std::string> Race::driversCollection = std::vector<std::string>();

Race::Race(Car &pCar)
{
	track = std::make_shared<Track>(Track::selectTrack());
	playerCar = std::make_shared<Car>(pCar);
	player = std::make_shared<Concurrent>(Profile::active->name, playerCar);
	players.push_back(*player);
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
		players.push_back(Concurrent(driver, car));
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
		Terminal::get() << "En position " << i+1 << ", " << players[i].name << " - " << players[i].car->manufacturer << " " << players[i].car->name << "\n";
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
	for (size_t i = 0; i <= players.size(); i++)
	{
		if(std::rand()%101 < probaAccident[i])
		{
			players[i].out = true;
			players[i].score = 0;
			if(i == 0) Profile::active->careerStats.accidents++;
			Terminal::get() << "Le joueur " << players[i].name << " " << crashCollection[rand()%crashCollection.size()] <<"\n";
		}
		else
		{
			players[i].score = score[i];
		}
	}
	Terminal::get() <<"\n\nPressez [ENTREE] pour voir les resultats.\n";
	getch();
	std::sort(players.begin(), players.end(), std::greater<Concurrent>());
	ptrdiff_t playerPos = std::find(players.begin(), players.end(), *player) - players.begin();
	if (playerPos < 3 && !player->out) Profile::active->careerStats.victories++;//Si le joueur finit sur le podium & pas d'accident
	else Profile::active->careerStats.losses++;
	//on affiche les resultats
	for (size_t i = 0; i < players.size(); i++)
	{
		Terminal::get() << "[" << i+1 << "e] = " << players[i].score << "="
										<< players[i].name << " - " << players[i].car->manufacturer << " " << players[i].car->name << "\n";
	}
	Terminal::get() <<"\n\n";
	Profile::active->careerStats.races++;
	Terminal::get() <<"Pressez [ENTREE] pour continuer.\n";
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
		results.push_back(((players[i].car->getVitesse()/2)+(players[i].car->getAcceleration()*2/track->curves))*((std::rand()%26)+75)/100);
	}
	return (results);
}


std::vector<int> Race::calculerProbaAccident()
{
	std::vector<int> results;

	for (size_t i = 0; i < players.size(); i++)
	{
		results.push_back( (players[i].car->getTires()->getDurability() / track->curves) + (players[i].car->getAerodynamisme() / 1) + std::rand()%5); //1 is wind
	}
	return (results);
}

Concurrent::Concurrent(std::string n, std::shared_ptr<Car> c)
 : name(n), car(c), score(0), out(false)
{
}

bool operator==(const Concurrent &a, const Concurrent &b)
{
	return (a.name == b.name);
}

bool operator>(const Concurrent &a, const Concurrent &b)
{
	return (a.score > b.score);
}