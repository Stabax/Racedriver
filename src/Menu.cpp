#include "Menu.hh"
#include "Game.hh"
#include "Collection.hpp"
#include "ScriptEngine.hh"
#include <fstream>
#include "sha/sha.h"

//Menu

std::shared_ptr<Menu> Menu::active = nullptr;

Menu::Menu(const std::string &path, const std::string &id)
 : _cursor(0)
{
  MenuFile menuFile(path);
	if (!menuFile.load()) throw(std::runtime_error("Error on loading Menu XML"));
	const pugi::xml_document &root = menuFile.getData();
	pugi::xml_node menu = root.first_child();

	while (menu && strcmp(menu.name(), "Menu") != 0 && menu.attribute("Id").value() != id) menu = menu.next_sibling();
	if (!menu) throw(std::runtime_error("Menu not found"));
	for (pugi::xml_node el = menu.first_child(); el; el = el.next_sibling())
	{
		try {
			_items.push_back(MenuItem::create(el));
		} catch(std::exception &e) {
			Menu::error(e.what());
		}
	}
	ScriptEngine::loadScripts(root);
}

bool Menu::update()
{
	char input = getch();
	if(input == KEY_UP) --_cursor;
	else if(input == KEY_DOWN) ++_cursor;
	else return (false);
	if (_cursor >= _items.size()) _cursor = 0;
	else if (_cursor < 0) _cursor = _items.size() - 1;
	return (true);
}

void Menu::render()
{
	Terminal::get().clearScreen();
	for (size_t i = 0; i < _items.size(); i++)
	{
		if (i == _cursor) Terminal::get() << setColor(Terminal::Color::RedOnBlack);
		_items[i]->render();
		if (i == _cursor) Terminal::get() << resetAttrs();
	}
}

void Menu::error(std::string str)
{
	Menu::msg("ERREUR: "+str);
}

void Menu::msg(std::string str)
{
	Terminal::get() << setColor(Terminal::Color::BlackOnRed)
									<< "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
	                << ":: " << str << "\n"
	                << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n"
									<< resetAttrs();
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

void Menu::Goto(std::string id)
{
	active = std::make_shared<Menu>(Menu("", id));
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