#include "GameEngine.hpp"

GameEngine::GameEngine()
{
  extern sf::Vector2i	g_winsize;

  g_winsize.x = 1024;
  g_winsize.y = 768;
  _win.setPosition(sf::Vector2i(10, 10));
  _win.create(sf::VideoMode(g_winsize.x, g_winsize.y), "RaceDriver");
  _win.setKeyRepeatEnabled(false);
  _win.setFramerateLimit(90);
  _gameState = SMenu;
}

GameEngine::~GameEngine()
{

}

bool GameEngine::initialize()
{
  std::cout << "Initializing Game, please wait...\n";
  if (!_ambiant.openFromFile("Data/music/daisuke.ogg"))
    return (false);
  _prevIndex = 0;
  _menuIndex = 0;
  std::vector<std::pair<std::string, int (MenuHandle::*)()>> items = {std::make_pair("Play", &MenuHandle::back),
								      std::make_pair("Options", &MenuHandle::back),
								      std::make_pair("Quit", &MenuHandle::quit)};
  _menus.push_back(new Menu("Main Menu", items, "truckdriver", "carbon"));
  _ambiant.play();
  return (true);
}

bool GameEngine::updateGame()
{
  return (true);
}

bool GameEngine::updateMenu(sf::Event event)
{
  int	status;

  status = _menus[_menuIndex]->update(event, &_handle);
  if (status == -2)
    return (false);
  else if (status == -1)
    _menuIndex = _prevIndex;
  else if (status > 100)
    {
      _prevIndex = _menuIndex;
      _menuIndex = static_cast<short int>(status % 100);
    }
  return (true);
}

bool GameEngine::update()
{
  sf::Event	event;

  while (_win.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	{
	  _win.close();
	  return (false);
	}
      switch (_gameState)
	{
	case SMenu:
	  if (updateMenu(event) == false)
	    return (false);
	  break;
	case SGame:
	  if (updateGame() == false)
	    return (false);
	  break;
	}
    }
  return (true);
}

void GameEngine::drawGame()
{

}

void GameEngine::drawMenu()
{
  _menus[_menuIndex]->draw(_win);
}

void GameEngine::draw()
{
  _win.clear();
  switch (_gameState)
    {
    case SMenu:
      drawMenu();
      break;
    case SGame:
      drawGame();
      break;
    }
  _win.display();
}

