#ifndef MENU_HH_
#define MENU_HH_

#include <string>

class Menu
{
public:
  Menu();

  static void msg(std::string str);
  static void error(std::string str);
  
  static bool askConfirmation();
  static int askChoice();

private:

};

std::string getHashFromFile(std::string path);
std::string getString();

#endif /* !MENU_HH_ */