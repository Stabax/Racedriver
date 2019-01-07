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
			std::shared_ptr<MenuItem> obj = MenuItem::create(el);
			_entities.push_back(obj);
			if (obj->isSelectable()) _items.push_back(obj);
		} catch(std::exception &e) {
			Menu::error(e.what());
		}
	}
	if (_items.size() > 0) _items[_cursor]->toggleHover();
	ScriptEngine::loadScripts(root);
}

bool Menu::update()
{
	int prevCursor = _cursor;
	int input = getch();
	if(input == KEY_UP) --_cursor;
	else if(input == KEY_DOWN) ++_cursor;
	else return (false);
	if (_cursor >= _items.size()) _cursor = 0;
	else if (_cursor < 0) _cursor = _items.size() - 1;
	_items[prevCursor]->toggleHover();
	_items[_cursor]->toggleHover();
	return (true);
}

void Menu::render()
{
	Terminal::get().clearScreen();
	for (size_t i = 0; i < _entities.size(); i++)
	{
		_entities[i]->render();
	}
}

bool Menu::run()
{
	bool quit = false;
	while (!quit)
	{
		active->render();
		while (!active->update());
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

void Menu::goTo(std::string path, std::string id)
{
	active = std::make_shared<Menu>(Menu(path, id));
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