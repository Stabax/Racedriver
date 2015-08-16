#ifndef SETTINGSMENU_HH_
#define SETTINGSMENU_HH_

#include <Menus/OptionsMenu.hh>
#include <GameEngine.hpp>

class GameEngine; //Forward declaration cross-includes

class SettingsMenu : public OptionsMenu
{
public:
  SettingsMenu();
  ~SettingsMenu();

  void setResolution(GameEngine &game);
  void fullscreenToggle(GameEngine &game);
  void musicToggle(GameEngine &game);

  int update(sf::Event event);
  int update(sf::Event event, GameEngine &game);
  void draw(sf::RenderWindow &win);

private:

};

#endif
