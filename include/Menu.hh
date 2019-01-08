#ifndef MENU_HH_
#define MENU_HH_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "DataFile.hh"
#include "MenuItem.hh"

/*!
 * @brief Base/Generic class for Menu
 */
class Menu
{
public:
  //Generic
  static void msg(std::string str);
  static void error(std::string str);

  static bool askConfirmation();
  static int askChoice();

  static void setActiveDocument(const std::string &path);
  static void goTo(std::string id, std::string path = "");
  static bool run();

  static std::shared_ptr<Menu> active;
  static std::shared_ptr<MenuFile> activeDoc;

  //Instance
  Menu(const std::string &id);

  void updateCursor(bool add);
  bool update();
  void render();

private:
  std::vector<std::shared_ptr<MenuItem>> _entities;
  std::vector<std::shared_ptr<MenuItem>> _items;
  int _cursor;
};

std::string getHashFromFile(std::string path);
std::string getString();

#endif /* !MENU_HH_ */