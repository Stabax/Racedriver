#include <chrono>
#include <thread>
#include <ctime>
#include <iostream>
#include <httplib.h>
#include <sstream>
#include <fstream>
#include "Menu.hh"
#include "Game.hh"
#include "Track.hh"
#include "Collection.hpp"
#include "Race.hh"
#include "Accident.hh"
#include "ScriptEngine.hh"
#include "Localization.hh"

class Car;

//Singleton storage ptr
std::unique_ptr<Game> Game::instance = nullptr;

Game::Game()
{
  if (Game::instance != nullptr) throw ("Cannot reinstantiate singleton");
  Game::instance = std::unique_ptr<Game>(this);
	Terminal::start();
}

bool Game::load()
{
  Terminal &term = Terminal::windows.at("main");

	Localization::load("en-US");
	term << "Chargement en Cours...\n";
	try
	{
		Collection<Engine>::load(Engine::collection);
		Collection<Tires>::load(Tires::collection);
		Collection<Spoiler>::load(Spoiler::collection);
		Collection<Car>::load(Car::collection);

		Entity::loadCollection();
		Track::loadCollection();
		Accident::loadCollection();
		Race::loadDrivers();
		ScriptEngine::init();
	}
	catch (const std::runtime_error &e)
	{
		Menu::alert(e.what());
		term << "\n\nPressez [ENTREE] pour quitter.\n";
		getch();
		return (false);
	}
	return (true);
}

int Game::main()
{
	std::srand(std::time(0));
	if (!load()) return (-1); //Load game
	if (!update()) Menu::goTo("Home", "./Data/Menus/Main.xml"); //If nothing showed while cheking updates, move to home
	Menu::run();
	return (0);
}

void Game::removeUpdatePackage()
{
	std::remove("Update/update.zip");
}

bool Game::update()
{
	httplib::Client http(SERVER);

	auto res = http.Get("/racedriver/version");
	if (res && res->status == 200 && res->body != GAME_VERSION) {
		std::string menu;
		menu += "<Menu Title='Game'>"
						" <Text><Lang Id='update.newversion'/>. (" + res->body + ")</Text>"
						" <Text><Lang Id='update.updatetoenjoy'/>.</Text>"
						" <Sep/>"
						" <Button Type='Intern' Target='alert(\"not impl\")'><Lang Id='update.downloads'/></Button>"
						" <Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Home'><Lang Id='update.obsolete'/></Button>"
						"	<Button Type='Intern' Target='exit()'><Lang Id='global.quit'/></Button>"
						"</Menu>";
		Menu::goTo("", menu, DataSource::Document);
		return (true);
	}
	return (false);
}
