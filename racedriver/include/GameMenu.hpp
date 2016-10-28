#ifndef GAMEMENU_HPP_
#define GAMEMENU_HPP_

#include "engine/Menu.hpp"

class GameMenu : public Menu
{
public:
  GameMenu();
  ~GameMenu();

  void update();
  void draw();
private:
  
};

#endif /* !GAMEMENU_HPP_ */
