#include "Menu.hh"
#include "Game.hh"
#include "Collection.hpp"
#include <fstream>
#include "sha/sha.h"

std::map<std::string, std::shared_ptr<MenuModule>> Menu::modules = std::map<std::string, std::shared_ptr<MenuModule>>();

Menu::Menu(const std::string &path)
{
  MenuFile menu(path);
}


bool Menu::invokeMethod(const std::string &methodPath)
{
	size_t sep = methodPath.find(INVOKE_SEPARATOR);
	if (sep == std::string::npos)
	{
		throw (std::runtime_error("Could not find method"));
		return (false);
	}
	std::shared_ptr<MenuModule> module = modules[methodPath.substr(0, sep)];

	module->methods[methodPath.substr(sep, methodPath.size() - sep)]();
	return (true);
}

void Menu::error(std::string str)
{
	Menu::msg("ERREUR: "+str);
}

void Menu::msg(std::string str)
{
	Terminal::get() << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
	                << ":: " << str << "\n"
	                << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
}

bool Menu::askConfirmation()
{
  char input;
  Terminal::get() << "=====================\n"
                  << "Etes-vous sur ? [O/n]\n"
                  << "=====================\n";
  input = getch();
  if (input == 'o' || input == 'O') return (true);
  return (false);
}

int Menu::askChoice()
{
  char input;
  Terminal::get() << "=====================\n"
                  << "Choix ? ";
  input = getch();
  return (atoi(&input));
}

MenuModule::MenuModule(const std::string &id)
{
	Menu::modules.emplace(id, std::shared_ptr<MenuModule>(this));
}

//Helpers

std::string getString()
{
	char str[256];
	getnstr(str, 255);
	return (std::string(str));
}

std::string getHashFromFile(std::string path)
{
	std::ifstream file(path.c_str()); //flux de lecture de la sauvegarde

	std::string ligneChargee;
	std::string saveContent;
	std::string lock;

	while(getline(file, ligneChargee))
	{
		saveContent += ligneChargee; //On remplit le string qui contient la sauvegarde
	}
	saveContent += PWD_SALT;
	lock = sha256(saveContent); //On inscrit le lock dans le fichier

	return lock;
}