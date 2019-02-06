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
 : _id(id), _lastInput(0), _title(None), _cursor(0), _clickCallback(nullptr)
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
			if (obj == nullptr) continue; //Discard if non-object entity is parsed
			_entities.push_back(obj);
			if (obj->isSelectable()) _items.push_back(obj);
		} catch(std::exception &e) {
			Menu::error(e.what());
		}
	}
	if (menu.attribute("Title")) _title = Menu::convertASCIILogo(menu.attribute("Title").value());
	if (menu.attribute("OnLoad")) _onLoadScript = menu.attribute("OnLoad").value();
	if (_items.size() > 0) _items[_cursor]->toggleHover();
}

void Menu::onLoad()
{
	if (!_onLoadScript.empty()) ScriptEngine::runScript(_onLoadScript);
}

void Menu::setActiveDocument(const std::string &source, const DataSource sourceMode)
{
	setActiveDocument(std::make_shared<MenuFile>(source, sourceMode));
}

void Menu::setActiveDocument(std::shared_ptr<MenuFile> doc)
{
	activeDoc = doc;
	if (!activeDoc->load()) throw(std::runtime_error("Error on loading Menu XML"));
	ScriptEngine::loadScripts(activeDoc->getData());
	MenuDialog::load(activeDoc->getData());
}

void Menu::setClickCallback(std::function<void()> callback)
{
	_clickCallback = std::make_shared<std::function<void()>>(callback);
}

bool Menu::update()
{
	_lastInput = getch();
	if(_lastInput == KEY_UP) updateCursor(false);
	else if(_lastInput == KEY_DOWN) updateCursor(true);
	else if(_lastInput == KEY_ENTER || _lastInput == '\n' || _lastInput == '\r') _items[_cursor]->select();
	else if (_lastInput == KEY_F(11)) ScriptEngine::console(*this);
	else return (false);
	return (true);
}

int Menu::getCursor()
{
	return (_cursor);
}

void Menu::updateCursor(bool add)
{
	int prevCursor = _cursor;

	_cursor += (add ? 1 : -1);
	if (_cursor >= static_cast<int>(_items.size())) _cursor = 0;
	else if (_cursor < 0) _cursor = _items.size() - 1;
	_items[prevCursor]->toggleHover();
	_items[_cursor]->toggleHover();
}

void Menu::render()
{
	Terminal &term = Terminal::windows.at("main");

	term.clearScreen();
	for (size_t i = 0; i <_alerts.size(); i++) _alerts[i]->render();
	if (_title != 0)
	{
		printASCIILogo(_title);
		term << "\n";
	}
	for (size_t i = 0; i < _entities.size(); i++)
	{
		_entities[i]->render();
		term << "\n";
	}
}

bool Menu::run()
{
	bool quit = false;
	while (!quit)
	{
		active->render();
		while (!active->update())
		{
			if (active->_clickCallback != nullptr)
			{
				(*active->_clickCallback)();
			}
		}
	}
	return (true);
}

void Menu::renderConsole(std::string command)
{
	Terminal &term = Terminal::windows.at("main");
	term.clearScreen();
	for (size_t i = 0; i <_alerts.size(); i++) _alerts[i]->render();
  term << "> " << command;
}

void Menu::alert(std::string str)
{
	if (Menu::active != nullptr)
	{
		std::string itemXML = "<Alert>" + str + "</Alert>";
		MenuFile menu(itemXML, DataSource::Document);
		if (!menu.load()) throw(std::runtime_error("Error on loading Alert XML"));
		Menu::active->addAlert(MenuItem::create(menu.getData().first_child()));
	}
	else msg(str);
}

Menu::ASCIILogo Menu::convertASCIILogo(std::string art)
{
	if (art == "Game") return (Game);
	else if (art == "Options") return (Options);
	else if (art == "Garage") return (Garage);
	else if (art == "Stats") return (Stats);
	else if (art == "Car") return (Car);
	else return (None);
}

