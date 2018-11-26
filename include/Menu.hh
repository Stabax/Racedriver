#ifndef MENU_HH_
#define MENU_HH_

#include <string>
#include <map>
#include <pugixml.hpp>

class Menu
{
public:
  Menu();

  static void msg(std::string str);
  static void error(std::string str);

  static bool askConfirmation();
  static int askChoice();

private:
  std::map<std::string, MenuModule> _modules;
};

class MenuModule
{
public:
  MenuModule();
  AddMethod(std::string name, void *instance);

private:
  std::map<std::string, void *> _methods;
};

std::string getHashFromFile(std::string path);
std::string getString();

#endif /* !MENU_HH_ */