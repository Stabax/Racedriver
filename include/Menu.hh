#ifndef MENU_HH_
#define MENU_HH_

#include <string>
#include <map>
#include <memory>
#include <functional>
#include <pugixml.hpp>

#define INVOKE_SEPARATOR  "::"

struct MenuModule
{
  MenuModule(const std::string &id);
  virtual void registerMethods() = 0;

  std::map<std::string, std::function<void()>> methods;
};

class Menu
{
public:
  Menu();

  static void msg(std::string str);
  static void error(std::string str);

  static bool askConfirmation();
  static int askChoice();

  static bool invokeMethod(const std::string &methodId);

  static std::map<std::string, std::shared_ptr<MenuModule>> modules;
};

std::string getHashFromFile(std::string path);
std::string getString();

#endif /* !MENU_HH_ */