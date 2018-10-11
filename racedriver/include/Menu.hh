#ifndef MENU_HH_
#define MENU_HH_

#include <string>

class Menu
{
public:
  Menu();

  static void msg(std::string str);
  static void error(std::string str);

private:

};

#endif /* !MENU_HH_ */