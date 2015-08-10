#ifndef SETTINGSMENU_HH_
#define SETTINGSMENU_HH_

#include <Menus/OptionsMenu.hh>

class SettingsMenu : public OptionsMenu
{
public:
  SettingsMenu();
  ~SettingsMenu();

  int update(sf::Event event);
  void draw(sf::RenderWindow &win);

private:

};

#endif
