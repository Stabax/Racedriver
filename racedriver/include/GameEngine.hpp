#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <Menu.hh>

enum GameState {
  SMenu,
  SGame
};

class GameEngine
{
 public:
  GameEngine();
  ~GameEngine();

  bool updateGame();
  bool updateMenu();
  bool update();
  void drawGame();
  void drawMenu();
  void draw();

 private:
  short int		_menuIndex;
  std::vector<Menu *>	_menus;
  GameState		_gameState;

};

#endif
