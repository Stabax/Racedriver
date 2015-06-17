#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
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

  bool initialize();

  bool updateGame();
  bool updateMenu(sf::Event event);
  bool update();
  void drawGame();
  void drawMenu();
  void draw();

 private:
  sf::RenderWindow	_win;
  sf::Music		_ambiant;
  short int		_menuIndex;
  std::vector<Menu *>	_menus;
  GameState		_gameState;

};

#endif
