#include "Menu.hh"
#include "Game.hh"
#include "Collection.hpp"
#include "ScriptEngine.hh"
#include <fstream>
#include "sha/sha.h"

//Menu

std::shared_ptr<Menu> Menu::active = nullptr;
std::shared_ptr<MenuFile> Menu::activeDoc = nullptr;

Menu::Menu(const std::string &id)
 : _cursor(0)
{
	xml_node menu;

	for (pugi::xml_node el = activeDoc->getData().first_child(); el; el = el.next_sibling())
	{
		if (strcmp(el.name(), "Menu") == 0 && el.attribute("Id").value() == id) menu = el;
	}
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
}

void Menu::setActiveDocument(const std::string &path)
{
	activeDoc = std::make_shared<MenuFile>(path);
	if (!activeDoc->load()) throw(std::runtime_error("Error on loading Menu XML"));
	ScriptEngine::loadScripts(activeDoc->getData());
	MenuDialog::load(activeDoc->getData());
}

bool Menu::update()
{
	int input = getch();
	Terminal::get().clearScreen();
	if(input == KEY_UP) updateCursor(false);
	else if(input == KEY_DOWN) updateCursor(true);
	else if(input == KEY_ENTER || input == '\n' || input == '\r') _items[_cursor]->select();
	else return (false);
	return (true);
}

void Menu::updateCursor(bool add)
{
	int prevCursor = _cursor;

	_cursor += (add ? 1 : -1) * 1;
	if (_cursor >= _items.size()) _cursor = 0;
	else if (_cursor < 0) _cursor = _items.size() - 1;
	_items[prevCursor]->toggleHover();
	_items[_cursor]->toggleHover();
}

void Menu::render()
{
	for (size_t i = 0; i < _entities.size(); i++)
	{
		_entities[i]->render();
		Terminal::get() << "\n";
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

void Menu::goTo(std::string id, std::string path)
{
	if (path != "") setActiveDocument(path);
	active = std::make_shared<Menu>(Menu(id));
}

std::shared_ptr<MenuItem> Menu::getItem(const std::string &id)
{
	auto obj = std::find_if(_entities.begin(), _entities.end(),
    			[=] (std::shared_ptr<MenuItem> m) { return (m->getId() == id); });
	if (obj == _entities.end()) throw (std::runtime_error("Specified item does not exist"));
	return *(obj);
}

//MenuDialog

std::map<std::string, MenuDialog> MenuDialog::dialogs = std::map<std::string, MenuDialog>();

MenuDialog::MenuDialog(xml_node &data)
 : _data(data.first_child().value())
{

}

void MenuDialog::load(const xml_document &doc)
{
	for (pugi::xml_node el = doc.first_child(); el; el = el.next_sibling())
	{
		if (strcmp(el.name(), "Dialog") == 0)
		{
			dialogs.emplace(el.attribute("Id").value(), MenuDialog(el));
		}
	}
}

void MenuDialog::open()
{
	_win = Terminal::get().addChildWindow(Point(), Point(50, 50));
}

void MenuDialog::render()
{

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
