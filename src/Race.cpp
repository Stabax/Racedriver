#include <chrono>
#include <thread>
#include <functional>
#include <iomanip>
#include "Menu.hh"
#include "Race.hh"
#include "Accident.hh"

std::vector<std::string> Race::driversCollection = std::vector<std::string>();

Race::Race(std::shared_ptr<Car> pCar, Track &pTrack)
{
	_players.push_back(Concurrent(Profile::active->name, pCar));
	_track = std::make_shared<Track>(pTrack);
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

bool Race::preparations()
{
	Terminal &term = Terminal::windows.at("main");
	int prixCourse;
	auto player = std::find_if(_players.begin(), _players.end(),
    			[=] (const Concurrent &c) { return (c.name == Profile::active->name); });

	prixCourse = 50;
	std::string menu;
	menu += "<Menu>"
					" <Text>Les preparatifs du circuit: " + _track->name + " s'elevent a " + std::to_string(prixCourse) + "c</Text>"
					" <Sep/>"
					" <Button Type='Intern' Target=''>Oklm</Button>"
					" <Button Type='Intern' Target=''>Cancel</Button>"
					"</Menu>";
	Menu::popUp("", menu, DataSource::Document);
	if(Profile::active->credits < prixCourse)
	{
		Menu::alert("Vous ne disposez pas d'assez de crédits pour payer les preparatifs.");
		return (false);
	}
	else if(player->car->integrity.count()*100 < 20)
	{
		Menu::alert("Votre vehicule est trop endommage pour concourir.");
		return (false);
	}
	else if(player->car->getTires()->integrity.count() < 15)
	{
		Menu::alert("Vos pneus sont trop uses pour concourir.");
		return (false);
	}
	if(player->car->nitro.count() < 100)
	{
		Menu::alert("Attention: Votre reservoir de nitro n'est pas plein.\n");
	}
	if(player->car->getTires()->integrity.count() < 55)
	{
		Menu::alert("Attention: Tires deteriores.\n");
	}
	if(1) //Should be bound to confirm button
	{
			randomizeOpponents(7);
			return (true);
	}
	return (false);
}

void Race::randomizeOpponents(size_t count)
{
	std::vector<std::string> usedNames;
	std::string driver;

	for (size_t i = 0; i < count; i++)
	{
		std::shared_ptr<Car> car = std::make_shared<Car>(Car::collection[rand() % 2]);
		do
		{
			driver = driversCollection[rand() % driversCollection.size()];
		} while (std::find(usedNames.begin(), usedNames.end(), driver) != usedNames.end());
		usedNames.push_back(driver);
		_players.push_back(Concurrent(driver, car));
	}
}

bool Race::start()
{
	Terminal &term = Terminal::windows.at("main");
	auto player = std::find_if(_players.begin(), _players.end(),
    			[=] (const Concurrent &c) { return (c.name == Profile::active->name); });

	term.clearScreen();
	term << "Bienvenue à tous et a toutes !\n"
			 << "Aujourd'hui va se derouler l'evenement tant attendu par tous les fans de sportives,"
			 << "tout le monde s'est reuni et l'ambiance est a son comble sur le circuit: " << _track->name << ".\n"
			 << "On m'annonce qu'il totalise " << _track->length << " m, et comprend pas moins de <JSPCB> de virages serres !\n"
			 << "<Inserer commentaire meteo>" << "\n"
			 << "D'autre part, il y a un vent de Force <ZAIREAU> dans l'enceinte du circuit.\n\n"
			 << "Sans attendre passons tout de suite a la liste des Participants:\n\n";
	//on liste les concurrents
	for (size_t i = 0; i < _players.size(); i++)
	{
		term << "En position " << i+1 << ", " << _players[i].name << " - " << _players[i].car->manufacturer << " " << _players[i].car->name << "\n";
	}
	term <<"\n\nPressez [ENTREE] pour commencer la course.\n";
	getch();

	term.clearScreen();
	Menu::msg("Depart dans 3...");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	term.clearScreen();
	Menu::msg("Depart dans 2...");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	term.clearScreen();
	Menu::msg("Depart dans 1...");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	term.clearScreen();
	Menu::msg("GO !");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	compute(); //Calculer la course
	if (player - _players.begin() < 3 && !player->out) Profile::active->careerStats.victories++;//Si le joueur finit sur le podium & pas d'accident
	else Profile::active->careerStats.losses++;
	Profile::active->careerStats.races++;
	term <<"Pressez [ENTREE] pour quitter le circuit.\n";
	getch();
	Profile::active->save();
	return (true);
}

void Race::compute()
{
	auto player = std::find_if(_players.begin(), _players.end(),
    			[=] (Concurrent &c) { return (c.name == Profile::active->name); });
	std::vector<int> probaAccident = calculerProbaAccident();
	size_t rtick = 0, ftick = 0;
	omni::Second tickDuration = omni::Second(1);

	while (std::find_if(_players.begin(), _players.end(),
		 [this] (const Concurrent &c) { return (!c.out && c.position < _track->length); }) != _players.end())
	{
		for (size_t i = 0; i < _players.size(); i++)
		{
			if (_players[i].out) continue; //Skip out _players
			_players[i].car->update(tickDuration, omni::Meter(0));
			_players[i].position += _players[i].car->speed * omni::Second(1);
			if (_players[i].position > _track->length)
			{
				_players[i].out = true;
				_players[i].time = tickDuration * rtick;
			}
			if (rtick % 30 == 0) //each 30 ticks of 1 sec
			{
				if (std::rand() % 101 < probaAccident[i])
				{
					_players[i].out = true;
					_players[i].time = tickDuration * rtick;
					if(player->name == _players[i].name) Profile::active->careerStats.accidents++;
					_players[i].outmsg = Accident::collection[rand() % Accident::collection.size()].message + " (Tick" + std::to_string(ftick) + ")";
				}
				ftick++;
			}
		}
		render(rtick);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		rtick++;
	}
}

void Race::render(int rtick)
{
	Terminal &term = Terminal::windows.at("main");

	std::sort(_players.begin(), _players.end(), std::greater<Concurrent>());
	term.clearScreen();
	term << "(Tick " << rtick << ")\n";
	for (size_t i = 0; i < _players.size(); i++)
	{
		term << "[" << i+1 << "e]" << (_players[i].out ? " <K.O.> " : " ")  << _players[i].name << " : " << _players[i].position << "\n"
				 << "  |-> " << _players[i].car->manufacturer << " " << _players[i].car->name << "\n"
			   << "  |-> " << _players[i].car->speed.count() << "km/h (" << _players[i].car->getEngine()->power.count() << "ch at " << _players[i].car->getEngine()->revolutions.count() << ") [" << _players[i].car->getEngine()->gear << "]\n"
				 << "  |-> " << _players[i].car->getEngine()->torque.count() << "Nm\n";
		if (_players[i].out)
		{
			time_t timecpy = _players[i].time.count();
			std::ostringstream oss;
			oss << std::put_time(std::localtime(&timecpy), "%H:%M:%S");
			term << "  |-> " << _players[i].outmsg << "\n";
			term << "  |-> " << oss.str() << "\n";
		}
	}
}


std::vector<int> Race::calculerProbaAccident()
{
	std::vector<int> results;

	for (size_t i = 0; i < _players.size(); i++)
	{
		results.push_back(std::rand()%25);
	}
	return (results);
}

Concurrent::Concurrent(std::string n, std::shared_ptr<Car> c)
 : name(n), car(c), position(0), out(false)
{
}

bool operator==(const Concurrent &a, const Concurrent &b)
{
	return (a.position > b.position);
}

bool operator>(const Concurrent &a, const Concurrent &b)
{
	return (a.position > b.position);
}