#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <MusicBox.hh>
#include <Menus/MainMenu.hh>
#include <Menus/ProfileMenu.hh>
#include <Menus/SettingsMenu.hh>

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
  void createWindow(bool fullscreen);
  MusicBox &getMusicBox();

  bool updateGame();
  bool updateMenu(sf::Event event);
  bool update();
  void drawGame();
  void drawMenu();
  void draw();

 private:
  sf::RenderWindow	_win;
  MusicBox		_ambiant;
  short int		_menuIndex, _prevIndex;
  std::vector<Menu *>	_menus;
  GameState		_gameState;

};

#endif
