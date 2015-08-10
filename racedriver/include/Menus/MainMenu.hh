#ifndef MAINMENU_HH_
#define MAINMENU_HH_

#include <Menus/Menu.hh>

class MainMenu : public Menu
{
public:
  MainMenu();
  ~MainMenu();

  int update(sf::Event event);
  void draw(sf::RenderWindow &win);

private:

};

#endif
