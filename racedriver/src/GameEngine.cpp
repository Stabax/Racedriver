#include "GameEngine.hpp"

GameEngine::GameEngine()
{
  extern sf::Vector2i	g_winsize;

  std::cout << "Initializing Game, please wait...\n";
  g_winsize.x = 1024;
  g_winsize.y = 768;
  _win.setPosition(sf::Vector2i(10, 10));
  _win.create(sf::VideoMode(g_winsize.x, g_winsize.y), "RaceDriver");
  _win.setKeyRepeatEnabled(false);
  _win.setFramerateLimit(90);
  _gameState = SMenu;
  initialize();
}

GameEngine::~GameEngine()
{

}

bool GameEngine::initialize()
{
  if (!_ambiant.openFromFile("daisuke.ogg"))
    return (false);
  _menuIndex = 0;
  std::vector<std::string> items = {"Play", "Options", "Quit"};
  _menus.push_back(new Menu("Main Menu", items, "font"));
  _ambiant.play();
  return (true);
}

bool GameEngine::updateGame()
{
  return (true);
}

bool GameEngine::updateMenu(sf::Event event)
{
  _menus[_menuIndex]->update(event);
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

