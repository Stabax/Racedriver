#include "GameEngine.hpp"

GameEngine::GameEngine()
{
  std::cout << "Initializing Game, please wait...\n";
  _gameState = SMenu;
  _menuIndex = 0;
}

GameEngine::~GameEngine()
{

}

bool GameEngine::updateGame()
{
  return (true);
}

bool GameEngine::updateMenu()
{
  _menus[_menuIndex]->update();
  return (true);
}

bool GameEngine::update()
{
  switch (_gameState)
    {
    case SMenu:
      if (updateMenu() == false)
	return (false);
      break;
    case SGame:
      if (updateGame() == false)
	return (false);
      break;
    }
  return (true);
}

void GameEngine::drawGame()
{

}

void GameEngine::drawMenu()
{
  _menus[_menuIndex]->draw();
}

void GameEngine::draw()
{
  switch (_gameState)
    {
    case SMenu:
      drawMenu();
      break;
    case SGame:
      drawGame();
      break;
    }
}

