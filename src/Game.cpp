#include <chrono>
#include <thread>
#include <ctime>
#include <iostream>
#include <curl/include/curl/curl.h>
#include <sstream>
#include <fstream>
#include "Menu.hh"
#include "Game.hh"
#include "Accident.hh"
#include "menusPrincipaux.hh"
#include "ScriptEngine.hh"

//Singleton storage ptr
std::unique_ptr<Game> Game::instance = nullptr;

Game::Game()
{
  if (Game::instance != nullptr) throw ("Cannot reinstantiate singleton");
  Game::instance = std::unique_ptr<Game>(this);
}

bool Game::load()
{
	_term << "Chargement en Cours...\n";
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
	}
	catch (const std::runtime_error &e)
	{
		Menu::alert(e.what());
		Terminal::get() <<"\n\nPressez [ENTREE] pour quitter.\n";
		getch();
		return (false);
	}
	return (true);
}

int Game::main()
{
	// BEGIN
	std::srand(std::time(0)); //INITIALISATION DE L'ALEATOIRE
	if (!update()) //on verifie et fait les mises à jour
	{
		_term << setColor(Terminal::Color::RedOnBlack)
					<< ">Vous allez jouer avec une version potentiellement obsolete de Racedriver.\n"
					<< resetAttrs()
		      << ">Appuyez sur [ENTREE] pour continuer.\n";
		getch();
	}
	_term.clearScreen();
	if (!load()) return -1;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	//Main loop hook
	Menu::goTo("Home", "./Data/Menus/Main.xml");
	Menu::run();
	//menuRacedriver(); //on lance le coeur du jeu
	return 0;
}

void Game::printASCIILogo()
{
	Terminal::get() << setColor(Terminal::Color::RedOnBlack)
									<< " ________                  ________       _____                    \n"
									<< " ___  __ \\_____ ______________  __ \\_________(_)__   ______________\n"
									<< " __  /_/ /  __ `/  ___/  _ \\_  / / /_  ___/_  /__ | / /  _ \\_  ___/\n"
									<< " _  _, _// /_/ // /__ /  __/  /_/ /_  /   _  / __ |/ //  __/  /    \n"
									<< " /_/ |_| \\__,_/ \\___/ \\___//_____/ /_/    /_/  _____/ \\___//_/     \n"
									<< resetAttrs();
}

void Game::removeUpdatePackage()
{
	std::remove("Update/update.zip");
}

bool Game::update()
{
	CURL *curlVersion = curl_easy_init(); //On crée un flux cURL et on "instancie" le flux
	CURLcode resVersion; //CURLcode est un type enum de Curl stockant un état d'erreur.

	//on indique l'url cible
	curl_easy_setopt(curlVersion, CURLOPT_URL, "/bin/version");

	//on indique quelle est la fonction d'ecriture du fichier. on utilise celle de la bibliothèque standard
	curl_easy_setopt(curlVersion, CURLOPT_WRITEFUNCTION, fwrite);

	//création et ouverture d'un fichier en ecriture
	FILE *versionFile = fopen("Update/version.cdx", "w");
	if (!versionFile)
	{
		Menu::alert("Impossible d'écrire dans le répertoire du jeu");
		return (false);
	}

	//on indique le fichier de destination chez le client
	curl_easy_setopt(curlVersion, CURLOPT_WRITEDATA, versionFile);

	_term << ">Recuperation des informations de mise a jour...\n\n";
	//on lance le flux (curl version ici) ==> telechargement du fichier
	//l'état du telechargement est stocké dans un type CURLcode (ici resVersion)
	resVersion = curl_easy_perform(curlVersion);

	//on libère les ressources utilisées
	curl_easy_cleanup(curlVersion);
	fclose(versionFile); //On ferme le fichier téléchargé car on en a plus besoin

	//si le téléchargement s'est mal dérroulé
	if(CURLE_OK != resVersion)
	{
		//echec de la récupération du fichier de version
		Menu::alert("La recuperation des informations de mise a jour a echoue. Verifiez votre connexion.");
		return (false);
	}
	std::ifstream latestVersion("Update/version.cdx");
	std::string stringLatestVersion;	//derniere version disponible
	std::getline(latestVersion, stringLatestVersion);

	//si la verion actuelle est differente de la version disponible, on telecharge la derniere version de racedriver
	if(GAME_VERSION != stringLatestVersion)
	{
		Menu::msg("Votre client est obsolete, une mise a jour est disponible !");
		_term << "Vous allez telecharger la derniere version de Racedriver.\n";
		if (!Menu::askConfirmation()) return (false);

		FILE *updateFile = fopen("Update/update.zip", "w");
		CURL *curlUpdate;
		CURLcode resUpdate;
		std::string binURL;

		curlUpdate = curl_easy_init();
		binURL = "bin/"+stringLatestVersion+".zip";
		_term << "\n>Connexion au serveur distant...\n";
		curl_easy_setopt(curlUpdate, CURLOPT_URL, binURL.c_str());
		curl_easy_setopt(curlUpdate, CURLOPT_WRITEFUNCTION, fwrite);
		curl_easy_setopt(curlUpdate, CURLOPT_WRITEDATA, updateFile);

		_term << ">Telechargement de la mise à jour...\n\n";
		resUpdate = curl_easy_perform(curlUpdate);

		curl_easy_cleanup(curlUpdate);
		fclose(updateFile);
		//echec du dl
		if(CURLE_OK != resUpdate)
		{
			Menu::alert("Le telechargement de la mise a jour a echoue.");
			return (false);
		}
		Menu::msg("Le client a ete mis a jour avec succes !");
		_term << ">Vous devez redemmarer le jeu pour appliquer les modifications.\n";
		_term << ">Appuyez sur [Entree] pour quitter.";
		getch();
		//décompression du .zip téléchargé
		//opérateur ternaire: si OS == 0 (linux) on appelle execl pour unpack linux, sinon on appelle execl pour unpack.exe windows
		//OS == 0 ? execl("Update/unpack", "unpack", "-qq", "-o", "Update/update.zip", NULL) : execl("Update/unpack.exe", "unpack.exe", "-qq", "-o", "Update/update.zip", NULL);
		//le programme se termine ici grace à l'apel à execl()
		return (true);
	}
	Menu::msg("Aucune mise à jour disponible.");
	_term << ">Appuyez sur [Entree] pour continuer.\n";
	getch();
	return (true);
}