void Menu::printASCIILogo(ASCIILogo art)
{
	Terminal &term = Terminal::windows.at("main");
	switch (art)
	{
	case Game:
		term << setColor(Terminal::Color::RedOnBlack)
				 << " ________                  ________       _____                    \n"
				 << " ___  __ \\_____ ______________  __ \\_________(_)__   ______________\n"
				 << " __  /_/ /  __ `/  ___/  _ \\_  / / /_  ___/_  /__ | / /  _ \\_  ___/\n"
				 << " _  _, _// /_/ // /__ /  __/  /_/ /_  /   _  / __ |/ //  __/  /    \n"
				 << " /_/ |_| \\__,_/ \\___/ \\___//_____/ /_/    /_/  _____/ \\___//_/     \n"
				 << resetAttrs;
		break;
	case Options:
		term << setColor(Terminal::Color::RedOnBlack)
				 << "_______          _____ _____                        \n"
				 << "__  __ \\________ __  /____(_)______ _______ ________\n"
				 << "_  / / /___  __ \\_  __/__  / _  __ \\__  __ \\__  ___/\n"
				 << "/ /_/ / __  /_/ // /_  _  /  / /_/ /_  / / /_(__  ) \n"
				 << "\\____/  _  .___/ \\__/  /_/   \\____/ /_/ /_/ /____/  \n"
				 << "        /_/                                         \n"
				 << resetAttrs;
		break;
	case Garage:
		term << setColor(Terminal::Color::RedOnBlack)
				 << "_________                                       \n"
				 << "__  ____/______ _______________ ________ ______ \n"
				 << "_  / __  _  __ `/__  ___/_  __ `/__  __ `/_  _ \\\n"
				 << "/ /_/ /  / /_/ / _  /    / /_/ / _  /_/ / /  __/\n"
				 << "\\____/   \\__,_/  /_/     \\__,_/  _\\__, /  \\___/ \n"
				 << "                                 /____/         \n"
				 << resetAttrs;
		break;
	case Stats:
		term << setColor(Terminal::Color::RedOnBlack)
				 << "_____________         _____         \n"
				 << "__  ___/__  /_______ ___  /_________\n"
				 << "_____ \\ _  __/_  __ `/_  __/__  ___/\n"
				 << "____/ / / /_  / /_/ / / /_  _(__  ) \n"
				 << "/____/  \\__/  \\__,_/  \\__/  /____/  \n"
				 << resetAttrs;
		break;
	case Car:
	Terminal::get() << setColor(Terminal::Color::RedOnBlack)
									<< "		                      ___..............._\n"
									<< "             __.. ' _'.\"\"\"\"\"\"\\\\\"\"\"\"\"\"\"\"- .`-._\n"
									<< " ______.-'         (_) |      \\\\           ` \\\\`-. _\n"
									<< "/_       --------------'-------\\\\---....______\\\\__`.`  -..___\n"
									<< "| T      _.----._           Xxx|x...           |          _.._`--. _\n"
									<< "| |    .' ..--.. `.         XXX|XXXXXXXXXxx==  |       .'.---..`.     -._\n"
									<< "\\_j   /  /  __  \\  \\        XXX|XXXXXXXXXXX==  |      / /  __  \\ \\        `-.\n"
									<< " _|  |  |  /  \\  |  |       XXX|\"\"'            |     / |  /  \\  | |          |\n"
									<< "|__\\_j  |  \\__/  |  L__________|_______________|_____j |  \\__/  | L__________J\n"
									<< "     `'\\ \\      / ./__________________________________\\ \\      / /___________\\\n"
									<< "        `.`----'.'                                     `.`----'.'\n"
									<< "          `\"\"\"\"'                                         `\"\"\"\"'\n"
									<< resetAttrs();
		break;
	case None:
	default:
		break;
	}
}

void Menu::error(std::string str)
{
	Menu::msg("ERREUR: "+str);
}

void Menu::msg(std::string str)
{
	Terminal &term = Terminal::windows.at("main");
	term << setColor(Terminal::Color::BlackOnRed)
			 << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
			 << ":: " << str << "\n"
			 << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n"
			 << resetAttrs;
}

bool Menu::askConfirmation()
{
	Terminal &term = Terminal::windows.at("main");
  char input;
  term << "=====================\n"
			 << "Etes-vous sur ? [O/n]\n"
			 << "=====================\n";
  input = getch();
  if (input == 'o' || input == 'O') return (true);
  return (false);
}

int Menu::askChoice()
{
	Terminal &term = Terminal::windows.at("main");
  char input;
  term << "=====================\n"
			 << "Choix ? ";
  input = getch();
  return (atoi(&input));
}

void Menu::addAlert(std::shared_ptr<MenuItem> menuItem)
{
	_alerts.push_back(menuItem);
	if (_alerts.size() > 4) _alerts.pop_front();
}

void Menu::goTo(std::string id, std::string source, const DataSource dataMode)
{
	if (source != "") setActiveDocument(source, dataMode);
	active = std::make_shared<Menu>(Menu(id));
	active->onLoad();
}

void Menu::popUp(std::string id, std::string source, const DataSource dataMode)
{
	std::shared_ptr<MenuFile> prevDoc = activeDoc;
	std::string prevId = active->_id;
	goTo(id, source, dataMode);
	while (1)
	{
		active->render();
		active->update();
		if(active->_lastInput == KEY_ENTER || active->_lastInput == '\n' || active->_lastInput == '\r') break;
	};
	if (active->_clickCallback != nullptr)
	{
		(*active->_clickCallback)();
	}
	setActiveDocument(prevDoc);
	goTo(prevId);
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
	//_win = Terminal::get().addChildWindow(Point(), Point(50, 50));
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
