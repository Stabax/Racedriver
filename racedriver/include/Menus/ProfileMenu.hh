#ifndef PROFILEMENU_HH_
#define PROFILEMENU_HH_

#include <dirent.h>
#include <Menus/Menu.hh>
#ifndef WIN32
    #include <sys/types.h>
#endif

class ProfileMenu : public Menu
{
public:
  ProfileMenu();
  ~ProfileMenu();

  int update(sf::Event event);
  void draw(sf::RenderWindow &win);

private:

};

#endif
