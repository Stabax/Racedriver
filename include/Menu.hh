#ifndef MENU_HH_
#define MENU_HH_

#include <string>
#include <map>

class Menu
{
public:
  Menu();

  template <typename T>
  void catalog(const std::map<std::string, T> &collection);

  static void msg(std::string str);
  static void error(std::string str);
  
  static bool askConfirmation();
  static int askChoice();

private:

};

std::string getHashFromFile(std::string path);
std::string getString();

#endif /* !MENU_HH_ */